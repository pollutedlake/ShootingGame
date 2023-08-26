#include "stdafx.h"
#include "Enemy.h"
#include "Bullets.h"

Enemy::Enemy(void) : _rc(RectMake(0, 0, 0, 0)), _currentFrameX(0), _currentFrameY(0), _x(0.0f), _y(0.0f), _worldTimeCount(0.0f), _rndTimeCount(0.0f),
_rndFireCount(0.0f),
_bulletFireCount(0.0f)
{

}

HRESULT Enemy::init(void)
{
    return S_OK;
}

HRESULT Enemy::init(const char* imageName, POINT position)
{
    _worldTimeCount = GetTickCount();
    _rndTimeCount = RND->getFromFloatTo(50, 150);

    _bulletFireCount = TIMEMANAGER->getWorldTime();
    _rndFireCount = RND->getFromFloatTo(2.0f, 6.0f);

    _x = position.x;
    _y = position.y;
    _image = IMAGEMANAGER->findImage(imageName);
    _rc = RectMakeCenter(position.x, position.y,
        _image->getFrameWidth(), _image->getFrameHeight());
    return S_OK;
}

HRESULT Enemy::init(const char* imageName, POINT center, int radius, float angle)
{
    // DO NOTHING
    return S_OK;
}

HRESULT Enemy::init(const char* imageName, POINT position, int rndSpeed)
{
    // DO NOTHING
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

// �������� �ʴ� ���� : ������ �������� �ٸ���. -> ����� ������ Ŭ�����ε�.. -> �ڽ� ����
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

void Enemy::getDamaged(void)
{

}

bool Enemy::bulletCountFire(void)
{
    if (_rndFireCount + _bulletFireCount <= TIMEMANAGER->getWorldTime())
    {
        _bulletFireCount = TIMEMANAGER->getWorldTime();
        _rndFireCount = RND->getFromFloatTo(2.0f, 6.0f);
        return true;
    }
    return false;
}
