#include"SelectScene.h"
#include "TitleScene.h"
#include "GamePlayScene.h"
#include "EndScene.h"
#include"ClearScene.h"
#include"EndScene.h"
#include"GameOverScene.h"
#include"GamePlayScene.h"
#include"Resources.h"
#include"WholeScene.h"

void SelectScene::Initialize(GameSceneManager *pEngine, DebugCamera *camera, Audio *audio, Fps *fps)
{
	Resources *resources = Resources::GetInstance();
	WholeScene *wholeScene = WholeScene::GetInstance();

	// �w�i�X�v���C�g����
	backGround = Sprite::Create(1, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	Stage1Sprite = Sprite::Create(6, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	Stage2Sprite = Sprite::Create(7, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	Stage3Sprite = Sprite::Create(8, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	Stage4Sprite = Sprite::Create(9, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	Stage5Sprite = Sprite::Create(10, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	playerIconSprite = Sprite::Create(12, { 64,64 });
	fadeIN = Sprite::Create(18, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	fadeOut = Sprite::Create(19, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });

	// 3D�I�u�W�F�N�g����
	objPlayer = Player::Create(resources->GetModel(ResourcesName::modelPlayer));

	for (int i = 0; i < 10; i++)
	{
		cloud[i] = ModelObj::Create(resources->GetModel(ResourcesName::modelCloud));
	}

	for (int y = 0; y < 6; y++)
	{
		for (int x = 0; x < 24; x++)
		{
			titleStageBox[y][x] = ModelObj::Create(resources->GetModel(ResourcesName::modelStageBox));
		}
	}

	//�w�i�p�̌��h���p�I�u�W�F�N�g
	for (int i = 0; i < backObjNum; i++)
	{
		backObj1[i] = ModelObj::Create(resources->GetModel(ResourcesName::modelBackObj1));
		backObj2[i] = ModelObj::Create(resources->GetModel(ResourcesName::modelBackObj2));
		backObj3[i] = ModelObj::Create(resources->GetModel(ResourcesName::modelBackObj3));
	}

	//�w�i�p�̌��h���p�I�u�W�F�N�g
	for (int i = 0; i < backObjNum; i++)
	{
		if (i == 0)
		{
			backObj1Pos[i] = { (float)wholeScene->GetRand(0,30),-40 + (float)wholeScene->GetRand(10,13),(float)wholeScene->GetRand(30,40) };
			backObj2Pos[i] = { (float)wholeScene->GetRand(0,30),-40 + (float)wholeScene->GetRand(10,12),(float)wholeScene->GetRand(40,50) };
			backObj3Pos[i] = { (float)wholeScene->GetRand(0,30),-40 + (float)wholeScene->GetRand(5,10),(float)wholeScene->GetRand(30,40) };
		}
		else
		{
			backObj1Pos[i] = { backObj1Pos[i - 1].x + (float)wholeScene->GetRand(20,100),-40 + (float)wholeScene->GetRand(10,13),(float)wholeScene->GetRand(30,40) };
			backObj2Pos[i] = { backObj2Pos[i - 1].x + (float)wholeScene->GetRand(20,100),-40 + (float)wholeScene->GetRand(10,12),(float)wholeScene->GetRand(40,50) };
			backObj3Pos[i] = { backObj3Pos[i - 1].x + (float)wholeScene->GetRand(20,100),-40 + (float)wholeScene->GetRand(5,10),(float)wholeScene->GetRand(30,40) };
		}

		backObj1[i]->SetPosition(backObj1Pos[i]);
		backObj2[i]->SetPosition(backObj2Pos[i]);
		backObj3[i]->SetPosition(backObj3Pos[i]);

		backObj1Size[i] = (float)wholeScene->GetRand(3, 10);
		backObj2Size[i] = (float)wholeScene->GetRand(5, 14);
		backObj3Size[i] = (float)wholeScene->GetRand(5, 8);

		backObj1[i]->SetScale({ backObj1Size[i],15,backObj1Size[i] });
		backObj2[i]->SetScale({ backObj2Size[i],20,backObj2Size[i] });
		backObj3[i]->SetScale({ backObj3Size[i],10,backObj3Size[i] });
	}

	audio->PlayLoadedSound(resources->GetSoundData(ResourcesName::soundData2), 0.05f);
	objPlayer->Initialize();
	objPlayer->SetRotation({ 0,0,0 });
	for (int i = 0; i < 10; i++)
	{
		cloud[i]->SetPosition({ (float)(8 * i) - 15.0f + (float)wholeScene->GetRand(-5,2),20 + (float)wholeScene->GetRand(-2,4),(float)wholeScene->GetRand(10,5) });
		cloudPos[i] = cloud[i]->GetPosition();
	}

	for (int y = 0; y < 6; y++)
	{
		for (int x = 0; x < 24; x++)
		{
			if (selectMap[y][x] == 1)
			{
				titleStageBox[y][x]->SetPosition({ 2.0f * x - 10.0f, -2.0f * y + 10.0f, 0 });
				stageBoxPos[y][x] = titleStageBox[y][x]->GetPosition();
			}
		}
	}
	// �J���������_���Z�b�g
	camera->SetTarget({ objPlayer->GetPosition().x, 10, 0 });
	camera->SetEye({ objPlayer->GetPosition().x, 10, -20 });
	gameTimer = 180 * 61;

	if (wholeScene->GetSelectNum() == 0)
	{
		stage1SpriteSize = stageSpriteMaxSize;
		stage2SpriteSize = stageSpriteMinSize;
		stage3SpriteSize = stageSpriteMinSize;
		stage4SpriteSize = stageSpriteMinSize;
		stage5SpriteSize = stageSpriteMinSize;
	}
	if (wholeScene->GetSelectNum() == 1)
	{
		stage1SpriteSize = stageSpriteMinSize;
		stage2SpriteSize = stageSpriteMaxSize;
		stage3SpriteSize = stageSpriteMinSize;
		stage4SpriteSize = stageSpriteMinSize;
		stage5SpriteSize = stageSpriteMinSize;
	}
	if (wholeScene->GetSelectNum() == 2)
	{
		stage1SpriteSize = stageSpriteMinSize;
		stage2SpriteSize = stageSpriteMinSize;
		stage3SpriteSize = stageSpriteMaxSize;
		stage4SpriteSize = stageSpriteMinSize;
		stage5SpriteSize = stageSpriteMinSize;
	}
	if (wholeScene->GetSelectNum() == 3)
	{
		stage1SpriteSize = stageSpriteMinSize;
		stage2SpriteSize = stageSpriteMinSize;
		stage3SpriteSize = stageSpriteMinSize;
		stage4SpriteSize = stageSpriteMaxSize;
		stage5SpriteSize = stageSpriteMinSize;
	}
	if (wholeScene->GetSelectNum() == 4)
	{
		stage1SpriteSize = stageSpriteMinSize;
		stage2SpriteSize = stageSpriteMinSize;
		stage3SpriteSize = stageSpriteMinSize;
		stage4SpriteSize = stageSpriteMinSize;
		stage5SpriteSize = stageSpriteMaxSize;
	}
	selectMoveTime = 0.2f;
	moveStageBlockSpeed = -0.06f;
	stageSelectJumpFlag = false;

	selectNumber = wholeScene->GetSelectNum();

	sizeX = 1280/2;
	sizeY = 720/2;
	t = 0;
	easingFlag = false;

	fadeOutSizeX = 1280 * 5;
	fadeOutSizeY = 720 * 5;
	fadeOutT = 0;
	fadeOutFlag = true;

	selectedStageFlag = false;
	goTitleFlag = false;

	particleMan = ParticleManager::GetInstance();
}

void SelectScene::Update(GameSceneManager *pEngine, Audio *audio, DebugText *debugText, LightGroup *lightGroup, DebugCamera *camera, Fps *fps)
{
	Input *input = Input::GetInstance();
	Controller *controller = Controller::GetInstance();
	Resources *resources = Resources::GetInstance();
	WholeScene *wholeScene = WholeScene::GetInstance();

#pragma region �X�V����
	//�e�̈ʒu
	lightGroup->SetCircleShadowDir(0, XMVECTOR({ 0,-1,0 }));
	lightGroup->SetCircleShadowCasterPos(0, objPlayer->GetPosition());
	lightGroup->SetCircleShadowAtten(0, XMFLOAT3({ objPlayer->GetShadowSize().x,objPlayer->GetShadowSize().y,0.0f }));
	lightGroup->SetCircleShadowFactorAngle(0, objPlayer->GetShadowSize());

	// �J���������_���Z�b�g
	camera->SetUp({ 0, 1, 0 });
	camera->SetTarget({ objPlayer->GetPosition().x, 10, 0 });
	camera->SetEye({ objPlayer->GetPosition().x, 10, -20 });

	//�v���C���[�̑�����\��
	debugText->SetPos(150, 64);
	debugText->SetSize(0.5f);
	debugText->Printf("%d", wholeScene->GetTotalPlayerNum());

	//�^�C�g�����痈���Ƃ���player�̃W�����v��h��
	if (input->isKeyTrigger(DIK_SPACE) || controller->TriggerButton(static_cast<int>(Button::A)) == true)
	{
		stageSelectJumpFlag = true;
	}

	//fadeout
	if (fadeOutFlag == true)
	{
		fadeOutT += 0.005f;
		easing::Updete(fadeOutSizeX, 0, 3, fadeOutT);
		easing::Updete(fadeOutSizeY, 0, 3, fadeOutT);
		if (fadeOutT > 0.3f)
		{
			fadeOutFlag = false;
		}

		fadeOut->SetSize({ (float)fadeOutSizeX,(float)fadeOutSizeY });
	}

	for (int i = 0; i < 10; i++)
	{
		cloudPos[i].x -= 0.03f;
		if (cloud[i]->GetPosition().x < objPlayer->GetPosition().x - 40.0f)
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
	//fadeout���I�������I���ł���悤�ɂȂ�
	if (fadeOutFlag == false)
	{
		//�w�i�p�̌��h���p�I�u�W�F�N�g
		for (int i = 0; i < backObjNum; i++)
		{
			backObj1Pos[i].x -= 0.06f;
			backObj2Pos[i].x -= 0.03f;
			backObj3Pos[i].x -= 0.12f;

			if (backObj1[i]->GetPosition().x < objPlayer->GetPosition().x - 100.0f)
			{
				if (i == 0)
				{
					backObj1Pos[i] = { backObj1Pos[backObjNum - 1].x + (float)wholeScene->GetRand(20,100),-40 + (float)wholeScene->GetRand(10,12),(float)wholeScene->GetRand(40,50) };
				}
				else
				{
					backObj1Pos[i] = { backObj1Pos[i - 1].x + (float)wholeScene->GetRand(20,100),-40 + (float)wholeScene->GetRand(10,12),(float)wholeScene->GetRand(40,50) };
				}

				backObj1Size[i] = (float)wholeScene->GetRand(5, 14);
			}

			if (backObj2[i]->GetPosition().x < objPlayer->GetPosition().x - 100.0f)
			{
				if (i == 0)
				{
					backObj2Pos[i] = { backObj2Pos[backObjNum - 1].x + (float)wholeScene->GetRand(20,100),-40 + (float)wholeScene->GetRand(10,12),(float)wholeScene->GetRand(40,50) };
				}
				else
				{
					backObj2Pos[i] = { backObj2Pos[i - 1].x + (float)wholeScene->GetRand(20,100),-40 + (float)wholeScene->GetRand(10,12),(float)wholeScene->GetRand(40,50) };
				}

				backObj2Size[i] = (float)wholeScene->GetRand(5, 14);
			}

			if (backObj3[i]->GetPosition().x < objPlayer->GetPosition().x - 100.0f)
			{
				if (i == 0)
				{
					backObj3Pos[i] = { backObj3Pos[backObjNum - 1].x + (float)wholeScene->GetRand(20,100),-40 + (float)wholeScene->GetRand(10,12),(float)wholeScene->GetRand(40,50) };
				}
				else
				{
					backObj3Pos[i] = { backObj3Pos[i - 1].x + (float)wholeScene->GetRand(20,100),-40 + (float)wholeScene->GetRand(10,12),(float)wholeScene->GetRand(40,50) };
				}

				backObj3Size[i] = (float)wholeScene->GetRand(5, 14);
			}

			backObj1[i]->SetPosition(backObj1Pos[i]);
			backObj2[i]->SetPosition(backObj2Pos[i]);
			backObj3[i]->SetPosition(backObj3Pos[i]);

			backObj1[i]->SetScale({ backObj1Size[i],15,backObj1Size[i] });
			backObj2[i]->SetScale({ backObj2Size[i],20,backObj2Size[i] });
			backObj3[i]->SetScale({ backObj3Size[i],10,backObj3Size[i] });
		}

		//�u���b�N�̃X�N���[��
		for (int y = 0; y < 6; y++)
		{
			for (int x = 0; x < 24; x++)
			{
				stageBoxPos[y][x].x += moveStageBlockSpeed;
				if (selectMap[y][x] == 1 && titleStageBox[y][x]->GetPosition().x > objPlayer->GetPosition().x + 25 && moveStageBlockSpeed == 0.06f)
				{
					if (x == 23)
					{
						stageBoxPos[y][x] = { titleStageBox[y][0]->GetPosition().x - 2.0f, -2.0f * y + 10.0f, 0 };
					}
					else
					{
						stageBoxPos[y][x] = { titleStageBox[y][x + 1]->GetPosition().x - 2.0f, -2.0f * y + 10.0f, 0 };
					}

				}

				if (selectMap[y][x] == 1 && titleStageBox[y][x]->GetPosition().x < objPlayer->GetPosition().x - 25 && moveStageBlockSpeed == moveStageBlockSpeed)
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

		if (input->isKeyTrigger(DIK_ESCAPE) || controller->TriggerButton(static_cast<int>(Button::START)) == true)
		{
			easingFlag = true;
			goTitleFlag = true;
		}
		//�X�e�[�W�Z���N�g
		if ((input->isKeyTrigger(DIK_A) || controller->TriggerButton(static_cast<int>(Button::LEFT)) == true)
			&& wholeScene->GetSelectNum() > 0 && selectMoveTime >= 0.2f)
		{
			selectMoveTime = 0;
			selectNumber -= 1;
		}
		else if ((input->isKeyTrigger(DIK_D) || controller->TriggerButton(static_cast<int>(Button::RIGHT)) == true)
			&& wholeScene->GetSelectNum() < 4 && selectMoveTime >= 0.2f)
		{
			selectMoveTime = 0;
			selectNumber += 1;
		}
		else
		{
			selectMoveTime += 0.08f;
		}
	}
	easing::Updete(selectPos, selectInterval * wholeScene->GetSelectNum(), InSine, selectMoveTime);

	//�^�C�g���ɖ߂�Ƃ���
	if (goTitleFlag == true)
	{
		if (sizeX > 1280 * 15)
		{
			//�^�C�g���ɖ߂������ɃC�[�W���O����������悤�ɂ���
			wholeScene->SetGoTitleFlag(true);
			audio->StopLoadedSound(resources->GetSoundData(ResourcesName::soundData2));
			pEngine->changeState(new TitleScene());
			return;
		}
	}
	//�X�e�[�W�𔻒f���鐔�����Z�b�g
	wholeScene->SetSelectNum(selectNumber);

	//�w��̈ʒu�ɂ���X�e�[�W�ԍ��̉摜��傫������
	if (wholeScene->GetSelectNum() == 0)
	{
		easing::Updete(stage1SpriteSize, stageSpriteMaxSize, InSine, selectMoveTime);
		easing::Updete(stage2SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
		easing::Updete(stage3SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
		easing::Updete(stage4SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
		easing::Updete(stage5SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
		wholeScene->SetStageFireNum(1);
	}
	if (wholeScene->GetSelectNum() == 1)
	{
		easing::Updete(stage1SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
		easing::Updete(stage2SpriteSize, stageSpriteMaxSize, InSine, selectMoveTime);
		easing::Updete(stage3SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
		easing::Updete(stage4SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
		easing::Updete(stage5SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
		wholeScene->SetStageFireNum(2);
	}
	if (wholeScene->GetSelectNum() == 2)
	{
		easing::Updete(stage1SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
		easing::Updete(stage2SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
		easing::Updete(stage3SpriteSize, stageSpriteMaxSize, InSine, selectMoveTime);
		easing::Updete(stage4SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
		easing::Updete(stage5SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
		wholeScene->SetStageFireNum(3);
	}
	if (wholeScene->GetSelectNum() == 3)
	{
		easing::Updete(stage1SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
		easing::Updete(stage2SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
		easing::Updete(stage3SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
		easing::Updete(stage4SpriteSize, stageSpriteMaxSize, InSine, selectMoveTime);
		easing::Updete(stage5SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
		wholeScene->SetStageFireNum(4);
	}
	if (wholeScene->GetSelectNum() == 4)
	{
		easing::Updete(stage1SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
		easing::Updete(stage2SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
		easing::Updete(stage3SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
		easing::Updete(stage4SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
		easing::Updete(stage5SpriteSize, stageSpriteMaxSize, InSine, selectMoveTime);
		wholeScene->SetStageFireNum(5);
	}

	Stage1Sprite->SetSize({ (float)stage1SpriteSize,(float)stage1SpriteSize });
	Stage2Sprite->SetSize({ (float)stage2SpriteSize,(float)stage2SpriteSize });
	Stage3Sprite->SetSize({ (float)stage3SpriteSize,(float)stage3SpriteSize });
	Stage4Sprite->SetSize({ (float)stage4SpriteSize,(float)stage4SpriteSize });
	Stage5Sprite->SetSize({ (float)stage5SpriteSize,(float)stage5SpriteSize });

	if (stageSelectJumpFlag && easingFlag == false && fadeOutFlag == false)
	{
		objPlayer->Jump();
	}

	particleMan->Update();
	lightGroup->Update();
	camera->Update();
	objPlayer->Update();
	for (int y = 0; y < 6; y++)
	{
		for (int x = 0; x < 24; x++)
		{
			titleStageBox[y][x]->Update();
			objPlayer->HitObjBase(titleStageBox[y][x]);

			if (GameCollision::CollisionPlayerLeftToObj(objPlayer, titleStageBox[y][x]))
			{
				objPlayer->HitObjLeft(titleStageBox[y][x]);
			}
			else if (GameCollision::CollisionPlayerRightToObj(objPlayer, titleStageBox[y][x]))
			{
				objPlayer->HitObjRight(titleStageBox[y][x]);
			}
			else if (GameCollision::CollisionPlayerDownToObj(objPlayer, titleStageBox[y][x]))
			{
				objPlayer->HitObjDown(titleStageBox[y][x]);
			}
			else if (GameCollision::CollisionPlayerUpToObj(objPlayer, titleStageBox[y][x]))
			{
				objPlayer->HitObjUp(titleStageBox[y][x]);
			}
		}
	}

	for (int i = 0; i < 10; i++)
	{
		cloud[i]->Update();
	}

	//�X�e�[�W�ԍ������炷
	Stage1Sprite->SetPosition({ WinApp::window_width / 2.0f + selectInterval * 0 - (float)selectPos, WinApp::window_height / 2.0f });
	Stage2Sprite->SetPosition({ WinApp::window_width / 2.0f + selectInterval * 1 - (float)selectPos, WinApp::window_height / 2.0f });
	Stage3Sprite->SetPosition({ WinApp::window_width / 2.0f + selectInterval * 2 - (float)selectPos, WinApp::window_height / 2.0f });
	Stage4Sprite->SetPosition({ WinApp::window_width / 2.0f + selectInterval * 3 - (float)selectPos, WinApp::window_height / 2.0f });
	Stage5Sprite->SetPosition({ WinApp::window_width / 2.0f + selectInterval * 4 - (float)selectPos, WinApp::window_height / 2.0f });

	//�w��̈ʒu��Space�������Ƃ��̃X�e�[�W�ɂƂ�
	if (objPlayer->GetJumpTimer() > 5 && fadeOutFlag == false)
	{
		easingFlag = true;
		selectedStageFlag = true;
	}

	if (easingFlag == true)
	{
		t += 0.01f;
		easing::Updete(sizeX, 1280 * 17, 3, t);
		easing::Updete(sizeY, 720 * 17, 3, t);

		fadeIN->SetSize({ (float)sizeX,(float)sizeY });
	}

	if (sizeX > 1280 * 15 && selectedStageFlag == true)
	{
		if (wholeScene->GetSelectNum() == 0 && selectMoveTime >= 0.2f)
		{
			audio->StopLoadedSound(resources->GetSoundData(ResourcesName::soundData2));
			pEngine->changeState(new GamePlayScene(1));
		}
		else if (wholeScene->GetSelectNum() == 1 && selectMoveTime >= 0.2f)
		{
			audio->StopLoadedSound(resources->GetSoundData(ResourcesName::soundData2));
			pEngine->changeState(new GamePlayScene(2));
		}
		else if (wholeScene->GetSelectNum() == 2 && selectMoveTime >= 0.2f)
		{
			audio->StopLoadedSound(resources->GetSoundData(ResourcesName::soundData2));
			pEngine->changeState(new GamePlayScene(3));
		}
		else if (wholeScene->GetSelectNum() == 3 && selectMoveTime >= 0.2f)
		{
			audio->StopLoadedSound(resources->GetSoundData(ResourcesName::soundData2));
			pEngine->changeState(new GamePlayScene(4));
		}
		else if (wholeScene->GetSelectNum() == 4 && selectMoveTime >= 0.2f)
		{
			audio->StopLoadedSound(resources->GetSoundData(ResourcesName::soundData2));
			pEngine->changeState(new GamePlayScene(5));
		}
	}

	//�w�i�p�̌��h���p�I�u�W�F�N�g
	for (int i = 0; i < backObjNum; i++)
	{
		backObj1[i]->Update();
		backObj2[i]->Update();
		backObj3[i]->Update();
	}
}

void SelectScene::Draw(GameSceneManager *pEngine, DirectXApp *common, DebugText *debugText)
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

	//�w�i�p�̌��h���p�I�u�W�F�N�g�̕`��
	for (int i = 0; i < backObjNum; i++)
	{
		backObj1[i]->Draw();
		backObj2[i]->Draw();
		backObj3[i]->Draw();
	}

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

	//�p�[�e�B�N���`��
	particleMan->Draw(common->GetCmdList().Get());

	//�[�x�o�b�t�@�N���A
	common->ClearDepthBuffer();

	/*�X�v���C�g�`��*/
	/*�X�v���C�g�`��O����*/
	Sprite::PreDraw(common->GetCmdList().Get());
	// �f�o�b�O�e�L�X�g�̕`��
	debugText->DrawAll(common->GetCmdList().Get());
	//�v���C���[�A�C�R���\��
	playerIconSprite->Draw();

	Stage1Sprite->Draw();
	Stage2Sprite->Draw();
	Stage3Sprite->Draw();
	Stage4Sprite->Draw();
	Stage5Sprite->Draw();

	//fadein
	if (easingFlag == true)
	{
		fadeIN->Draw();
	}
	//fadeout
	if (fadeOutFlag == true)
	{
		fadeOut->Draw();
	}

	/*�X�v���C�g�`��㏈��*/
	Sprite::PostDraw();
}
