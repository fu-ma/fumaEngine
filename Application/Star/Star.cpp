#include "Star.h"

Star *Star::Create(Model *model)
{
	// 3Dオブジェクトのインスタンスを生成
	Star *instance = new Star();
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

bool Star::Initialize()
{
	if (!ModelObj::Initialize())
	{
		return false;
	}

	toNotDisplay = false;
	return true;
}

void Star::GetStar()
{
	//とりあえず取得したら消えるだけ
	toNotDisplay = true;
}

void Star::Update()
{
	// 行列の更新など
	ModelObj::Update();
}

void Star::Draw()
{
	if (toNotDisplay == false)
	{
		ModelObj::Draw();
	}
}
