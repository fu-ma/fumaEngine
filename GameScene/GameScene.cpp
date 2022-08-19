#include "GameScene.h"
#include <cassert>
#include <sstream>
#include <iomanip>
#include"FbxLoader.h"

#pragma warning(disable : 4996)

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
}

void GameScene::TitleDraw()
{
#pragma region �`�揈��

	/*�X�v���C�g�`��*/
	/*�X�v���C�g�`��O����*/
	Sprite::PreDraw(common->GetCmdList().Get());

	// �w�i�X�v���C�g�`��
	titleSprite->Draw();
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
	//debugText->DrawAll(common->GetCmdList().Get());

	/*�X�v���C�g�`��㏈��*/
	Sprite::PostDraw();
}

void GameScene::GamePlayInit()
{
	//�����Đ�
	audio->PlayLoadedSound(soundData1, 0.05f);
	objFighter->Initialize();
	for (int y = 0; y < 6; y++)
	{
		for (int x = 0; x < 24; x++)
		{
			enemy[y][x]->Initialize();
			enemy[y][x]->SetPosition({ -100.0f, -100.0f, 0 });
		}
	}
	objFighter->SetPosition({ 10,2,0 });
	
	object1->SetPosition({ 0,5,0 });

	object1->PlayAnimation();
	for (int y = 0; y < 6; y++)
	{
		for (int x = 0; x < 24; x++)
		{
			if (map1[y][x] == 1)
			{
				objStageBox[y][x]->SetPosition({ 2.0f * x, -2.0f * y + 10.0f, 0 });
			}
			if (map1[y][x] == 2)
			{
				enemy[y][x]->SetPosition({ 2.0f * x, -2.0f * y + 10.0f, 0 });
			}
		}
	}
	gameTimer = 0;
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
	// �J���������_���Z�b�g
	camera->SetTarget({ objFighter->GetPosition().x + 10, 10, 0});
	camera->SetDistance(20.0f);

	//�V�[���J��
	if (input->isKeyTrigger(DIK_N))
	{
		SceneTime = 0;
		audio->StopLoadedSound(soundData1);
		SceneNo = static_cast<int>(GameSceneNo::End);
	}

	gameTimer++;

	if (gameTimer > 60)
	{
		objFighter->Move();
	}

	for (int y = 0; y < 6; y++)
	{
		for (int x = 0; x < 24; x++)
		{
			objFighter->CollisionObj(objStageBox[y][x]);
			objFighter->CollisionEnemy(enemy[y][x]);
		}
	}

	lightGroup->Update();
	particleMan->Update();
	camera->Update();
	//objSkydome->Update();
	//objGround->Update();
	objFighter->Update();
	for (int y = 0; y < 6; y++)
	{
		for (int x = 0; x < 24; x++)
		{
			enemy[y][x]->Update();
			objStageBox[y][x]->Update();
		}
	}
	//FBX�p�̃I�u�W�F�N�g�̍X�V
	object1->Update();
}

void GameScene::GamePlayDraw()
{
#pragma region �`�揈��

	///*�X�v���C�g�`��*/
	///*�X�v���C�g�`��O����*/
	Sprite::PreDraw(common->GetCmdList().Get());

	//// �w�i�X�v���C�g�`��
	backGround->Draw();
	///*�X�v���C�g�`��㏈��*/
	Sprite::PostDraw();
	////�[�x�o�b�t�@�N���A
	common->ClearDepthBuffer();

	/*���f���`��*/
	/*���f���`��O����*/
	ModelObj::PreDraw(common->GetCmdList().Get());

	//objSkydome->Draw();
	//objGround->Draw();
	//FBX
	object1->Draw(common->GetCmdList().Get());
	objFighter->Draw();
	for (int y = 0; y < 6; y++)
	{
		for (int x = 0; x < 24; x++)
		{
			enemy[y][x]->Draw();
			objStageBox[y][x]->Draw();
		}
	}
	//objSphere->Draw();
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
	Sprite::LoadTexture(1, L"Resources/backGround3.png");
	Sprite::LoadTexture(2, L"Resources/titleSprite.png");
	// �w�i�X�v���C�g����
	backGround = Sprite::Create(1, { WinApp::window_width/2.0f,WinApp::window_height/2.0f });
	titleSprite= Sprite::Create(2, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	// ���f���ǂݍ���
	//modelSkydome = Model::CreateFromOBJ("skydome", true);
	//modelGround = Model::CreateFromOBJ("ground", true);
	modelFighter = Model::CreateFromOBJ("player", true);
	//modelSphere = Model::CreateFromOBJ("sphere");
	modelStageBox = Model::CreateFromOBJ("StageBox", true);
	// 3D�I�u�W�F�N�g����
	objFighter = Player::Create(modelFighter);

	//objSkydome = ModelObj::Create(modelSkydome);
	//objGround = TouchableObject::Create(modelGround);
	//objSphere = ModelObj::Create(modelSphere);
	for (int y = 0; y < 6; y++)
	{
		for (int x = 0; x < 24; x++)
		{
			objStageBox[y][x] = ModelObj::Create(modelStageBox);
			enemy[y][x] = Enemy::Create(modelFighter);
		}
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
