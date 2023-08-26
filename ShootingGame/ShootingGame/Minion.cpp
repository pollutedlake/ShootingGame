#include "stdafx.h"
#include "Minion.h"

HRESULT Minion::init(const char* imageName, POINT center, int radius, float angle)
{
	_worldTimeCount = GetTickCount();
	_rndTimeCount = RND->getFromFloatTo(50, 150);
	_angle = angle;
	_radius = radius;
	_x = center.x;
	_y = center.y;
	_image = IMAGEMANAGER->findImage(imageName);
	_rc = RectMakeCenter(center.x, center.y,
		_image->getFrameWidth(), _image->getFrameHeight());
	return S_OK;
}

void Minion::move(void)
{
	_count++;
	if (_count % 5 == 0)
	{
		_angle++;
		_count = 0;
	}
	_rc = RectMakeCenter(_x + _radius * cos((_angle)), _y + _radius * sin(_angle),
		_image->getFrameWidth(), _image->getFrameHeight());
}

Minion::Minion()
{
	// Do Nothing
}

Minion::~Minion()
{
	// Do Nothing
}
