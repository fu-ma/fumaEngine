#pragma once
#include "GameSceneManagerState.h"

class GameOverScene : public GameSceneManagerState
{
private:
	std::unique_ptr<Sprite> EndSprite;
public:
	GameOverScene(const int stageNum = 0) { }
	~GameOverScene()
	{
	}
	void Initialize(GameSceneManager *pEngine, DebugCamera *camera, Audio *audio, Fps *fps);
	void Update(GameSceneManager *pEngine, Audio *audio, DebugText *debugText, LightGroup *lightGroup, DebugCamera *camera, Fps *fps);
	void Draw(GameSceneManager *pEngine, DirectXApp *common, DebugText *debugText);
};

