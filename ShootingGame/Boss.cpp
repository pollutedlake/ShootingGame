#include "Stdafx.h"
#include "Boss.h"
#include "Player.h"

HRESULT Boss::init(void)
{
	_image = IMAGEMANAGER->addFrameImage("Boss2", "Resources/Images/Boss2.bmp", 6696, 186, 36, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Bullet1", "Resources/Images/Bullet1.bmp", 72, 20, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Bullet2", "Resources/Images/Bullet2.bmp", 18, 16, 1, 1, true, RGB(255, 0, 255));
	_x = WINSIZE_X / 2;
	_y = -150;
	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth() * 1.5f, _image->getFrameHeight() * 1.5f);

	_bullet = new Bullet;
	_bullet->init("Bullet1", 200, WINSIZE_Y);

	_bullet2 = new Bullet;
	_bullet2->init("Bullet2", 50, WINSIZE_Y);

	_ani = new Animation;
	_ani->init(_image->getWidth(), _image->getHeight(), _image->getFrameWidth(), _image->getFrameHeight());
	_ani->setPlayFrame(0, _image->getMaxFrameX(), true, true);
	_ani->setFPS(24);
	_ani->AniStart();

	_power = new Power;
	_power->init(WINSIZE_Y * 3);

	_active = false;
	_activateY = 4000;

	_hp = 2000;

	_pattern = Pattern1;
	return S_OK;
}

void Boss::release(void)
{
	_power->release();
	SAFE_DELETE(_power);
}

void Boss::update(float y)
{	
	if(!_active)
	{
		if (y < _activateY)
		{
			_y += 2.0f;
			_rc = RectMakeCenter(_x, _y, _image->getFrameWidth() * 1.5f, _image->getFrameHeight() * 1.5f);
			if (_y > 150.0f)
			{
				_active = true;
				SOUNDMANAGER->stopSoundFMOD("BattleBG");
				SOUNDMANAGER->playSoundFMOD("Boss", 1.0f);
			}
		}
	}
	else
	{
		move();
		_bullet->update();
		_bullet2->update();
		_power->update();
	}
}

void Boss::render(void)
{
	draw();
	animation();
	_power->render();
}

void Boss::move(void)
{
	switch (_pattern)
	{
		case Pattern1:
			BossPattern1();
			if (_bulletCount >= 12)
			{
				_pattern = Pattern2;
				_bulletCount = 0;
				return;
			}
		break;
		case Pattern2:
			BossPattern2();
			if (_bulletCount > 4)
			{
				_pattern = Pattern3;
				_bulletCount = 0;
				_bullet2Count = 0;
			}
		break;
		case Pattern3:
			BossPattern3();
			if (_bullet2Count >= 3)
			{
				_pattern = Pattern4;
				_bulletCount = 0;
				_bullet2Count = 0;
			}
		break;
		case Pattern4:
			BossPattern4();
			if (_bullet2Count >= 2)
			{
				_pattern = Pattern5;
				_bulletCount = 0;
				_bullet2Count = 0;
			}
		break;
		case Pattern5:
			BossPattern5();
			if (_bullet2Count >= 72)
			{
				_pattern = Pattern6;
				_bulletCount = 0;
				_bullet2Count = 0;
			}
		case Pattern6:
			BossPattern6();
			if (_bulletCount >= 25)
			{
				_pattern = Pattern1;
				_bulletCount = 0;
				_bullet2Count = 0;
			}
			break;
	}
}

void Boss::draw(void)
{
	_image->aniRender(getMemDC(), _rc.left, _rc.top, _rc.right - _rc.left, _rc.bottom - _rc.top, _ani);

	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end();)
	{
		_viEffect->img->frameRender(getMemDC(), _viEffect->rc.left, _viEffect->rc.top,
			_viEffect->img->getFrameWidth() * 2, _viEffect->img->getFrameHeight() * 2, _viEffect->img->getFrameX(), _viEffect->img->getFrameY());
		_viEffect->count++;
		if (_viEffect->count % 5 == 0)
		{
			_viEffect->img->setFrameX(_viEffect->img->getFrameX() + 1);
			if (_viEffect->img->getFrameX() >= _viEffect->img->getMaxFrameX())
			{
				SAFE_DELETE(_viEffect->img);
				_viEffect = _vEffect.erase(_viEffect);
			}
			else
			{
				++_viEffect;
			}
		}
		else
		{
			++_viEffect;
		}
	}

	_bullet->render();
	_bullet2->render();
}

