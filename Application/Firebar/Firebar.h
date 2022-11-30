#pragma once
#include "ModelObj.h"
class Firebar
{
	using XMVECTOR = DirectX::XMVECTOR;
	using XMFLOAT3 = DirectX::XMFLOAT3;
public:
	Firebar(float centerX, float centerY, int num,bool direction,float angleSpeed);
	~Firebar();
	void StaticInit();
	/// <summary>
	/// èâä˙âª
	/// </summary>
	/// <returns>ê¨î€</returns>
	bool Initialize();

	/// <summary>
	/// ñàÉtÉåÅ[ÉÄèàóù
	/// </summary>
	void Update();
	void Move();
	void Draw();

	ModelObj *GetCenter() { return firebar[0]; }
	const int &GetNum() { return num; }
	ModelObj *GetFire(int num) { return firebar[num]; }
private:
	static const int GIMMICK_NUM = 100;
	const float MOVE_SPEED = 1.2f;
	Model *modelGimmick = nullptr;
	Model *modelGimmickCenter = nullptr;
	int num;
	float centerX;
	float centerY;
	bool direction;
	float addX[GIMMICK_NUM];
	float addY[GIMMICK_NUM];
	float angle[GIMMICK_NUM];
	float angleSpeed = 0.5f;
	float radius[GIMMICK_NUM];
	bool moveFlag[GIMMICK_NUM];
	float length[GIMMICK_NUM];
	ModelObj *firebar[GIMMICK_NUM] = { nullptr };
	XMFLOAT3 gimmickCenter[GIMMICK_NUM];
	XMFLOAT3 fireRot[GIMMICK_NUM];
};

