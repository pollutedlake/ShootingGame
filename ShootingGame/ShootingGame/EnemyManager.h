#pragma once
#include "GameNode.h"
#include "Enemy.h"
#include "Bullets.h"

class Player;

class EnemyManager : public GameNode
{
private:
	typedef vector<Enemy*> vEnemy;
	typedef vector<Enemy*>::iterator viEnemy;

private:
	vEnemy _vMinion;
	viEnemy _viMinion;
	Bullet* _bullet;
	Player* _player;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void setMinion(void);
	void removeMinion(int arrNum);

	void minionBulletFire(void);
	void collision(void);

	vector<Enemy*> getMinions(void) {return _vMinion;}
	Bullet* getBullet(void) {return _bullet;}
	void setRocketMemoryAddress(Player* player) { _player = player;}

	EnemyManager();
	~EnemyManager();
};

