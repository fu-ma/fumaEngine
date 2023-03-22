#include "Player.h"
#include "DebugText.h"
#include "SphereCollider.h"
#include "ParticleManager.h"
#include "CollisionManager.h"
#include "CollisionAttribute.h"
#include"Resources.h"
#include"Json.h"
#include"ParticleManager.h"

using namespace DirectX;

Player * Player::Create(Model * model)
{
	// 3Dオブジェクトのインスタンスを生成
	Player* instance = new Player();
	if (instance == nullptr) {
		return nullptr;
	}

	// 初期化
	if (!instance->Initialize())
	{
		delete instance;
		assert(0);
	}

	if (model)
	{
		instance->SetModel(model);
	}

	return instance;
}

bool Player::Initialize()
{
	Resources *resources = Resources::GetInstance();
	Json *json = Json::GetInstance();

	//moveParticle = new Particle();
	//moveParticle->Initialize(resources->GetModel(ResourcesName::modelExplosionUpParticle));

	//explosionLeftParticle = new Particle();
	//explosionLeftParticle->Initialize(resources->GetModel(ResourcesName::modelExplosionLeftParticle));

	//explosionRightParticle = new Particle();
	//explosionRightParticle->Initialize(resources->GetModel(ResourcesName::modelExplosionRightParticle));

	pushEnemyParticle = new Particle();
	pushEnemyParticle->Initialize(resources->GetModel(ResourcesName::modelEnemy));

	if (!ModelObj::Initialize())
	{
		return false;
	}
	
	speed = 0;
	jump = 0.5f;
	jumpChange = 0;
	jumpChangeTimer = 0;
	t = 0;
	treadTime = 0;
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
	jumpTimer = 0;

	invincibleTimer = 0;
	HP = (int)json->ReadFile("Resources/data.json","HP");
	rotation.y = 0;
	rotation.z = 0;
	position.x = 10;
	position.y = 2;
	moveFlag = false;

	constMoveSpeed = json->ReadFile("Resources/data.json","moveSpeed");
	moveSpeed = constMoveSpeed;

	constRotSpeed = json->ReadFile("Resources/data.json", "rotSpeed");
	rotSpeed = constRotSpeed;

	jumpChangeBlockFlag = false;

	oldPos = {};

	enemyHitShakeFlag = false;
	shadowSize.x = SHADOW_MAX_SIZE;
	shadowSize.y = SHADOW_MAX_SIZE;

	cameraMoveY = 0;
	playerStandFlag = false;
	return true;
}

void Player::SetValue()
{
	Json *json = Json::GetInstance();

	json->AddString("jump", "0.5f");
	json->AddString("HP", "2");
	json->AddString("moveSpeed", "0.14f");
	json->AddString("rotSpeed", "3.5f");
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

	//moveParticle->Update(TYPE::explosionUP, { position.x,position.y - scale.y/2 , 0 });
	//explosionLeftParticle->Update(TYPE::explosionLEFT, { position.x,position.y,0 });
	//explosionRightParticle->Update(TYPE::explosionRIGHT, { position.x,position.y,0 });
	pushEnemyParticle->Update(TYPE::explosion, { position.x,position.y-1,0 });

	oldPos = position;

	// 行列の更新など
	ModelObj::Update();
}

void Player::Draw()
{
	if (invincibleTimer % 20 == 0 || invincibleTimer % 20 == 1 || invincibleTimer % 20 == 2 || invincibleTimer >= 500)
	{
		ModelObj::Draw();
	}
	//moveParticle->Draw();
	//explosionLeftParticle->Draw();
	//explosionRightParticle->Draw();
	pushEnemyParticle->Draw();
}

