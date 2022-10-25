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
		//ügæ¾
		QueryPerformanceFrequency(&mTimeFreq);
		//vªJnÔÌú»
		QueryPerformanceCounter(&mTimeStart);
	}
	//FPSÅè
	double TimeWait();

	const double &GetFrame() { return frame; }
private:
	double frame;

	const double FRAME_TIME = 0.0;
	//vªJn
	LARGE_INTEGER mTimeStart;
	//vªI¹
	LARGE_INTEGER mTimeEnd;
	//vªüg
	LARGE_INTEGER mTimeFreq;
};

