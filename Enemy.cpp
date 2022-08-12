#include "Enemy.h"

Enemy *Enemy::Create(Model *model)
{
	// 3D�I�u�W�F�N�g�̃C���X�^���X�𐶐�
	Enemy *instance = new Enemy();
	if (instance == nullptr) {
		return nullptr;
	}

	// ������
	if (!instance->Initialize()) {
		delete instance;
		assert(0);
	}

	if (model) {
		instance->SetModel(model);
	}

	return instance;
}

bool Enemy::Initialize()
{
	if (!ModelObj::Initialize())
	{
		return false;
	}

	HP = 1;
	return true;
}

void Enemy::Update()
{
	// �s��̍X�V�Ȃ�
	ModelObj::Update();
}

void Enemy::Move()
{
}

void Enemy::Draw()
{
	if (HP != 0)
	{
		ModelObj::Draw();
	}
}

void Enemy::Deth()
{
	HP = 0;
}
