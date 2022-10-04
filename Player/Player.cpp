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
	t = 0;
	treadSpeed = 0;
	treadFlag = false;
	notHitFlag = false;
	enemyNotUpFlag = false;
	invincibleFlag = false;
	leftWallJumpFlag = false;
	rightWallJumpFlag = false;
	leftWallJumpTimer = 0;
	rightWallJumpTimer = 0;
	leftWallColFlag = false;
	rightWallColFlag = false;

	invincibleTimer = 0;
	HP = 2;
	rotation.y = 0;
	position.x = 10;
	position.y = 2;
	moveFlag = false;
	return true;
}

void Player::Update()
{
	if (HP == 2)
	{
		scale = { 1.0f,1.0f,1.0f };
	}
	if (HP == 1)
	{
		scale = { 0.7f,0.7f,0.7f };
	}
	if (HP == 0)
	{
		scale = { 0.0f,0.0f,0.0f };
	}
	// 行列の更新など
	ModelObj::Update();
}

void Player::Draw()
{
	if (invincibleTimer % 10 == 0 || invincibleTimer % 15 == 0 || invincibleTimer >= 500)
	{
		ModelObj::Draw();
	}
}

void Player::Move()
{
	Input *input = Input::GetInstance();
	Controller *controller = Controller::GetInstance();

	//重力処理
	if (speed > gravity * 20)
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

	//左壁キック
	if (leftWallJumpFlag == false)
	{
		leftWallJumpTimer = 0;
	}
	if (leftWallJumpFlag == true)
	{
		leftWallJumpTimer++;
		rightWallColFlag = false;
		if (leftWallJumpTimer < wallJumpMax)
		{
			position.y += jump * 1.5f;
			position.x += jump * 1.5f;
			leftWallColFlag = true;
		}
		else if (leftWallJumpTimer > wallJumpMax * 2.5f)
		{
			leftWallJumpFlag = false;
		}
	}

	//右壁キック
	if (rightWallJumpFlag == false)
	{
		rightWallJumpTimer = 0;
	}
	if (rightWallJumpFlag == true)
	{
		rightWallJumpTimer++;
		leftWallColFlag = false;
		if (rightWallJumpTimer < wallJumpMax)
		{
			position.y += jump * 1.5f;
			position.x -= jump * 1.5f;
			rightWallColFlag = true;
		}
		else if (rightWallJumpTimer > wallJumpMax * 2.5f)
		{
			rightWallJumpFlag = false;
		}
	}

	//移動処理
	if (moveFlag == false)
	{
		if (input->isKey(DIK_A) || controller->PushButton(static_cast<int>(Button::LEFT)) == true)
		{
			if (leftWallJumpFlag == false)
			{
				position.x -= 0.1f;
			}

			//プレイヤーの向きを左側にする
			rotation.y = 180;
		}
		else if (input->isKey(DIK_D) || controller->PushButton(static_cast<int>(Button::RIGHT)) == true)
		{
			if (rightWallJumpFlag == false)
			{
				position.x += 0.1f;
			}

			//プレイヤーの向きを右側にする
			rotation.y = 0;
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

				if (jumpChangeTimer > 0 && jumpChangeTimer < 50)
				{
					jumpChange++;
					jumpChangeTimer = 0;
				}
				else if (jumpChangeTimer > 50)
				{
					jumpChange = 0;
					jumpChangeTimer = 0;
				}

				if (jumpMax == 60)
				{
					rotation.z -= 2.5f;
				}
				if (jumpMax == 100)
				{
					rotation.z -= 5;
				}
			}
		}
	}

	if (jumpTimer > 0 && (!(input->isKey(DIK_SPACE))) && !(controller->PushButton(static_cast<int>(Button::A)) == true))
	{
		jumpFlag = true;
	}

	//無敵時間
	if (invincibleFlag == true)
	{
		invincibleTimer++;
		if (invincibleTimer > 300)
		{
			invincibleFlag = false;
			invincibleTimer = 0;
			notHitFlag = false;
		}
	}

	if (treadFlag == true)
	{
		easing::Updete(treadSpeed, 0.4, 2, t);
		position.y += (float)treadSpeed;
		if (treadSpeed >= 0.4)
		{
			t = 0;
			treadSpeed = 0;
			treadFlag = false;
		}
	}

	//エフェクト
	if (onCollisionFlag == true)
	{
		//衝突時にパーティクルを発生させる
		for (int i = 0; i < 5; ++i)
		{
			const float rnd_vel = 0.1f;
			XMFLOAT3 vel{};
			vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
			vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;

			ParticleManager::GetInstance()->Add(100, position, vel, XMFLOAT3(), 1.0f, 0.0f);
		}
		onCollisionFlag = false;
	}
}

