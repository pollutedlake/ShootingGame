#pragma once
#include "GameNode.h"
#include "Bullets.h"
#include "Animation.h"

#define ROCKET_SPEED 3.0f

#pragma region 스마트 포인터
#pragma endregion

enum EWeapon
{
	MISSILE, BEAM
};

class EnemyManager;

class Player : public GameNode, public std::enable_shared_from_this<Player>
{
private:

	GImage* _image;
	EWeapon _setWeapon;
	EnemyManager* _em;
	Animation* _ani;

	RECT _rc;
	float _x, _y;
	float _currentHp;
	float _maxHp;
	bool _beamIrradiation;

	float _timeElapsed;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void collision(void);
	void setEnemyMemoryAddress(EnemyManager* em) { _em = em; }
	void removeMissile(int arrNum);

	POINT getPosition(void) { return PointMake(_x, _y); }
	RECT getRect(void) { return _rc; }


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