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
	objPlayer->Initialize();
	for (int i = 0; i < 10; i++)
	{
		cloud[i]->SetPosition({(float)(8*i)-15.0f + (float)GetRand(-5,2),20 + (float)GetRand(-2,4),(float)GetRand(10,5) });
		cloudPos[i] = cloud[i]->GetPosition();
	}

	for (int y = 0; y < 6; y++)
	{
		for (int x = 0; x < 24; x++)
		{
			if (selectMap[y][x] == 1)
			{
				titleStageBox[y][x]->SetPosition({ 2.0f * x , -2.0f * y + 10.0f, 0 });
				stageBoxPos[y][x] = titleStageBox[y][x]->GetPosition();
			}
		}
	}
	// �J���������_���Z�b�g
	camera->SetTarget({ objPlayer->GetPosition().x + 10, 10, 0 });
	camera->SetDistance(20.0f);
	gameTimer = 180 * 61;
}

void GameScene::TitleUpdate()
{
#pragma region �X�V����
	//�_�̈ړ�
	{
		for (int i = 0; i < 10; i++)
		{
			cloudPos[i].x -= 0.01f;
			if (cloud[i]->GetPosition().x < objPlayer->GetPosition().x - 25.0f)
			{
				if (i == 0)
				{
					cloudPos[i] = { cloud[9]->GetPosition().x + 8.0f + (float)GetRand(-5,2),20 + (float)GetRand(-2,4),(float)GetRand(10,5) };
				}
				else
				{
					cloudPos[i] = { cloud[i - 1]->GetPosition().x + 8.0f + (float)GetRand(-5,2),20 + (float)GetRand(-2,4),(float)GetRand(10,5) };
				}
			}
			cloud[i]->SetPosition(cloudPos[i]);
		}
	}
	//�u���b�N�̃X�N���[��
	for (int y = 0; y < 6; y++)
	{
		for (int x = 0; x < 24; x++)
		{
			stageBoxPos[y][x].x -= 0.01f;
			if (selectMap[y][x] == 1 && titleStageBox[y][x]->GetPosition().x < objPlayer->GetPosition().x - 15)
			{
				if (x == 0)
				{
					stageBoxPos[y][x] = { titleStageBox[y][24 - 1]->GetPosition().x + 2.0f, -2.0f * y + 10.0f, 0 };
				}
				else
				{
					stageBoxPos[y][x] = { titleStageBox[y][x - 1]->GetPosition().x + 2.0f, -2.0f * y + 10.0f, 0 };
				}

			}
			titleStageBox[y][x]->SetPosition(stageBoxPos[y][x]);
		}
	}

	//�V�[���J��
	if (input->isKeyTrigger(DIK_N))
	{
		SceneTime = 0;
		audio->StopLoadedSound(soundData2);
		SceneNo = static_cast<int>(GameSceneNo::Stage1);
	}

	lightGroup->Update();
	particleMan->Update();
	camera->Update();
	objPlayer->Update();
	for (int y = 0; y < 6; y++)
	{
		for (int x = 0; x < 24; x++)
		{
			titleStageBox[y][x]->Update();
		}
	}

	for (int i = 0; i < 10; i++)
	{
		cloud[i]->Update();
	}
}

void GameScene::TitleDraw()
{
#pragma region �`�揈��

	/*�X�v���C�g�`��*/
	/*�X�v���C�g�`��O����*/
	Sprite::PreDraw(common->GetCmdList().Get());

	// �w�i�X�v���C�g�`��
	backGround->Draw();
	/*�X�v���C�g�`��㏈��*/
	Sprite::PostDraw();
	//�[�x�o�b�t�@�N���A
	common->ClearDepthBuffer();

	/*���f���`��*/
	/*���f���`��O����*/
	ModelObj::PreDraw(common->GetCmdList().Get());

	for (int i = 0; i < 10; i++)
	{
		cloud[i]->Draw();
	}
	objPlayer->Draw();
	for (int y = 0; y < 6; y++)
	{
		for (int x = 0; x < 24; x++)
		{
			titleStageBox[y][x]->Draw();
		}
	}

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
	titleSprite->Draw();

	/*�X�v���C�g�`��㏈��*/
	Sprite::PostDraw();
}

void GameScene::Stage1Init()
{
	//�����Đ�
	audio->PlayLoadedSound(soundData1, 0.05f);
	objPlayer->Initialize();
	for (int y = 0; y < Y_MAX; y++)
	{
		for (int x = 0; x < X_MAX; x++)
		{
			enemy[y][x]->Initialize();
		}
	}
	
	for (int y = 0; y < Y_MAX; y++)
	{
		for (int x = 0; x < X_MAX; x++)
		{
			objStageBox[y][x]->SetPosition({ -100, 0, 0 });
			enemy[y][x]->SetPosition({ -100, 0, 0 });
			enemy[y][x]->SetRotation({ 0,180,0 });

			if (map1[y][x] == 1)
			{
				objStageBox[y][x]->SetPosition({ 2.0f * x, -2.0f * y + Y_MAX * 2.0f, 0 });
			}
			if (map1[y][x] == 2)
			{
				enemy[y][x]->SetPosition({ 2.0f * x, -2.0f * y + Y_MAX * 2.0f + 0.5f, 0 });
			}
			if (map1[y][x] == 10)
			{
				objGoal->SetPosition({ 2.0f * x, -2.0f * y + Y_MAX * 2.0f - 0.5f, 0 });
				objGoal->SetScale({ 1.0f,3.0f,1.0f });
				objGoal->SetRotation({ 0, 90,0 });
			}
		}
	}
}

