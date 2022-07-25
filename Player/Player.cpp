#include "Player.h"
#include "Input.h"
#include "DebugText.h"
#include "SphereCollider.h"
#include "ParticleManager.h"
#include "CollisionManager.h"
#include "CollisionAttribute.h"
#include"Controller.h"

using namespace DirectX;

Player * Player::Create(Model * model)
{
	// 3Dオブジェクトのインスタンスを生成
	Player* instance = new Player();
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

bool Player::Initialize()
{
	if (!ModelObj::Initialize())
	{
		return false;
	}
	
	speed = 0;
	return true;
}

void Player::Update()
{
	Input* input = Input::GetInstance();
	Controller *controller = Controller::GetInstance();

	if (speed > gravity * 50)
	{
		speed += gravity / 5;
	}
	position.y += speed;
	position.x += moveSpeed;
	if (input->isKey(DIK_A) || controller->PushButton(static_cast<int>(Button::LEFT)) == true)
	{
		moveSpeed = -0.1f;
	}
	else if (input->isKey(DIK_D) || controller->PushButton(static_cast<int>(Button::RIGHT)) == true)
	{
		moveSpeed = 0.1f;
	}
	else
	{
		moveSpeed *= 0.9f;
	}

	if (jumpAliveTimer == 0)
	{
		if (input->isKey(DIK_SPACE) || controller->PushButton(static_cast<int>(Button::A)) == true)
		{
			jumpFlag = true;
			if (jumpTimer < 40)
			{
				position.y += jump;
			}
			jumpTimer++;
		}
		else
		{
			//空中のジャンプ制限
			jumpAliveTimer = 1;
			jumpFlag = false;
		}
	}

	if (jumpFlag == true && jumpTimer > 40)
	{
		jumpAliveTimer = 1;
	}

	if (jumpFlag == false)
	{
		jumpAliveTimer = 0;
	}

	// 行列の更新など
	ModelObj::Update();
}

void Player::CollisionObj(ModelObj *obj2)
{
	Input *input = Input::GetInstance();
	Controller *controller = Controller::GetInstance();

	XMVECTOR boxPos = XMLoadFloat3(&obj2->GetPosition());
	XMVECTOR distance = { position.x - boxPos.m128_f32[0],0,0 };
	XMVECTOR boxRad = XMLoadFloat3(&obj2->GetScale());

	if (speed < gravity && jumpFlag == false)
	{
		jumpAliveTimer = 1;
	}
	if (input->isKey(DIK_A) || controller->PushButton(static_cast<int>(Button::LEFT)) == true)
	{
		if (Collision::CheckBox2Box({ position.x - 0.1f,position.y - 0.1f,0 },
			{ obj2->GetPosition().x + 0.1f,obj2->GetPosition().y - 0.1f,0 },
			scale.x, obj2->GetScale().x))
		{
			position =
			{
				boxPos.m128_f32[0] + boxRad.m128_f32[0] + scale.x + 0.11f,
				position.y ,
				0
			};
		}
	}
	if (input->isKey(DIK_D) || controller->PushButton(static_cast<int>(Button::RIGHT)) == true)
	{
		if (Collision::CheckBox2Box({ position.x + 0.1f,position.y + 0.1f,0 },
			{ obj2->GetPosition().x - 0.1f,obj2->GetPosition().y + 0.1f,0 },
			scale.x, obj2->GetScale().x))
		{
			position =
			{
				boxPos.m128_f32[0] - boxRad.m128_f32[0] - scale.x - 0.11f,
				position.y ,
				0
			};
		}
	}
	if (Collision::CheckBox2Box({ position.x + 0.1f,position.y - 0.1f,0 },
		{ obj2->GetPosition().x + 0.1f,obj2->GetPosition().y + 0.1f,0 },
		scale.x, obj2->GetScale().x))
	{
		position =
		{
			position.x,
			boxPos.m128_f32[1] + boxRad.m128_f32[0] + scale.x + 0.01f ,
			0
		};
		speed = gravity / 5;
		jumpTimer = 0;
		//着地しているときのみジャンプを可能にする
		if ((!(input->isKey(DIK_SPACE))) && !(controller->PushButton(static_cast<int>(Button::A)) == true))
		{
			jumpFlag = false;
		}
	}
	if (Collision::CheckBox2Box({ position.x - 0.1f,position.y + 0.1f,0 },
		{ obj2->GetPosition().x - 0.1f,obj2->GetPosition().y - 0.1f,0 },
		scale.x, obj2->GetScale().x))
	{
		position =
		{
			position.x,
			boxPos.m128_f32[1] - boxRad.m128_f32[0] - scale.x - 0.001f - jump ,
			0
		};
		jumpAliveTimer = 1;
	}
}
