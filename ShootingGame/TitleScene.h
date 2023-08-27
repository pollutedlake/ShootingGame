#pragma once
#include "GameNode.h"

class TitleScene : public GameNode
{
private:
	GImage* _bgImg;
	GImage* _startButton;
	int _bgSpeed;
	int _buttonAlpha;
	bool _alphaIncrease;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};

