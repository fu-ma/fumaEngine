#pragma once
#include<chrono>
#include<thread>

class Fps
{
public: // �ÓI�����o�ϐ�
	static Fps *GetInstance();
public://�����o�֐�
	//FPS�Œ菉����
	void InitializeFixFPS();
	//FPS�Œ�X�V
	void UpdateFixFPS();
private://�����o�ϐ�
	//�L�^���ԁiFPS�Œ�p�j
	std::chrono::steady_clock::time_point reference_;
};

