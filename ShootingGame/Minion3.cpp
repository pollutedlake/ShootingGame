#include "Stdafx.h"
#include "Minion3.h"

HRESULT Minion3::init(const char* imageName, float startX, float startY, bool isLeft, int activeY, int hp)
{
	_worldTimeCount = GetTickCount();
	_rndTimeCount = RND->getFromFloatTo(50, 150);

	_bulletFireCount = TIMEMANAGER->getWorldTime();
	_rndFireCount = 0.5f;

	_hp = hp;
	_x = startX;
	_y = startY;
	_image = IMAGEMANAGER->findImage(imageName);
	_rc = RectMakeCenter(startX, startY,
		_image->getFrameWidth(), _image->getFrameHeight());
	_activateY = activeY;
	_active = false;
	_inactive = false;
	_isLeft = isLeft;
	if(isLeft)
	{
		_radius = getDistance(0, 0, startX, startY);
		_angle = getAngle(0, 0, startX, startY);
	}
	else
	{
		_radius = getDistance(WINSIZE_X, 0, startX, startY);
		_angle = getAngle(WINSIZE_X, 0, startX, startY);
	}
	return S_OK;
}

void Minion3::move(void)
{
	if (_isLeft)
	{
		_angle -= 0.005f;
		_x = _radius * cosf(_angle);
		_y = _radius * -sinf(_angle);
		_rc = RectMakeCenter(_x, _y,
			_image->getFrameWidth(), _image->getFrameHeight());
		if (_rc.right < 0)
		{
			_inactive = true;
		}
	}
	else
	{
		_angle += 0.005f;
		_x = WINSIZE_X + _radius * cosf(_angle);
		_y = _radius * -sinf(_angle);
		_rc = RectMakeCenter(_x, _y,
			_image->getFrameWidth(), _image->getFrameHeight());
		if (_rc.left > WINSIZE_X)
		{
			_inactive = true;
		}
	}
}

Minion3::Minion3()
{
}

Minion3::~Minion3()
{
}
