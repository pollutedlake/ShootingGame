#include "stdafx.h"
#include "TitleScene.h"

HRESULT TitleScene::init(void)
{
	_bgImg = IMAGEMANAGER->addImage("TitleBG", "Resources/Images/TitleBG.bmp", 672, 672);
	_startButton = IMAGEMANAGER->addImage("StartButton", "Resources/Images/StartButton.bmp", 305, 57, true, RGB(255, 0, 255));
	_buttonAlpha = 0;
	_alphaIncrease = true;
	return S_OK;
}

void TitleScene::release(void)
{
	
}

void TitleScene::update(void)
{
	if (_alphaIncrease)
	{
		_buttonAlpha++;
	}
	else
	{
		_buttonAlpha--;
	}
	if (_buttonAlpha > 255)
	{
		_buttonAlpha = 255;
		_alphaIncrease = false;
	}
	else if (_buttonAlpha < 0)
	{
		_buttonAlpha = 0;
		_alphaIncrease = true;
	}
	if (KEYMANAGER->isOnceKeyDown('X') || KEYMANAGER->isOnceKeyDown('x'))
	{
		SCENEMANAGER->changeScene("SelectPlayer");
	}
}

void TitleScene::render(void)
{
	_bgImg->render(getMemDC());
	_startButton->alphaRender(getMemDC(), WINSIZE_X / 2 - _startButton->getWidth() / 2, 500, _buttonAlpha);
}
