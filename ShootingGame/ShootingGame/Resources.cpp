#include "Stdafx.h"
#include "Resources.h"

HRESULT Resources::init(void)
{
	IMAGEMANAGER->addImage("BattleBG", "./Resources/Images/BattleBG.bmp", 224, 1840);

	return S_OK;
}