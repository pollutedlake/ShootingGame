#pragma once
#include "Enemy.h"


class Minion1 : public Enemy
{
private:
	int _count;

public:
	void move(void);

	Minion1();
	~Minion1();
};

