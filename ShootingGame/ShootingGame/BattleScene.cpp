#include "stdafx.h"
#include "BattleScene.h"

HRESULT BattleScene::init(void)
{
	_bgImg = IMAGEMANAGER->addImage("BattleBG", "Resources/Images/BattleBG.bmp", 448, 3680);
	_bgSpeed = 0.2f;
	_y = 0.0f;

	_player = new Player;
	_player->init();

	return S_OK;
}

void BattleScene::release(void)
{
	TIMEMANAGER->update();
}

void BattleScene::update(void)
{
	_y -= _bgSpeed;
	_player->update();
}

void BattleScene::render(void)
{
	_bgImg->render(getMemDC(), 0, 0, 0, _bgImg->getHeight() - WINSIZE_Y + _y, WINSIZE_X, WINSIZE_Y);
	_player->render();
}
