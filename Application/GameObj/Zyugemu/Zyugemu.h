#pragma once
#include"Enemy.h"
#include"ModelObj.h"
#include"Resources.h"

class Zyugemu : public ModelObj
{
	using XMVECTOR = DirectX::XMVECTOR;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMFLOAT3 = DirectX::XMFLOAT3;

	enum Pattern
	{
		SET,
		RESERVE,
		ATTACK,
	};
private:
	std::vector<std::unique_ptr<Enemy>> enemy;
	Pattern pattern;
	//プレイヤーの位置情報セット用
	XMFLOAT3 playerPos;
	//トゲゾーが動くか動かないか
	std::vector<bool> isAttackFlag;

	float moveSpeed;
	int moveTime;
	float gravity;
	float jump;
	XMFLOAT3 togePos;
public:
	/// <summary>
	/// 3Dオブジェクト生成
	/// </summary>
	/// <returns></returns>
	static Zyugemu *Create(Model *model = nullptr);
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
	void Move(const XMFLOAT3 &playerPos);
	void Draw() override;

	void CollisionObject(ModelObj *obj2);

	Enemy *GetEnemy(const int &num) { return enemy[num].get(); }
	size_t GetALLEnemy() { return enemy.size(); }
};

