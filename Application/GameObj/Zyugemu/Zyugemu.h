#pragma once
#include"Enemy.h"
#include"ModelObj.h"
#include"Resources.h"

class Zyugemu : public ModelObj
{
	using XMVECTOR = DirectX::XMVECTOR;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMFLOAT3 = DirectX::XMFLOAT3;

	enum Pattern
	{
		SET,
		RESERVE,
		ATTACK,
	};
private:
	std::vector<std::unique_ptr<Enemy>> enemy;
	Pattern pattern;
	//�v���C���[�̈ʒu���Z�b�g�p
	XMFLOAT3 playerPos;
	//�g�Q�]�[�������������Ȃ���
	std::vector<bool> isAttackFlag;

	float moveSpeed;
	int moveTime;
	float gravity;
	float jump;
	XMFLOAT3 togePos;
public:
	/// <summary>
	/// 3D�I�u�W�F�N�g����
	/// </summary>
	/// <returns></returns>
	static Zyugemu *Create(Model *model = nullptr);
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
	void Move(const XMFLOAT3 &playerPos);
	void Draw() override;

	void CollisionObject(ModelObj *obj2);

	Enemy *GetEnemy(const int &num) { return enemy[num].get(); }
	size_t GetALLEnemy() { return enemy.size(); }
};

