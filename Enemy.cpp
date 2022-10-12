#include "Enemy.h"
#include "Input.h"
#include"Controller.h"

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
	Input *input = Input::GetInstance();
	Controller *controller = Controller::GetInstance();

	//�ߋ��̈ʒu��ۑ�
	oldPos = position;

	//�d�͏���
	if (speed > gravity * 20)
	{
		speed += gravity / 5;
	}
	position.y += speed;

}

void Enemy::Draw()
{
	if (HP != 0)
	{
		ModelObj::Draw();
	}
}

void Enemy::CollisionObject(ModelObj *obj2)
{
	XMVECTOR boxPos = XMLoadFloat3(&obj2->GetPosition());
	XMVECTOR boxRad = XMLoadFloat3(&obj2->GetScale());

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
		}
	}
	if (Collision::CheckBox2Box({ position.x + 0.1f,position.y - 0.1f,0 },
		{ obj2->GetPosition().x + 0.1f,obj2->GetPosition().y + 0.1f,0 },
		scale.x, scale.y + 0.5f + speed, obj2->GetScale().x, obj2->GetScale().y))
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

void Enemy::Deth()
{
	HP = 0;
}
