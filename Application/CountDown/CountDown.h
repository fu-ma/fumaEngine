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
	//ステージ開始までのカウントダウン
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

	//スクロールするスピード
	const float moveSpeed = 0.015f;
};