void Player::CollisionObj(ModelObj *obj2)
{
	Input *input = Input::GetInstance();
	Controller *controller = Controller::GetInstance();

	XMVECTOR boxPos = XMLoadFloat3(&obj2->GetPosition());
	XMVECTOR boxRad = XMLoadFloat3(&obj2->GetScale());

	//空中処理
	if (speed < gravity && (!(input->isKey(DIK_SPACE))) && !(controller->PushButton(static_cast<int>(Button::A)) == true))
	{
		jumpFlag = true;
	}

	//壁キック後の当たり判定
	if (leftWallColFlag)
	{
		if (Collision::CheckBox2Box({ position.x + 0.1f,position.y + 0.1f,0 },
			{ obj2->GetPosition().x - 0.1f,obj2->GetPosition().y + 0.1f,0 },
			scale.x - jump * 1.5f, scale.y + speed, obj2->GetScale().x, obj2->GetScale().y))
		{
			position =
			{
				boxPos.m128_f32[0] - boxRad.m128_f32[0] - scale.x - 0.11f,
				position.y ,
				0
			};
		}
	}

	if (rightWallColFlag)
	{
		if (Collision::CheckBox2Box({ position.x - 0.1f,position.y - 0.1f,0 },
			{ obj2->GetPosition().x + 0.1f,obj2->GetPosition().y - 0.1f,0 },
			scale.x - jump * 1.5f, scale.y + speed, obj2->GetScale().x, obj2->GetScale().y))
		{
			position =
			{
				boxPos.m128_f32[0] + boxRad.m128_f32[0] + scale.x + 0.11f,
				position.y ,
				0
			};
		}
	}

	if (input->isKey(DIK_A) || controller->PushButton(static_cast<int>(Button::LEFT)) == true)
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

			if (jumpFlag == true)
			{
				speed = gravity * 1.8f;
				rotation.y = 180;
				rotation.z = 0;
				if (input->isKeyTrigger(DIK_SPACE) || controller->TriggerButton(static_cast<int>(Button::A)) == true)
				{
					leftWallJumpFlag = true;
				}
			}
		}
	}
	if (input->isKey(DIK_D) || controller->PushButton(static_cast<int>(Button::RIGHT)) == true)
	{
		if (Collision::CheckBox2Box({ position.x + 0.1f,position.y + 0.1f,0 },
			{ obj2->GetPosition().x - 0.1f,obj2->GetPosition().y + 0.1f,0 },
			scale.x,scale.y + speed, obj2->GetScale().x,obj2->GetScale().y))
		{
			position =
			{
				boxPos.m128_f32[0] - boxRad.m128_f32[0] - scale.x - 0.11f,
				position.y ,
				0
			};

			if (jumpFlag == true)
			{
				speed = gravity * 1.8f;
				rotation.y = 0;
				rotation.z = 0;
				if (input->isKeyTrigger(DIK_SPACE) || controller->TriggerButton(static_cast<int>(Button::A)) == true)
				{
					rightWallJumpFlag = true;
				}
			}
		}
	}
	if (Collision::CheckBox2Box({ position.x + 0.1f,position.y - 0.1f,0 },
		{ obj2->GetPosition().x + 0.1f,obj2->GetPosition().y + 0.1f,0 },
		scale.x, scale.y + speed, obj2->GetScale().x, obj2->GetScale().y))
	{
		position =
		{
			position.x,
			boxPos.m128_f32[1] + boxRad.m128_f32[0] + scale.x + 0.01f ,
			0
		};
		speed = 0;
		rotation.z = 0.0f;
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
		scale.x, scale.y + speed, obj2->GetScale().x, obj2->GetScale().y))
	{
		position =
		{
			position.x,
			boxPos.m128_f32[1] - boxRad.m128_f32[0] - scale.x - 0.001f - jump ,
			0
		};
		jumpFlag = true;
		leftWallJumpFlag = false;
		leftWallJumpFlag = false;
	}
}

