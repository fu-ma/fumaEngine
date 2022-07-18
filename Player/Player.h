#pragma once
#include"ModelObj.h"
#include"DebugCamera.h"
#include<math.h>
#include"DebugCamera.h"

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
	void moveSphere(ModelObj* obj2);
private:
	const float gravity = (- 9.8f / 60/ 20);
	//const float gravity = (-9.8f / 60 / 40);
	float rot1;
	float rot2;
	float speed;
	XMFLOAT3 moveSpeed = {};
	bool onGround = true;
	// 落下ベクトル
	XMVECTOR fallV;
	XMVECTOR V;
	XMFLOAT3 up = { 0, 1, 0 };
	// カメラ回転行列
	XMMATRIX matPlayerRot;
	float angleX;
	float angleY;
};

