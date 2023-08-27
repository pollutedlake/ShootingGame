#pragma once
#include "GameNode.h"

struct tagItem
{
	GImage* img;
	RECT rc;
	float moveDist;
	int count;
	float exX, exY;
	float x, y;
	float fireX, fireY;
	float angle;
	float speed;
	int frameX, frameY;
};

class Power : public GameNode
{
private:
	vector<tagItem> _vItem;
	vector<tagItem>::iterator _viItem;

	float _range;

public:
	HRESULT init(float range);
	void release(void);
	void update(void);
	void render(void);

	void createItem(float x, float y, float angle, float speed);
	void removeItem(int arrNum);
	void draw(void);
	void move(void);

	vector<tagItem> getItem(void) { return _vItem; }

	Power() {};
	~Power() {};
};

class GoldBar : public GameNode
{
private:
	vector<tagItem> _vItem;
	vector<tagItem>::iterator _viItem;

	float _range;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void createItem(float x, float y);
	void removeItem(int arrNum);
	void draw(void);
	void move(void);

	vector<tagItem> getItem(void) { return _vItem; }

	GoldBar() {};
	~GoldBar() {};
};