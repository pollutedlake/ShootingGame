#include "stdafx.h"
#include "Enemy.h"
#include "Bullets.h"

Enemy::Enemy(void) : _rc(RectMake(0, 0, 0, 0)), _currentFrameX(0), _currentFrameY(0), _x(0.0f), _y(0.0f), _worldTimeCount(0.0f), _rndTimeCount(0.0f),
_rndFireCount(0.0f),
_bulletFireCount(0.0f), _active(false), _activateY(0)
{

}

HRESULT Enemy::init(void)
{
    return S_OK;
}

HRESULT Enemy::init(const char* imageName, POINT position, int activeY, int hp)
{
    _worldTimeCount = GetTickCount();
    _rndTimeCount = RND->getFromFloatTo(50, 150);

    _bulletFireCount = TIMEMANAGER->getWorldTime();
    _rndFireCount = 0.5f;

    _hp = hp;
    _x = position.x;
    _y = position.y;
    _image = IMAGEMANAGER->findImage(imageName);
    _rc = RectMakeCenter(position.x, position.y,
        _image->getFrameWidth(), _image->getFrameHeight());
    _activateY = activeY;
    _inactive = false;
    return S_OK;
}

HRESULT Enemy::init(const char* imageName, float startX, float startY, float x, float y, int activeY, int hp)
{
    return S_OK;
}

HRESULT Enemy::init(const char* imageName, float startX, float startY, bool isLeft, int activeY, int hp)
{
    return S_OK;
}

void Enemy::release(void)
{
}

void Enemy::update(void)
{
    move();
}

void Enemy::render(void)
{
    draw();
    animation();
}

void Enemy::move(void)
{
}

void Enemy::draw(void)
{
    _image->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
}

void Enemy::animation(void)
{
    if (_rndTimeCount + _worldTimeCount <= GetTickCount())
    {
        _worldTimeCount = GetTickCount();
        _currentFrameX++;

        if (_image->getMaxFrameX() < _currentFrameX)
        {
            _currentFrameX = 0;
        }
    }
}

bool Enemy::getDamaged(int damage)
{
    _hp -= damage;
    if (_hp < 0)
    {
        _hp = 0;
        return true;
    }
    return false;
}

bool Enemy::bulletCountFire(void)
{
    if (_rndFireCount + _bulletFireCount <= TIMEMANAGER->getWorldTime())
    {
        _bulletFireCount = TIMEMANAGER->getWorldTime();
		_rndFireCount = RND->getFromFloatTo(0.5f, 1.0f);
        return true;
    }
    return false;
}
