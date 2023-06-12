#pragma once
#include "ModelObj.h"
#include"easing.h"

enum class ThornDirection
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

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
	/// �Ƃ��Ƃ��_�̉�]����
	/// </summary>
	void RollingStick();

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update() override;

	void Draw() override;

	void SetOldStickPos(const XMFLOAT3 &pos) { this->oldPosX = pos.x; this->oldPosY = pos.y; }

	void SetDirection(const ThornDirection &direction) { this->direction = direction; }
	const ThornDirection &GetDirection() { return direction; }
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
	double posX;
	//�����ʒu��ۑ����邽�߂̕ϐ�
	double oldPosY;
	double oldPosX;
	//����
	ThornDirection direction = ThornDirection::UP;
};

