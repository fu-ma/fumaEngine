#pragma once
#include "ModelObj.h"
class Enemy : public ModelObj
{
	using XMVECTOR = DirectX::XMVECTOR;
	using XMFLOAT4 = DirectX::XMFLOAT4;
public:
	/// <summary>
	/// 3D�I�u�W�F�N�g����
	/// </summary>
	/// <returns></returns>
	static Enemy *Create(Model *model = nullptr);
public:

	/// <summary>
	/// ������
	/// </summary>
	/// <returns>����</returns>
	bool Initialize() override;

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update() override;
	void Move();
	void Draw() override;

	const int &GetHP() { return HP; }
	void Deth();
private:
	int HP = 1;

};

