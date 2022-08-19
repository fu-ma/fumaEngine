#include "Controller.h"

WORD Controller::ThumbToPad(SHORT sThumbX, SHORT sThumbY, SHORT sDeadZone)
{
	WORD wButtons = 0;

	if (sThumbY >= sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_UP;
	}
	else if (sThumbY <= -sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_DOWN;
	}

	if (sThumbX <= -sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_LEFT;
	}
	else if (sThumbX >= sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_RIGHT;
	}

	return wButtons;
}

Controller *Controller::GetInstance()
{
	static Controller instance;

	return &instance;
}

void Controller::Initialize(DWORD controllerNum)
{
	//構造体のクリア
	ZeroMemory(&state, sizeof(XINPUT_STATE));
	
	dwResult = XInputGetState(controllerNum, &state);
	//接続成功
	if (dwResult == ERROR_SUCCESS)
	{
		return;
	}
	//接続失敗
	else
	{
		return;
	}
}

void Controller::Update(DWORD controllerNum)
{
	//構造体のクリア
	oldstate = state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));

	dwResult = XInputGetState(controllerNum, &state);

	if ((state.Gamepad.sThumbLX<XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		state.Gamepad.sThumbLX>-XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
		(state.Gamepad.sThumbLY<XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		state.Gamepad.sThumbLY>-XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		state.Gamepad.sThumbLX = 0;
		state.Gamepad.sThumbLY = 0;
	}

	//左スティックからの入力を方向パッドに変換
	state.Gamepad.wButtons |= ThumbToPad(state.Gamepad.sThumbLX, state.Gamepad.sThumbLY, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);

}

bool Controller::PushButton(int button)
{
	if (state.Gamepad.wButtons & button)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Controller::TriggerButton(int button)
{
	if ((state.Gamepad.wButtons & button) && !(oldstate.Gamepad.wButtons & button))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Controller::PushLt()
{
	if (state.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Controller::PushRt()
{
	if (state.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Controller::PushLeftStickUp()
{
	if (state.Gamepad.sThumbLY >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Controller::PushLeftStickDown()
{
	if (state.Gamepad.sThumbLY <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Controller::PushLeftStickLeft()
{
	if (state.Gamepad.sThumbLX <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Controller::PushLeftStickRight()
{
	if (state.Gamepad.sThumbLX >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		return true;
	}
	else
	{
		return false;
	}
}
