#pragma once
#include"ModelObj.h"
#include"DebugCamera.h"
#include<math.h>
#include"DebugCamera.h"
#include"Collision.h"
#include"Enemy.h"
#include"easing.h"
#include"Particle.h"
#include"GameControl.h"

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
	~Player()
	{
		delete moveParticle;
		moveParticle = nullptr;
		/*delete explosionLeftParticle;
		explosionLeftParticle = nullptr;
		delete explosionRightParticle;
		explosionRightParticle = nullptr;*/
		delete pushEnemyParticle;
		pushEnemyParticle = nullptr;
		delete gameControl;
		gameControl = nullptr;
	}
	/// <summary>
	/// 初期化
	/// </summary>
	/// <returns>成否</returns>
	bool Initialize() override;

	void SetValue();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update() override;
	void Draw() override;
	//プレイヤーのすべての動き
	void Move();
	//ステージセレクト用に使うジャンプだけの処理
	void Jump();
	//壁の左に当たった時の処理
	void HitObjLeft(ModelObj *obj2);
	//壁の右に当たった時の処理
	void HitObjRight(ModelObj *obj2);
	//壁の下に当たった時の処理
	void HitObjDown(ModelObj *obj2);
	//壁の上に当たった時の処理
	void HitObjUp(ModelObj *obj2);
	//壁（どこでも）に当たった時の処理
	void HitObjBase(ModelObj *obj2);

	void HitEnemyLeftAndRight(Enemy *enemy);
	void HitEnemyDown(Enemy *enemy);
	void HitEnemyUp(Enemy *enemy);

	void HitGimmick(ModelObj *obj2);
	void HitGoal(ModelObj *obj2);

	const int &GetHP() { return HP; }

	const bool &GetOnCollision() { return onCollisionFlag; }
	void notOnCollision() { this->onCollisionFlag = false; }
	const bool &GetJumpChangeBlockFlag() { return jumpChangeBlockFlag; }
	const bool &GetPlayerStop() { return moveFlag; }
	const int &GetJumpTimer() { return jumpTimer; }
	const bool &GetEnemyHitShakeFlag() { return enemyHitShakeFlag; }
	void SetNotEnemyHitShakeFlag() { enemyHitShakeFlag = false; }
	const XMFLOAT2 &GetShadowSize() { return shadowSize; }
	const float &GetCameraMoveY() { return cameraMoveY; }
	const float &GetMoveSpeed() { return moveSpeed; }

private:
	const float gravity = (- 9.8f / 60/ 15) * 1.2f;
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
	float jump;

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
	double treadTime = 0;

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

	//移動スピード
	float moveSpeed;

	//プレイヤーの移動時の回転速度
	float rotSpeed;

	//プレイヤーの移動時の回転速度固定用
	float constRotSpeed;

	//固定用の移動スピード
	float constMoveSpeed;

	//ジャンプで切り替わる床用のフラグ
	bool jumpChangeBlockFlag;

	//移動時パーティクル
	Particle *moveParticle;

	//壁キック時のパーティクル
	//Particle *explosionLeftParticle;
	//Particle *explosionRightParticle;

	//敵を踏んだ時のパーティクル
	Particle *pushEnemyParticle;
	XMFLOAT3 enemyPos;

	//あたり判定用の過去の位置
	XMFLOAT3 oldPos;

	//シェイクするかのフラグ
	bool enemyHitShakeFlag;

	//ジャンプによってエフェクトを変化させる
	int jumpEffectNum;

	//2段3段ジャンプしたときにカメラを移動させるための変数
	float cameraMoveY;

	//着地しているフラグ
	bool playerStandFlag;

	//影の大きさ
	XMFLOAT2 shadowSize;

	//入力用のまとめクラス
	GameControl *gameControl;

private:
	//影のサイズ変更のための変数
	const float SHADOW_SIZE_CHANGE = 0.003f;
	//影のマックスの大きさ
	const float SHADOW_MAX_SIZE = 0.3f;
	//影のマックスの小ささ
	const float SHADOW_MIN_SIZE = 0.001f;
private:
	//重複化を防ぐための関数
	void HitEnemy(Enemy *enemy);

	//ネスト対策
	void invincibleTime();

	//重力処理
	void Gravity();
	//プレイヤーのジャンプ処理
	void PlayerJump();
};

