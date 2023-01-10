#pragma once
#include "GameSceneManagerState.h"

class GameOverScene : public GameSceneManagerState
{
private:
	Sprite *EndSprite = nullptr;
public:
	GameOverScene(const int stageNum = 0) { }
	~GameOverScene()
	{
		delete EndSprite;
		EndSprite = nullptr;
	}
	void Initialize(GameSceneManager *pEngine, DebugCamera *camera, Audio *audio, Fps *fps);
	void Update(GameSceneManager *pEngine, Audio *audio, DebugText *debugText, LightGroup *lightGroup, DebugCamera *camera, Fps *fps);
	void Draw(GameSceneManager *pEngine, DirectXApp *common, DebugText *debugText);
};

