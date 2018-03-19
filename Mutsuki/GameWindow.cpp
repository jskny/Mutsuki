/*
 *	ゲームに不要な余計な処理を隠蔽する。
 *	2011 / 07 / 28
 *	jskny
*/


// コマンドラインを消す。
#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")


#include	<DxLib.h>
#include	<assert.h>


#include	"GameWindow.h"


//---------------------------------------------------------


int main(int argc, char* argv[])
{
	if (!WindowCreate()) {
		return (1);
	}

	while (WindowLoop()) {
		// なにもしない。
	}

	WindowClose();

	return (0);
}


//---------------------------------------------------------


static	bool		s_flagLoopEnd = false; // これが true なら終了。
static	long long int	s_windowLoopCounter = 0; // ウインドウループの間インクリメントされ続ける変数。
static	long int	s_windowLoopWaitCounter = 0;

static	BaseSequence*	s_sequenceCurrent = NULL;


BaseSequence::~BaseSequence()
{
}


BaseSequence* BaseSequence::update(void)
{
	return (this);
}


void BaseSequence::init(void)
{
}


// 指定したフレーム分
// Update を呼ぶのをスキップする。
void WindowWait(int count)
{
	if (count <= 0) {
		return;
	}

	if (s_windowLoopWaitCounter > 0) {
		assert("why ? crash of library memory.");
	}

	s_windowLoopWaitCounter = count;

}


// フレームカウントの取得
long long int WindowLoopCounter(void)
{
	return (s_windowLoopCounter);
}


void GameSystemSetStartupSequence(BaseSequence* s)
{
	if (s == NULL) {
		assert("StartupSequence is incorrect.");
		return;
	}

	s_sequenceCurrent = s;
	s_sequenceCurrent->init();
}


bool WindowCreate(void)
{
	// window モードの設定 TRUE 通常、 FALSE フルスクリーン
	ChangeWindowMode(TRUE);
	SetMainWindowText("GameLib");

	if (SetGraphMode(800, 600, 16) != DX_CHANGESCREEN_OK) {
		// ウインドウサイズの変更に失敗した
		return (false);
	}


	// ウインドウアイコン
	SetWindowIconID(1012);

	// ウインドウサイズを変更可能にするか否か 変更可能 TRUE 不可能 FALSE
	SetWindowSizeChangeEnableFlag(FALSE);
	// プログラムの二重起動を許可するか否か 許可 TRUE 非許可 FALSE
	SetDoubleStartValidFlag(FALSE);

	// 非アクティブ時に処理を続けるか否か (続ける TRUE)
	SetAlwaysRunFlag(FALSE);
	// 垂直同期信号を待つか待たないか (待つ TRUE)
	SetWaitVSyncFlag(FALSE); // wait_fps の邪魔をするので無視する。
	// ログを表示するか否か 表示 TRUE 非表示 FALSE
	SetOutApplicationLogValidFlag(TRUE);

	// DxLib を再起動可能にする。
	SetDxLibEndPostQuitMessageFlag(FALSE);

	// DirectDrawをマルチスレッド化するか
	// TRUE マルチ
	SetMultiThreadFlag(TRUE);

	// ウインドウのスタイル
	// 0 通常
	// 1 タイトルバー無 枠あり
	// 2 タイトルバー無 枠なし
	SetWindowStyleMode(0);

	// 描画対象の指定
	SetDrawScreen(DX_SCREEN_BACK);
	// 光度を設定
	SetDrawBright(255, 255, 255);
	// 透過色を設定
	SetTransColor(0, 0, 0);


	// Z バッファを有効化
	SetUseZBuffer3D(TRUE);
	// Z バッファにデータを書き込む。
	SetWriteZBuffer3D(TRUE);


	if (DxLib_Init() == -1) {
		return (false);
	}

	s_flagLoopEnd = false;
	s_windowLoopCounter = 0;

	GameSystemStartup();
	return (true);
}

void WindowClose(void)
{
	delete (s_sequenceCurrent);
	s_sequenceCurrent = NULL;


	GameSystemDestroy();
	DxLib_End();
}

void WindowLoopBreak(void)
{
	s_flagLoopEnd = true;
}

bool WindowLoop(void)
{
	if (	ProcessMessage() == 0 &&
		CheckHitKey(KEY_INPUT_ESCAPE) == 0 &&
		!s_flagLoopEnd)
	{
		if (s_windowLoopWaitCounter == 0) {
			ClsDrawScreen();
			auto next = s_sequenceCurrent->update();
			if (next != s_sequenceCurrent) {
				// 画面遷移が発生
				// 昔の画面を解放し新しい画面へ移る。
				delete (s_sequenceCurrent);
				s_sequenceCurrent = next;
				s_sequenceCurrent->init();
			}

			ScreenFlip();
			Sleep(10);
		}
		else {
			Sleep(17);
		}

		// なぜ、このコードが書かれているのか、
		// それは、
		// もし、カウンター関連のバグがあったとして、
		// そのエラーが発生するのは、
		// unsigned long int の最大値、
		// 約四億フレーム後。
		// とゆーことがないようにするため。
		if (s_windowLoopCounter > 100) {
			s_windowLoopCounter = 0;
		}

		s_windowLoopCounter++;
		if (s_windowLoopWaitCounter > 0) {
			s_windowLoopWaitCounter--;
		}
	}
	else {
		return (false);
	}

	return (true);
}

