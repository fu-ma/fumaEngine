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
}
