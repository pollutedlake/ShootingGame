#pragma once
#include "GameNode.h"
#include "Player.h"
#include "Boss.h"
#include "EnemyManager.h"

class BattleScene : public GameNode
{
private:
	GImage* _uiImg;
	GImage* _bgImg;
	GImage* _black;
	GImage* _scoreImg;
	float _bgSpeed;
	float _x, _y;

	Player* _player;
	EnemyManager* _em;
	Boss* _boss;

	bool _isClear;

	int _score;
	int _blackAlpha;

public:
	
	HRESULT init(void);
	void update(void);
	void release(void);
	void render(void);

	virtual void collision(void);

	BattleScene() {}
	~BattleScene() {}
};