void Player::Move()
{
	//プレイヤーの重力処理
	Gravity();

	//左壁キック
	if (leftWallJumpFlag == false)
	{
		leftWallJumpTimer = 0;
	}
	if (leftWallJumpFlag == true)
	{
		if (leftWallJumpTimer == 0)
		{
			//explosionLeftParticle->SetFlag(true);
			for (int i = 0; i < 60; ++i)
			{
				const float rnd_vel = 0.2f;
				XMFLOAT3 vel{};
				vel.x = (float)rand() / RAND_MAX * rnd_vel / 4.0f - 0;
				vel.y = (float)rand() / RAND_MAX * rnd_vel / 2.0f - rnd_vel / 4.0f;

				ParticleManager::GetInstance()->Add(60, XMFLOAT3({ position.x, position.y - scale.y / 2, 0 }), vel, XMFLOAT3(), 2.0f, 0.0f);
			}
		}
		leftWallJumpTimer += 2;
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
		if (rightWallJumpTimer == 0)
		{
			//explosionRightParticle->SetFlag(true);
			for (int i = 0; i < 60; ++i)
			{
				const float rnd_vel = 0.2f;
				XMFLOAT3 vel{};
				vel.x = (float)rand() / RAND_MAX * -rnd_vel / 4.0f;
				vel.y = (float)rand() / RAND_MAX * rnd_vel / 2.0f - rnd_vel / 4.0f;

				ParticleManager::GetInstance()->Add(60, XMFLOAT3({ position.x, position.y - scale.y / 2, 0 }), vel, XMFLOAT3(), 2.0f, 0.0f);
			}
		}
		rightWallJumpTimer += 2;
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
		if (gameControl->moveControl(Move::LEFT))
		{
			if (leftWallJumpFlag == false)
			{
				position.x -= (float)moveSpeed;
			}

			//プレイヤーの向きを左側にする
			rotation.z += rotSpeed;
		}
		else if (gameControl->moveControl(Move::RIGHT))
		{
			if (rightWallJumpFlag == false)
			{
				position.x += (float)moveSpeed;
			}

			//プレイヤーの向きを右側にする
			rotation.z -= rotSpeed;
		}
	}

	//プレイヤーのジャンプ処理
	PlayerJump();

	//無敵時間
	invincibleTime();

	if (treadFlag == true)
	{
		t += 0.01f;
		easing::Updete(treadTime, 0.5, 3, t);
		if (treadTime < 0.4)
		{
			position.y += jump + (float)treadTime;
		}
		if (treadTime >= 0.5)
		{
			t = 0;
			treadTime = 0;
			treadFlag = false;
		}
	}

}

void Player::Jump()
{
	//重力処理
	if (speed > gravity * 20)
	{
		speed += gravity / 2;
	}
	position.y += speed + gravity;

	//1.2.3段ジャンプ処理
	if (jumpChange == 0)
	{
		jumpMax = 20;
	}
	if (jumpChange == 1)
	{
		jumpMax = 40;
	}
	if (jumpChange == 2)
	{
		jumpMax = 60;
	}
	
	if (jumpFlag == false)
	{
		if (gameControl->moveControl(Move::JUMPTRIGGER))
		{
			jumpChangeBlockFlag = !jumpChangeBlockFlag;
			//ジャンプパーティクル
			//moveParticle->SetFlag(true);
			for (int i = 0; i < 60; ++i)
			{
				const float rnd_vel = 0.2f;
				XMFLOAT3 vel{};
				vel.x = (float)rand() / RAND_MAX * rnd_vel / 2.0f - rnd_vel / 4.0f;
				vel.y = (float)rand() / RAND_MAX * rnd_vel / 4.0f - 0;

				ParticleManager::GetInstance()->Add(60, XMFLOAT3({ position.x, position.y - scale.y / 2, 0 }), vel, XMFLOAT3(), 2.0f, 0.0f);
			}
		}
		if (gameControl->moveControl(Move::JUMP))
		{
			if (jumpTimer < jumpMax)
			{
				position.y += jump;
				//影が最小までなるまで小さくする
				if (shadowSize.x >= SHADOW_MIN_SIZE)
				{
					shadowSize.x -= SHADOW_SIZE_CHANGE;
					shadowSize.y -= SHADOW_SIZE_CHANGE;
				}
			}
			if (jumpTimer < jumpMax)
			{
				jumpTimer += 2;
			}

			if (jumpChange > 2)
			{
				jumpChange = 0;
			}
			if (jumpChangeTimer > 0 && jumpChangeTimer < 20)
			{
				jumpChange++;
				jumpChangeTimer = 0;
			}
			else if (jumpChangeTimer > 20)
			{
				jumpChange = 0;
				jumpChangeTimer = 0;
			}

			if (jumpMax == 40)
			{
				rotation.y -= 2.5f;
			}
			if (jumpMax == 60)
			{
				rotation.y -= 5;
			}
		}
	}
}

