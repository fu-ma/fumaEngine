#pragma once
#include "GameSceneManagerState.h"

class ClearScene : public GameSceneManagerState
{
private:
	Sprite *StageClear = nullptr;
public:
	ClearScene(const int stageNum = 0) { }
	~ClearScene()
	{
		delete StageClear;
		StageClear = nullptr;
	}
	void Initialize(GameSceneManager *pEngine, DebugCamera *camera, Audio *audio, Fps *fps);
	void Update(GameSceneManager *pEngine, Audio *audio, DebugText *debugText, LightGroup *lightGroup, DebugCamera *camera, Fps *fps);
	void Draw(GameSceneManager *pEngine, DirectXApp *common, DebugText *debugText);
};

