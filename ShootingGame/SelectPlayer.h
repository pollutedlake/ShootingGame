#pragma once
#include "GameNode.h"

class SelectPlayer : public GameNode
{
private:
	GImage* _bgImg;
	int _frameX, _frameY;
	float _timeCount;

	GImage* _black;
	int _blackAlpha;

	bool _choice;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};

