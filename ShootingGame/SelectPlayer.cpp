#include "Stdafx.h"
#include "SelectPlayer.h"

HRESULT SelectPlayer::init(void)
{
	_bgImg = IMAGEMANAGER->addFrameImage("SelectPlayer", "Resources/Images/SelectPlayer.bmp", 1509, 7931, 3, 11);
	_black = IMAGEMANAGER->addImage("Black", "Resources/Images/Black.bmp", WINSIZE_X, WINSIZE_Y);
	SOUNDMANAGER->addSoundFMOD("SelectPlayerBG", "Resources/Sounds/SelectPlayerBG.wav", true);
	SOUNDMANAGER->addSoundFMOD("PlayerSelected", "Resources/Sounds/PlayerSelected.wav", true);
	_frameX = _frameY = 0;
	_timeCount = TIMEMANAGER->getWorldTime();
	_choice = false;
	_blackAlpha = 0;
	SOUNDMANAGER->playSoundFMOD("SelectPlayerBG", 1.0f);
	return S_OK;
}

void SelectPlayer::release(void)
{
	
}

void SelectPlayer::update(void)
{
	if (_choice)
	{
		_blackAlpha++;
		if (_blackAlpha > 255)
		{
			SOUNDMANAGER->stopAllSoundFMOD();	
			SCENEMANAGER->changeScene("Battle");
		}
	}
	else
	{
		if (1.0f + _timeCount <= TIMEMANAGER->getWorldTime())
		{
			_timeCount = TIMEMANAGER->getWorldTime();
			_frameY++;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			_frameX++;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			_frameX--;
		}
		if (KEYMANAGER->isOnceKeyDown('X') || KEYMANAGER->isOnceKeyDown('x'))
		{
			SOUNDMANAGER->playSoundFMOD("PlayerSelected", 1.0f);
			_choice = true;
		}
		if (_frameY > 10)
		{
			_frameY = 10;
			SOUNDMANAGER->playSoundFMOD("PlayerSelected", 1.0f);
			_choice = true;
		}
	}
}

void SelectPlayer::render(void)
{
	_bgImg->frameRender(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, _frameX, _frameY);
	_black->alphaRender(getMemDC(), 0, 0, _blackAlpha);
}
