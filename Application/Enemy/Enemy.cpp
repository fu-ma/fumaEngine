#include "Enemy.h"
#include"Engine/Input/Input.h"
#include"Engine/Input/Controller.h"
#include"Resources.h"

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
	Resources *resources = Resources::GetInstance();
	if (!ModelObj::Initialize())
	{
		return false;
	}

	HP = 1;
	angleSpeed = -0.03f;
	jumpTimer = 60;
	jump = 0.1f;
	fire = ModelObj::Create(resources->GetModel(ResourcesName::modelFire));
	fire->Initialize();
	fire->SetPosition(position);
	shotFlag = false;
	shotTimer = 0;
	fireScale = { 0.5f,0.5f,0.5f };
	fire->SetScale(fireScale);
	return true;
}

void Enemy::Update()
{
	// 行列の更新など
	ModelObj::Update();
	fire->Update();
}

void Enemy::Move(const XMFLOAT3 &playerPos)
{
	Input *input = Input::GetInstance();
	Controller *controller = Controller::GetInstance();

	//過去の位置を保存
	oldPos = position;

	if (enemyName == "NORMAL")
	{
		//重力処理
		if (speed > gravity * 20)
		{
			speed += gravity / 5;
		}
		position.y += speed;
		position.x += angleSpeed;
	}

	if (enemyName == "JUMP")
	{
		//ジャンプ処理
		if (jumpTimer < 60)
		{
			position.y += jump;
			jumpTimer++;
		}
		//重力処理
		if (speed > gravity * 15)
		{
			speed += gravity / 6;
		}
		position.y += speed;
		position.x += angleSpeed;
	}
	if (enemyName == "FIRE")
	{
		shotTimer++;
		if (shotTimer > 60)
		{
			shotFlag = true;
		}
		if (shotFlag == false)
		{
			fire->SetPosition(position);

			firePosX = fire->GetPosition().x;
			firePosY = fire->GetPosition().y;

			playerPosX = playerPos.x;
			playerPosY = playerPos.y;

			differenceX = playerPosX - firePosX;
			differenceY = playerPosY - firePosY;
			movement = sqrtf(differenceX * differenceX + differenceY * differenceY);
		}
		if (shotFlag == true)
		{
			fireScale.x -= 0.001f;
			fireScale.y -= 0.001f;
			fireScale.z -= 0.001f;

			fire->SetScale(fireScale);
			fire->SetPosition({ fire->GetPosition().x + ((differenceX / movement) * 0.2f), fire->GetPosition().y + ((differenceY / movement) * 0.2f), fire->GetPosition().z });
			if (fire->GetScale().x <= 0.0f)
			{
				shotTimer = 0;
				fireScale.x = 0.5f;
				fireScale.y = 0.5f;
				fireScale.z = 0.5f;
				shotFlag = false;
			}
		}
	}
}

void Enemy::Draw()
{
	if (HP != 0)
	{
		ModelObj::Draw();
	}

	if (shotFlag && HP != 0)
	{
		fire->Draw();
	}
}

void Enemy::CollisionObject(ModelObj *obj2)
{
	XMVECTOR boxPos = XMLoadFloat3(&obj2->GetPosition());
	XMVECTOR boxRad = XMLoadFloat3(&obj2->GetScale());

	if (enemyName == "NORMAL" || enemyName == "" || enemyName == "FIRE")
	{
		if (oldPos.x > position.x)
		{
			if (Collision::CheckBox2Box({ position.x - 0.1f,position.y - 0.1f,0 },
				{ obj2->GetPosition().x + 0.1f,obj2->GetPosition().y - 0.1f,0 },
				scale.x, scale.y, obj2->GetScale().x, obj2->GetScale().y))
			{
				position =
				{
					boxPos.m128_f32[0] + boxRad.m128_f32[0] + scale.x + 0.11f,
					position.y ,
					0
				};

				angleSpeed = 0.03f;
				rotation.y = 0;
			}
		}
		if (oldPos.x < position.x)
		{
			if (Collision::CheckBox2Box({ position.x + 0.1f,position.y + 0.1f,0 },
				{ obj2->GetPosition().x - 0.1f,obj2->GetPosition().y + 0.1f,0 },
				scale.x, scale.y, obj2->GetScale().x, obj2->GetScale().y))
			{
				position =
				{
					boxPos.m128_f32[0] - boxRad.m128_f32[0] - scale.x - 0.11f,
					position.y ,
					0
				};
				angleSpeed = -0.03f;
				rotation.y = 180;
			}
		}
		if (Collision::CheckBox2Box({ position.x + 0.1f,position.y - 0.1f,0 },
			{ obj2->GetPosition().x + 0.1f,obj2->GetPosition().y + 0.1f,0 },
			scale.x, scale.y, obj2->GetScale().x, obj2->GetScale().y))
		{
			position =
			{
				position.x,
				boxPos.m128_f32[1] + boxRad.m128_f32[0] + scale.x + 0.51f ,
				0
			};
			speed = 0;
		}
	}

	if (enemyName == "JUMP")
	{
		if (oldPos.x > position.x)
		{
			if (Collision::CheckBox2Box({ position.x - 0.1f,position.y - 0.1f,0 },
				{ obj2->GetPosition().x + 0.1f,obj2->GetPosition().y - 0.1f,0 },
				scale.x, scale.y + speed, obj2->GetScale().x, obj2->GetScale().y))
			{
				position =
				{
					boxPos.m128_f32[0] + boxRad.m128_f32[0] + scale.x + 0.11f,
					position.y ,
					0
				};

				angleSpeed = 0.03f;
				rotation.y = 0;
			}
		}
		if (oldPos.x < position.x)
		{
			if (Collision::CheckBox2Box({ position.x + 0.1f,position.y + 0.1f,0 },
				{ obj2->GetPosition().x - 0.1f,obj2->GetPosition().y + 0.1f,0 },
				scale.x, scale.y + speed, obj2->GetScale().x, obj2->GetScale().y))
			{
				position =
				{
					boxPos.m128_f32[0] - boxRad.m128_f32[0] - scale.x - 0.11f,
					position.y ,
					0
				};
				angleSpeed = -0.03f;
				rotation.y = 180;
			}
		}
		if (Collision::CheckBox2Box({ position.x + 0.1f,position.y - 0.1f,0 },
			{ obj2->GetPosition().x + 0.1f,obj2->GetPosition().y + 0.1f,0 },
			scale.x, scale.y + speed, obj2->GetScale().x, obj2->GetScale().y))
		{
			position =
			{
				position.x,
				boxPos.m128_f32[1] + boxRad.m128_f32[0] + scale.x + 0.51f ,
				0
			};
			speed = 0;
			jump = 0.1f;
			jumpTimer = 0;
		}
	}

}

void Enemy::Death()
{
	HP = 0;
}
