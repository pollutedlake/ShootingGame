#include "Stdafx.h"
#include "Player.h"
#include "EnemyManager.h"

HRESULT Player::init(void)
{
	_image = IMAGEMANAGER->addFrameImage("Player1", "Resources/Images/Player1.bmp", 145 * 2, 48 * 2, 5, 2, true, RGB(255, 0, 255));
	SOUNDMANAGER->addSoundFMOD("playerShot", "Resources/Sounds/playerShot.wav");

	_beamIrradiation = false;

	_currentHp = 10;
	_maxHp = 10;

	_ani = new Animation;
	_ani->init(_image->getWidth(), _image->getHeight(), 29 * 2, 24 * 2);
	_ani->setPlayFrame(2, 2, false, false);

	_missileM1 = new MissileM1;
	_missileM1->init(MAX_BULLET, WINSIZE_Y);
	_missileM2 = new MissileM2;
	_missileM2->init(MAX_BULLET, WINSIZE_Y);
	_missileM3 = new MissileM3;
	_missileM3->init(MAX_BULLET, WINSIZE_Y);
	_missileM4 = new MissileM4;
	_missileM4->init(MAX_BULLET, WINSIZE_Y);
	_rocketMissile = new RocketMissile;
	_rocketMissile->init(MAX_BULLET, WINSIZE_Y);

	_setWeapon = MISSILEM1;

	_attackTime = 0.0f;

	_rocketFireCount = 0.0f;

	_x = WINSIZE_X / 2;
	_y = WINSIZE_Y - 50;

	_rc = RectMakeCenter(_x, _y, _ani->getFrameWidth(), _ani->getFrameHeight());


	return S_OK;
}

void Player::release(void)
{
	_ani->release();
	SAFE_DELETE(_ani);
}

void Player::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_ani->setPlayFrame(2, 4, true, false);
		_ani->AniStart();
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _rc.right < WINSIZE_X)
	{
		_x += ROCKET_SPEED;
		if (_ani->getFrameIdx() % 4 == 0)
		{
			_ani->AniPause();
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		_ani->AniResume();
	}


	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_ani->setPlayFrame(2, 0, true, false);
		_ani->AniStart();
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _rc.left > 0)
	{
		_x -= ROCKET_SPEED;
		if (_ani->getFrameIdx() % 4 == 0)
		{
			_ani->AniPause();
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		_ani->AniResume();
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP) && _rc.top)
	{
		_y -= ROCKET_SPEED;
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _rc.bottom < WINSIZE_Y)
	{
		_y += ROCKET_SPEED;
	}

	_rc = RectMakeCenter(_x, _y, _ani->getFrameWidth(), _ani->getFrameHeight());

	_attackTime += TIMEMANAGER->getElapsedTime();
	if (_attackTime > ATTACK_SPEED)
	{
		switch (_setWeapon)
		{
		case MISSILEM1:
			if (KEYMANAGER->isStayKeyDown('x') || KEYMANAGER->isStayKeyDown('X'))
			{
				SOUNDMANAGER->playSoundFMOD("playerShot", 0.5f);
				_missileM1->fire(_x, _y - 36);
			}
			break;
		case MISSILEM2:
			if (KEYMANAGER->isOnceKeyDown('x') || KEYMANAGER->isStayKeyDown('X'))
			{
				SOUNDMANAGER->playSoundFMOD("playerShot", 0.5f);
				_missileM2->fire(_x, _y - 36);
				if (1.0f + _rocketFireCount <= TIMEMANAGER->getWorldTime())
				{
					_rocketFireCount = TIMEMANAGER->getWorldTime();
					_rocketMissile->fire(_x, _y);
				}
			}
			break;
		case MISSILEM3:
			if (KEYMANAGER->isOnceKeyDown('x') || KEYMANAGER->isStayKeyDown('X'))
			{
				SOUNDMANAGER->playSoundFMOD("playerShot", 0.5f);
				_missileM3->fire(_x, _y - 36);
				if (0.5f + _rocketFireCount <= TIMEMANAGER->getWorldTime())
				{
					_rocketFireCount = TIMEMANAGER->getWorldTime();
					_rocketMissile->fire(_x, _y);
				}
			}
			break;
		case MISSILEM4:
			if (KEYMANAGER->isOnceKeyDown('x') || KEYMANAGER->isStayKeyDown('X'))
			{
				SOUNDMANAGER->playSoundFMOD("playerShot", 0.5f);
				_missileM4->fire(_x, _y - 36);
				if (0.25f + _rocketFireCount <= TIMEMANAGER->getWorldTime())
				{
					_rocketFireCount = TIMEMANAGER->getWorldTime();
					_rocketMissile->fire(_x, _y);
				}
			}
			break;
		case BEAM:
			if (KEYMANAGER->isStayKeyDown(VK_SPACE))
			{
				_beamIrradiation = true;
			}
			else
			{
				_beamIrradiation = false;
			}
			break;
		}
		_attackTime = 0.0f;
	}

	_ani->frameUpdate(TIMEMANAGER->getElapsedTime());
	_missileM1->update();
	_missileM2->update();
	_missileM3->update();
	_missileM4->update();
	_rocketMissile->update();

}

void Player::render(void)
{
	_image->aniRender(getMemDC(), _rc.left, _rc.top, _ani);
	_missileM1->render();
	_missileM2->render();
	_missileM3->render();
	_missileM4->render();
	_rocketMissile->render();
}

void Player::removeMissileM1(int arrNum)
{
	_missileM1->removeBullet(arrNum);
}

void Player::removeMissileM2(int arrNum)
{
	_missileM2->removeBullet(arrNum);
}

void Player::removeMissileM3(int arrNum)
{
	_missileM3->removeBullet(arrNum);
}

void Player::removeMissileM4(int arrNum)
{
	_missileM4->removeBullet(arrNum);
}

void Player::removeRocketMissile(int arrNum)
{
	_rocketMissile->removeBullet(arrNum);
}

void Player::powerUp()
{
	_setWeapon = (EWeapon)(((int)_setWeapon) + 1);
	if ((int)_setWeapon > MISSILEM4)
	{
		_setWeapon = MISSILEM4;
	}
}
