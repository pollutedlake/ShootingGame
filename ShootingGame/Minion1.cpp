#include "stdafx.h"
#include "Minion1.h"

void Minion1::move(void)
{
	_count++;
	if (_count % 5 == 0)
	{
		_count = 0;
	}
	_y += 3.0f;
	_rc = RectMakeCenter(_x, _y,
		_image->getFrameWidth(), _image->getFrameHeight());
	if (_y > WINSIZE_Y)
	{
		_inactive = true;
	}
}

Minion1::Minion1()
{
	// Do Nothing
}

Minion1::~Minion1()
{
	// Do Nothing
}
