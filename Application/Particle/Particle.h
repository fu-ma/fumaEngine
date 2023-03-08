#pragma once
#include"Engine/3dModel/ModelObj.h"

enum class TYPE
{
	explosion = 0,
	move,
	LEFT,
	RIGHT,
	explosionLEFT,
	explosionRIGHT,
	explosionUP,
};
class Particle
{
	using XMVECTOR = DirectX::XMVECTOR;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
private:
	//パーティクル最大数
	static const int PARTICLE_NUM = 20;

private:
	ModelObj *particle[PARTICLE_NUM];
	XMFLOAT3 particlePos[PARTICLE_NUM];
	XMFLOAT3 particleScale[PARTICLE_NUM];
	XMFLOAT3 vel[PARTICLE_NUM];

	bool moveFlag[PARTICLE_NUM];
	bool setFlag;
	int time;
public:
	Particle()
	{
		for (int i = 0; i < PARTICLE_NUM; i++)
		{
			particle[i] = nullptr;
			particlePos[i] = { 0,0,0 };
			vel[i] = { 0,0,0 };
			moveFlag[i] = false;
		}
		setFlag = false;
	}

	~Particle()
	{
		for (int i = 0; i < PARTICLE_NUM; i++)
		{
			delete particle[i];
			particle[i] = nullptr;
		}
	}
	/// <summary>
	/// 初期化
	/// </summary>
	/// <returns>成否</returns>
	bool Initialize(Model *model);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Set(const XMFLOAT3 &particlePos, const XMFLOAT3 &rotation = {});
	void Update(const TYPE &type, const XMFLOAT3 &particlePos);
	void Draw();

	void SetPositionAll(XMFLOAT3 pos)
	{
		for (int i = 0; i < PARTICLE_NUM; i++)
		{
			particle[i]->SetPosition(pos);
		}
	}

	void SetPosition(int particleNum,XMFLOAT3 pos)
	{
		particle[particleNum]->SetPosition(pos);
	}

	void SetFlag(bool setFlag)
	{
		this->setFlag = setFlag;
	}

	const bool &GetFlag() { return setFlag; }
};

