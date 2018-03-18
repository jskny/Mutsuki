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
	// メモリ解放処理は、ライブラリが行う。
	GameSystemSetStartupSequence(p);

	return;
}


void GameSystemDestroy()
{
}

