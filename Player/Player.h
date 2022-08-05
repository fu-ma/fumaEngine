#pragma once
#include"ModelObj.h"
#include"DebugCamera.h"
#include<math.h>
#include"DebugCamera.h"
#include"Collision.h"

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
	void Move();
	void CollisionObj(ModelObj *obj2);
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
};

