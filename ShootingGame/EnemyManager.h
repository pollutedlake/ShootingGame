#pragma once
#include "GameNode.h"
#include "Enemy.h"
#include "Bullets.h"
#include "Items.h"

class Player;

class EnemyManager : public GameNode
{
private:
	typedef vector<Enemy*> vEnemy;
	typedef vector<Enemy*>::iterator viEnemy;

	vector<tagEffect> _vEffect;
	vector<tagEffect>::iterator _viEffect;

	Power* _power;
	GoldBar* _goldBar;

private:
	vEnemy _vMinion;
	viEnemy _viMinion;
	Bullet* _bullet;
	Player* _player;

public:
	HRESULT init(void);
	void release(void);
	void update(int y);
	void render(void);

	void setMinion(void);
	void removeMinion(int arrNumm, int missile, int damage, int* score);
	void removePower(int arrNum);
	void removeGoldBar(int arrNum);

	void minionBulletFire(void);

	vector<Enemy*> getMinions(void) {return _vMinion;}
	Bullet* getBullet(void) {return _bullet;}
	Power* getPower(void) {return _power;}
	GoldBar* getGoldBar(void) {return _goldBar;}
	void setPlayerMemoryAddress(Player* player) { _player = player;}

	EnemyManager();
	~EnemyManager();
};

