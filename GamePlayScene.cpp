#include "GamePlayScene.h"
#include "TitleScene.h"
#include "GamePlayScene.h"
#include "EndScene.h"
#include"ClearScene.h"
#include"EndScene.h"
#include"SelectScene.h"
#include"GameOverScene.h"
#include"Resources.h"
#include"WholeScene.h"

void GamePlayScene::Initialize(GameSceneManager *pEngine, DebugCamera *camera, Audio *audio, Fps *fps)
{
	Resources *resources = Resources::GetInstance();
	WholeScene *wholeScene = WholeScene::GetInstance();

	// �w�i�X�v���C�g����
	backGround = Sprite::Create(1, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	playerIconSprite = Sprite::Create(12, { 64,64 });
	GameOver = Sprite::Create(4, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	goTitle = Sprite::Create(14, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f - WinApp::window_height / 6.0f });
	reStart = Sprite::Create(15, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	Return = Sprite::Create(16, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f + WinApp::window_height / 6.0f });
	ClearStageSprite = Sprite::Create(17, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	// 3D�I�u�W�F�N�g����
	objPlayer = Player::Create(resources->GetModel(ResourcesName::modelPlayer));

	for (int i = 0; i < 10; i++)
	{
		cloud[i] = ModelObj::Create(resources->GetModel(ResourcesName::modelCloud));
	}
	for (int y = 0; y < Y_MAX; y++)
	{
		for (int x = 0; x < X_MAX; x++)
		{
			objStageBox[y][x] = ModelObj::Create(resources->GetModel(ResourcesName::modelStageBox));
			enemy[y][x] = Enemy::Create(resources->GetModel(ResourcesName::modelEnemy));
			objRedBlock[y][x] = ModelObj::Create(resources->GetModel(ResourcesName::modelRedBlock));
			objBlueBlock[y][x] = ModelObj::Create(resources->GetModel(ResourcesName::modelBlueBlock));
		}
	}

	for (int i = 0; i < 10; i++)
	{
		cloud[i]->SetPosition({ (float)(8 * i) - 15.0f + (float)wholeScene->GetRand(-5,2),20 + (float)wholeScene->GetRand(-2,4),(float)wholeScene->GetRand(10,5) });
		cloudPos[i] = cloud[i]->GetPosition();
	}

	objGoal = ModelObj::Create(resources->GetModel(ResourcesName::modelGoal));

	playerParticle = new Particle();
	playerParticle->Initialize(resources->GetModel(ResourcesName::modelEnemy));
	//�J�E���g�_�E���N���X������
	countDown = new CountDown();
	if (wholeScene->GetSelectNum() == 0)
	{
		StageSet(map1, wholeScene->GetStageFireNum(), audio, fps);
	}
	if (wholeScene->GetSelectNum() == 1)
	{
		StageSet(map2, wholeScene->GetStageFireNum(), audio, fps);
	}
	if (wholeScene->GetSelectNum() == 2)
	{
		StageSet(map3, wholeScene->GetStageFireNum(), audio, fps);
	}
	if (wholeScene->GetSelectNum() == 3)
	{
		StageSet(map4, wholeScene->GetStageFireNum(), audio, fps);
	}
	if (wholeScene->GetSelectNum() == 4)
	{
		StageSet(map5, wholeScene->GetStageFireNum(), audio, fps);
	}

	objPlayer->SetPosition({ 10, 4, 0 });
}

void GamePlayScene::Update(GameSceneManager *pEngine, Audio* audio,DebugText *debugText, LightGroup *lightGroup, DebugCamera *camera, Fps *fps)
{
	StageUpdate(pEngine, audio, debugText, lightGroup, camera, fps);
}

void GamePlayScene::Draw(GameSceneManager *pEngine, DirectXApp *common, DebugText *debugText)
{
	StageDraw(common, debugText);
}

void GamePlayScene::StageSet(const int Map[Y_MAX][X_MAX], const int stageNum, Audio *audio, Fps *fps)
{
	Resources *resources = Resources::GetInstance();
	WholeScene *wholeScene = WholeScene::GetInstance();

	for (int y = 0; y < Y_MAX; y++)
	{
		for (int x = 0; x < X_MAX; x++)
		{
			map[y][x] = Map[y][x];
		}
	}
	objPlayer->Initialize();
	gimmickCenterNum = 0;
	enemyNum = 0;

	for (int y = 0; y < Y_MAX; y++)
	{
		for (int x = 0; x < X_MAX; x++)
		{

			objStageBox[y][x]->SetPosition({ -100, 0, 0 });
			enemy[y][x]->Initialize();
			enemy[y][x]->SetPosition({ -100, 0, 0 });
			enemy[y][x]->SetRotation({ 0,180,0 });
			objRedBlock[y][x]->SetPosition({ -100,0,0 });
			objBlueBlock[y][x]->SetPosition({ -100,0,0 });

			//�u���b�N
			if (map[y][x] == 1)
			{
				objStageBox[y][x]->SetPosition({ 2.0f * x, -2.0f * y + Y_MAX * 2.0f, 0 });
			}
			//�G
			if (map[y][x] == 2)
			{
				enemy[y][x]->SetPosition({ 2.0f * x, -2.0f * y + Y_MAX * 2.0f + 0.5f, 0 });
			}
			//�ԃu���b�N
			if (map[y][x] == 4)
			{
				objRedBlock[y][x]->SetPosition({ 2.0f * x, -2.0f * y + Y_MAX * 2.0f, 0 });
			}
			//�u���b�N
			if (map[y][x] == 5)
			{
				objBlueBlock[y][x]->SetPosition({ 2.0f * x, -2.0f * y + Y_MAX * 2.0f, 0 });
			}
			//�S�[��
			if (map[y][x] == 10)
			{
				objGoal->SetPosition({ 2.0f * x, -2.0f * y + Y_MAX * 2.0f - 0.5f, 0 });
				objGoal->SetScale({ 1.0f,3.0f,1.0f });
				objGoal->SetRotation({ 0, 90,0 });
			}
		}
	}

	for (int x = 0; x < X_MAX; x++)
	{
		for (int y = 0; y < Y_MAX; y++)
		{
			gimmickCenter[x] = { -100,0,0 };
			//�t�@�C�A�[�o�[
			if (map[y][x] == 3)
			{
				gimmickCenter[gimmickCenterNum] = { 2.0f * x, -2.0f * y + Y_MAX * 2.0f, 0 };
				gimmickCenterNum++;
			}
		}
	}

	fire.clear();
	for (int i = 0; i < gimmickCenterNum; i++)
	{
		wholeScene->SetStageData(wholeScene->GetStageDatas(stageNum - 1,i));
		firebar = new Firebar(gimmickCenter[i].x, gimmickCenter[i].y, wholeScene->GetStageData().firebarNum, wholeScene->GetStageData().direction, wholeScene->GetStageData().firebarSpeed);
		firebar->StaticInit();
		fire.push_back(firebar);
	}


	for (auto &fireBar : fire)
	{
		fireBar->Initialize();
	}

	gameTimer = (int)fps->GetFrame() * 60 * 2;

	//�J�E���g�_�E���p�̉摜�̏����l�̐ݒ�
	countDown->Initialize();

	gameOverFlag = false;
	skullSizeX = 1280 * 5;
	skullSizeY = 720 * 5;
	gameOverTime = 0;

	stopFlag = false;
	stopNum = 0;
	stopMoveTime = 0;
	if (stopNum == 0)
	{
		goTitleSpriteSize = stopSpriteMinSize;
		reStartSpriteSize = stopSpriteMinSize;
		ReturnSpriteSize = stopSpriteMaxSize;
	}

	clearStopFlag = false;
	audio->PlayLoadedSound(resources->GetSoundData(ResourcesName::soundData1), 0.05f);

	totalPlayer = wholeScene->GetTotalPlayerNum();
	selectNum = wholeScene->GetSelectNum();
}

void GamePlayScene::StageUpdate(GameSceneManager *pEngine, Audio *audio, DebugText *debugText, LightGroup *lightGroup, DebugCamera *camera, Fps *fps)
{
	Input *input = Input::GetInstance();
	Controller *controller = Controller::GetInstance();
	Resources *resources = Resources::GetInstance();
	WholeScene *wholeScene = WholeScene::GetInstance();

	// �J���������_���Z�b�g
	camera->SetTarget({ objPlayer->GetPosition().x + 10, 12, 0 });
	camera->SetDistance(20.0f);
	//�V�[���J��
	if ((playerParticle->GetFlag() == false && objPlayer->GetHP() == 0) || objPlayer->GetPosition().y < -Y_MAX * 2.0f - 10 || gameTimer < 0)
	{
		gameOverFlag = true;
	}

	//Esc���X�^�[�g�{�^���i�R���g���[���[�j���������Ƃ��Ɉꎞ��~����
	if (input->isKeyTrigger(DIK_ESCAPE) || controller->TriggerButton(static_cast<int>(Button::START)) == true)
	{
		stopFlag = !stopFlag;
	}

	if (stopFlag == true)
	{
		if (input->isKeyTrigger(DIK_W) || controller->TriggerButton(static_cast<int>(Button::UP)) == true)
		{
			if (stopNum < 2 && stopMoveTime >= 0.2f)
			{
				stopMoveTime = 0;
				stopNum++;
			}
		}
		else if (input->isKeyTrigger(DIK_S) || controller->TriggerButton(static_cast<int>(Button::DOWN)) == true)
		{
			if (stopNum > 0 && stopMoveTime >= 0.2f)
			{
				stopMoveTime = 0;
				stopNum--;
			}
		}
		else
		{
			stopMoveTime += 0.008f;
		}
	}
	if (stopNum == 0)
	{
		easing::Updete(goTitleSpriteSize, stopSpriteMinSize, InSine, stopMoveTime);
		easing::Updete(reStartSpriteSize, stopSpriteMinSize, InSine, stopMoveTime);
		easing::Updete(ReturnSpriteSize, stopSpriteMaxSize, InSine, stopMoveTime);
	}
	if (stopNum == 1)
	{
		easing::Updete(goTitleSpriteSize, stopSpriteMinSize, InSine, stopMoveTime);
		easing::Updete(reStartSpriteSize, stopSpriteMaxSize, InSine, stopMoveTime);
		easing::Updete(ReturnSpriteSize, stopSpriteMinSize, InSine, stopMoveTime);
	}
	if (stopNum == 2)
	{
		easing::Updete(goTitleSpriteSize, stopSpriteMaxSize, InSine, stopMoveTime);
		easing::Updete(reStartSpriteSize, stopSpriteMinSize, InSine, stopMoveTime);
		easing::Updete(ReturnSpriteSize, stopSpriteMinSize, InSine, stopMoveTime);
	}

	if (input->isKeyTrigger(DIK_SPACE) || controller->TriggerButton(static_cast<int>(Button::A)) == true)
	{
		//���h���{�^�����������Ƃ�
		if (stopNum == 0 && stopMoveTime >= 0.2f)
		{
			stopFlag = false;
		}

		//���X�^�[�g�{�^�����������Ƃ�
		if (stopNum == 1 && stopMoveTime >= 0.2f)
		{
			audio->StopLoadedSound(resources->GetSoundData(ResourcesName::soundData1));
			fire.clear();
			pEngine->changeState(new GamePlayScene());
			return;
		}

		//�Z���N�g�ɖ߂�{�^�����������Ƃ�
		if (stopNum == 2 && stopMoveTime >= 0.2f)
		{
			audio->StopLoadedSound(resources->GetSoundData(ResourcesName::soundData1));
			fire.clear();
			pEngine->changeState(new SelectScene());
			return;
		}
	}

	//�f�X���̉�ʑJ��
	if (gameOverFlag == true)
	{
		easing::Updete(skullSizeX, 1280, 3, gameOverTime);
		easing::Updete(skullSizeY, 720, 3, gameOverTime);
		gameOverTime += 0.001f;
		if (gameOverTime > 0.2)
		{
			audio->StopLoadedSound(resources->GetSoundData(ResourcesName::soundData1));
			//�c�@�����炷
			totalPlayer--;
			wholeScene->SetTotalPlayerNum(totalPlayer);

			if (wholeScene->GetTotalPlayerNum() == 0)
			{
				fire.clear();
				pEngine->changeState(new GameOverScene());
				return;
			}
			else
			{
				fire.clear();
				pEngine->changeState(new SelectScene());
				return;
			}
		}
		GameOver->SetSize({ (float)skullSizeX, (float)skullSizeY });
	}

	//3,2,1,�X�^�[�g
	if (stopFlag == false)
	{
		countDown->Update();
	}

	//�S�[�������Ƃ��Ɏ��Ԍv�����~�߂�
	if (objPlayer->GetPlayerStop() == true)
	{
		clearStopFlag = true;
	}
	//�X�^�[�ƕ\��������Ă��炵�΂炭����
	if (countDown->GetStart() >= 0.8)
	{
		//�ꎞ��~���Ă��Ȃ�������
		if (stopFlag == false && clearStopFlag == false)
		{
			gameTimer--;
		}
	}

	//�^�C�}�[��\��
	debugText->SetPos(1200, 50);
	debugText->SetSize(3);
	debugText->Printf("%d", gameTimer / (int)fps->GetFrame() / 2);

	//�v���C���[�̑�����\��
	debugText->SetPos(150, 64);
	debugText->SetSize(5);
	debugText->Printf("%d", wholeScene->GetTotalPlayerNum());

	//�_�̈ړ�
	{
		for (int i = 0; i < 10; i++)
		{
			cloudPos[i].x -= 0.01f;
			if (cloud[i]->GetPosition().x < objPlayer->GetPosition().x - 25.0f)
			{
				if (i == 0)
				{
					cloudPos[i] = { cloud[9]->GetPosition().x + 8.0f + (float)wholeScene->GetRand(-5,2),20 + (float)wholeScene->GetRand(-2,4),(float)wholeScene->GetRand(10,5) };
				}
				else
				{
					cloudPos[i] = { cloud[i - 1]->GetPosition().x + 8.0f + (float)wholeScene->GetRand(-5,2),20 + (float)wholeScene->GetRand(-2,4),(float)wholeScene->GetRand(10,5) };
				}
			}
			cloud[i]->SetPosition(cloudPos[i]);
		}
	}
	//�����悤�ɂȂ�
	if (countDown->GetStart() >= 0.2 && stopFlag == false)
	{
		if (playerParticle->GetFlag() == false)
		{
			objPlayer->notOnCollision();
		}
		if (objPlayer->GetHP() > 0 && gameOverFlag == false)
		{
			objPlayer->Move();
		}

		for (int y = 0; y < Y_MAX; y++)
		{
			for (int x = 0; x < X_MAX; x++)
			{
				if (enemy[y][x]->GetPosition().x >= 0)
				{
					enemy[y][x]->Move();
					for (int w = 0; w < Y_MAX; w++)
					{
						for (int z = 0; z < X_MAX; z++)
						{
							enemy[y][x]->CollisionObject(objStageBox[w][z]);
						}
					}
				}
			}
		}

		for (auto &fireBar : fire)
		{
			fireBar->Move();
		}
	}

	//�����蔻��
	if (countDown->GetStart() >= 0.2 && stopFlag == false)
	{
		for (int y = 0; y < Y_MAX; y++)
		{
			for (int x = 0; x < X_MAX; x++)
			{
				objPlayer->CollisionObj(objStageBox[y][x]);
				objPlayer->CollisionEnemy(enemy[y][x]);
				if (objPlayer->GetJumpChangeBlockFlag() == false)
				{
					objPlayer->CollisionObj(objRedBlock[y][x]);
				}
				if (objPlayer->GetJumpChangeBlockFlag() == true)
				{
					objPlayer->CollisionObj(objBlueBlock[y][x]);
				}
			}
		}
	}

	for (auto &fireBar : fire)
	{
		fireBar->Move();
		objPlayer->CollisionObj(fireBar->GetCenter());
		for (int i = 0; i < fireBar->GetNum(); i++)
		{
			if (i != 0)
			{
				objPlayer->CollisionGimmick(fireBar->GetFire(i));
			}
		}
		fireBar->Update();
	}

	//�S�[���Ƃ̂����蔻��
	if (objPlayer->CollisionGoal(objGoal) == true)
	{
		audio->StopLoadedSound(resources->GetSoundData(ResourcesName::soundData1));
		fire.clear();
		pEngine->changeState(new ClearScene());
		//�X�e�[�W�ԍ������̃X�e�[�W�̔ԍ��ɂ���
		if (wholeScene->GetSelectNum() < 4)
		{
			selectNum += 1;
			wholeScene->SetSelectNum(selectNum);
		}
		return;
	}

	if (objPlayer->GetOnCollision())
	{
		playerParticle->SetFlag(true);
	}

	lightGroup->Update();
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
			if (objRedBlock[y][x]->GetPosition().x >= 0)
			{
				objRedBlock[y][x]->Update();
			}
			if (objBlueBlock[y][x]->GetPosition().x >= 0)
			{
				objBlueBlock[y][x]->Update();
			}
		}
	}

	objGoal->Update();
	playerParticle->Update(0, { objPlayer->GetPosition().x,objPlayer->GetPosition().y , 0 });

	goTitle->SetSize({ (float)goTitleSpriteSize * 3,(float)goTitleSpriteSize });
	reStart->SetSize({ (float)reStartSpriteSize * 3,(float)reStartSpriteSize });
	Return->SetSize({ (float)ReturnSpriteSize * 3,(float)ReturnSpriteSize });
}

