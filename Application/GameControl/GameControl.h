#pragma once
//���̃Q�[���̈ړ����͂��܂Ƃ߂��N���X
enum class Move
{
	LEFT,
	RIGHT,
	JUMP,
	JUMPTRIGGER,
	WALLJUMPLEFT,
	WALLJUMPRIGHT,
};

enum class Menu
{
	UPTRIGGER,
	DOWNTRIGGER,
	SPACETRIGGER,
	ESCAPETRIGGER,
	ANYKEYBORD,
	ANYPAD,
};

class GameControl
{
public:
	bool menuControl(const Menu &menu);
	bool moveControl(const Move &move);
};

