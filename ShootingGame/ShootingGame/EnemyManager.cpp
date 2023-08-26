#include "stdafx.h"
#include "EnemyManager.h"
#include "Player.h"

HRESULT EnemyManager::init(void)
{
 	IMAGEMANAGER->addFrameImage("���ĸ�", "Resources/Images/ShootingGame/Minion.bmp", 0.0f, 0.0f, 1140, 47, 19, 1, true, RGB(255, 0, 255));
 	IMAGEMANAGER->addImage("�� �̻���", "Resources/Images/ShootingGame/Bullet.bmp", 7 * 2, 7 * 2, true, RGB(255, 0, 255));
	setMinion();

	_bullet = new Bullet;
	_bullet->init("�� �̻���", 30, 1000);
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

}

void EnemyManager::update(void)
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->update();
	}
	minionBulletFire();
	_bullet->update();
	collision();
}

void EnemyManager::render(void)
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->render();
	}
	_bullet->render();
}

void EnemyManager::setMinion(void)
{
	
}

void EnemyManager::removeMinion(int arrNum)
{
	
	SAFE_DELETE(_vMinion[arrNum]);
	_vMinion.erase(_vMinion.begin() + arrNum);
}

void EnemyManager::minionBulletFire(void)
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		if ((*_viMinion)->bulletCountFire())
		{
			RECT rc = (*_viMinion)->getRect();
			_bullet->fire(rc.left + (rc.right - rc.left) / 2, 
						  rc.bottom + (rc.top - rc.bottom) / 2 + 30, 
						  getAngle(rc.left + (rc.right - rc.left) / 2, rc.bottom + (rc.top - rc.bottom) / 2, _player->getPosition().x, _player->getPosition().y),
						  RND->getFromFloatTo(2.0f, 4.0f));
		}
	}
}

void EnemyManager::collision(void)
{
	for (int i = 0; i < _bullet->getBullet().size(); i++)
	{
		RECT rc;

	}
}

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
}
