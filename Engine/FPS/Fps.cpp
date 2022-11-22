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

		return 0;
	}
	fps = 1 / frameTime;

	if (frameTime > 0.0)
	{
		// �o�ߎ��Ԃ�0���傫��(�������Ȃ��Ɖ��̌v�Z�Ń[�����Z�ɂȂ�Ǝv���)
		fps = (fps * 0.99f) + (0.01f / frameTime); // ����fps���v�Z
	}

	mTimeStart = mTimeEnd;
	return fps;
}
