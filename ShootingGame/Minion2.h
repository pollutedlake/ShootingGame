#pragma once
#include "Enemy.h"


class Minion2 : public Enemy
{
private:
	int _count;
	float _destX;
	float _destY;

public:
	HRESULT init(const char* imageName, float startX, float startY, float destX, float destY, int activeY, int hp);
	void move(void);

	Minion2();
	~Minion2();
};