void Boss::animation(void)
{
	_ani->frameUpdate(TIMEMANAGER->getElapsedTime());
}

void Boss::removePower(int arrNum)
{
	_power->removeItem(arrNum);
}

bool Boss::getDamaged(RECT rc, int missile, int damage)
{
	tagEffect effect;
	effect.img = new GImage;
	switch (missile)
	{
	case 0:
		effect.img->init("Resources/Images/Explosion1.bmp", 0.f, 0.f, 200, 20, 10, 1, true, RGB(255, 0, 255));
		break;
	case 1:
		effect.img->init("Resources/Images/Explosion4.bmp", 0.f, 0.f, 1040, 65, 16, 1, true, RGB(0, 248, 0));
		break;
	}
	effect.x = RND->getFromIntTo(rc.left, rc.right);
	effect.y = RND->getFromIntTo(rc.bottom - 50, rc.bottom);
	effect.rc = RectMakeCenter(effect.x, effect.y, effect.img->getFrameWidth(), effect.img->getFrameHeight());
	_vEffect.push_back(effect);

	_hp -= damage;
	if(_hp < 0)
	{
		_hp = 0;
		return true;
	}
	if (RND->getInt(40) < 1)
	{
		_power->createItem(effect.x, effect.y, RND->getFloat(2 * PI), 3.0f);
	}
	return false;
}

bool Boss::bulletCountFire(void)
{
	switch (_pattern)
	{
		case Pattern1:
			if (0.2f + _bulletFireCount <= TIMEMANAGER->getWorldTime())
			{
				_bulletFireCount = TIMEMANAGER->getWorldTime();
				return true;
			}
		break;
		case Pattern2:
			if (0.4f + _bulletFireCount <= TIMEMANAGER->getWorldTime())
			{
				_bulletFireCount = TIMEMANAGER->getWorldTime();
				return true;
			}
		break;
		case Pattern3:
			if (0.4f + _bulletFireCount <= TIMEMANAGER->getWorldTime())
			{
				_bulletFireCount = TIMEMANAGER->getWorldTime();
				return true;
			}
		break;
		case Pattern4:
			if (0.05f + _bulletFireCount <= TIMEMANAGER->getWorldTime())
			{
				_bulletFireCount = TIMEMANAGER->getWorldTime();
				return true;
			}
		break;
		case Pattern5:
			if (0.05f + _bulletFireCount <= TIMEMANAGER->getWorldTime())
			{
				_bulletFireCount = TIMEMANAGER->getWorldTime();
				return true;
			}
			break;
		case Pattern6:
			if (0.05f + _bulletFireCount <= TIMEMANAGER->getWorldTime())
			{
				_bulletFireCount = TIMEMANAGER->getWorldTime();
				return true;
			}
			break;
	}
	return false;
}

bool Boss::bullet2CountFire(void)
{
	switch (_pattern)
	{
		case Pattern2:
			if (_bullet2Count < 11)
		{
			if (0.2f + _bullet2FireCount <= TIMEMANAGER->getWorldTime())
			{
				_bullet2FireCount = TIMEMANAGER->getWorldTime();
				return true;
			}
		}
			else
		{
			if (0.8f + _bullet2FireCount <= TIMEMANAGER->getWorldTime())
			{
				_bullet2FireCount = TIMEMANAGER->getWorldTime();
				return true;
			}
		}
		break;
		case Pattern3:
			if (0.8f + _bullet2FireCount <= TIMEMANAGER->getWorldTime())
			{
				_bullet2FireCount = TIMEMANAGER->getWorldTime();
				return true;
			}
		break;
		case Pattern4:
			if (1.0f + _bullet2FireCount <= TIMEMANAGER->getWorldTime())
			{
				_bullet2FireCount = TIMEMANAGER->getWorldTime();
				return true;
			}
		break;
		case Pattern5:
			if (0.1f + _bullet2FireCount <= TIMEMANAGER->getWorldTime())
			{
				_bullet2FireCount = TIMEMANAGER->getWorldTime();
				return true;
			}
			break;
		case Pattern6:
			if (0.05f + _bullet2FireCount <= TIMEMANAGER->getWorldTime())
			{
				_bullet2FireCount = TIMEMANAGER->getWorldTime();
				return true;
			}
			break;
	}
	return false;
}

