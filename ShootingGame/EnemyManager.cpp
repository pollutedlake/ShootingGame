#include "stdafx.h"
#include "EnemyManager.h"
#include "Player.h"
#include "Minion1.h"
#include "Minion2.h"
#include "Minion3.h"

HRESULT EnemyManager::init(void)
{
 	IMAGEMANAGER->addFrameImage("Minion1", "Resources/Images/Minion1.bmp", 352, 36, 11, 1, true, RGB(0, 128, 128));
 	IMAGEMANAGER->addFrameImage("Minion2", "Resources/Images/Minion2.bmp", 480, 120, 2, 1, true, RGB(0, 128, 128));
 	IMAGEMANAGER->addFrameImage("Minion3", "Resources/Images/Minion3.bmp", 352, 36, 11, 1, true, RGB(0, 128, 128));
 	IMAGEMANAGER->addFrameImage("Minion4", "Resources/Images/Minion4.bmp", 440, 40, 11, 1, true, RGB(0, 128, 128));
	IMAGEMANAGER->addFrameImage("Bullet1", "Resources/Images/Bullet1.bmp", 72, 20, 6, 1, true, RGB(255, 0, 255));
	setMinion();

	_bullet = new Bullet;
	_bullet->init("Bullet1", 30, WINSIZE_Y);

	_power = new Power;
	_power->init(WINSIZE_Y * 3);

	_goldBar = new GoldBar;
	_goldBar->init();
	return S_OK;
}

void EnemyManager::release(void)
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->release();
		SAFE_DELETE(*_viMinion);
	}
	_bullet->release();
	SAFE_DELETE(_bullet);
	_power->release();
	SAFE_DELETE(_power);
	_goldBar->release();
	SAFE_DELETE(_goldBar);
}

void EnemyManager::update(int y)
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end();)
	{
		if ((*_viMinion)->getActivateY() > y)
		{
			(*_viMinion)->setActive(true);
		}
		if (!(*_viMinion)->getActive())
		{
			++_viMinion;
			continue;
		}
		(*_viMinion)->update();
		if ((*_viMinion)->isInActive())
		{
			_viMinion = _vMinion.erase(_viMinion);
		}
		else
		{
			++_viMinion;
		}
	}
	minionBulletFire();
	_bullet->update();
	_power->update();
	_goldBar->update();
}

void EnemyManager::render(void)
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->render();
	}
	_bullet->render();
	_power->render();
	_goldBar->render();
	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end();)
	{
		_viEffect->img->frameRender(getMemDC(), _viEffect->rc.left, _viEffect->rc.top);
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
}

void EnemyManager::setMinion(void)
{
	Enemy* enemy;
	for (int i = 0; i < 3; i++)
	{
		enemy = new Minion1;
		enemy->init("Minion1", PointMake(300 - 50 * i, -50), 4800, 1);
		_vMinion.push_back(enemy);
	}
	for (int i = 0; i < 8; i++)
	{
		enemy = new Minion3;
		enemy->init("Minion3", 500, -50, true, 4750 - 5 * i, 5);
		_vMinion.push_back(enemy);
	}
	for (int i = 0; i < 2; i++)
	{
		enemy = new Minion2;
		enemy->init("Minion2", WINSIZE_X / 2 + 300.0f * ((i % 2 == 0) ? 1 : -1), -120, 
			WINSIZE_X / 2 + 300 * ((i % 2 == 0) ? 1 : -1), 200, 4700, 10);
		_vMinion.push_back(enemy);
	}
	for (int i = 0; i < 8; i++)
	{
		enemy = new Minion3;
		enemy->init("Minion4", 100, -50, false, 4650 - 5 * i, 7);
		_vMinion.push_back(enemy);
	}
	for (int i = 0; i < 3; i++)
	{
		enemy = new Minion1;
		enemy->init("Minion1", PointMake(300 + 50 * i, -50), 4600, 1);
		_vMinion.push_back(enemy);
	}
	enemy = new Minion2;
	enemy->init("Minion2", WINSIZE_X, -120,
		0, WINSIZE_Y + 120, 4550, 10);
	_vMinion.push_back(enemy);
	enemy = new Minion2;
	enemy->init("Minion2", 0, -120,
		WINSIZE_X, WINSIZE_Y + 120, 4550, 10);
	_vMinion.push_back(enemy);
	for (int i = 0; i < 8; i++)
	{
		enemy = new Minion2;
		enemy->init("Minion4", -200, 250, 75 * i, 300, 4500, 1);
		_vMinion.push_back(enemy);
	}
	for (int i = 0; i < 8; i++)
	{
		enemy = new Minion2;
		enemy->init("Minion4", WINSIZE_X + 200, 250, WINSIZE_X - 75 * i, 300, 4450, 1);
		_vMinion.push_back(enemy);
	}
	enemy = new Minion1;
	enemy->init("Minion2", PointMake(300, -100), 4400, 5);
	_vMinion.push_back(enemy);
	enemy = new Minion1;
	enemy->init("Minion2", PointMake(500, -100), 4400, 5);
	_vMinion.push_back(enemy);

}

void EnemyManager::removeMinion(int arrNum, int missile, int damage, int* score)
{
	tagEffect effect;
	effect.img = new GImage;
	switch (missile)
	{
	case 0:
		effect.img->init("Resources/Images/Explosion1.bmp", 0.f, 0.f, 200, 20, 10, 1, true, RGB(255, 0, 255));
		break;
	case 1:
		effect.img->init("Resources/Images/Explosion3.bmp", 0.f, 0.f, 360, 27, 12, 1, true, RGB(255, 255, 255));
		break;
	}
	effect.x = _vMinion[arrNum]->getPosition().x;
	effect.y = _vMinion[arrNum]->getPosition().y;
	effect.rc = RectMakeCenter(effect.x, effect.y, effect.img->getFrameWidth(), effect.img->getFrameHeight());
	_vEffect.push_back(effect);

	if(_vMinion[arrNum]->getDamaged(damage))
	{
		SOUNDMANAGER->playSoundFMOD("Blast3", 0.5f);
		if (RND->getInt(10) < 1)
		{
			_power->createItem(_vMinion[arrNum]->getPosition().x, _vMinion[arrNum]->getPosition().y, RND->getFloat(2 * PI), 3.0f);
		}
		_goldBar->createItem(_vMinion[arrNum]->getPosition().x, _vMinion[arrNum]->getPosition().y);

		*score += 200;
		SAFE_DELETE(_vMinion[arrNum]);
		_vMinion.erase(_vMinion.begin() + arrNum);
	}
}

void EnemyManager::removePower(int arrNum)
{
	_power->removeItem(arrNum);
}

void EnemyManager::removeGoldBar(int arrNum)
{
	_goldBar->removeItem(arrNum);
}

void EnemyManager::minionBulletFire(void)
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		if((*_viMinion)->getActive())
		{
			if ((*_viMinion)->bulletCountFire())
			{
				cout << "fire" << endl;
				RECT rc = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2, 
							  rc.bottom + (rc.top - rc.bottom) / 2 + 20, 
							  getAngle(rc.left + (rc.right - rc.left) / 2, rc.bottom + (rc.top - rc.bottom) / 2, _player->getPosition().x, _player->getPosition().y),
							  3.0f);
			}
		}
	}
}

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
}
