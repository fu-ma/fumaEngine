#include "Star.h"

Star *Star::Create(Model *model)
{
	// 3D�I�u�W�F�N�g�̃C���X�^���X�𐶐�
	Star *instance = new Star();
	if (instance == nullptr) {
		return nullptr;
	}

	// ������
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
	moveingFlag = false;
	return true;
}

void Star::GetStar()
{
	moveingFlag = true;
}

void Star::Moveing()
{
	if (moveingFlag == true)
	{
		rotation.y += 5;
		position.y += 0.2f;
		scale.x -= 0.02f;
		scale.y -= 0.02f;
		scale.z -= 0.02f;
		if (scale.x <= 0.05f && scale.x >= -0.05f)
		{
			toNotDisplay = true;
		}
	}
}

void Star::Update()
{
	Moveing();
	// �s��̍X�V�Ȃ�
	ModelObj::Update();
}

void Star::Draw()
{
	if (toNotDisplay == false)
	{
		ModelObj::Draw();
	}
}
