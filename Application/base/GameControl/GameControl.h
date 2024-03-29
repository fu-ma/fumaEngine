#pragma once
//このゲームの移動入力をまとめたクラス
enum class Move
{
	LEFT,
	RIGHT,
	JUMP,
	JUMPTRIGGER,
	WALLJUMPLEFT,
	WALLJUMPRIGHT,
	LEFTTRIGER,
	RIGHTTRIGER,
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

