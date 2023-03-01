#include "GameScene.h"
#include <cassert>
#include <sstream>
#include <iomanip>
#include"FbxLoader.h"

#pragma warning(disable : 4996)

using namespace DirectX;

void GameScene::staticInit()
{
	//���N���X�̏�����
	Framework::staticInit();

	//���C�g����
	lightGroup.reset(LightGroup::Create());
	//3D�I�u�W�F�N�g�Ƀ��C�g���Z�b�g
	ModelObj::SetLightGroup(lightGroup.get());
	lightGroup->SetDirLightActive(0, true);
	lightGroup->SetDirLightActive(1, true);
	lightGroup->SetDirLightActive(2, true);

	lightGroup->SetSpotLightActive(0, false);
	lightGroup->SetCircleShadowActive(0, true);

	// 3D�I�u�W�F�N�g�ɃJ�������Z�b�g
	ModelObj::SetCamera(camera.get());

	//���C�g�O���[�v���Z�b�g
	FBXObject3d::SetLightGroup(lightGroup.get());

	manager = new GameSceneManager();
	////�c�@��ݒ�
	wholeScene = WholeScene::GetInstance();
	wholeScene->StaticInit();
}

void GameScene::Init()
{
	//���N���X�̏�����
	Framework::Init();

	manager->Initialize(camera.get(), audio.get(), fps.get());
}

bool GameScene::Update()
{
	//���N���X�̍X�V
	if (Framework::Update() == false)
	{
		return false;
	}

	manager->Update(debugText,audio.get(), lightGroup.get(), camera.get(), fps.get());

	return true;
}

void GameScene::Draw()
{
	//�`��J�n
	common->PreDraw();
	manager->Draw(common.get(), debugText);
	//�`��I��
	common->PostDraw();
	manager->StateDelete();
}