#pragma once
#include "ModelObj.h"
#include"easing.h"

class ThornStick : public ModelObj
{
public:
	/// <summary>
	/// 3D�I�u�W�F�N�g����
	/// </summary>
	/// <returns></returns>
	static ThornStick *Create(Model *model = nullptr);

public:
	void Move();

	/// <summary>
	/// ������
	/// </summary>
	/// <returns>����</returns>
	bool Initialize() override;

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update() override;

	void Draw() override;

	void SetOldStickPos(const XMFLOAT3 &pos) { this->oldPosY = pos.y; }
private:
	//�����𐧌����邽�߂̎���
	int timer;
	//�C�[�W���O�p
	double moveX;
	double moveY;
	double rotateY;
	double moveStartT;
	double moveT;
	double moveEndT;
	double posY;
	//�����ʒu��ۑ����邽�߂̕ϐ�
	double oldPosY;
};