void Boss::removeBullet(int arrNum)
{
	_bullet->removeBullet(arrNum);
}

void Boss::removeBullet2(int arrNum)
{
	_bullet2->removeBullet(arrNum);
}

void Boss::BossPattern1()
{
	if (bulletCountFire())
	{
		RECT rc = getRect();
		if(_bulletCount < 3)
		{
			for(int i = 0; i < 4; i++)
			{
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 30,
					PI / 180.0f * (225.f + 30.f * (float)i),
					3.0f);
			}
		}
		else if(_bulletCount < 6)
		{
			for (int i = 0; i < 3; i++)
			{
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 30,
					PI / 180.0f * (240.f + 30.f * (float)i),
					3.0f);
			}
		}
		else if (_bulletCount < 9)
		{
			for (int i = 0; i < 4; i++)
			{
				_bullet->fire(rc.left + (rc.right - rc.left) / 2 + 50,
					rc.bottom + (rc.top - rc.bottom) / 2 + 30,
					PI / 180.0f * (235.f + 30.f * (float)i),
					3.0f);
			}
		}
		else
		{
			for (int i = 0; i < 3; i++)
			{
				_bullet->fire(rc.left + (rc.right - rc.left) / 2 + 50,
					rc.bottom + (rc.top - rc.bottom) / 2 + 30,
					PI / 180.0f * (240.f + 30.f * (float)i),
					3.0f);
			}
		}
		_bulletCount++;
	}
}

void Boss::BossPattern2()
{
	if (bullet2CountFire())
	{
		RECT rc = getRect();
		if (_bullet2Count < 3)
		{
			_bullet2->fire(rc.left + (rc.right - rc.left) / 2 - 25,
				rc.bottom + (rc.top - rc.bottom) / 2,
				toDegree(280.f - 10.f * (float)_bullet2Count),
				3.0f);
		}
		else if (_bullet2Count == 3)
		{
			_bullet2->fire(rc.left + (rc.right - rc.left) / 2 - 25,
				rc.bottom + (rc.top - rc.bottom) / 2,
				toDegree(270.0f),
				3.0f);
				_playerLeft = _player->getPosition().x - WINSIZE_X / 2 < 0;
		}
		else if(_bullet2Count < 11)
		{
			_bullet2->fire(rc.left + (rc.right - rc.left) / 2 - 25,
				rc.bottom + (rc.top - rc.bottom) / 2,
				toDegree(280.f + (_playerLeft ? -1 : 1) * 10.f * ((float)_bullet2Count - 3)),
				3.0f);
		}
		else
		{
			_bullet2->fire(rc.left + (rc.right - rc.left) / 2 - 25,
				rc.bottom + (rc.top - rc.bottom) / 2,
				getAngle(rc.left + (rc.right - rc.left) / 2 - 25, rc.bottom + (rc.top - rc.bottom) / 2, _player->getPosition().x, _player->getPosition().y),
				3.0f);
		}
		_bullet2Count++;
	}

	if (bulletCountFire() && _bullet2Count >= 11)
	{
		RECT rc = getRect();
		if (_bulletCount % 2 == 0)
		{
			for (int i = 0; i < 3; i++)
			{
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 30,
					getAngle(rc.left + (rc.right - rc.left) / 2 - 25, rc.bottom + (rc.top - rc.bottom) / 2,
					_player->getPosition().x, _player->getPosition().y) - toDegree(10.0f) + toDegree(10.0f * i),
					3.0f);
			}
			for (int i = 0; i < 2; i++)
			{
				_bullet->fire(rc.left + (rc.right - rc.left) / 2 + 50,
					rc.bottom + (rc.top - rc.bottom) / 2 + 30,
					getAngle(rc.left + (rc.right - rc.left) / 2 - 25, rc.bottom + (rc.top - rc.bottom) / 2, 
					_player->getPosition().x, _player->getPosition().y) - toDegree(10.0f) + toDegree(20.0f * i),
					3.0f);
			}
		}
		else
		{
			for (int i = 0; i < 2; i++)
			{
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 30,
					getAngle(rc.left + (rc.right - rc.left) / 2 - 25, rc.bottom + (rc.top - rc.bottom) / 2, 
					_player->getPosition().x, _player->getPosition().y)- toDegree(10.0f) + toDegree(20.0f * i),
					3.0f);
			}
			for (int i = 0; i < 3; i++)
			{
				_bullet->fire(rc.left + (rc.right - rc.left) / 2 + 50,
					rc.bottom + (rc.top - rc.bottom) / 2 + 30,
					getAngle(rc.left + (rc.right - rc.left) / 2 - 25, rc.bottom + (rc.top - rc.bottom) / 2, 
					_player->getPosition().x, _player->getPosition().y) - toDegree(10.0f) + toDegree(10.0f * i),
					3.0f);
			}
		}
		_bulletCount++;
	}
}