void Player::HitObjLeft(ModelObj *obj2)
{
	XMVECTOR boxPos = XMLoadFloat3(&obj2->GetPosition());
	XMVECTOR boxRad = XMLoadFloat3(&obj2->GetScale());

	if (oldPos.x > position.x)
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
			rotation.z = 0;
			rightWallColFlag = false;
			if (gameControl->moveControl(Move::WALLJUMPLEFT))
			{
				leftWallJumpFlag = true;
			}
		}
	}
	else
	{
		rotSpeed = constRotSpeed;
	}
}

void Player::HitObjRight(ModelObj *obj2)
{
	XMVECTOR boxPos = XMLoadFloat3(&obj2->GetPosition());
	XMVECTOR boxRad = XMLoadFloat3(&obj2->GetScale());

	if (oldPos.x < position.x)
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
			rotation.z = 0;
			leftWallColFlag = false;
			if (gameControl->moveControl(Move::WALLJUMPRIGHT))
			{
				rightWallJumpFlag = true;
			}
		}
	}
	else
	{
		rotSpeed = constRotSpeed;
	}
}

void Player::HitObjDown(ModelObj *obj2)
{
	XMVECTOR boxPos = XMLoadFloat3(&obj2->GetPosition());
	XMVECTOR boxRad = XMLoadFloat3(&obj2->GetScale());

	position =
	{
		position.x,
		boxPos.m128_f32[1] + boxRad.m128_f32[0] + scale.x + 0.011f ,
		0
	};
	speed = 0;
	moveSpeed = constMoveSpeed;
	rotation.y = 0.0f;

	//着地してるとき影の大きさをリセット
	shadowSize.x = SHADOW_MAX_SIZE;
	shadowSize.y = SHADOW_MAX_SIZE;
	//着地しているときのみジャンプを可能にする
	if (!(gameControl->moveControl(Move::JUMP)))
	{
		jumpChangeTimer++;
		jumpTimer = 0;
		jumpFlag = false;
	}

	playerStandFlag = true;

	rightWallJumpFlag = false;
	rightWallColFlag = false;
	leftWallJumpFlag = false;
	leftWallColFlag = false;
}

void Player::HitObjUp(ModelObj *obj2)
{
	XMVECTOR boxPos = XMLoadFloat3(&obj2->GetPosition());
	XMVECTOR boxRad = XMLoadFloat3(&obj2->GetScale());

	position =
	{
		position.x,
		boxPos.m128_f32[1] - boxRad.m128_f32[0] - scale.x - 0.011f - jump ,
		0
	};
	jumpFlag = true;
	rightWallJumpFlag = false;
	leftWallJumpFlag = false;
}

