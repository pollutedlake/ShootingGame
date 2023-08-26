#include "Stdafx.h"
#include "MainGame.h"
HRESULT MainGame::init(void)
{
	GameNode::init(true);
	SCENEMANAGER->init();
	SCENEMANAGER->changeScene("Battle");
	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();
}

void MainGame::update(void)
{
	GameNode::update();
	SCENEMANAGER->update();
}

void MainGame::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
	SCENEMANAGER->render();
	TIMEMANAGER->render(getMemDC());
	this->getBackBuffer()->render(getHDC());
}