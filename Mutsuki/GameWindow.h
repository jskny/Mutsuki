/*
 *	ゲームに不要な余計な処理を隠蔽する。
 *	2011 / 07 / 28
 *	jskny
*/


// 追記
// 2018/03/18
// 画面遷移システムを追加した。


#pragma once


class BaseSequence;


//-------------------------------------
// user
//-------------------------------------

// システム起動時に一度だけ呼び出されます。
// この関数内で、最初の画面を設定したりします。
extern	void		GameSystemStartup();
extern	void		GameSystemDestroy();
extern	void		GameSystemSetStartupSequence(BaseSequence* s);



//-------------------------------------
// DxLib を直接制御する時に使う。
//-------------------------------------

// library
extern	bool		WindowCreate(void);
extern	void		WindowClose(void);
extern	bool		WindowLoop(void);

// ウィンドウループから抜ける。
extern	void		WindowLoopBreak(void);

// 指定したフレーム分
// Update を呼ぶのをスキップする。
extern	void		WindowWait(int count);

// フレームカウントの取得
extern	long long int	WindowLoopCounter(void);


//-------------------------------------
// 画面遷移管理
//-------------------------------------


// 基本となる画面
// これを継承して各種画面を作成する。
class BaseSequence
{
public:
	virtual		~BaseSequence() = 0;
	virtual		BaseSequence* update(void) = 0;
	virtual	void	init(void) = 0; // シーケンス起動時に呼ばれる。
	virtual void	destroy(void) = 0;

};