void GameScene::Stage1Update()
{
	//objPlayer->moveSphere(objStageBox);
	//camera->SetTarget(objPlayer->GetPosition());
	// �J���������_���Z�b�g
	camera->SetTarget({ objPlayer->GetPosition().x + 10, 12, 0});
	camera->SetDistance(20.0f);
	//�V�[���J��
	if (objPlayer->GetHP() == 0 || objPlayer->GetPosition().y < -Y_MAX * 2.0f-10 || gameTimer < 0)
	{
		SceneTime = 0;
		audio->StopLoadedSound(soundData1);
		SceneNo = static_cast<int>(GameSceneNo::GameOver);
	}

	gameTimer--;
	debugText->SetPos(1200, 50);
	debugText->SetSize(3);
	debugText->Printf("%d", gameTimer/180);

	//�_�̈ړ�
	{
		for (int i = 0; i < 10; i++)
		{
			cloudPos[i].x -= 0.01f;
			if (cloud[i]->GetPosition().x < objPlayer->GetPosition().x - 25.0f)
			{
				if (i == 0)
				{
					cloudPos[i] = { cloud[9]->GetPosition().x + 8.0f + (float)GetRand(-5,2),20 + (float)GetRand(-2,4),(float)GetRand(10,5) };
				}
				else
				{
					cloudPos[i] = { cloud[i - 1]->GetPosition().x + 8.0f + (float)GetRand(-5,2),20 + (float)GetRand(-2,4),(float)GetRand(10,5) };
				}
			}
			cloud[i]->SetPosition(cloudPos[i]);
		}
	}

	if (gameTimer < 180 * 60)
	{
		objPlayer->Move();
	}

	for (int y = 0; y < Y_MAX; y++)
	{
		for (int x = 0; x < X_MAX; x++)
		{
			objPlayer->CollisionObj(objStageBox[y][x]);
			objPlayer->CollisionEnemy(enemy[y][x]);
		}
	}

	if (objPlayer->CollisionGoal(objGoal) == true)
	{
		SceneTime = 0;
		audio->StopLoadedSound(soundData1);
		SceneNo = static_cast<int>(GameSceneNo::Clear);
	}

	lightGroup->Update();
	particleMan->Update();
	camera->Update();
	for (int i = 0; i < 10; i++)
	{
		cloud[i]->Update();
	}
	objPlayer->Update();
	for (int y = 0; y < Y_MAX; y++)
	{
		for (int x = 0; x < X_MAX; x++)
		{
			if (objStageBox[y][x]->GetPosition().x >= 0)
			{
				objStageBox[y][x]->Update();
			}
			if (enemy[y][x]->GetPosition().x >= 0)
			{
				enemy[y][x]->Update();
			}
		}
	}

	objGoal->Update();
}

void GameScene::Stage1Draw()
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
	for (int i = 0; i < 10; i++)
	{
		cloud[i]->Draw();
	}
	objPlayer->Draw();
	for (int y = 0; y < Y_MAX; y++)
	{
		for (int x = 0; x < X_MAX; x++)
		{
			if (enemy[y][x]->GetPosition().x >= 0)
			{
				enemy[y][x]->Draw();
			}
			if (objStageBox[y][x]->GetPosition().x >= 0)
			{
				objStageBox[y][x]->Draw();
			}
		}
	}

	objGoal->Draw();
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

void GameScene::Stage2Init()
{
}

void GameScene::Stage2Update()
{
}

void GameScene::Stage2Draw()
{
}

void GameScene::Stage3Init()
{
}

void GameScene::Stage3Update()
{
}

void GameScene::Stage3Draw()
{
}
void GameScene::Stage4Init()
{
}

void GameScene::Stage4Update()
{
}

void GameScene::Stage4Draw()
{
}
void GameScene::Stage5Init()
{
}

void GameScene::Stage5Update()
{
}

void GameScene::Stage5Draw()
{
}

void GameScene::GameOverInit()
{
}

void GameScene::GameOverUpdate()
{
	//�V�[���J��
	if (input->isKeyTrigger(DIK_N))
	{
		audio->PlayLoadedSound(soundData3, 0.05f);
		SceneTime = 0;
		SceneNo = static_cast<int>(GameSceneNo::Title);
	}
}

void GameScene::GameOverDraw()
{
	/*�X�v���C�g�`��*/
	/*�X�v���C�g�`��O����*/
	Sprite::PreDraw(common->GetCmdList().Get());
	GameOver->Draw();
	/*�X�v���C�g�`��㏈��*/
	Sprite::PostDraw();
	//�[�x�o�b�t�@�N���A
	common->ClearDepthBuffer();

}