void Player::CollisionEnemy(Enemy *enemy)
{
	Input *input = Input::GetInstance();
	Controller *controller = Controller::GetInstance();

	if (input->isKey(DIK_A) || controller->PushButton(static_cast<int>(Button::LEFT)) == true)
	{
		if (Collision::CheckBox2Box({ position.x - 0.1f,position.y - 0.1f,0 },
			{ enemy->GetPosition().x + 0.1f,enemy->GetPosition().y - 0.1f,0 },
			scale.x - 0.1f, scale.y - 0.1f, enemy->GetScale().x, enemy->GetScale().y))
		{
			if (enemy->GetHP() == 1)
			{
				if (invincibleFlag == false)
				{
					HP--;
					onCollisionFlag = true;
				}
				invincibleFlag = true;
				notHitFlag = true;
			}
		}
	}

	if (input->isKey(DIK_D) || controller->PushButton(static_cast<int>(Button::RIGHT)) == true)
	{
		if (Collision::CheckBox2Box({ position.x + 0.1f,position.y + 0.1f,0 },
			{ enemy->GetPosition().x - 0.1f,enemy->GetPosition().y + 0.1f,0 },
			scale.x - 0.1f, scale.y - 0.1f, enemy->GetScale().x, enemy->GetScale().y))
		{
			if (enemy->GetHP() == 1)
			{
				if (invincibleFlag == false)
				{
					HP--;
					onCollisionFlag = true;
				}
				invincibleFlag = true;
				notHitFlag = true;
			}
		}
	}

	if (Collision::CheckBox2Box({ position.x,position.y,0 },
		{ enemy->GetPosition().x,enemy->GetPosition().y,0 },
		scale.x, scale.y - 0.3f, enemy->GetScale().x, enemy->GetScale().y))
	{
		if (enemy->GetHP() == 1)
		{
			notHitFlag = true;
			if (invincibleFlag == false)
			{
				HP--;
				onCollisionFlag = true;
			}
			invincibleFlag = true;
		}
		if (input->isKey(DIK_SPACE) || controller->PushButton(static_cast<int>(Button::A)) == true)
		{
			enemyNotUpFlag = true;
		}
	}

	//プレイヤーが敵より上に行ったら
	if (position.y > enemy->GetPosition().y + enemy->GetScale().y * 2.0f)
	{
		enemyNotUpFlag = false;
	}

	if (notHitFlag == false && enemyNotUpFlag == false)
	{
		if (Collision::CheckBox2Box({ position.x + 0.1f,position.y - 0.1f,0 },
			{ enemy->GetPosition().x + 0.1f,enemy->GetPosition().y + 0.1f,0 },
			scale.x, scale.y + speed + jump, enemy->GetScale().x, enemy->GetScale().y))
		{
			if (enemy->GetHP() == 1)
			{
				treadFlag = true;
				rotation.z = 0.0f;
				enemy->Deth();
			}
		}
	}

}

void Player::CollisionGimmick(ModelObj *obj2)
{
	if (Collision::CheckBox2Box({ position.x,position.y,0 },
		{ obj2->GetPosition().x,obj2->GetPosition().y,0 },
		scale.x, scale.y, obj2->GetScale().x, obj2->GetScale().y))
	{
		if (invincibleFlag == false)
		{
			HP--;
			onCollisionFlag = true;
			ParticleManager::GetInstance()->LoadTexture(L"Resources/effect1.png");
		}
		invincibleFlag = true;
	}
}

bool Player::CollisionGoal(ModelObj *obj2)
{
	if (Collision::CheckBox2Box({ position.x,position.y,0 },
		{ obj2->GetPosition().x,obj2->GetPosition().y,0 },
		scale.x, scale.y, obj2->GetScale().x, 10.0f))
	{
		speed = 0;
		moveFlag = true;
		position.y -= 0.02f;
		if (Collision::CheckBox2Box({ position.x,position.y,0 },
			{ obj2->GetPosition().x,obj2->GetPosition().y,0 },
			scale.x, scale.y, obj2->GetScale().x, obj2->GetScale().y))
		{
			return true;
		}
	}

	return false;
}