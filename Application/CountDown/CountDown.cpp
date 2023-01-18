#include "CountDown.h"

CountDown::CountDown()
{
	CountDown3 = Sprite::Create(8, { WinApp::window_width + WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	CountDown2 = Sprite::Create(7, { WinApp::window_width + WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	CountDown1 = Sprite::Create(6, { WinApp::window_width + WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	CountDownStart = Sprite::Create(11, { WinApp::window_width + WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
}

CountDown::~CountDown()
{
	delete CountDown3;
	CountDown3 = nullptr;
	delete CountDown2;
	CountDown2 = nullptr;
	delete CountDown1;
	CountDown1 = nullptr;
	delete CountDownStart;
	CountDownStart = nullptr;
}

void CountDown::Initialize()
{
	//カウントダウン用の画像の初期値の設定
	CountDown1Pos = WinApp::window_width + WinApp::window_width / 2.0f;
	CountDown2Pos = WinApp::window_width + WinApp::window_width / 2.0f;
	CountDown3Pos = WinApp::window_width + WinApp::window_width / 2.0f;
	CountDownStartPos = WinApp::window_width + WinApp::window_width / 2.0f;

	CountDownTime3 = 0;
	CountDownTime2 = 0;
	CountDownTime1 = 0;
	CountDownStartTime = 0;
	CountDownEndTime = 0;
}

void CountDown::Update()
{
	//3.2.1.スタート
	if (CountDownTime3 < 0.8)
	{
		CountDownTime3 += moveSpeed;
		easing::Updete(CountDown3Pos, WinApp::window_width / 2.0f, InSine, CountDownTime3);
	}

	if (CountDownTime3 >= 0.8 && CountDownTime2 < 0.8)
	{
		CountDownTime2 += moveSpeed;
		easing::Updete(CountDown3Pos, -WinApp::window_width / 2.0f, InSine, CountDownTime2);
		easing::Updete(CountDown2Pos, WinApp::window_width / 2.0f, InSine, CountDownTime2);
	}

	if (CountDownTime2 >= 0.8 && CountDownTime1 < 0.8)
	{
		CountDownTime1 += moveSpeed;
		easing::Updete(CountDown2Pos, -WinApp::window_width / 2.0f, InSine, CountDownTime1);
		easing::Updete(CountDown1Pos, WinApp::window_width / 2.0f, InSine, CountDownTime1);
	}

	if (CountDownTime1 >= 0.8 && CountDownStartTime < 0.8)
	{
		CountDownStartTime += moveSpeed;
		easing::Updete(CountDown1Pos, -WinApp::window_width / 2.0f, InSine, CountDownStartTime);
		easing::Updete(CountDownStartPos, WinApp::window_width / 2.0f, InSine, CountDownStartTime);
	}

	if (CountDownStartTime >= 0.8 && CountDownEndTime < 0.8)
	{
		CountDownEndTime += moveSpeed;
		easing::Updete(CountDownStartPos, -WinApp::window_width / 2.0f, InSine, CountDownEndTime);
	}

	CountDown3->SetPosition({ (float)CountDown3Pos,WinApp::window_height / 2.0f });
	CountDown2->SetPosition({ (float)CountDown2Pos,WinApp::window_height / 2.0f });
	CountDown1->SetPosition({ (float)CountDown1Pos,WinApp::window_height / 2.0f });
	CountDownStart->SetPosition({ (float)CountDownStartPos,WinApp::window_height / 2.0f });
}

void CountDown::Draw()
{
	//カウントダウン表示
	CountDown3->Draw();
	CountDown2->Draw();
	CountDown1->Draw();
	CountDownStart->Draw();
}
