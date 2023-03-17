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
		easing::Updete(moveY, -0.2, 3, moveStartT);
	}
	else if (timer == 60)
	{
		rotateY = 0;
		moveY = 0;
	}
	else if (timer < 120)
	{
		moveStartT = 0;
		moveT += 0.005f;
		easing::Updete(rotateY, -10, 3, moveT);
		easing::Updete(moveY, 0.5, 3, moveT);
	}
	else if (timer == 120)
	{
		posY = position.y;
		rotateY = 0;
		moveY = 0;
	}
	else if (timer < 180)
	{
		moveT = 0;
		moveEndT += 0.005f;
		easing::Updete(posY, oldPosY, 3, moveEndT);
		position.y = (float)posY;
	}
	else
	{
		moveEndT = 0;
		timer = 0;
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
	oldPosY = position.y;
	scale = { 1.4f,1.0f,1.4f };

	return true;
}

void ThornStick::Update()
{
	position.x += (float)moveX;
	position.y += (float)moveY;

	rotation.y += (float)rotateY;
	// 行列の更新など
	ModelObj::Update();
}

void ThornStick::Draw()
{
	//描画
	ModelObj::Draw();
}
