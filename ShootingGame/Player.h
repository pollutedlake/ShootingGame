#pragma once
#include "GameNode.h"
#include "Bullets.h"
#include "Animation.h"

#define ROCKET_SPEED 3.0f
#define ATTACK_SPEED 0.13f

enum EWeapon
{
	MISSILEM1, MISSILEM2, MISSILEM3, MISSILEM4, BEAM
};

class EnemyManager;

class Player : public GameNode, public std::enable_shared_from_this<Player>
{
private:

	GImage* _image;
	EWeapon _setWeapon;
	EnemyManager* _em;
	Animation* _ani;

	MissileM1* _missileM1;
	MissileM2* _missileM2;
	MissileM3* _missileM3;
	MissileM4* _missileM4;
	RocketMissile* _rocketMissile;

	float _attackTime;

	RECT _rc;
	float _x, _y;
	float _currentHp;
	float _maxHp;
	bool _beamIrradiation;
	float _rocketFireCount;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void setEnemyMemoryAddress(EnemyManager* em) { _em = em; }
	void removeMissileM1(int arrNum);
	void removeMissileM2(int arrNum);
	void removeMissileM3(int arrNum);
	void removeMissileM4(int arrNum);
	void removeRocketMissile(int arrNum);

	POINT getPosition(void) { return PointMake(_x, _y); }
	RECT getRect(void) { return _rc; }

	MissileM1* getMissileM1(void) { return _missileM1; }
	MissileM2* getMissileM2(void) { return _missileM2; }
	MissileM3* getMissileM3(void) { return _missileM3; }
	MissileM4* getMissileM4(void) { return _missileM4; }
	RocketMissile* getRocketMissile(void) { return _rocketMissile; }

	void powerUp();

	inline void hitDamage(float damage)
	{
		if (_currentHp <= 0)
		{
			_currentHp = 0;
			return;
		}

		_currentHp -= damage;
	}

	Player() { }
	~Player() { }
};