void Player::HitObjBase(ModelObj *obj2)
{
	XMVECTOR boxPos = XMLoadFloat3(&obj2->GetPosition());
	XMVECTOR boxRad = XMLoadFloat3(&obj2->GetScale());

	//空中処理
	if (speed < gravity && !(gameControl->moveControl(Move::JUMP)))
	{
		jumpFlag = true;
	}

	//壁キック後の当たり判定
	if (leftWallColFlag)
	{
		if (Collision::CheckBox2Box({ position.x + 0.2f,position.y + 0.2f,0 },
			{ obj2->GetPosition().x - 0.2f,obj2->GetPosition().y + 0.2f,0 },
			scale.x + 0.2f, scale.y - 0.2f, obj2->GetScale().x, obj2->GetScale().y))
		{
			rightWallJumpFlag = false;
			position =
			{
				boxPos.m128_f32[0] - boxRad.m128_f32[0] - scale.x - 0.11f,
				position.y ,
				0
			};
			leftWallColFlag = false;
			moveSpeed = 0.01f;
		}
	}

	if (rightWallColFlag)
	{
		if (Collision::CheckBox2Box({ position.x - 0.2f,position.y - 0.2f,0 },
			{ obj2->GetPosition().x + 0.2f,obj2->GetPosition().y - 0.2f,0 },
			scale.x + 0.2f, scale.y - 0.2f, obj2->GetScale().x, obj2->GetScale().y))
		{
			leftWallJumpFlag = false;
			position =
			{
				boxPos.m128_f32[0] + boxRad.m128_f32[0] + scale.x + 0.11f,
				position.y ,
				0
			};
			rightWallColFlag = false;
			moveSpeed = 0.01f;
		}
	}

}

void Player::HitEnemyLeftAndRight(Enemy *enemy)
{
	HitEnemy(enemy);
}

void Player::HitEnemyDown(Enemy *enemy)
{
	HitEnemy(enemy);
	if (gameControl->moveControl(Move::JUMP))
	{
		enemyNotUpFlag = true;
	}
}

void Player::HitEnemyUp(Enemy *enemy)
{
	//プレイヤーが敵より上に行ったら
	if (position.y > enemy->GetPosition().y + enemy->GetScale().y * 2.0f)
	{
		enemyNotUpFlag = false;
	}

	if (notHitFlag == false && enemyNotUpFlag == false)
	{
		if (enemy->GetHP() == 1)
		{
			pushEnemyParticle->SetFlag(true);
			enemyPos = enemy->GetPosition();
			t = 0;
			treadTime = 0;
			treadFlag = true;
			rotation.y = 0.0f;
			enemy->Death();
		}
	}
}

void Player::HitGimmick(ModelObj *obj2)
{
	if (invincibleFlag == false)
	{
		HP--;
		onCollisionFlag = true;
	}
	invincibleFlag = true;
}

void Player::HitGoal(ModelObj *obj2)
{
	speed = 0;
	moveFlag = true;
	position.y -= 0.02f;
}

void Player::HitEnemy(Enemy *enemy)
{
	if (enemy->GetHP() == 1)
	{
		if (invincibleFlag == false)
		{
			HP--;
			enemyHitShakeFlag = true;
			onCollisionFlag = true;
		}
		invincibleFlag = true;
		notHitFlag = true;
	}
}

void Player::invincibleTime()
{
	if (invincibleFlag == false) return;
	invincibleTimer++;
	if (invincibleTimer <= 300) return;
	invincibleFlag = false;
	invincibleTimer = 0;
	notHitFlag = false;
}

void Player::Gravity()
{
	//重力処理
	if (speed > gravity * 20)
	{
		speed += gravity / 2;
	}
	position.y += speed + gravity;
}

