#pragma once
//���̃Q�[���̈ړ����͂��܂Ƃ߂��N���X
enum class Move
{
	LEFT,
	RIGHT,
	JUMP,
	WALLJUMPLEFT,
	WALLJUMPRIGHT,
};

class GameControl
{
	void moveControl(const Move &move);
};

