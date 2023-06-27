#include "Zyugemu.h"

Zyugemu *Zyugemu::Create(Model *model)
{
	// 3Dオブジェクトのインスタンスを生成
	Zyugemu *instance = new Zyugemu();
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

bool Zyugemu::Initialize()
{
	if (!ModelObj::Initialize())
	{
		return false;
	}
	pattern = Pattern::SET;
	moveSpeed = 0;

	return true;
}

void Zyugemu::Update()
{
	for (const auto &oneEnemy : enemy)
	{
		oneEnemy->Update();
	}
	// 行列の更新など
	ModelObj::Update();
}

void Zyugemu::Move(const XMFLOAT3 &playerPos)
{
	Resources *resources = Resources::GetInstance();

	if (pattern == Pattern::SET)
	{
		isAttackFlag.push_back(false);
		enemy.push_back(std::make_unique<Enemy>());
		enemy[enemy.size() - 1].reset(Enemy::Create(resources->GetModel(ResourcesName::modelThornEnemy)));
		enemy[enemy.size() - 1]->SetAction("TOGEZOU");
		enemy[enemy.size() - 1]->Initialize();
		enemy[enemy.size() - 1]->SetRotation({ 0,180,0 });
		enemy[enemy.size() - 1]->SetPosition(position);
		moveSpeed = -0.1f;
		moveTime = 0;
		jump = 0;
		gravity = -0.2f;
		togePos = { 0,0,0 };

		this->playerPos = playerPos;
		pattern = Pattern::RESERVE;
	}
	if (pattern == Pattern::RESERVE)
	{
		moveTime++;
		if (position.x <= playerPos.x - 10)
		{
			moveSpeed = 0.1f;
		}
		if (position.x >= playerPos.x + 10)
		{
			moveSpeed = -0.1f;
		}

		enemy[enemy.size() - 1]->SetPosition(position);
		position.x += moveSpeed;

		if (moveTime > 120)
		{
			pattern = Pattern::ATTACK;
		}
	}
	if (pattern == Pattern::ATTACK)
	{
		moveTime++;
		if (moveTime < 160)
		{
			jump += 0.1f;
			if (this->playerPos.x < enemy[enemy.size() - 1]->GetPosition().x)
			{
				togePos.x -= 0.1f;
			}
			if (this->playerPos.x > enemy[enemy.size() - 1]->GetPosition().x)
			{
				togePos.x += 0.1f;
			}

			enemy[enemy.size() - 1]->SetPosition({ position.x + togePos.x,position.y + gravity + jump ,position.z });
		}
		if (moveTime > 160)
		{
			enemy[enemy.size() - 1]->SetMoveSpeed(0);
			isAttackFlag[enemy.size() - 1] = true;
		}
		if (moveTime > 260)
		{
			enemy[enemy.size() - 1]->SetMoveSpeed(-0.03f);
		}

		if (moveTime > 280)
		{
			pattern = Pattern::SET;
		}
	}

	for (int i = 0; i < isAttackFlag.size(); i++)
	{
		if (isAttackFlag[i] == true)
		{
			enemy[i]->Move(playerPos);
		}
	}
}

void Zyugemu::Draw()
{
	ModelObj::Draw();
	for (const auto &oneEnemy : enemy)
	{
		oneEnemy->Draw();
	}
}

void Zyugemu::CollisionObject(ModelObj *obj2)
{
	for (int i = 0; i < isAttackFlag.size(); i++)
	{
		if (isAttackFlag[i] == true)
		{
			enemy[i]->CollisionObject(obj2);
		}
	}
}
