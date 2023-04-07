#pragma once
#include "ModelObj.h"
#include"Collision.h"
#include<math.h>

class Star : public ModelObj
{
	using XMVECTOR = DirectX::XMVECTOR;
	using XMFLOAT4 = DirectX::XMFLOAT4;
public:
	/// <summary>
	/// 3D�I�u�W�F�N�g����
	/// </summary>
	/// <returns></returns>
	static Star *Create(Model *model = nullptr);
public:

	/// <summary>
	/// ������
	/// </summary>
	/// <returns>����</returns>
	bool Initialize() override;
	
	void GetStar();
	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update() override;
	void Draw() override;
private:
	bool toNotDisplay;
};