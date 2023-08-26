#pragma once
#include "Enemy.h"


class Minion : public Enemy
{
private:
	float _angle;
	int _count;
	int _radius;

public:
	HRESULT init(const char* imageName, POINT center, int radius, float angle);
	void move(void);


	Minion();
	~Minion();
};

