#pragma once
#include "Enemy.h"


class Minion3 : public Enemy
{
private:
	int _count;
	float _angle;
	float _radius;
	bool _isLeft;

public:
	HRESULT init(const char* imageName, float startX, float startY, bool isLeft, int activeY, int hp);
	void move(void);

	Minion3();
	~Minion3();
};

