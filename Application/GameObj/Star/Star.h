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
	
	//�X�^�[�擾�����Ƃ�
	void GetStar();

	//�����o��
	void Moveing();
	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update() override;
	void Draw() override;

	const bool &GetMoveingFlag() { return moveingFlag; }
private:
	//�����邩�����̃t���O
	bool toNotDisplay;
	//�����o���t���O
	bool moveingFlag;
};