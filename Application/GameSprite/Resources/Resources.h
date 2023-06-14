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
	soundData4,
	soundData5,
	soundData6,
	soundData7,
	soundData8,
	soundData9,
	soundData10,
	soundData11,
	soundData12,
	soundData13,
	soundData14,
	modelPlayer,
	modelCloud,
	modelStageBox,
	modelEnemy,
	modelThornEnemy,
	modelRedBlock,
	modelBlueBlock,
	modelWireBlock,
	modelGoal,
	modelSignboard,
	modelSignboardA,
	modelSignboardSpace,
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
	modelFire,
	modelStar,
	modelBluePlayer,
	modelRedPlayer,
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
	SoundData soundData4;
	SoundData soundData5;
	SoundData soundData6;
	SoundData soundData7;
	SoundData soundData8;
	SoundData soundData9;
	SoundData soundData10;
	SoundData soundData11;
	SoundData soundData12;
	SoundData soundData13;
	SoundData soundData14;

	//プレイヤー
	std::unique_ptr<Model> modelPlayer;
	std::unique_ptr<Model> modelBluePlayer;
	std::unique_ptr<Model> modelRedPlayer;

	//チュートリアル用の看板
	std::unique_ptr<Model> modelSignboard;
	std::unique_ptr<Model> modelSignboardA;
	std::unique_ptr<Model> modelSignboardSpace;

	//雲
	std::unique_ptr<Model> modelCloud;

	//ステージブロック
	std::unique_ptr<Model> modelStageBox;
	//敵
	std::unique_ptr<Model> modelEnemy;
	std::unique_ptr<Model> modelThornEnemy;

	//一定時間で切り替わる床
	std::unique_ptr<Model> modelRedBlock;
	std::unique_ptr<Model> modelBlueBlock;
	std::unique_ptr<Model> modelWireBlock;

	//ゴール
	std::unique_ptr<Model> modelGoal;

	//背景用の見栄えをよくするためのもの
	std::unique_ptr<Model> modelBackObj1;
	std::unique_ptr<Model> modelBackObj2;
	std::unique_ptr<Model> modelBackObj3;

	//エフェクト用の卵の殻
	std::unique_ptr<Model> modelEggShell;

	//プレイヤーの移動時のパーティクル
	std::unique_ptr<Model> modelParticle;

	//壁キック時のパーティクル
	std::unique_ptr<Model> modelExplosionLeftParticle;
	std::unique_ptr<Model> modelExplosionRightParticle;

	//ジャンプ時のパーティクル
	std::unique_ptr<Model> modelExplosionUpParticle;

	//火の玉のモデル
	std::unique_ptr<Model> modelFire;
	
	//とげこん棒用
	std::unique_ptr<Model> modelThornStick;

	//星用のモデル
	std::unique_ptr<Model> modelStar;

	//設定したリソースを読み込まなかった場合エラーを出るようにする
	SoundData sound;
	std::unique_ptr<Model> model;

	//egg用のモデル
	FBXModel *modelEgg;

	//GameClear用のモデル
	FBXModel *modelStageClear;
private:
	Resources() = default;
	~Resources() = default;
};

