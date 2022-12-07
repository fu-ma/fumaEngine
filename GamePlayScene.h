#pragma once
#include "GameSceneManagerState.h"

class GamePlayScene : public GameSceneManagerState
{
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
private:
	Sprite *backGround = nullptr;
	Sprite *goTitle = nullptr;
	Sprite *reStart = nullptr;
	Sprite *Return = nullptr;
	Sprite *playerIconSprite = nullptr;
	Sprite *ClearStageSprite = nullptr;
	Sprite *GameOver = nullptr;

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

	//ギミック
	Firebar *firebar;
	std::vector<Firebar *> fire;

	XMFLOAT3 gimmickCenter[GIMMICK_NUM];
	int gimmickCenterNum;

	//一定時間で切り替わる床
	ModelObj *objRedBlock[Y_MAX][X_MAX];
	ModelObj *objBlueBlock[Y_MAX][X_MAX];

	//ゴール
	ModelObj *objGoal = nullptr;

	//パーティクル
	Particle *playerParticle = nullptr;

	//カウントダウンクラス
	CountDown *countDown = nullptr;

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

