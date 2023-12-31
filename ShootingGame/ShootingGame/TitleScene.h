#pragma once
#include "GameNode.h"

class TitleScene : public GameNode
{
private:
	GImage* _bgImg;
	int _bgSpeed;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};

