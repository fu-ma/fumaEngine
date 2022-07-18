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

	if (input->isKey(DIK_A) || controller->PushButton(static_cast<int>(Button::LEFT)) == true)
	{
		position.x-= 0.1f;
	}
	else if (input->isKey(DIK_D) || controller->PushButton(static_cast<int>(Button::RIGHT)) == true)
	{
		position.x+= 0.1f;
	}
	// 向いている方向に移動
	if (input->isKey(DIK_S) || controller->PushButton(static_cast<int>(Button::DOWN)) == true)
	{
		position.y-= 0.1f;
	}
	else if (input->isKey(DIK_W) || controller->PushButton(static_cast<int>(Button::UP)) == true)
	{
		position.y += 0.1f;
	}

	// 行列の更新など
	ModelObj::Update();
}

void Player::moveSphere(ModelObj *obj2)
{
	XMVECTOR nowPosition = XMLoadFloat3(&position);
	XMVECTOR spherePosition = XMLoadFloat3(&obj2->GetPosition());
	XMVECTOR sphereRadius = XMLoadFloat3(&obj2->GetScale());
	XMVECTOR distance = nowPosition - spherePosition;
	distance = XMVector3Normalize(distance) * sphereRadius;
	position =
	{
		spherePosition.m128_f32[0] + distance.m128_f32[0],
		spherePosition.m128_f32[1] + distance.m128_f32[1],
		spherePosition.m128_f32[2] + distance.m128_f32[2]
	};
}