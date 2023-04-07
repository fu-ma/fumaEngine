#pragma once
#include "ModelObj.h"
#include"Collision.h"
#include<math.h>

class Star : public ModelObj
{
	using XMVECTOR = DirectX::XMVECTOR;
	using XMFLOAT4 = DirectX::XMFLOAT4;
public:
	/// <summary>
	/// 3Dオブジェクト生成
	/// </summary>
	/// <returns></returns>
	static Star *Create(Model *model = nullptr);
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <returns>成否</returns>
	bool Initialize() override;
	
	void GetStar();
	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update() override;
	void Draw() override;
private:
	bool toNotDisplay;
};