#include "WholeScene.h"

WholeScene *WholeScene::GetInstance()
{
	static WholeScene instance;

	return &instance;
}

void WholeScene::StaticInit()
{
	totalPlayerNum = 5;
	selectNum = 0;
	stageNum = 1;
	goTileEaseFlag = false;
	for (int i = 0; i < 5; i++)
	{
		starNum[i] = {0,0,0};
	}
}
