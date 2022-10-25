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
		//���g���擾
		QueryPerformanceFrequency(&mTimeFreq);
		//�v���J�n���Ԃ̏�����
		QueryPerformanceCounter(&mTimeStart);
	}
	//FPS�Œ�
	double TimeWait();

	const double &GetFrame() { return frame; }
private:
	double frame;

	const double FRAME_TIME = 0.0;
	//�v���J�n
	LARGE_INTEGER mTimeStart;
	//�v���I��
	LARGE_INTEGER mTimeEnd;
	//�v�����g��
	LARGE_INTEGER mTimeFreq;
};

