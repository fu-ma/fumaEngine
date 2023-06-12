#pragma once
#include "GameSceneManagerState.h"
#include"ParticleManager.h"

class ClearScene : public GameSceneManagerState
{
	using XMFLOAT3 = DirectX::XMFLOAT3;
private:
	std::unique_ptr<Sprite> StageClear;
	std::unique_ptr<Sprite> fadeOut;
	std::unique_ptr<Sprite> fadeIn;
	std::unique_ptr<FBXObject3d> egg;
	std::unique_ptr<FBXObject3d> gameClear;
	ParticleManager *particleMan = nullptr;

	//開始時のフェイドアウト用変数
	double fadeOutSizeX;
	double fadeOutSizeY;
	double fadeOutT;
	bool fadeOutFlag;

	//開始時のフェイドイン用変数
	double fadeInSizeX;
	double fadeInSizeY;
	double fadeInT;
	bool fadeInFlag;

	//ステージセレクトに行ったか判断するためのフラグ
	bool goSelectFlag;

	//パーティクル用の座標
	XMFLOAT3 parPosLeft;
	XMFLOAT3 parPosRight;
	float saveVel;
	int particleTimer;
public:
	ClearScene(const int stageNum = 0) { }
	~ClearScene()
	{
	}
	void Initialize(GameSceneManager *pEngine, DebugCamera *camera, Audio *audio, Fps *fps);
	void Update(GameSceneManager *pEngine, Audio *audio, DebugText *debugText, LightGroup *lightGroup, DebugCamera *camera, Fps *fps);
	void Draw(GameSceneManager *pEngine, DirectXApp *common, DebugText *debugText);
};

