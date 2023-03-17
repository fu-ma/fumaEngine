#include "GameCollision.h"

bool GameCollision::CollisionPlayerLeftToObj(Player *player, ModelObj *obj, XMFLOAT3 objScale)
{
	if (CheckBox2Box({ player->GetPosition().x - 0.2f,player->GetPosition().y,0},
		{ obj->GetPosition().x + 0.2f,obj->GetPosition().y,0 },
		player->GetScale().x - 0.2f, player->GetScale().y - 0.2f, objScale.x, objScale.y))
	{
		return true;
	}
	return false;
}

bool GameCollision::CollisionPlayerRightToObj(Player *player, ModelObj *obj, XMFLOAT3 objScale)
{
	if (CheckBox2Box({ player->GetPosition().x + 0.2f,player->GetPosition().y,0 },
		{ obj->GetPosition().x - 0.2f,obj->GetPosition().y,0 },
		player->GetScale().x - 0.2f, player->GetScale().y - 0.2f, objScale.x, objScale.y))
	{
		return true;
	}
	return false;
}

bool GameCollision::CollisionPlayerDownToObj(Player *player, ModelObj *obj, XMFLOAT3 objScale)
{
	if (CheckBox2Box({ player->GetPosition().x + 0.2f,player->GetPosition().y - 0.2f,0 },
		{ obj->GetPosition().x + 0.2f,obj->GetPosition().y + 0.2f,0 },
		player->GetScale().x - player->GetMoveSpeed() - 0.2f, player->GetScale().y + 0.01f, objScale.x, objScale.y))
	{
		return true;
	}
	return false;
}

bool GameCollision::CollisionPlayerUpToObj(Player *player, ModelObj *obj, XMFLOAT3 objScale)
{
	if (CheckBox2Box({ player->GetPosition().x - 0.2f,player->GetPosition().y + 0.2f,0 },
		{ obj->GetPosition().x - 0.2f,obj->GetPosition().y - 0.2f,0 },
		player->GetScale().x - player->GetMoveSpeed() - 0.2f, player->GetScale().y - 0.01f, objScale.x, objScale.y))
	{
		return true;
	}
	return false;
}

bool GameCollision::CollisionPlayerLeftAndRightToEnemy(Player *player, Enemy *enemy)
{
	if (CheckBox2Box({ player->GetPosition().x,player->GetPosition().y,0 },
		{ enemy->GetPosition().x,enemy->GetPosition().y,0 },
		player->GetScale().x + 0.2f, player->GetScale().y - 0.2f, enemy->GetScale().x + enemy->GetSpeed(), enemy->GetScale().y))
	{
		return true;
	}
	return false;
}

bool GameCollision::CollisionPlayerDownToEnemy(Player *player, Enemy *enemy)
{
	if (CheckBox2Box({ player->GetPosition().x,player->GetPosition().y,0 },
		{ enemy->GetPosition().x,enemy->GetPosition().y,0 },
		player->GetScale().x, player->GetScale().y - 0.3f, enemy->GetScale().x + enemy->GetSpeed(), enemy->GetScale().y))
	{
		return true;
	}
	return false;
}

bool GameCollision::CollisionPlayerUpToEnemy(Player *player, Enemy *enemy)
{
	if (Collision::CheckBox2Box({ player->GetPosition().x + 0.1f,player->GetPosition().y - 0.1f,0 },
		{ enemy->GetPosition().x + 0.1f,enemy->GetPosition().y + 0.1f,0 },
		player->GetScale().x - 0.2f, player->GetScale().y + 0.2f, enemy->GetScale().x, enemy->GetScale().y))
	{
		return true;
	}
	return false;
}

bool GameCollision::CollisionPlayerToGimmick(Player *player, ModelObj *gimmick, XMFLOAT3 gimmickScale)
{
	if (Collision::CheckBox2Box({ player->GetPosition().x,player->GetPosition().y,0 },
		{ gimmick->GetPosition().x,gimmick->GetPosition().y,0 },
		player->GetScale().x, player->GetScale().y, gimmickScale.x, gimmickScale.y))
	{
		return true;
	}
	return false;
}

bool GameCollision::CollisionPlayerToGoalflag(Player *player, ModelObj *goal)
{
	if (Collision::CheckBox2Box({ player->GetPosition().x,player->GetPosition().y,0 },
		{ goal->GetPosition().x,goal->GetPosition().y,0 },
		player->GetScale().x, player->GetScale().y, goal->GetScale().x, 10.0f))
	{
		return true;
	}
	return false;
}

bool GameCollision::CollisionPlayerToGoal(Player *player, ModelObj *goal)
{
	if (Collision::CheckBox2Box({ player->GetPosition().x,player->GetPosition().y,0 },
		{ goal->GetPosition().x,goal->GetPosition().y,0 },
		player->GetScale().x, player->GetScale().y, goal->GetScale().x, goal->GetScale().y))
	{
		return true;
	}
	return false;
}
