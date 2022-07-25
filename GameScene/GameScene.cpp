#include "GameScene.h"
#include <cassert>
#include <sstream>
#include <iomanip>
#include"FbxLoader.h"

using namespace DirectX;

void GameScene::TitleInit()
{
	audio->PlayLoadedSound(soundData2, 0.05f);
	objFighter->SetPosition({ 1,1,0 });
	//objSphere->SetPosition({ -1,1,0 });
	// �J���������_���Z�b�g
	camera->SetTarget({ 0, 1, 0 });
	camera->SetDistance(3.0f);
}

void GameScene::TitleUpdate()
{
#pragma region �X�V����

	//�V�[���J��
	if (input->isKeyTrigger(DIK_N))
	{
		SceneTime = 0;
		audio->StopLoadedSound(soundData2);
		SceneNo = static_cast<int>(GameSceneNo::GamePlay);
	}

	lightGroup->Update();
	particleMan->Update();
	camera->Update();
	//objSkydome->Update();
	//objGround->Update();
	objFighter->Update();
	//objSphere->Update();
	for (int i = 0; i < 20; i++)
	{
		objStageBox[i]->Update();
	}
}

void GameScene::TitleDraw()
{
#pragma region �`�揈��

	/*�X�v���C�g�`��*/
	/*�X�v���C�g�`��O����*/
	Sprite::PreDraw(common->GetCmdList().Get());

	// �w�i�X�v���C�g�`��
	spriteBG->Draw();
	/*�X�v���C�g�`��㏈��*/
	Sprite::PostDraw();
	//�[�x�o�b�t�@�N���A
	common->ClearDepthBuffer();

	/*���f���`��*/
	/*���f���`��O����*/
	ModelObj::PreDraw(common->GetCmdList().Get());

	/*���f���`��㏈��*/
	ModelObj::PostDraw();
	// �p�[�e�B�N���̕`��
	//particleMan->Draw(common->GetCmdList().Get());

	//�[�x�o�b�t�@�N���A
	common->ClearDepthBuffer();

	/*�X�v���C�g�`��*/
	/*�X�v���C�g�`��O����*/
	Sprite::PreDraw(common->GetCmdList().Get());
	// �f�o�b�O�e�L�X�g�̕`��
	debugText->DrawAll(common->GetCmdList().Get());

	/*�X�v���C�g�`��㏈��*/
	Sprite::PostDraw();
}

void GameScene::GamePlayInit()
{
	//�����Đ�
	audio->PlayLoadedSound(soundData1, 0.05f);
	//objFighter->SetPosition({ 1,1,0 });
	objFighter->SetScale({ 0.7f, 0.7f, 0.7f });
	//objSphere->SetScale({ 10, 10, 10 });
	objFighter->SetPosition({ 10,0,0 });
	// �J���������_���Z�b�g
	camera->SetTarget({ 10, 10, 0 });
	camera->SetDistance(20.0f);
	object1->SetPosition({ 0,5,0 });

	object1->PlayAnimation();
	for (int i = 0; i < 20; i++)
	{
		objStageBox[i]->SetPosition({ 2.0f * i, 0, 0 });
	}
}

void GameScene::GamePlayUpdate()
{
	//�}�e���A���p�����[�^�����f���ɔ��f
	model1->SetBaseColor(XMFLOAT3(0,1,1));
	model1->SetMetalness(1.0f);
	model1->SetSpecular(0.5f);
	model1->SetRoughness(0.3f);
	model1->TransferMaterial();

	//objFighter->moveSphere(objStageBox);
	//camera->SetTarget(objFighter->GetPosition());

	//�V�[���J��
	if (input->isKeyTrigger(DIK_N))
	{
		SceneTime = 0;
		audio->StopLoadedSound(soundData1);
		SceneNo = static_cast<int>(GameSceneNo::End);
	}

	for (int i = 0; i < 20; i++)
	{

		objFighter->CollisionObj(objStageBox[i]);
	}
	lightGroup->Update();
	particleMan->Update();
	camera->Update();
	//objSkydome->Update();
	//objGround->Update();
	objFighter->Update();
	//objSphere->Update();
	for (int i = 0; i < 20; i++)
	{

		objStageBox[i]->Update();
	}
	//FBX�p�̃I�u�W�F�N�g�̍X�V
	object1->Update();
}

void GameScene::GamePlayDraw()
{
#pragma region �`�揈��

	///*�X�v���C�g�`��*/
	///*�X�v���C�g�`��O����*/
	//Sprite::PreDraw(common->GetCmdList().Get());

	//// �w�i�X�v���C�g�`��
	//spriteBG->Draw();
	///*�X�v���C�g�`��㏈��*/
	//Sprite::PostDraw();
	////�[�x�o�b�t�@�N���A
	//common->ClearDepthBuffer();

	/*���f���`��*/
	/*���f���`��O����*/
	ModelObj::PreDraw(common->GetCmdList().Get());

	//objSkydome->Draw();
	//objGround->Draw();
	//FBX
	object1->Draw(common->GetCmdList().Get());
	objFighter->Draw();
	//objSphere->Draw();
	for (int i = 0; i < 20; i++)
	{

		objStageBox[i]->Draw();
	}
	// �p�[�e�B�N���̕`��
	particleMan->Draw(common->GetCmdList().Get());

	/*���f���`��㏈��*/
	ModelObj::PostDraw();

	//�[�x�o�b�t�@�N���A
	common->ClearDepthBuffer();

	/*�X�v���C�g�`��*/
	/*�X�v���C�g�`��O����*/
	Sprite::PreDraw(common->GetCmdList().Get());
	// �f�o�b�O�e�L�X�g�̕`��
	debugText->DrawAll(common->GetCmdList().Get());

	/*�X�v���C�g�`��㏈��*/
	Sprite::PostDraw();

}

