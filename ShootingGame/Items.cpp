#include "Stdafx.h"
#include "Items.h"

HRESULT Power::init(float range)
{
	_range = range;
	return S_OK;
}

void Power::release(void)
{

}

void Power::update(void)
{
	move();
}

void Power::render(void)
{
	draw();
}

void Power::createItem(float x, float y, float angle, float speed)
{
	tagItem item;
	ZeroMemory(&item, sizeof(tagItem));

	item.img = IMAGEMANAGER->addFrameImage("PowerItem", "Resources/Images/Item_Power.bmp", 150, 18, 6, 1, true, RGB(0, 128, 128));
	item.speed = speed;
	item.angle = angle;
	item.x = item.exX = x;
	item.y = item.exY = y;
	item.frameX = item.frameY = 0;
	item.moveDist = 0;
	item.count = 0;
	item.rc = RectMakeCenter(item.x, item.y,
		item.img->getFrameWidth() * 1.5f, item.img->getFrameHeight() * 1.5f);
	_vItem.push_back(item);
}

void Power::removeItem(int arrNum)
{
	_vItem.erase(_vItem.begin() + arrNum);
}

void Power::draw(void)
{
	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); ++_viItem)
	{
		_viItem->img->frameRender(getMemDC(), _viItem->rc.left, _viItem->rc.top,
			_viItem->img->getFrameWidth() * 1.5f, _viItem->img->getFrameHeight() * 1.5f,
			_viItem->frameX, _viItem->frameY);
	}
}

void Power::move(void)
{
	for (_viItem = _vItem.begin(); _viItem != _vItem.end();)
	{
		if (_viItem->rc.right > WINSIZE_X)
		{
			_viItem->rc.right = WINSIZE_X;
			_viItem->angle = PI - _viItem->angle;
		}
		if (_viItem->rc.left < 0)
		{
			_viItem->rc.left = 0;
			_viItem->angle = PI - _viItem->angle;
		}
		if (_viItem->rc.top < 0)
		{
			_viItem->rc.top = 0;
			_viItem->angle = 2 * PI - _viItem->angle; 
		}
		if (_viItem->rc.bottom > WINSIZE_Y)
		{
			_viItem->rc.bottom = WINSIZE_Y;
			_viItem->angle = 2 * PI - _viItem->angle;
		}
		_viItem->x += cosf(_viItem->angle) * _viItem->speed;
		_viItem->y += -sinf(_viItem->angle) * _viItem->speed;
		_viItem->moveDist += getDistance(_viItem->exX, _viItem->exY, _viItem->x, _viItem->y);
		_viItem->exX = _viItem->x;
		_viItem->exY = _viItem->y;
		_viItem->rc = RectMakeCenter(_viItem->x, _viItem->y, _viItem->img->getFrameWidth() * 1.5f, _viItem->img->getFrameHeight() * 1.5f);
		_viItem->count++;
		if (_viItem->count % 15 == 0)
		{
			_viItem->frameX++;
			if (_viItem->frameX >= _viItem->img->getMaxFrameX())
			{
				_viItem->frameX = 0;
			}
		}
		if (_viItem->moveDist >= _range)
		{
			_viItem = _vItem.erase(_viItem);
		}
		else
		{
			++_viItem;
		}
	}
}

HRESULT GoldBar::init()
{
	return E_NOTIMPL;
}

void GoldBar::release(void)
{
}

void GoldBar::update(void)
{
	move();
}

void GoldBar::render(void)
{
	draw();
}

void GoldBar::createItem(float x, float y)
{
	tagItem item;
	ZeroMemory(&item, sizeof(tagItem));

	item.img = IMAGEMANAGER->addFrameImage("GoldBar", "Resources/Images/GoldBar.bmp", 16, 80, 1, 8, true, RGB(255, 0, 255));
	item.x = item.exX = x;
	item.y = item.exY = y;
	item.frameX = item.frameY = 0;
	item.moveDist = 0;
	item.count = 0;
	item.rc = RectMakeCenter(item.x, item.y,
		item.img->getFrameWidth() * 1.5f, item.img->getFrameHeight() * 1.5f);
	_vItem.push_back(item);
}

void GoldBar::removeItem(int arrNum)
{
	_vItem.erase(_vItem.begin() + arrNum);
}

void GoldBar::draw(void)
{
	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); ++_viItem)
	{
		_viItem->img->frameRender(getMemDC(), _viItem->rc.left, _viItem->rc.top,
			_viItem->img->getFrameWidth() * 1.5f, _viItem->img->getFrameHeight() * 1.5f,
			_viItem->frameX, _viItem->frameY);
	}
}

void GoldBar::move(void)
{
	for (_viItem = _vItem.begin(); _viItem != _vItem.end();)
	{
		_viItem->y += 0.5f;
		_viItem->rc = RectMakeCenter(_viItem->x, _viItem->y, _viItem->img->getFrameWidth() * 1.5f, _viItem->img->getFrameHeight() * 1.5f);
		_viItem->count++;
		if (_viItem->count % 15 == 0)
		{
			_viItem->frameY++;
			if (_viItem->frameY >= _viItem->img->getMaxFrameY())
			{
				_viItem->frameY = 0;
			}
		}
		if (_viItem->rc.top > WINSIZE_Y)
		{
			_viItem = _vItem.erase(_viItem);
		}
		else
		{
			++_viItem;
		}
	}
}
