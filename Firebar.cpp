#include "Firebar.h"

Firebar *Firebar::Create(Model *model)
{
	// 3Dオブジェクトのインスタンスを生成
	Firebar *instance = new Firebar();
	if (instance == nullptr) {
		return nullptr;
	}

	// 初期化
	if (!instance->Initialize()) {
		delete instance;
		assert(0);
	}

	if (model) {
		instance->SetModel(model);
	}

	return instance;
}

bool Firebar::Initialize()
{
	if (!ModelObj::Initialize())
	{
		return false;
	}

	angle = 0;
	addX = 0;
	addY = 0;
	length = 0;
	moveFlag = false;

	return true;
}

void Firebar::Update()
{
	// 行列の更新など
	ModelObj::Update();
}

void Firebar::Move(float centerX,float centerY,float length, bool direction)
{
	float radius = angle * 3.14f / 180.0f;
	this->length = length;

	addX = cos(radius) * this->length;
	addY = sin(radius) * this->length;

	position.x = centerX + addX;
	position.y = centerY + addY;

	if (moveFlag == true)
	{
		if (direction == false)
		{
			angle -= 0.5f;
		}
		if (direction == true)
		{
			angle += 0.5f;
		}
	}
}

void Firebar::Draw()
{
	ModelObj::Draw();
}