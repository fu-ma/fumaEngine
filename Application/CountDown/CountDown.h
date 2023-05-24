#pragma once
#include"easing.h"
#include"Sprite.h"

class CountDown
{
public:
	CountDown();
	~CountDown();
	void Initialize();
	void Update();
	void Draw();

	const double &GetStart() { return CountDownEndTime; }
private:
	//�X�e�[�W�J�n�܂ł̃J�E���g�_�E��
	Sprite *CountDown3 = nullptr;
	Sprite *CountDown2 = nullptr;
	Sprite *CountDown1 = nullptr;
	Sprite *CountDownStart = nullptr;

	double CountDownTime3;
	double CountDownTime2;
	double CountDownTime1;
	double CountDownStartTime;
	double CountDownEndTime;
	double CountDown3Pos;
	double CountDown2Pos;
	double CountDown1Pos;
	double CountDownStartPos;

	//�X�N���[������X�s�[�h
	const float moveSpeed = 0.015f;
};

