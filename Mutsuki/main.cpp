/*
 *	Mutsuki 睦月
 *	久しぶりにゲームでも作る？
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
	this->m_handleFontTitle = CreateFontToHandle("メイリオ", 24, 2, DX_FONTTYPE_NORMAL);
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
	// メモリ解放処理は、ライブラリが行う。
	GameSystemSetStartupSequence(p);

	return;
}


void GameSystemDestroy()
{
}

