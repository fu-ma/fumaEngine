#pragma once
#include "ModelObj.h"
#include"Collision.h"

class Enemy : public ModelObj
{
	using XMVECTOR = DirectX::XMVECTOR;
	using XMFLOAT4 = DirectX::XMFLOAT4;
public:
	/// <summary>
	/// 3Dオブジェクト生成
	/// </summary>
	/// <returns></returns>
	static Enemy *Create(Model *model = nullptr);
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
	void Draw() override;
	void CollisionObject(ModelObj *obj2);

	//敵の状態をセット
	void SetAction(const std::string &enemyName) { this->enemyName = enemyName; }

	const int &GetHP() { return HP; }
	const float &GetSpeed() { return speed; }
	void Death();
private:
	int HP = 1;
	const float gravity = (-9.8f / 60 / 20);
	//const float gravity = (-9.8f / 60 / 40);
	//重力を加算するためのスピード
	float speed;
	float angleSpeed;
	XMFLOAT3 oldPos;

	//ぴょんぴょんする敵
	int jumpTimer;
	float jump;

	//動きをセットするための変数
	std::string enemyName;
};

