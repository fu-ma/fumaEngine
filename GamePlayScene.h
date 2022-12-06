#pragma once
#include "GameSceneManagerState.h"

class GamePlayScene : public GameSceneManagerState
{
public:
	GamePlayScene(const int stageNum = 0) { this->stageNum = stageNum; }
	void Initialize(GameSceneManager *pEngine, DebugCamera *camera, Audio *audio, Fps *fps);
	void Update(GameSceneManager *pEngine, Audio *audio, DebugText *debugText, LightGroup *lightGroup, DebugCamera * camera, Fps *fps);
	void Draw(GameSceneManager *pEngine, DirectXApp *common, DebugText *debugText);

private:
#pragma region ステージセット
	void StageSet(const int Map[Y_MAX][X_MAX], const int stageNum, Audio *audio, Fps *fps);

#pragma region 共通更新関数
	void StageUpdate(GameSceneManager *pEngine, Audio *audio, DebugText *debugText, LightGroup *lightGroup, DebugCamera *camera, Fps *fps);

#pragma region 共通描画関数
	void StageDraw(DirectXApp* common,DebugText *debugText);

private:
	int stageNum;
};

