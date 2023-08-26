#include "Stdafx.h"
#include "Player.h"
#include "EnemyManager.h"

HRESULT Player::init(void)
{
	_image = IMAGEMANAGER->addFrameImage("Player", "Resources/Images/Player.bmp", 105, 42, 5, 2, true, RGB(255, 0, 255));

	_beamIrradiation = false;

	_currentHp = 10;
	_maxHp = 10;

	_ani = new Animation;
	_ani->init(_image->getWidth(), _image->getHeight(), 21, 21);

	_x = WINSIZE_X / 2;
	_y = WINSIZE_Y / 2;

	_rc = RectMakeCenter(_x, _y, _image->getWidth(), _image->getHeight());


	return S_OK;
}

void Player::release(void)
{

}

void Player::update(void)
{
	if (KEYMANAGER->isOnceKeyDown('1')) hitDamage(1.0f);

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _rc.right < WINSIZE_X)
	{
		_x += ROCKET_SPEED;
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _rc.left > 0)
	{
		_x -= ROCKET_SPEED;
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP) && _rc.top)
	{
		_y -= ROCKET_SPEED;
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _rc.bottom < WINSIZE_Y)
	{
		_y += ROCKET_SPEED;
	}

	_rc = RectMakeCenter(_x, _y, _image->getWidth(), _image->getHeight());

	switch (_setWeapon)
	{
	case MISSILE:
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
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

	_ani->frameUpdate(TIMEMANAGER->getElapsedTime());

	collision();

}

void Player::render(void)
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top);
}

void Player::collision(void)
{
	
}

void Player::removeMissile(int arrNum)
{
}