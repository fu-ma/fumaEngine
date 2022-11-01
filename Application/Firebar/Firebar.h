#pragma once
#include "ModelObj.h"
class Firebar
{
	using XMVECTOR = DirectX::XMVECTOR;
	using XMFLOAT3 = DirectX::XMFLOAT3;
public:
	Firebar();
	~Firebar();
	void StaticInit();
	/// <summary>
	/// ������
	/// </summary>
	/// <returns>����</returns>
	bool Initialize(float centerX, float centerY, int num);

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();
	void Move(bool direction = false);
	void Draw();

	ModelObj *GetCenter() { return firebar[0]; }
	const int &GetNum() { return num; }
	ModelObj *GetFire(int num) { return firebar[num]; }
	void SetAngleSpeed(float angleSpeed) { this->angleSpeed = angleSpeed; }
private:
	static const int GIMMICK_NUM = 100;
	Model *modelGimmick = nullptr;
	Model *modelGimmickCenter = nullptr;
	int num;
	float centerX;
	float centerY;
	float addX[GIMMICK_NUM];
	float addY[GIMMICK_NUM];
	float angle[GIMMICK_NUM];
	float angleSpeed = 0.5f;
	float radius[GIMMICK_NUM];
	bool moveFlag[GIMMICK_NUM];
	float length[GIMMICK_NUM];
	ModelObj *firebar[GIMMICK_NUM] = { nullptr };
	XMFLOAT3 gimmickCenter[GIMMICK_NUM];
};
