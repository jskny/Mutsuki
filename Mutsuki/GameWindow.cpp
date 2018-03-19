/*
 *	�Q�[���ɕs�v�ȗ]�v�ȏ������B������B
 *	2011 / 07 / 28
 *	jskny
*/


// �R�}���h���C���������B
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
		// �Ȃɂ����Ȃ��B
	}

	WindowClose();

	return (0);
}


//---------------------------------------------------------


static	bool		s_flagLoopEnd = false; // ���ꂪ true �Ȃ�I���B
static	long long int	s_windowLoopCounter = 0; // �E�C���h�E���[�v�̊ԃC���N�������g���ꑱ����ϐ��B
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


// �w�肵���t���[����
// Update ���ĂԂ̂��X�L�b�v����B
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


// �t���[���J�E���g�̎擾
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
	// window ���[�h�̐ݒ� TRUE �ʏ�A FALSE �t���X�N���[��
	ChangeWindowMode(TRUE);
	SetMainWindowText("GameLib");

	if (SetGraphMode(800, 600, 16) != DX_CHANGESCREEN_OK) {
		// �E�C���h�E�T�C�Y�̕ύX�Ɏ��s����
		return (false);
	}


	// �E�C���h�E�A�C�R��
	SetWindowIconID(1012);

	// �E�C���h�E�T�C�Y��ύX�\�ɂ��邩�ۂ� �ύX�\ TRUE �s�\ FALSE
	SetWindowSizeChangeEnableFlag(FALSE);
	// �v���O�����̓�d�N���������邩�ۂ� ���� TRUE �񋖉� FALSE
	SetDoubleStartValidFlag(FALSE);

	// ��A�N�e�B�u���ɏ����𑱂��邩�ۂ� (������ TRUE)
	SetAlwaysRunFlag(FALSE);
	// ���������M����҂��҂��Ȃ��� (�҂� TRUE)
	SetWaitVSyncFlag(FALSE); // wait_fps �̎ז�������̂Ŗ�������B
	// ���O��\�����邩�ۂ� �\�� TRUE ��\�� FALSE
	SetOutApplicationLogValidFlag(TRUE);

	// DxLib ���ċN���\�ɂ���B
	SetDxLibEndPostQuitMessageFlag(FALSE);

	// DirectDraw���}���`�X���b�h�����邩
	// TRUE �}���`
	SetMultiThreadFlag(TRUE);

	// �E�C���h�E�̃X�^�C��
	// 0 �ʏ�
	// 1 �^�C�g���o�[�� �g����
	// 2 �^�C�g���o�[�� �g�Ȃ�
	SetWindowStyleMode(0);

	// �`��Ώۂ̎w��
	SetDrawScreen(DX_SCREEN_BACK);
	// ���x��ݒ�
	SetDrawBright(255, 255, 255);
	// ���ߐF��ݒ�
	SetTransColor(0, 0, 0);


	// Z �o�b�t�@��L����
	SetUseZBuffer3D(TRUE);
	// Z �o�b�t�@�Ƀf�[�^���������ށB
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
				// ��ʑJ�ڂ�����
				// �̂̉�ʂ�������V������ʂֈڂ�B
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

		// �Ȃ��A���̃R�[�h��������Ă���̂��A
		// ����́A
		// �����A�J�E���^�[�֘A�̃o�O���������Ƃ��āA
		// ���̃G���[����������̂́A
		// unsigned long int �̍ő�l�A
		// ��l���t���[����B
		// �Ƃ�[���Ƃ��Ȃ��悤�ɂ��邽�߁B
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

