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
	
	//スター取得したとき
	void GetStar();

	//動き出す
	void Moveing();
	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update() override;
	void Draw() override;

	const bool &GetMoveingFlag() { return moveingFlag; }
private:
	//消えるか同化のフラグ
	bool toNotDisplay;
	//動き出すフラグ
	bool moveingFlag;
};