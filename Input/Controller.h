#pragma once
#include<Windows.h>
#include<Xinput.h>

#pragma comment(lib,"xinput.lib")
enum class Button
{
	A = XINPUT_GAMEPAD_A,
	B = XINPUT_GAMEPAD_B,
	X = XINPUT_GAMEPAD_X,
	Y = XINPUT_GAMEPAD_Y,
	UP = XINPUT_GAMEPAD_DPAD_UP,
	DOWN = XINPUT_GAMEPAD_DPAD_DOWN,
	LEFT = XINPUT_GAMEPAD_DPAD_LEFT,
	RIGHT = XINPUT_GAMEPAD_DPAD_RIGHT,
	START = XINPUT_GAMEPAD_START,
	LEFTTHUMB = XINPUT_GAMEPAD_LEFT_THUMB,
	RIGHTTHUMB = XINPUT_GAMEPAD_RIGHT_THUMB,
	LB = XINPUT_GAMEPAD_LEFT_SHOULDER,
	RB = XINPUT_GAMEPAD_RIGHT_SHOULDER,

};

class Controller
{
private:
	XINPUT_STATE state;
	XINPUT_STATE oldstate;
	DWORD dwResult;
	//スティックの入力を方向パッドに変換
	WORD ThumbToPad(SHORT sThumbX,SHORT sThumbY,SHORT sDeadZone);
public: // 静的メンバ関数
	static Controller *GetInstance();

public:
	void Initialize(DWORD controllerNum);
	void Update(DWORD controllerNum);
	bool PushButton(int button);
	bool TriggerButton(int button);
	bool PushLt();
	bool PushRt();
	bool PushLeftStickUp();
	bool PushLeftStickDown();
	bool PushLeftStickLeft();
	bool PushLeftStickRight();
};