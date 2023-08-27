#include "Stdafx.h"
#include "BattleScene.h"

void BattleScene::collision(void)
{
	for (int i = 0; i < _player->getMissileM1()->getBullet().size(); i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &_player->getMissileM1()->getBullet()[i].rc, &CollisionAreaResizing(_boss->getRect(), 100, 200)))
		{
			if (rc.bottom < 0)
			{
				continue;
			}
			SOUNDMANAGER->playSoundFMOD("Blast", 0.5f);
			_score += 10;
			_player->removeMissileM1(i);
			if (_boss->getDamaged(rc, 0, 1))
			{
				SOUNDMANAGER->stopAllSoundFMOD();
				_score += 5000;
				SOUNDMANAGER->playSoundFMOD("Clear", 1.0f);
				_isClear = true;
			}
			break;
		}
	}
	for (int i = 0; i < _player->getMissileM1()->getBullet().size(); i++)
	{
		for (int j = 0; j < _em->getMinions().size(); j++)
		{
			RECT rc;
			if (IntersectRect(&rc, &_player->getMissileM1()->getBullet()[i].rc, &_em->getMinions()[j]->getRect()))
			{
				if (rc.bottom < 0)
				{
					continue;
				}
				SOUNDMANAGER->playSoundFMOD("Blast", 0.5f);
				_score += 10;
				_player->removeMissileM1(i);
				_em->removeMinion(j, 0, 1, &_score);
				break;
			}
		}
	}
	for (int i = 0; i < _player->getMissileM2()->getBullet().size(); i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &_player->getMissileM2()->getBullet()[i].rc, &CollisionAreaResizing(_boss->getRect(), 100, 200)))
		{
			if (rc.bottom < 0)
			{
				continue;
			}
			SOUNDMANAGER->playSoundFMOD("Blast", 0.5f);
			_score += 10;
			_player->removeMissileM2(i);
			if (_boss->getDamaged(rc, 0, 2))
			{
				SOUNDMANAGER->stopAllSoundFMOD();
				_score += 5000;
				SOUNDMANAGER->playSoundFMOD("Clear", 1.0f);
				_isClear = true;
			}
			break;
		}
	}
	for (int i = 0; i < _player->getMissileM2()->getBullet().size(); i++)
	{
		for (int j = 0; j < _em->getMinions().size(); j++)
		{
			RECT rc;
			if (IntersectRect(&rc, &_player->getMissileM2()->getBullet()[i].rc, &_em->getMinions()[j]->getRect()))
			{
				if (rc.bottom < 0)
				{
					continue;
				}
				SOUNDMANAGER->playSoundFMOD("Blast", 0.5f);
				_score += 10;
				_player->removeMissileM2(i);
				_em->removeMinion(j, 0, 2, &_score);
				break;
			}
		}
	}
	for (int i = 0; i < _player->getMissileM3()->getBullet().size(); i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &_player->getMissileM3()->getBullet()[i].rc, &CollisionAreaResizing(_boss->getRect(), 100, 200)))
		{
			if (rc.bottom < 0)
			{
				continue;
			}
			SOUNDMANAGER->playSoundFMOD("Blast", 0.5f);
			_score += 10;
			_player->removeMissileM3(i);
			if (_boss->getDamaged(rc, 0, 3))
			{
				SOUNDMANAGER->stopAllSoundFMOD();
				SOUNDMANAGER->playSoundFMOD("Clear", 1.0f);
				_isClear = true;
			}
			break;
		}
	}
	for (int i = 0; i < _player->getMissileM3()->getBullet().size(); i++)
	{
		for (int j = 0; j < _em->getMinions().size(); j++)
		{
			RECT rc;
			if (IntersectRect(&rc, &_player->getMissileM3()->getBullet()[i].rc, &_em->getMinions()[j]->getRect()))
			{
				if (rc.bottom < 0)
				{
					continue;
				}
				SOUNDMANAGER->playSoundFMOD("Blast", 0.5f);
				_score += 10;
				_player->removeMissileM3(i);
				_em->removeMinion(j, 0, 3, & _score);
				break;
			}
		}
	}
	for (int i = 0; i < _player->getMissileM4()->getBullet().size(); i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &_player->getMissileM4()->getBullet()[i].rc, &CollisionAreaResizing(_boss->getRect(), 100, 200)))
		{
			if (rc.bottom < 0)
			{
				continue;
			}
			SOUNDMANAGER->playSoundFMOD("Blast", 0.5f);
			_score += 10;
			_player->removeMissileM4(i);
			if (_boss->getDamaged(rc, 0, 4))
			{
				SOUNDMANAGER->stopAllSoundFMOD();
				SOUNDMANAGER->playSoundFMOD("Clear", 1.0f);
				_isClear = true;
			}
			break;
		}
	}
	for (int i = 0; i < _player->getMissileM4()->getBullet().size(); i++)
	{
		for (int j = 0; j < _em->getMinions().size(); j++)
		{
			RECT rc;
			if (IntersectRect(&rc, &_player->getMissileM4()->getBullet()[i].rc, &_em->getMinions()[j]->getRect()))
			{
				if (rc.bottom < 0)
				{
					continue;
				}
				SOUNDMANAGER->playSoundFMOD("Blast", 0.5f);
				_score += 10;
				_player->removeMissileM4(i);
				_em->removeMinion(j, 0, 4, &_score);
				break;
			}
		}
	}
	for (int i = 0; i < _player->getRocketMissile()->getBullet().size(); i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &_player->getRocketMissile()->getBullet()[i].rc, &CollisionAreaResizing(_boss->getRect(), 100, 200)))
		{
			if (rc.bottom < 0)
			{
				continue;
			}
			SOUNDMANAGER->playSoundFMOD("Blast2", 0.5f);
			_score += 10;
			_player->removeRocketMissile(i);
			if (_boss->getDamaged(rc, 1, 4))
			{
				SOUNDMANAGER->stopAllSoundFMOD();
				SOUNDMANAGER->playSoundFMOD("Clear", 1.0f);
				_isClear = true;
			}
			break;
		}
	}
	for (int i = 0; i < _player->getRocketMissile()->getBullet().size(); i++)
	{
		for (int j = 0; j < _em->getMinions().size(); j++)
		{
			RECT rc;
			if (IntersectRect(&rc, &_player->getRocketMissile()->getBullet()[i].rc, &_em->getMinions()[j]->getRect()))
			{
				if (rc.bottom < 0)
				{
					continue;
				}
				SOUNDMANAGER->playSoundFMOD("Blast2", 0.5f);
				_score += 10;
				_player->removeRocketMissile(i);
				_em->removeMinion(j, 1, 4, &_score);
				break;
			}
		}
	}


	for(int i = 0; i < _boss->getBullet1()->getBullet().size(); i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &CollisionAreaResizing(_player->getRect(), 50, 30), &_boss->getBullet1()->getBullet()[i].rc))
		{
			_player->hitDamage(10);
			_boss->removeBullet(i);
			break;
		}
	}
	for (int i = 0; i < _boss->getBullet2()->getBullet().size(); i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &CollisionAreaResizing(_player->getRect(), 50, 30), &_boss->getBullet2()->getBullet()[i].rc))
		{
			_player->hitDamage(10);
			_boss->removeBullet2(i);
			break;
		}
	}

	for (int i = 0; i < _em->getPower()->getItem().size(); i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &CollisionAreaResizing(_player->getRect(), 50, 30), &_em->getPower()->getItem()[i].rc))
		{
			SOUNDMANAGER->playSoundFMOD("PowerUp", 1.0f);
			_score += 100;
			_player->powerUp();
			_em->removePower(i);
			break;
		}
	}
	for (int i = 0; i < _boss->getPower()->getItem().size(); i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &_player->getRect(), &_boss->getPower()->getItem()[i].rc))
		{
			_score += 100;
			_player->powerUp();
			_boss->removePower(i);
			break;
		}
	}

	for (int i = 0; i < _em->getGoldBar()->getItem().size(); i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &_player->getRect(), &_em->getGoldBar()->getItem()[i].rc))
		{
			SOUNDMANAGER->playSoundFMOD("getGold", 0.5f);
			_score += 500;
			_em->removeGoldBar(i);
			break;
		}
	}
}