void Player::PlayerJump()
{
	//1.2.3段ジャンプ処理
	if (jumpChange == 0)
	{
		jumpMax = 20;
	}
	if (jumpChange == 1)
	{
		jumpMax = 40;
	}
	if (jumpChange == 2)
	{
		jumpMax = 60;
	}

	if (moveFlag == false)
	{
		if (jumpFlag == false)
		{
			if (gameControl->moveControl(Move::JUMP))
			{
				playerStandFlag = false;
				if (jumpTimer < jumpMax)
				{
					position.y += jump;
				}
				if (jumpTimer < jumpMax)
				{
					jumpTimer += 2;
				}

				if (jumpChangeTimer > 0 && jumpChangeTimer < 20)
				{
					jumpChange++;
					jumpChangeTimer = 0;
				}
				else if (jumpChangeTimer > 20)
				{
					jumpChange = 0;
					jumpChangeTimer = 0;
				}

				if (jumpChange > 2)
				{
					jumpChange = 0;
				}

				if (jumpMax == 40)
				{
					rotation.y -= 2.5f;
				}
				if (jumpMax == 60)
				{
					rotation.y -= 5;
				}
			}
			if (gameControl->moveControl(Move::JUMPTRIGGER))
			{
				jumpChangeBlockFlag = !jumpChangeBlockFlag;
				//ジャンプパーティクル
				//moveParticle->SetFlag(true);
				if (jumpChange == 0)
				{
					for (int i = 0; i < 10; ++i)
					{
						const float rnd_vel = 0.2f;
						XMFLOAT3 vel{};
						vel.x = (float)rand() / RAND_MAX * rnd_vel / 2.0f - rnd_vel / 4.0f;
						vel.y = (float)rand() / RAND_MAX * rnd_vel / 4.0f - 0;

						ParticleManager::GetInstance()->Add(20, XMFLOAT3({ position.x, position.y - scale.y / 2, 0 }), vel, XMFLOAT3(), 1.0f, 0.0f);
					}
				}
				if (jumpChange == 1)
				{
					for (int i = 0; i < 30; ++i)
					{
						const float rnd_vel = 0.2f;
						XMFLOAT3 vel{};
						vel.x = (float)rand() / RAND_MAX * rnd_vel / 2.0f - rnd_vel / 4.0f;
						vel.y = (float)rand() / RAND_MAX * rnd_vel / 4.0f - 0;

						ParticleManager::GetInstance()->Add(40, XMFLOAT3({ position.x, position.y - scale.y / 2, 0 }), vel, XMFLOAT3(), 2.0f, 0.0f);
					}
				}
				if (jumpChange == 2)
				{
					for (int i = 0; i < 60; ++i)
					{
						const float rnd_vel = 0.2f;
						XMFLOAT3 vel{};
						vel.x = (float)rand() / RAND_MAX * rnd_vel / 2.0f - rnd_vel / 4.0f;
						vel.y = (float)rand() / RAND_MAX * rnd_vel / 4.0f - 0;

						ParticleManager::GetInstance()->Add(60, XMFLOAT3({ position.x, position.y - scale.y / 2, 0 }), vel, XMFLOAT3(), 3.0f, 0.0f);
					}
				}
			}
			//2段階目かつ重力よりもジャンプ力が高い場合
			if ((speed + gravity) < jump && jumpTimer < jumpMax && playerStandFlag == false)
			{
				if (jumpMax == 40)
				{
					cameraMoveY += 0.05f;
				}
				if (jumpMax == 60)
				{
					cameraMoveY += 0.1f;
				}
			}
			//2段階目かつ重力よりもジャンプ力が低い場合
			if (jumpTimer >= jumpMax && cameraMoveY > 0.0f && playerStandFlag == false)
			{
				if (jumpMax == 40)
				{
					cameraMoveY -= 0.05f;
				}
				if (jumpMax == 60)
				{
					cameraMoveY -= 0.1f;
				}
			}
		}
	}

	if (jumpTimer > 0 && (!gameControl->moveControl(Move::JUMP)))
	{
		if (cameraMoveY > 0.0f && playerStandFlag == false)
		{
			if (jumpMax == 40)
			{
				cameraMoveY -= 0.05f;
			}
			if (jumpMax == 60)
			{
				cameraMoveY -= 0.1f;
			}
		}
		jumpFlag = true;
	}

	//プレイヤーが着地している時滑らかにカメラを動かす
	if (playerStandFlag == true)
	{
		if (cameraMoveY <= 0.1f && cameraMoveY >= -0.1f)
		{
			cameraMoveY = 0;
		}
		else if (cameraMoveY > 0.0f)
		{
			if (jumpMax == 40)
			{
				cameraMoveY -= 0.05f;
			}
			if (jumpMax == 60)
			{
				cameraMoveY -= 0.1f;
			}
		}
		else if (cameraMoveY < 0.0f)
		{
			if (jumpMax == 40)
			{
				cameraMoveY += 0.05f;
			}
			if (jumpMax == 60)
			{
				cameraMoveY += 0.1f;
			}
		}

	}
}
