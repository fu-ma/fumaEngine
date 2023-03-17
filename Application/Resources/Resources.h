#pragma once
#include"Sprite.h"
#include"Audio.h"
#include"Model.h"
#include"FBXLoader.h"

enum class ResourcesName
{
	soundData1,
	soundData2,
	soundData3,
	modelPlayer,
	modelCloud,
	modelStageBox,
	modelEnemy,
	modelRedBlock,
	modelBlueBlock,
	modelWireBlock,
	modelGoal,
	modelJumpSignA,
	modelJumpSignSpace,
	modelWallSignA,
	modelWallSignSpace,
	modelBackObj1,
	modelBackObj2,
	modelBackObj3,
	modelEggShell,
	modelParticle,
	modelExplosionLeftParticle,
	modelExplosionRightParticle,
	modelExplosionUpParticle,
	modelEgg,
	modelStageClear,
	modelThornStick,
};

class Resources
{
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public: // 静的メンバ変数
	static Resources *GetInstance();

public:
	void StaticInit(Audio *audio);
	SoundData &GetSoundData(ResourcesName resourcesName);
	Model *GetModel(ResourcesName resourcesName);
	FBXModel *GetFBXModel(ResourcesName resourcesName);
private:
	SoundData soundData1;
	SoundData soundData2;
	SoundData soundData3;

	//プレイヤー
	Model *modelPlayer;

	//チュートリアル用の看板
	Model *modelJumpSignA;
	Model *modelJumpSignSpace;
	Model *modelWallSignA;
	Model *modelWallSignSpace;

	//雲
	Model *modelCloud;

	//ステージブロック
	Model *modelStageBox;
	//敵
	Model *modelEnemy;

	//一定時間で切り替わる床
	Model *modelRedBlock;
	Model *modelBlueBlock;
	Model *modelWireBlock;

	//ゴール
	Model *modelGoal;

	//背景用の見栄えをよくするためのもの
	Model *modelBackObj1;
	Model *modelBackObj2;
	Model *modelBackObj3;

	//エフェクト用の卵の殻
	Model *modelEggShell;

	//プレイヤーの移動時のパーティクル
	Model *modelParticle;

	//壁キック時のパーティクル
	Model *modelExplosionLeftParticle;
	Model *modelExplosionRightParticle;

	//ジャンプ時のパーティクル
	Model *modelExplosionUpParticle;

	//とげこん棒用
	Model *modelThornStick;
	//設定したリソースを読み込まなかった場合エラーを出るようにする
	SoundData sound;
	Model *model;

	//egg用のモデル
	FBXModel *modelEgg;

	//GameClear用のモデル
	FBXModel *modelStageClear;
private:
	Resources() = default;
	~Resources() = default;
};