void GamePlayScene::StageDraw(DirectXApp *common, DebugText *debugText)
{
	Resources *resources = Resources::GetInstance();
	///*�X�v���C�g�`��*/
///*�X�v���C�g�`��O����*/
	Sprite::PreDraw(common->GetCmdList().Get());

	//// �w�i�X�v���C�g�`��
	backGround->Draw();
	///*�X�v���C�g�`��㏈��*/
	Sprite::PostDraw();
	////�[�x�o�b�t�@�N���A
	common->ClearDepthBuffer();
#pragma region �`�揈��
	/*���f���`��*/
	/*���f���`��O����*/
	ModelObj::PreDraw(common->GetCmdList().Get());

	for (int i = 0; i < 10; i++)
	{
		cloud[i]->Draw();
	}
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
			//�����蔻��Ȃ��̃��C���[�u���b�N��\��
			if (objRedBlock[y][x]->GetPosition().x >= 0 && objPlayer->GetJumpChangeBlockFlag() == true)
			{
				objRedBlock[y][x]->SetModel(resources->GetModel(ResourcesName::modelWireBlock));
				objRedBlock[y][x]->Draw();
			}
			//�����蔻�肠��̃��b�h�u���b�N��\��
			if (objRedBlock[y][x]->GetPosition().x >= 0 && objPlayer->GetJumpChangeBlockFlag() == false)
			{
				objRedBlock[y][x]->SetModel(resources->GetModel(ResourcesName::modelRedBlock));
				objRedBlock[y][x]->Draw();
			}
			//�����蔻��Ȃ��̃��C���[�u���b�N��\��
			if (objBlueBlock[y][x]->GetPosition().x >= 0 && objPlayer->GetJumpChangeBlockFlag() == false)
			{
				objBlueBlock[y][x]->SetModel(resources->GetModel(ResourcesName::modelWireBlock));
				objBlueBlock[y][x]->Draw();
			}
			//�����蔻�肠��̃u���[�u���b�N��\��
			if (objBlueBlock[y][x]->GetPosition().x >= 0 && objPlayer->GetJumpChangeBlockFlag() == true)
			{
				objBlueBlock[y][x]->SetModel(resources->GetModel(ResourcesName::modelBlueBlock));
				objBlueBlock[y][x]->Draw();
			}
		}
	}

	for (auto &fireBar : fire)
	{
		fireBar->Draw();
	}

	objGoal->Draw();
	objPlayer->Draw();
	// �p�[�e�B�N���̕`��
	playerParticle->Draw();

	/*���f���`��㏈��*/
	ModelObj::PostDraw();

	//�[�x�o�b�t�@�N���A
	common->ClearDepthBuffer();

	/*�X�v���C�g�`��*/
/*�X�v���C�g�`��O����*/
	Sprite::PreDraw(common->GetCmdList().Get());
	// �f�o�b�O�e�L�X�g�̕`��
	debugText->DrawAll(common->GetCmdList().Get());

	//�J�E���g�_�E���`��
	if (stopFlag == false)
	{
		countDown->Draw();
	}
	//�v���C���[�A�C�R���\��
	playerIconSprite->Draw();

	//�ꎞ��~������
	if (stopFlag == true)
	{
		goTitle->Draw();
		reStart->Draw();
		Return->Draw();
	}

	//�Q�[���I�[�o�[�̑J��
	if (gameOverFlag == true)
	{
		GameOver->Draw();
	}
	/*�X�v���C�g�`��㏈��*/
	Sprite::PostDraw();
}
