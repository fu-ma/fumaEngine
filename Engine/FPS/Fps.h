#pragma once
#include<fstream>
#include<windows.h>
#include<timeapi.h>
#pragma comment(lib,"winmm.lib")

class Fps
{
public:
	Fps(double frame = 60) : FRAME_TIME(1.0f / frame)
	{
		this->frame = frame;
		//周波数取得
		QueryPerformanceFrequency(&mTimeFreq);
		//計測開始時間の初期化
		QueryPerformanceCounter(&mTimeStart);
	}
	//FPS固定
	double TimeWait();

	const double &GetFrame() { return frame; }
private:
	double frame;

	const double FRAME_TIME = 0.0;
	//計測開始
	LARGE_INTEGER mTimeStart;
	//計測終了
	LARGE_INTEGER mTimeEnd;
	//計測周波数
	LARGE_INTEGER mTimeFreq;
};

