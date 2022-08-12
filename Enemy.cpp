#include "Enemy.h"

Enemy *Enemy::Create(Model *model)
{
	// 3Dオブジェクトのインスタンスを生成
	Enemy *instance = new Enemy();
	if (instance == nullptr) {
		return nullptr;
	}

	// 初期化
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
	// 行列の更新など
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
