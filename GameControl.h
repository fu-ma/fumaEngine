#pragma once
//‚±‚ÌƒQ[ƒ€‚ÌˆÚ“®“ü—Í‚ğ‚Ü‚Æ‚ß‚½ƒNƒ‰ƒX
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

