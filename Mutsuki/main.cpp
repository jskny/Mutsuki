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
	void	destroy(void);
	BaseSequence*	update();

private:
	int	m_handleFontTitle;


};


void GTitle::init()
{
	this->m_handleFontTitle = CreateFontToHandle("���C���I", 24, 2, DX_FONTTYPE_NORMAL);
}


void GTitle::destroy(void)
{
	DeleteFontToHandle(this->m_handleFontTitle);
}


BaseSequence* GTitle::update()
{
	auto ret = this;


	DrawStringToHandle(0, 0, "Hello World !", GetColor(0xFF, 0, 0), this->m_handleFontTitle);


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

