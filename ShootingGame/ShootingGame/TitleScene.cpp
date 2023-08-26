#include "stdafx.h"
#include "TitleScene.h"

HRESULT TitleScene::init(void)
{
	_bgImg = IMAGEMANAGER->addImage("TitleBG", "Resources/Images/TitleBG.bmp", 224, 1840);
	return S_OK;
}

void TitleScene::release(void)
{
	
}

void TitleScene::update(void)
{
	
}

void TitleScene::render(void)
{
	_bgImg->render(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, 0, 0, _bgImg->getWidth(), _bgImg->getHeight());
}