void Boss::BossPattern3()
{
	if (bullet2CountFire())
	{
		RECT rc = getRect();
		for (int i = 0; i < 4; i++)
		{
			_bullet2->fire(WINSIZE_X / 2 + 50 + 20 * i,
				rc.bottom + (rc.top - rc.bottom) / 2 + 30 + 20 * i,
				toDegree(240.0f),
				3.0f);
		}
		for (int i = 0; i < 4; i++)
		{
			_bullet2->fire(WINSIZE_X / 2 - 50 - 20 * i,
				rc.bottom + (rc.top - rc.bottom) / 2 + 30 + 20 * i,
				toDegree(300.0f),
				3.0f);
		}
		_bullet2Count++;
	}
	if (bulletCountFire())
	{
		RECT rc = getRect();
		_bullet2->fire(WINSIZE_X / 2,
			rc.bottom + (rc.top - rc.bottom) / 2,
			getAngle(WINSIZE_X / 2, rc.bottom + (rc.top - rc.bottom) / 2, _player->getPosition().x, _player->getPosition().y),
			3.0f);
		_bulletCount++;
	}
}

void Boss::BossPattern4()
{
	if (bulletCountFire())
	{
		RECT rc = getRect();
		if (_bulletCount < 5)
		{
			for (int i = 0; i < 8; i++)
			{
				_bullet->fire(rc.left + (rc.right - rc.left) / 2 + 25 * cos(toDegree(45.0f * i + _bulletCount * 40.0f)),
					rc.bottom + (rc.top - rc.bottom) / 2 + 30 + 25 * -sin(toDegree(45.0f * i + _bulletCount * 40.0f)),
					toDegree(22.5f + 45.0f * i + _bulletCount * 5.0f),
					2.0f);
			}
			for (int i = 0; i < 8; i++)
			{
				_bullet->fire(rc.left + (rc.right - rc.left) / 2 + 50 + 25 * cos(toDegree(45.0f * i + _bulletCount * 40.0f)),
					rc.bottom + (rc.top - rc.bottom) / 2 + 30 + 25 * -sin(toDegree(45.0f * i + _bulletCount * 40.0f)),
					toDegree(22.5f + 45.0f * i - _bulletCount * 5.0f),
					2.0f);
			}
		}
		_bulletCount++;
	}
	if (bullet2CountFire() && _bulletCount >= 5)
	{
		RECT rc = getRect();
		for (int i = 0; i < 3; i++)
		{
			_bullet2->fire(WINSIZE_X / 2,
				rc.bottom + (rc.top - rc.bottom) / 2 + 30,
				getAngle(WINSIZE_X / 2, rc.bottom + (rc.top - rc.bottom) / 2, _player->getPosition().x, _player->getPosition().y),
				3.0f - 0.2f * i);
		}
		_bullet2Count++;
	}
}

