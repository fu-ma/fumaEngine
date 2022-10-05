#pragma once
#include "ModelObj.h"
class Firebar : public ModelObj
{
	using XMVECTOR = DirectX::XMVECTOR;
	using XMFLOAT4 = DirectX::XMFLOAT4;
public:
	/// <summary>
	/// 3Dオブジェクト生成
	/// </summary>
	/// <returns></returns>
	static Firebar *Create(Model *model = nullptr);
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
	void Move(float centerX, float centerY, float length, bool direction = false);
	void Draw() override;

	const float &GetLength() { return length; }
	const bool &GetMoveFlag() { return moveFlag; }
	void SetMoveFlag(bool moveFlag) { this->moveFlag = moveFlag; }
private:
	float addX;
	float addY;
	float length;
	float angle;
	bool moveFlag;
};

