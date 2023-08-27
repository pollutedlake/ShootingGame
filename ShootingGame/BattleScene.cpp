#include "stdafx.h"
#include "BattleScene.h"
#include "Collision.h"

HRESULT BattleScene::init(void)
{
	_uiImg = IMAGEMANAGER->addImage("UI", "Resources/Images/UI.bmp", 1280, 720);
	_bgImg = IMAGEMANAGER->addImage("BattleBG", "Resources/Images/BattleBG.bmp", 224 * 3, 1840 * 3);
	_black = IMAGEMANAGER->addImage("Black", "Resources/Images/Black.bmp", WINSIZE_X, WINSIZE_Y);
	_scoreImg = IMAGEMANAGER->addFrameImage("Score", "Resources/Images/Score.bmp", 47, 470, 1, 10, true, RGB(255, 40, 255));
	SOUNDMANAGER->addSoundFMOD("getGold", "Resources/Sounds/getGold.wav");
	SOUNDMANAGER->addSoundFMOD("Blast", "Resources/Sounds/blast.wav");
	SOUNDMANAGER->addSoundFMOD("Boss", "Resources/Sounds/boss.wav");
	SOUNDMANAGER->addSoundFMOD("Clear", "Resources/Sounds/Clear.wav");
	SOUNDMANAGER->addSoundFMOD("PowerUp", "Resources/Sounds/PowerUp.wav");
	SOUNDMANAGER->addSoundFMOD("Blast2", "Resources/Sounds/Blast2.wav");
	SOUNDMANAGER->addSoundFMOD("Blast3", "Resources/Sounds/Blast3.wav");
	SOUNDMANAGER->addSoundFMOD("BattleBG", "Resources/Sounds/BattleBG.wav");
	_bgSpeed = 0.5f;
	_x = 0.0f;
	_blackAlpha = 0;
	_y = _bgImg->getHeight() - WINSIZE_Y;

	_player = new Player;
	_player->init();

	_em = new EnemyManager;
	_em->init();

	_boss = new Boss;
	_boss->init();

	_em->setPlayerMemoryAddress(_player);
	_boss->setPlayerMemoryAddress(_player);
	_player->setEnemyMemoryAddress(_em);

	_score = 0.0f;

	SOUNDMANAGER->playSoundFMOD("BattleBG", 1.0f);

	return S_OK;
}

void BattleScene::release(void)
{
	_player->release();
	_em->release();
	_boss->release();
	SAFE_DELETE(_player);
	SAFE_DELETE(_em);
	SAFE_DELETE(_boss);
}

void BattleScene::update(void)
{
	_y -= _bgSpeed;
	if(!_isClear)
	{
		_player->update();
		_em->update(_y);
		_boss->update(_y);
		collision();
	}
	else
	{
		_blackAlpha++;
		if (_blackAlpha > 255)
		{
			SOUNDMANAGER->stopAllSoundFMOD();
			SCENEMANAGER->changeScene("Title");
		}
	}
	cout << _y << endl;
}

void BattleScene::render(void)
{
	RECT _rc;
	_rc = {0, 0, WINSIZE_X, WINSIZE_Y};
	_bgImg->loopRender(getMemDC(), &_rc, _x, _y);
	_em->render();
	_boss->render();
	_player->render();
	int temp = _score;
	for (int i = 0; i < 5; i++)
	{
		_scoreImg->frameRender(getMemDC(), WINSIZE_X - _scoreImg->getFrameWidth() * (i + 1), 0, 
			 0, temp % 10);
		temp /= 10;
	}
	if (_isClear)
	{
		_black->alphaRender(getMemDC(), 0, 0, _blackAlpha);
	}
}
