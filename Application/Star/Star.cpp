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
	return true;
}

void Star::GetStar()
{
	//�Ƃ肠�����擾����������邾��
	toNotDisplay = true;
}

void Star::Update()
{
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
