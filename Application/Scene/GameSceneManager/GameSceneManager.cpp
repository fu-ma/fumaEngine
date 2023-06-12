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
	keepState = new TitleScene();
	inputFlag = false;
	deleteFlag = false;
}

GameSceneManager::~GameSceneManager()
{
	delete state;
}

void GameSceneManager::Initialize(DebugCamera* camera, Audio *audio, Fps *fps)
{
	if (inputFlag == false)
	{
		newState();
		state->Initialize(this, camera, audio, fps);
		inputFlag = true;
	}
}

void GameSceneManager::Update(DebugText *debugText, Audio *audio, LightGroup *lightGroup, DebugCamera *camera, Fps *fps)
{
	state->Update(this, audio, debugText, lightGroup, camera, fps);
}

void GameSceneManager::Draw(DirectXApp *common, DebugText *debugText)
{
	state->Draw(this,common,debugText);
}

void GameSceneManager::changeState(GameSceneManagerState *newState)
{
	deleteFlag = true;
	keepState = newState;
}

void GameSceneManager::newState()
{
	state = keepState;
}

void GameSceneManager::StateDelete()
{
	if (deleteFlag == true)
	{
		delete state;
		state = nullptr;
		inputFlag = false;
		deleteFlag = false;
	}
}
