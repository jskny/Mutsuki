/*
 *	Mutsuki �r��
 *	�v���Ԃ�ɃQ�[���ł����H
 *	2018/03/18
 *	jskny
*/


#include	<DxLib.h>

#include	"GameWindow.h"


class GTitle : public BaseSequence
{
public:
	void	init();
	BaseSequence*	update();

};


void GTitle::init()
{
}


BaseSequence* GTitle::update()
{
	auto ret = this;

	printfDx("Hello World !\n");

	return (ret);
}


void GameSystemStartup()
{
	auto p = new GTitle();
	// ��������������́A���C�u�������s���B
	GameSystemSetStartupSequence(p);

	return;
}


void GameSystemDestroy()
{
}

