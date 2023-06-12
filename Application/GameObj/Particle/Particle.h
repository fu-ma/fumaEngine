#pragma once
#include<array>
#include"Engine/3d/3dModel/ModelObj.h"

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
	std::array<std::unique_ptr<ModelObj>, PARTICLE_NUM> particle;
	std::array<XMFLOAT3, PARTICLE_NUM> particlePos;
	std::array<XMFLOAT3, PARTICLE_NUM> particleScale;
	std::array<XMFLOAT3, PARTICLE_NUM> vel;

	std::array<bool, PARTICLE_NUM> moveFlag;
	bool setFlag;
	int time;
public:
	Particle()
	{
		setFlag = false;
	}

	~Particle()
	{
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

