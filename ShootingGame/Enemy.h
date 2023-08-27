#pragma once
#include "GameNode.h"

class Enemy : public GameNode
{
protected:
	GImage* _image;
	RECT _rc;
	int _hp;

	int _currentFrameX;
	int _currentFrameY;

	float _x, _y;
	float _rndTimeCount;
	float _worldTimeCount;

	float _rndFireCount;
	float _bulletFireCount;

	int _activateY;

	bool _active;
	bool _inactive;

public:
	HRESULT init(void);
	HRESULT init(const char* imageName, POINT position, int activeY, int hp);
	virtual HRESULT init(const char* imageName, float startX, float startY, float x, float y, int activeY, int hp);
	virtual HRESULT init(const char* imageName, float startX, float startY, bool isLeft, int activeY, int hp);

	void release(void);
	void update(void);
	void render(void);

	virtual void move(void);
	void draw(void);
	void animation(void);

	RECT getRect(void) { return _rc; }

	bool getDamaged(int damage);

	bool bulletCountFire(void);

	int getActivateY() {return _activateY;}
	void setActive(bool active) {_active = active;}
	bool getActive() {return _active;}
	bool isInActive() {return _inactive;}
	POINT getPosition() {return {(LONG)_x, (LONG)_y}; }

	Enemy(void);
	~Enemy(void) {}
};