void Boss::BossPattern5()
{
	if (bulletCountFire() && _bulletCount < 19)
	{
		RECT rc = getRect();
		if (_bulletCount < 8)
		{
			for (int i = 0; i < 8; i++)
			{
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 30,
					toDegree(22.5f + 45.0f * i + _bulletCount * 5.0f),
					2.0f);
			}
		}
		else if (_bulletCount > 10)
		{
			for (int i = 0; i < 8; i++)
			{
				_bullet->fire(rc.left + (rc.right - rc.left) / 2 + 50,
					rc.bottom + (rc.top - rc.bottom) / 2 + 30,
					toDegree(22.5f + 45.0f * i + (_bulletCount - 10) * 5.0f),
					2.0f);
			}
		}
		_bulletCount++;
	}
	if (bullet2CountFire() && _bulletCount == 19)
	{
		RECT rc = getRect();
		if (_bullet2Count < 4)
		{
			_bullet2->fire(WINSIZE_X / 2  - 80 - 10 * (_bullet2Count % 4),
				rc.bottom + (rc.top - rc.bottom) / 2 + 40 + 8 * (_bullet2Count % 4),
				toDegree(-5.0f - 3 * _bullet2Count / 4 - 20 * (_bullet2Count % 4)),
				2.0f);
		}
		else if (_bullet2Count < 8)
		{
			_bullet2->fire(WINSIZE_X / 2 + 80 + 10 * (_bullet2Count % 4),
				rc.bottom + (rc.top - rc.bottom) / 2 + 40 + 8 * (_bullet2Count % 4),
				toDegree(185.0f + 3 * _bullet2Count / 4 + 20 * (_bullet2Count % 4)),
				2.0f);
		}
		else if (_bullet2Count < 20)
		{
			_bullet2->fire(WINSIZE_X / 2 - 80 - 10 * (_bullet2Count % 4),
				rc.bottom + (rc.top - rc.bottom) / 2 + 40 + 8 * (_bullet2Count % 4),
				toDegree(-5.0f - 3 * _bullet2Count / 4 - 20 * (_bullet2Count % 4)),
				2.0f);
		}
		else if (_bullet2Count < 32)
		{
			_bullet2->fire(WINSIZE_X / 2 + 80 + 10 * (_bullet2Count % 4),
				rc.bottom + (rc.top - rc.bottom) / 2 + 40 + 8 * (_bullet2Count % 4),
				toDegree(185.0f + 3 * _bullet2Count / 4 + 20 * (_bullet2Count % 4)),
				2.0f);
		}
		else if (_bullet2Count < 52)
		{
			_bullet2->fire(WINSIZE_X / 2 - 80 - 10 * (_bullet2Count % 4),
				rc.bottom + (rc.top - rc.bottom) / 2 + 40 + 8 * (_bullet2Count % 4),
				toDegree(-5.0f - 3 * _bullet2Count / 4 - 20 * (_bullet2Count % 4)),
				2.0f);
		}
		else if (_bullet2Count < 72)
		{
			_bullet2->fire(WINSIZE_X / 2 + 80 + 10 * (_bullet2Count % 4),
				rc.bottom + (rc.top - rc.bottom) / 2 + 40 + 8 * (_bullet2Count % 4),
				toDegree(185.0f + 3 * _bullet2Count / 4 + 20 * (_bullet2Count % 4)),
				2.0f);
		}
		_bullet2Count++;
	}
}

void Boss::BossPattern6()
{
	if (bullet2CountFire())
	{
		RECT rc = getRect();
		if(_bullet2Count == 0)
		{
			for (int i = 0; i < 3; i++)
			{
				_bullet2->fire(WINSIZE_X / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 30,
					getAngle(WINSIZE_X / 2, rc.bottom + (rc.top - rc.bottom) / 2, _player->getPosition().x, _player->getPosition().y),
					3.0f - 0.2f * i);
			}
		}
		_bullet2Count++;
	}
	if (bulletCountFire() && _bullet2Count > 10)
	{
		RECT rc = getRect();
		if(_bulletCount < 16)
		{
			if (_bulletCount % 8 < 4)
			{
				_bullet2->fire(WINSIZE_X / 2 - 80 - 10 * (_bulletCount % 4),
					rc.bottom + (rc.top - rc.bottom) / 2 + 40 + 8 * (_bulletCount % 4),
					toDegree(-25.0f - 10 * _bulletCount / 8 - 20 * (_bulletCount % 4)),
					2.0f);
			}
			else
			{
				_bullet2->fire(WINSIZE_X / 2 + 80 + 10 * (_bulletCount % 4),
					rc.bottom + (rc.top - rc.bottom) / 2 + 40 + 8 * (_bulletCount % 4),
					toDegree(205.0f + 10 * _bulletCount / 8 + 20 * (_bulletCount % 4)),
					2.0f);
			}
		}
		_bulletCount++;
	}
}


Boss::Boss(void) : _currentFrameX(0), _currentFrameY(0), _x(0.0f), _y(0.0f), _worldTimeCount(0.0f), _rndFireCount(0.0f), _hp(100), _bulletFireCount(0.0f), _bullet2FireCount(0.0f), _bulletCount(0), _bullet2Count(0), _playerLeft(false)
{

}
