#pragma once
#include "ModelObj.h"
#include"easing.h"

class ThornStick : public ModelObj
{
public:
	/// <summary>
	/// 3Dオブジェクト生成
	/// </summary>
	/// <returns></returns>
	static ThornStick *Create(Model *model = nullptr);

public:
	void Move();

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

	void SetOldStickPos(const XMFLOAT3 &pos) { this->oldPosY = pos.y; }
private:
	//動きを制限するための時間
	int timer;
	//イージング用
	double moveX;
	double moveY;
	double rotateY;
	double moveStartT;
	double moveT;
	double moveEndT;
	double posY;
	//初期位置を保存するための変数
	double oldPosY;
};

