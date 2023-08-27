#include "Stdafx.h"
#include "Minion2.h"

HRESULT Minion2::init(const char* imageName, float startX, float startY, float destX, float destY, int activeY, int hp)
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
	_destY = destY;
	_destX = destX;
	return S_OK;
}

void Minion2::move(void)
{
	if (getDistance(_x, _y, _destX, _destY) > 3)
	{
		float angle = getAngle(_x, _y, _destX, _destY);
		_x += 3 * cosf(angle);
		_y += 3 * -sinf(angle);
	}
	_rc = RectMakeCenter(_x, _y,
		_image->getFrameWidth(), _image->getFrameHeight());
}

Minion2::Minion2()
{
}

Minion2::~Minion2()
{
}
