#pragma once
#include"ModelObj.h"
#include"DebugCamera.h"
#include<math.h>
#include"DebugCamera.h"
#include"Collision.h"
#include"Enemy.h"
#include"easing.h"

class Player : public ModelObj
{
	using XMVECTOR = DirectX::XMVECTOR;
	using XMFLOAT4 = DirectX::XMFLOAT4;
public:
	/// <summary>
	/// 3Dオブジェクト生成
	/// </summary>
	/// <returns></returns>
	static Player* Create(Model * model = nullptr);
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <returns>成否</returns>
	bool Initialize() override;

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update() override;
	void Draw() override;
	void Move();
	void CollisionObj(ModelObj *obj2);
	void CollisionEnemy(Enemy *enemy);
	void CollisionGimmick(ModelObj *obj2);
	bool CollisionGoal(ModelObj *obj2);
	const int &GetHP() { return HP; }

	const bool &GetOnCollision() { return onCollisionFlag; }
	void notOnCollision() { this->onCollisionFlag = false; }
private:
	const float gravity = (- 9.8f / 60/ 20);
	//const float gravity = (-9.8f / 60 / 40);
	//重力を加算するためのスピード
	float speed;
	//ジャンプするための変数
	int jumpTimer = 0;
	//長押しの時に多めにジャンプ
	int jumpChange = 0;

	//ジャンプのつながり
	int jumpChangeTimer = 0;
	//ジャンプごとの最大値
	int jumpMax;
	//直前にジャンプしたかどうか
	bool jumpFlag = false;
	float jump = 0.2f;

	//壁キック用
	bool leftWallJumpFlag = false;
	bool rightWallJumpFlag = false;
	int leftWallJumpTimer = 0;
	int rightWallJumpTimer = 0;
	bool leftWallColFlag = false;
	bool rightWallColFlag = false;
	const int wallJumpMax = 15;

	int HP = 2;

	//easing用の変数
	bool treadFlag = false;
	double t = 0;
	double treadSpeed = 0;

	bool notHitFlag = false;

	//敵と当たっているときにジャンプしてもバグらないようにするフラグ
	bool enemyNotUpFlag = false;

	//無敵時間フラグ
	bool invincibleFlag = false;
	//無敵時間
	int invincibleTimer = 0;

	//ゴール時の移動制御フラグ
	bool moveFlag = false;

	//エフェクトの判定フラグ
	bool onCollisionFlag = false;

private:
	//重複化を防ぐための関数
	void HitEnemy(Enemy *enemy);

	//ネスト対策
	void invincibleTime();
};

