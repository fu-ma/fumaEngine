#pragma once
#include "GameSceneManagerState.h"

class SelectScene : public GameSceneManagerState
{
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
private:
	Sprite *backGround = nullptr;
	Sprite *Stage1Sprite = nullptr;
	Sprite *Stage2Sprite = nullptr;
	Sprite *Stage3Sprite = nullptr;
	Sprite *Stage4Sprite = nullptr;
	Sprite *Stage5Sprite = nullptr;
	Sprite *playerIconSprite = nullptr;

	//雲
	ModelObj *cloud[10] = { nullptr };
	XMFLOAT3 cloudPos[10] = {};

	//敵
	Enemy *enemy[Y_MAX][X_MAX] = { nullptr };

	//プレイヤー
	Player *objPlayer = nullptr;

	//ステージブロック
	ModelObj *objStageBox[Y_MAX][X_MAX] = { nullptr };
	ModelObj *titleStageBox[6][24] = { nullptr };
	XMFLOAT3 stageBoxPos[6][24];
public:
	SelectScene(const int stageNum = 0) {  }
	void Initialize(GameSceneManager *pEngine, DebugCamera *camera, Audio *audio, Fps *fps);
	void Update(GameSceneManager *pEngine, Audio *audio, DebugText *debugText, LightGroup *lightGroup, DebugCamera *camera, Fps *fps);
	void Draw(GameSceneManager *pEngine, DirectXApp *common, DebugText *debugText);
};