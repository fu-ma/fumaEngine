#include "ThornStick.h"

ThornStick *ThornStick::Create(Model *model)
{
	// 3Dオブジェクトのインスタンスを生成
	ThornStick *instance = new ThornStick();
	if (instance == nullptr) {
		return nullptr;
	}

	// 初期化
	if (!instance->Initialize())
	{
		delete instance;
		assert(0);
	}

	if (model)
	{
		instance->SetModel(model);
	}

	return instance;
}

void ThornStick::Move()
{
	timer++;
	if (timer < 60)
	{
		moveStartT += 0.005f;
		easing::Updete(rotateY, 5, 3, moveStartT);
		if (direction == ThornDirection::UP)
		{
			easing::Updete(moveY, -0.2, 3, moveStartT);
		}
		if (direction == ThornDirection::DOWN)
		{
			easing::Updete(moveY, 0.2, 3, moveStartT);
		}
		if (direction == ThornDirection::LEFT)
		{
			easing::Updete(moveX, 0.2, 3, moveStartT);
		}
		if (direction == ThornDirection::RIGHT)
		{
			easing::Updete(moveX, -0.2, 3, moveStartT);
		}
	}
	else if (timer == 60)
	{
		rotateY = 0;
		moveY = 0;
		moveX = 0;
	}
	else if (timer < 120)
	{
		moveStartT = 0;
		moveT += 0.005f;
		easing::Updete(rotateY, -10, 3, moveT);
		if (direction == ThornDirection::UP)
		{
			easing::Updete(moveY, 0.5, 3, moveT);
		}
		if (direction == ThornDirection::DOWN)
		{
			easing::Updete(moveY, -0.5, 3, moveT);
		}
		if (direction == ThornDirection::LEFT)
		{
			easing::Updete(moveX, -0.5, 3, moveT);
		}
		if (direction == ThornDirection::RIGHT)
		{
			easing::Updete(moveX, 0.5, 3, moveT);
		}

	}
	else if (timer == 120)
	{
		posY = position.y;
		posX = position.x;
		rotateY = 0;
		moveY = 0;
		moveX = 0;
	}
	else if (timer < 180)
	{
		moveT = 0;
		moveEndT += 0.005f;
		if (direction == ThornDirection::UP || direction == ThornDirection::DOWN)
		{
			easing::Updete(posY, oldPosY, 3, moveEndT);
			position.y = (float)posY;
		}
		if (direction == ThornDirection::LEFT || direction == ThornDirection::RIGHT)
		{
			easing::Updete(posX, oldPosX, 3, moveEndT);
			position.x = (float)posX;
		}
	}
	else
	{
		moveEndT = 0;
		timer = 0;
	}

	if (direction == ThornDirection::UP)
	{
		//position.x += (float)moveX;
		position.y += (float)moveY;

		rotation.y += (float)rotateY;
	}
	if (direction == ThornDirection::DOWN)
	{
		//position.x += (float)moveX;
		position.y += (float)moveY;

		rotation.y += (float)rotateY;
	}
	if (direction == ThornDirection::LEFT)
	{
		position.x += (float)moveX;
		//position.y += (float)moveY;

		rotation.x += (float)rotateY;
	}
	if (direction == ThornDirection::RIGHT)
	{
		position.x += (float)moveX;
		//position.y += (float)moveY;

		rotation.x += (float)rotateY;
	}
}

bool ThornStick::Initialize()
{
	if (!ModelObj::Initialize())
	{
		return false;
	}

	moveX = 0;
	moveY = 0;
	rotateY = 0;
	moveStartT = 0;
	moveT = 0;
	moveEndT = 0;
	timer = 0;
	scale = { 1.4f,1.0f,1.4f };

	if (direction == ThornDirection::UP)
	{
		rotation.x = 0;
	}
	if (direction == ThornDirection::DOWN)
	{
		rotation.x = 180;
	}
	if (direction == ThornDirection::LEFT)
	{
		rotation.z = 90;
	}
	if (direction == ThornDirection::RIGHT)
	{
		rotation.z = 270;
	}

	return true;
}

void ThornStick::Update()
{
	// 行列の更新など
	ModelObj::Update();
}

void ThornStick::Draw()
{
	//描画
	ModelObj::Draw();
}
