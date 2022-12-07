#pragma once
#include "Singleton.h"
#include"Sprite.h"
#include"Audio.h"
#include"Model.h"

class Resources : public Singleton<Resources>
{
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	friend class Singleton<Resources>;

public:
	static void StaticInit(Audio *audio);

public:
	static SoundData soundData1;
	static SoundData soundData2;
	static SoundData soundData3;

	//プレイヤー
	static Model *modelPlayer;

	//雲
	static Model *modelCloud;

	//ステージブロック
	static Model *modelStageBox;
	//敵
	static Model *modelEnemy;

	//一定時間で切り替わる床
	static Model *modelRedBlock;
	static Model *modelBlueBlock;
	static Model *modelWireBlock;

	//ゴール
	static Model *modelGoal;

protected:
	Resources();
	virtual ~Resources();
};

