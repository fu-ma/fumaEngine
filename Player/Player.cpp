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
	jumpChange = 0;
	jumpChangeTimer = 0;
	return true;
}

void Player::Update()
{
	Input* input = Input::GetInstance();
	Controller *controller = Controller::GetInstance();

	//重力処理
	if (speed > gravity * 40)
	{
		speed += gravity / 5;
	}
	position.y += speed;

	//1.2.3段ジャンプ処理
	if (jumpChange == 0)
	{
		jumpMax = 40;
	}
	if (jumpChange == 1)
	{
		jumpMax = 60;
	}
	if (jumpChange == 2)
	{
		jumpMax = 100;
	}

	//移動処理
	if (input->isKey(DIK_A) || controller->PushButton(static_cast<int>(Button::LEFT)) == true)
	{
		position.x -= 0.1f;
	}
	else if (input->isKey(DIK_D) || controller->PushButton(static_cast<int>(Button::RIGHT)) == true)
	{
		position.x += 0.1f;
	}
	if (jumpFlag == false)
	{
		if (input->isKey(DIK_SPACE) || controller->PushButton(static_cast<int>(Button::A)) == true)
		{
			if (jumpTimer < jumpMax)
			{
				position.y += jump;
			}
			jumpTimer++;

			if (jumpChangeTimer > 0 && jumpChangeTimer < 30)
			{
				jumpChange++;
				jumpChangeTimer = 0;
			}
			else if (jumpChangeTimer > 30)
			{
				jumpChange = 0;
				jumpChangeTimer = 0;
			}
		}
	}

	if (jumpTimer > 0 && (!(input->isKey(DIK_SPACE))) && !(controller->PushButton(static_cast<int>(Button::A)) == true))
	{
		jumpFlag = true;
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

	//空中処理
	if (speed < gravity && (!(input->isKey(DIK_SPACE))) && !(controller->PushButton(static_cast<int>(Button::A)) == true))
	{
		jumpFlag = true;
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
		speed = gravity / 4;
		//着地しているときのみジャンプを可能にする
		if ((!(input->isKey(DIK_SPACE))) && !(controller->PushButton(static_cast<int>(Button::A)) == true))
		{
			jumpChangeTimer++;
			jumpTimer = 0;
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
		jumpFlag = true;
	}
}
