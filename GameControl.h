#pragma once
//このゲームの移動入力をまとめたクラス
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

