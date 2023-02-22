#include "GameControl.h"
#include "Engine/Input/Input.h"
#include"Engine/Input/Controller.h"

void GameControl::moveControl(const Move &move)
{
	Input *input = Input::GetInstance();
	Controller *controller = Controller::GetInstance();

	if (move == Move::LEFT)
	{

	}
	else if (move == Move::RIGHT)
	{

	}
	else if (move == Move::JUMP)
	{

	}
	else if (move == Move::WALLJUMPLEFT)
	{

	}
	else if (move == Move::WALLJUMPRIGHT)
	{

	}
}
