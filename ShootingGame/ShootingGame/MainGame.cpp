#include "Stdafx.h"
#include "MainGame.h"
#include "ResourcesClass.h"
HRESULT MainGame::init(void)
{
	GameNode::init(true);
	_assignment = new SG_MainGame;
	_assignment->init();
	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();
	_assignment->release();
	SAFE_DELETE(_assignment);
}

void MainGame::update(void)
{
	GameNode::update();
	_assignment->update();
}

void MainGame::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
	_assignment->render();
	this->getBackBuffer()->render(getHDC());
}