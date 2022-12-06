#pragma once
#include"Framework.h"
#include"GameSceneManagerState.h"

class GameSceneManagerState;

class GameSceneManager
{
public:
	//コンストラクタ
	GameSceneManager();
	//デストラクタ
	~GameSceneManager();

	void Initialize(DebugCamera *camera, Audio *audio, Fps *fps);
	void Update(DebugText *debugText, Audio *audio, LightGroup *lightGroup, DebugCamera *camera, Fps *fps);
	void Draw(DirectXApp *common, DebugText *debugText);

	void changeState(GameSceneManagerState* newState, DebugCamera *camera, Audio *audio, Fps *fps);

private:
	GameSceneManagerState *state;
};

