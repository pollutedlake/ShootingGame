#pragma once
#include "GameNode.h"
#include "Bullets.h"
#include "Animation.h"
#include "Items.h"

enum Pattern
{
	Pattern1,
	Pattern2,
	Pattern3,
	Pattern4,
	Pattern5,
	Pattern6
};

class Player;

class Boss : public GameNode
{
protected:
	Animation* _ani;
	GImage* _image;
	RECT _rc;
	Bullet* _bullet;
	Bullet* _bullet2;
	Player* _player;
	Pattern _pattern;

	Power* _power;

	int _hp;

	int _currentFrameX;
	int _currentFrameY;

	float _x, _y;
	float _worldTimeCount;

	int _activateY;

	float _rndFireCount;
	float _bulletFireCount;
	float _bullet2FireCount;

	int _bulletCount;
	int _bullet2Count;

	bool _active;

	bool _playerLeft;

	vector<tagEffect> _vEffect;
	vector<tagEffect>::iterator _viEffect;

public:
	HRESULT init(void);

	void release(void);
	void update(float y);
	void render(void);

	virtual void move(void);
	void draw(void);
	void animation(void);

	RECT getRect(void) { return _rc; }
	Bullet* getBullet1(void) { return _bullet; }
	Bullet* getBullet2(void) { return _bullet2; }
	Power* getPower(void) {return _power;}

	void removePower(int arrNum);

	void setPlayerMemoryAddress(Player* player) { _player = player; }

	bool getDamaged(RECT rc, int missile, int damage);

	bool bulletCountFire(void);
	bool bullet2CountFire(void);

	void removeBullet(int arrNum);
	void removeBullet2(int arrNum);

	void BossPattern1();
	void BossPattern2();
	void BossPattern3();
	void BossPattern4();
	void BossPattern5();
	void BossPattern6();

	Boss(void);
	~Boss(void) {}
};