void GameScene::EndInit()
{
}

void GameScene::EndUpdate()
{
	//�V�[���J��
	if (input->isKeyTrigger(DIK_N))
	{
		audio->PlayLoadedSound(soundData3, 0.05f);
		SceneTime = 0;
		SceneNo = static_cast<int>(GameSceneNo::Title);
	}

	lightGroup->Update();
	particleMan->Update();
	camera->Update();
	//objSkydome->Update();
	//objGround->Update();
	objFighter->Update();
	//objSphere->Update();
	for (int i = 0; i < 20; i++)
	{

		objStageBox[i]->Update();
	}

}

void GameScene::EndDraw()
{
	/*�X�v���C�g�`��*/
	/*�X�v���C�g�`��O����*/
	Sprite::PreDraw(common->GetCmdList().Get());

	/*�X�v���C�g�`��㏈��*/
	Sprite::PostDraw();
	//�[�x�o�b�t�@�N���A
	common->ClearDepthBuffer();
}

void GameScene::staticInit()
{
	//���N���X�̏�����
	Framework::staticInit();

	//���C�g����
	lightGroup.reset(LightGroup::Create());
	//3D�I�u�W�F�N�g�Ƀ��C�g���Z�b�g
	ModelObj::SetLightGroup(lightGroup.get());
	//lightGroup->SetDirLightActive(0, false);
	//lightGroup->SetDirLightActive(1, false);
	//lightGroup->SetDirLightActive(2, false);
	lightGroup->SetDirLightActive(0, true);
	lightGroup->SetDirLightActive(1, true);
	lightGroup->SetDirLightActive(2, true);

	//lightGroup->SetPointLightActive(0, false);
	//lightGroup->SetPointLightActive(1, false);
	//lightGroup->SetPointLightActive(2, false);
	lightGroup->SetSpotLightActive(0, true);
	lightGroup->SetCircleShadowActive(0, true);

	pointLightPos[0] = 0.5f;
	pointLightPos[1] = 1.0f;
	pointLightPos[2] = 0.0f;

	//�����ǂݍ���
	soundData1 = audio->SoundLoadWave("Resources/GAMEBGM.wav",true);
	soundData2 = audio->SoundLoadWave("Resources/TITLEBGM.wav",true);
	soundData3 = audio->SoundLoadWave("Resources/SPACESE.wav", false);

	// �e�N�X�`���ǂݍ���
	Sprite::LoadTexture(1, L"Resources/background.png");
	// �w�i�X�v���C�g����
	spriteBG = Sprite::Create(1, { 0.0f,0.0f });

	// ���f���ǂݍ���
	//modelSkydome = Model::CreateFromOBJ("skydome", true);
	//modelGround = Model::CreateFromOBJ("ground", true);
	modelFighter = Model::CreateFromOBJ("StageBox", true);
	//modelSphere = Model::CreateFromOBJ("sphere");
	modelStageBox = Model::CreateFromOBJ("StageBox", true);
	// 3D�I�u�W�F�N�g����
	objFighter = Player::Create(modelFighter);

	//objSkydome = ModelObj::Create(modelSkydome);
	//objGround = TouchableObject::Create(modelGround);
	//objSphere = ModelObj::Create(modelSphere);
	for (int i = 0; i < 20; i++)
	{
		objStageBox[i] = ModelObj::Create(modelStageBox);
	}
	//objFighter->SetParent(objSphere);

	// 3D�I�u�W�F�N�g�ɃJ�������Z�b�g
	ModelObj::SetCamera(camera.get());

	// ���f�������w�肵�ăt�@�C���ǂݍ���
	//FbxLoader::GetInstance()->LoadModelFromFile("cube");
	model1 = FbxLoader::GetInstance()->LoadModelFromFile("SpherePBR");
	//���C�g�O���[�v���Z�b�g
	FBXObject3d::SetLightGroup(lightGroup.get());

	//FBX�p��3D�I�u�W�F�N�g�����ƃ��f���̃Z�b�g
	object1 = new FBXObject3d;
	object1->Initialize();
	object1->SetModel(model1);

	// �p�[�e�B�N���}�l�[�W������
	// �p�[�e�B�N���}�l�[�W��������
	particleMan->SetCamera(camera.get());
}

void GameScene::Init()
{
	//���N���X�̏�����
	Framework::Init();

	switch (SceneNo)
	{
	case static_cast<int>(GameScene::GameSceneNo::Title):
		TitleInit();
		break;
	case static_cast<int>(GameScene::GameSceneNo::GamePlay):
		GamePlayInit();
		break;
	case static_cast<int>(GameScene::GameSceneNo::End):
		EndInit();
		break;
	default:
		break;
	}
}

bool GameScene::Update()
{
	//���N���X�̍X�V
	if (Framework::Update() == false)
	{
		return false;
	}

	switch (SceneNo)
	{
	case static_cast<int>(GameScene::GameSceneNo::Title):
		SceneTime = 1;
		TitleUpdate();
		break;
	case static_cast<int>(GameScene::GameSceneNo::GamePlay):
		SceneTime = 1;
		GamePlayUpdate();
		break;
	case static_cast<int>(GameScene::GameSceneNo::End):
		SceneTime = 1;
		EndUpdate();
		break;
	default:
		break;
	}

	return true;
}

void GameScene::Draw()
{

	switch (SceneNo)
	{
	case static_cast<int>(GameScene::GameSceneNo::Title):
		TitleDraw();
		break;
	case static_cast<int>(GameScene::GameSceneNo::GamePlay):
		GamePlayDraw();
		break;
	case static_cast<int>(GameScene::GameSceneNo::End):
		EndDraw();
		break;
	default:
		break;
	}
}
