/*
 *	�Q�[���ɕs�v�ȗ]�v�ȏ������B������B
 *	2011 / 07 / 28
 *	jskny
*/


// �ǋL
// 2018/03/18
// ��ʑJ�ڃV�X�e����ǉ������B


#pragma once


class BaseSequence;


//-------------------------------------
// user
//-------------------------------------

// �V�X�e���N�����Ɉ�x�����Ăяo����܂��B
// ���̊֐����ŁA�ŏ��̉�ʂ�ݒ肵���肵�܂��B
extern	void		GameSystemStartup();
extern	void		GameSystemDestroy();
extern	void		GameSystemSetStartupSequence(BaseSequence* s);



//-------------------------------------
// DxLib �𒼐ڐ��䂷�鎞�Ɏg���B
//-------------------------------------

// library
extern	bool		WindowCreate(void);
extern	void		WindowClose(void);
extern	bool		WindowLoop(void);

// �E�B���h�E���[�v���甲����B
extern	void		WindowLoopBreak(void);

// �w�肵���t���[����
// Update ���ĂԂ̂��X�L�b�v����B
extern	void		WindowWait(int count);

// �t���[���J�E���g�̎擾
extern	long long int	WindowLoopCounter(void);


//-------------------------------------
// ��ʑJ�ڊǗ�
//-------------------------------------


// ��{�ƂȂ���
// ������p�����Ċe���ʂ��쐬����B
class BaseSequence
{
public:
	virtual		~BaseSequence() = 0;
	virtual		BaseSequence* update(void) = 0;
	virtual	void	init(void) = 0; // �V�[�P���X�N�����ɌĂ΂��B
	virtual void	destroy(void) = 0;

};

