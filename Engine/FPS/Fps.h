#pragma once
#include<chrono>
#include<thread>

class Fps
{
public: // 静的メンバ変数
	static Fps *GetInstance();
public://メンバ関数
	//FPS固定初期化
	void InitializeFixFPS();
	//FPS固定更新
	void UpdateFixFPS();
private://メンバ変数
	//記録時間（FPS固定用）
	std::chrono::steady_clock::time_point reference_;
};

