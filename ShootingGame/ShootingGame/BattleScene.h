#pragma once
#include "GameNode.h"
#include "Player.h"
#include "Animation.h"

class BattleScene : public GameNode
{
private:
	GImage* _bgImg;
	Animation* _ani;
	float _bgSpeed;
	float _y;

	Player* _player;

public:
	
	HRESULT init(void);
	void update(void);
	void release(void);
	void render(void);

	BattleScene() {}
	~BattleScene() {}
};

