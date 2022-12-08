#include "GameSceneManager.h"
#include "ClearScene.h"
#include "TitleScene.h"
#include "GamePlayScene.h"
#include "EndScene.h"
#include"EndScene.h"
#include"SelectScene.h"
#include"GameOverScene.h"
#include"GamePlayScene.h"

GameSceneManager::GameSceneManager()
{
	state = new TitleScene();
}

GameSceneManager::~GameSceneManager()
{
	delete state;
}

void GameSceneManager::Initialize(DebugCamera* camera, Audio *audio, Fps *fps)
{
	state->Initialize(this,camera,audio,fps);
}

void GameSceneManager::Update(DebugText *debugText, Audio *audio, LightGroup *lightGroup, DebugCamera *camera, Fps *fps)
{
	state->Update(this, audio, debugText, lightGroup, camera, fps);
}

void GameSceneManager::Draw(DirectXApp *common, DebugText *debugText)
{
	state->Draw(this,common,debugText);
}

void GameSceneManager::changeState(GameSceneManagerState *newState, DebugCamera *camera, Audio *audio, Fps *fps)
{
	delete state;
	state = newState;
	state->Initialize(this, camera, audio, fps);
}
