#pragma once
#include "GameSceneManagerState.h"

class SelectScene : public GameSceneManagerState
{
public:
	SelectScene(const int stageNum = 0) {  }
	void Initialize(GameSceneManager *pEngine, DebugCamera *camera, Audio *audio, Fps *fps);
	void Update(GameSceneManager *pEngine, Audio *audio, DebugText *debugText, LightGroup *lightGroup, DebugCamera *camera, Fps *fps);
	void Draw(GameSceneManager *pEngine, DirectXApp *common, DebugText *debugText);
};