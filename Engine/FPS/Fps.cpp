#include "Fps.h"

double Fps::TimeWait()
{
	//今の時間を取得
	QueryPerformanceCounter(&mTimeEnd);
	//(今の時間ー前フレームの時間)/周波数=経過時間
	double frameTime = static_cast<double>(mTimeEnd.QuadPart - mTimeStart.QuadPart) / static_cast<double>(mTimeFreq.QuadPart);
	double fps = 0.0;

	//余裕があるとき
	if (frameTime < FRAME_TIME)
	{
		//Sleepの時間を計算
		DWORD sleepTime = static_cast<DWORD>((FRAME_TIME - frameTime) * 1000);
		timeBeginPeriod(1);
		//Sleep
		Sleep(sleepTime);
		timeEndPeriod(1);
	}
	fps = 1 / frameTime;

	mTimeStart = mTimeEnd;
	return fps;
}
