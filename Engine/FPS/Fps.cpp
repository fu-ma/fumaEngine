#include "Fps.h"

double Fps::TimeWait()
{
	//���̎��Ԃ��擾
	QueryPerformanceCounter(&mTimeEnd);
	//(���̎��ԁ[�O�t���[���̎���)/���g��=�o�ߎ���
	double frameTime = static_cast<double>(mTimeEnd.QuadPart - mTimeStart.QuadPart) / static_cast<double>(mTimeFreq.QuadPart);
	double fps = 0.0;

	//�]�T������Ƃ�
	if (frameTime < FRAME_TIME)
	{
		//Sleep�̎��Ԃ��v�Z
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
