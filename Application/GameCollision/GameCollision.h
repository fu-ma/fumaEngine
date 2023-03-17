#pragma once
#include"Collision.h"
#include"Player.h"
#include"ModelObj.h"
#include"Enemy.h"

class GameCollision : public Collision
{
	using XMFLOAT3 = DirectX::XMFLOAT3;
public:
	static bool CollisionPlayerLeftToObj(Player *player, ModelObj *obj, XMFLOAT3 objScale = {1,1,1});
	static bool CollisionPlayerRightToObj(Player *player, ModelObj *obj, XMFLOAT3 objScale = { 1,1,1 });
	static bool CollisionPlayerDownToObj(Player *player, ModelObj *obj, XMFLOAT3 objScale = { 1,1,1 });
	static bool CollisionPlayerUpToObj(Player *player, ModelObj *obj, XMFLOAT3 objScale = { 1,1,1 });

	static bool CollisionPlayerLeftAndRightToEnemy(Player *player, Enemy *enemy);
	static bool CollisionPlayerDownToEnemy(Player *player, Enemy *enemy);
	static bool CollisionPlayerUpToEnemy(Player *player, Enemy *enemy);

	static bool CollisionPlayerToGimmick(Player *player, ModelObj *gimmick,XMFLOAT3 gimmickScale);
	static bool CollisionPlayerToGoalflag(Player *player, ModelObj *goal);
	static bool CollisionPlayerToGoal(Player *player, ModelObj *goal);
};

