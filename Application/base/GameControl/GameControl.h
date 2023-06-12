#pragma once
//‚±‚ÌƒQ[ƒ€‚ÌˆÚ“®“ü—Í‚ğ‚Ü‚Æ‚ß‚½ƒNƒ‰ƒX
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

