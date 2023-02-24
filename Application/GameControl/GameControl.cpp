#include "GameControl.h"
#include "Engine/Input/Input.h"
#include"Engine/Input/Controller.h"

bool GameControl::menuControl(const Menu &menu)
{
	Input *input = Input::GetInstance();
	Controller *controller = Controller::GetInstance();

	if (menu == Menu::UPTRIGGER)
	{
		if (input->isKeyTrigger(DIK_W) || controller->TriggerButton(static_cast<int>(Button::UP)) == true)
		{
			return true;
		}
		return false;
	}
	else if (menu == Menu::DOWNTRIGGER)
	{
		if (input->isKeyTrigger(DIK_S) || controller->TriggerButton(static_cast<int>(Button::DOWN)) == true)
		{
			return true;
		}
		return false;
	}
	else if (menu == Menu::SPACETRIGGER)
	{
		if (input->isKeyTrigger(DIK_SPACE) || controller->TriggerButton(static_cast<int>(Button::A)) == true)
		{
			return true;
		}
		return false;
	}
	else if (menu == Menu::ESCAPETRIGGER)
	{
		if (input->isKeyTrigger(DIK_ESCAPE) || controller->TriggerButton(static_cast<int>(Button::START)) == true)
		{
			return true;
		}
		return false;
	}
	else if (menu == Menu::ANYKEYBORD)
	{
		if (input->isKeyTrigger(DIK_ESCAPE) || input->isKeyTrigger(DIK_A) || input->isKeyTrigger(DIK_B) || input->isKeyTrigger(DIK_C) || input->isKeyTrigger(DIK_D) ||
			input->isKeyTrigger(DIK_E) || input->isKeyTrigger(DIK_F) || input->isKeyTrigger(DIK_G) || input->isKeyTrigger(DIK_H) || input->isKeyTrigger(DIK_I) ||
			input->isKeyTrigger(DIK_J) || input->isKeyTrigger(DIK_K) || input->isKeyTrigger(DIK_L) || input->isKeyTrigger(DIK_M) || input->isKeyTrigger(DIK_N) ||
			input->isKeyTrigger(DIK_O) || input->isKeyTrigger(DIK_P) || input->isKeyTrigger(DIK_Q) || input->isKeyTrigger(DIK_R) || input->isKeyTrigger(DIK_S) ||
			input->isKeyTrigger(DIK_T) || input->isKeyTrigger(DIK_U) || input->isKeyTrigger(DIK_V) || input->isKeyTrigger(DIK_W) || input->isKeyTrigger(DIK_X) ||
			input->isKeyTrigger(DIK_Y) || input->isKeyTrigger(DIK_Z) || input->isKeyTrigger(DIK_SPACE) || input->isKeyTrigger(DIK_RETURN))
		{
			return true;
		}
		return false;
	}
	else if (menu == Menu::ANYPAD)
	{
		if (controller->TriggerButton(static_cast<int>(Button::START)) || controller->TriggerButton(static_cast<int>(Button::A)) ||
			controller->TriggerButton(static_cast<int>(Button::B)) || controller->TriggerButton(static_cast<int>(Button::X)) ||
			controller->TriggerButton(static_cast<int>(Button::Y)) || controller->TriggerButton(static_cast<int>(Button::LEFT)) ||
			controller->TriggerButton(static_cast<int>(Button::RIGHT)) || controller->TriggerButton(static_cast<int>(Button::UP)) ||
			controller->TriggerButton(static_cast<int>(Button::DOWN)))
		{
			return true;
		}
		return false;
	}
	return false;
}

bool GameControl::moveControl(const Move &move)
{
	Input *input = Input::GetInstance();
	Controller *controller = Controller::GetInstance();

	if (move == Move::LEFT)
	{
		if ((input->isKey(DIK_A) || controller->PushButton(static_cast<int>(Button::LEFT)) == true) &&
			input->isKey(DIK_D) == false && controller->PushButton(static_cast<int>(Button::RIGHT)) == false)
		{
			return true;
		}
		return false;
	}
	else if (move == Move::RIGHT)
	{
		if ((input->isKey(DIK_D) || controller->PushButton(static_cast<int>(Button::RIGHT)) == true) &&
			(input->isKey(DIK_A) == false && controller->PushButton(static_cast<int>(Button::LEFT)) == false))
		{
			return true;
		}
		return false;
	}
	else if (move == Move::JUMP)
	{
		if (input->isKey(DIK_SPACE) || controller->PushButton(static_cast<int>(Button::A)) == true)
		{
			return true;
		}
		return false;
	}
	else if (move == Move::JUMPTRIGGER)
	{
		if (input->isKeyTrigger(DIK_SPACE) || controller->TriggerButton(static_cast<int>(Button::A)) == true)
		{
			return true;
		}
		return false;
	}
	else if (move == Move::WALLJUMPLEFT)
	{
		if (input->isKeyTrigger(DIK_SPACE) || controller->TriggerButton(static_cast<int>(Button::A)) == true)
		{
			return true;
		}
		return false;
	}
	else if (move == Move::WALLJUMPRIGHT)
	{
		if (input->isKeyTrigger(DIK_SPACE) || controller->TriggerButton(static_cast<int>(Button::A)) == true)
		{
			return true;
		}
		return false;
	}

	return false;
}