void GameScene::ClearInit()
{
}

void GameScene::ClearUpdate()
{
	//�V�[���J��
	if (input->isKeyTrigger(DIK_N))
	{
		audio->PlayLoadedSound(soundData3, 0.05f);
		SceneTime = 0;
		SceneNo = static_cast<int>(GameSceneNo::Title);
	}
}

void GameScene::ClearDraw()
{
	/*�X�v���C�g�`��*/
	/*�X�v���C�g�`��O����*/
	Sprite::PreDraw(common->GetCmdList().Get());
	StageClear->Draw();
	/*�X�v���C�g�`��㏈��*/
	Sprite::PostDraw();
	//�[�x�o�b�t�@�N���A
	common->ClearDepthBuffer();

}

void GameScene::EndInit()
{
	objPlayer->Initialize();
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
	Sprite::LoadTexture(3, L"Resources/StageClear.png");
	Sprite::LoadTexture(4, L"Resources/GameOver.png");

	// �w�i�X�v���C�g����
	backGround = Sprite::Create(1, { WinApp::window_width/2.0f,WinApp::window_height/2.0f });
	titleSprite= Sprite::Create(2, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	StageClear = Sprite::Create(3, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	GameOver = Sprite::Create(4, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	// ���f���ǂݍ���
	modelPlayer = Model::CreateFromOBJ("player", true);
	modelEnemy = Model::CreateFromOBJ("enemy", true);
	modelStageBox = Model::CreateFromOBJ("StageBox", true);
	modelCloud = Model::CreateFromOBJ("cloud", true);
	modelGoal = Model::CreateFromOBJ("goal", true);
	// 3D�I�u�W�F�N�g����
	objPlayer = Player::Create(modelPlayer);

	for (int i = 0; i < 10; i++)
	{
		cloud[i] = ModelObj::Create(modelCloud);
	}
	for (int y = 0; y < Y_MAX; y++)
	{
		for (int x = 0; x < X_MAX; x++)
		{
			objStageBox[y][x] = ModelObj::Create(modelStageBox);
			enemy[y][x] = Enemy::Create(modelEnemy);
		}
	}

	for (int y = 0; y < 6; y++)
	{
		for (int x = 0; x < 24; x++)
		{
			titleStageBox[y][x] = ModelObj::Create(modelStageBox);
		}
	}

	objGoal = ModelObj::Create(modelGoal);

	// 3D�I�u�W�F�N�g�ɃJ�������Z�b�g
	ModelObj::SetCamera(camera.get());

	//���C�g�O���[�v���Z�b�g
	FBXObject3d::SetLightGroup(lightGroup.get());

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
	case static_cast<int>(GameScene::GameSceneNo::Stage1):
		Stage1Init();
		break;
	case static_cast<int>(GameScene::GameSceneNo::Stage2):
		Stage2Init();
		break;
	case static_cast<int>(GameScene::GameSceneNo::Stage3):
		Stage3Init();
		break;
	case static_cast<int>(GameScene::GameSceneNo::Stage4):
		Stage4Init();
		break;
	case static_cast<int>(GameScene::GameSceneNo::Stage5):
		Stage5Init();
		break;
	case static_cast<int>(GameScene::GameSceneNo::GameOver):
		GameOverInit();
		break;
	case static_cast<int>(GameScene::GameSceneNo::Clear):
		ClearInit();
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
	case static_cast<int>(GameScene::GameSceneNo::Stage1):
		SceneTime = 1;
		Stage1Update();
		break;
	case static_cast<int>(GameScene::GameSceneNo::Stage2):
		SceneTime = 1;
		Stage2Update();
		break;
	case static_cast<int>(GameScene::GameSceneNo::Stage3):
		Stage3Update();
		break;
	case static_cast<int>(GameScene::GameSceneNo::Stage4):
		SceneTime = 1;
		Stage4Update();
		break;
	case static_cast<int>(GameScene::GameSceneNo::Stage5):
		SceneTime = 1;
		Stage5Update();
		break;
	case static_cast<int>(GameScene::GameSceneNo::GameOver):
		SceneTime = 1;
		GameOverUpdate();
		break;
	case static_cast<int>(GameScene::GameSceneNo::Clear):
		SceneTime = 1;
		ClearUpdate();
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
	case static_cast<int>(GameScene::GameSceneNo::Stage1):
		Stage1Draw();
		break;
	case static_cast<int>(GameScene::GameSceneNo::Stage2):
		Stage2Draw();
		break;
	case static_cast<int>(GameScene::GameSceneNo::Stage3):
		Stage3Draw();
		break;
	case static_cast<int>(GameScene::GameSceneNo::Stage4):
		Stage4Draw();
		break;
	case static_cast<int>(GameScene::GameSceneNo::Stage5):
		Stage5Draw();
		break;
	case static_cast<int>(GameScene::GameSceneNo::GameOver):
		GameOverDraw();
		break;
	case static_cast<int>(GameScene::GameSceneNo::Clear):
		ClearDraw();
		break;
	case static_cast<int>(GameScene::GameSceneNo::End):
		EndDraw();
		break;
	default:
		break;
	}
}