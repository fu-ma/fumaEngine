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
	std::unique_ptr<Sprite> CountDown3;
	std::unique_ptr<Sprite> CountDown2;
	std::unique_ptr<Sprite> CountDown1;
	std::unique_ptr<Sprite> CountDownStart;

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

