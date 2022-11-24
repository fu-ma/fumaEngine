#pragma once
#include "ModelObj.h"
#include"Collision.h"

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
	void CollisionObject(ModelObj *obj2);

	//�G�̏�Ԃ��Z�b�g
	void SetAction(const std::string &enemyName) { this->enemyName = enemyName; }

	const int &GetHP() { return HP; }
	const float &GetSpeed() { return speed; }
	void Death();
private:
	int HP = 1;
	const float gravity = (-9.8f / 60 / 20);
	//const float gravity = (-9.8f / 60 / 40);
	//�d�͂����Z���邽�߂̃X�s�[�h
	float speed;
	float angleSpeed;
	XMFLOAT3 oldPos;

	//�҂��҂�񂷂�G
	int jumpTimer;
	float jump;

	//�������Z�b�g���邽�߂̕ϐ�
	std::string enemyName;
};

