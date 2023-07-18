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
	backGround.reset(Sprite::Create(ResourcesNo::backGround3, { WinApp::window_width / wholeScene->HALF_SIZE,WinApp::window_height / wholeScene->HALF_SIZE }));
	Stage1Sprite.reset(Sprite::Create(ResourcesNo::Stage1, { WinApp::window_width / wholeScene->HALF_SIZE,WinApp::window_height / wholeScene->HALF_SIZE }));
	Stage2Sprite.reset(Sprite::Create(ResourcesNo::Stage2, { WinApp::window_width / wholeScene->HALF_SIZE,WinApp::window_height / wholeScene->HALF_SIZE }));
	Stage3Sprite.reset(Sprite::Create(ResourcesNo::Stage3, { WinApp::window_width / wholeScene->HALF_SIZE,WinApp::window_height / wholeScene->HALF_SIZE }));
	Stage4Sprite.reset(Sprite::Create(ResourcesNo::Stage4, { WinApp::window_width / wholeScene->HALF_SIZE,WinApp::window_height / wholeScene->HALF_SIZE }));
	Stage5Sprite.reset(Sprite::Create(ResourcesNo::Stage5, { WinApp::window_width / wholeScene->HALF_SIZE,WinApp::window_height / wholeScene->HALF_SIZE }));
	playerIconSprite.reset(Sprite::Create(ResourcesNo::playerIcon, { 64,64 }));
	fadeIN.reset(Sprite::Create(ResourcesNo::fadeIN, { WinApp::window_width / wholeScene->HALF_SIZE,WinApp::window_height / wholeScene->HALF_SIZE }));
	fadeOut.reset(Sprite::Create(ResourcesNo::fadeOUT, { WinApp::window_width / wholeScene->HALF_SIZE,WinApp::window_height / wholeScene->HALF_SIZE }));

	for (int j = 0; j < STAR_STAGE_NUM; j++)
	{
		for (int i = 0; i < STAR_NUM; i++)
		{
			starSprite[i][j].reset(Sprite::Create(ResourcesNo::starSprite, {WinApp::window_width / wholeScene->HALF_SIZE,WinApp::window_height / wholeScene->HALF_SIZE }));
			noStarSprite[i][j].reset(Sprite::Create(ResourcesNo::noStarSprite, {WinApp::window_width / wholeScene->HALF_SIZE,WinApp::window_height / wholeScene->HALF_SIZE }));
		}
	}

	// 3D�I�u�W�F�N�g����
	objPlayer.reset(Player::Create(resources->GetModel(ResourcesName::modelPlayer)));

	for (int i = 0; i < cloud.size(); i++)
	{
		cloud[i].reset(ModelObj::Create(resources->GetModel(ResourcesName::modelCloud)));
	}

	//�w�i�p�̌��h���p�I�u�W�F�N�g
	for (int i = 0; i < backObjNum; i++)
	{
		backObj1[i].reset(ModelObj::Create(resources->GetModel(ResourcesName::modelBackObj1)));
		backObj2[i].reset(ModelObj::Create(resources->GetModel(ResourcesName::modelBackObj2)));
		backObj3[i].reset(ModelObj::Create(resources->GetModel(ResourcesName::modelBackObj3)));
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

	audio->PlayLoadedSound(resources->GetSoundData(ResourcesName::soundData2), resources->soundData2Bol);
	objPlayer->Initialize();
	objPlayer->SetRotation({ 0,0,0 });
	for (int i = 0; i < cloud.size(); i++)
	{
		cloud[i]->SetPosition({ (float)(8 * i) - 15.0f + (float)wholeScene->GetRand(-5,2),20 + (float)wholeScene->GetRand(-2,4),(float)wholeScene->GetRand(10,5) });
		cloudPos[i] = cloud[i]->GetPosition();
	}

	for (int y = 0; y < TITLE_STAGE_Y; y++)
	{
		for (int x = 0; x < TITLE_STAGE_X; x++)
		{
			titleStageBox[y][x].reset(ModelObj::Create(resources->GetModel(ResourcesName::modelStageBox)));
			if (selectMap[y][x] == 1)
			{
				titleStageBox[y][x]->SetPosition({ wholeScene->OBJECT_SIZE * x - 10.0f, -wholeScene->OBJECT_SIZE * y + 10.0f, 0 });
				stageBoxPos[y][x] = titleStageBox[y][x]->GetPosition();
			}
		}
	}
	// �J���������_���Z�b�g
	camera->SetTarget({ objPlayer->GetPosition().x, 10, 0 });
	camera->SetEye({ objPlayer->GetPosition().x, 10, -20 });
	gameTimer = 180 * 61;

	if (wholeScene->GetSelectNum() == static_cast<int>(WholeScene::STAGE_NUM::STAGE1))
	{
		stage1SpriteSize = stageSpriteMaxSize;
		stage2SpriteSize = stageSpriteMinSize;
		stage3SpriteSize = stageSpriteMinSize;
		stage4SpriteSize = stageSpriteMinSize;
		stage5SpriteSize = stageSpriteMinSize;
	}
	if (wholeScene->GetSelectNum() == static_cast<int>(WholeScene::STAGE_NUM::STAGE2))
	{
		stage1SpriteSize = stageSpriteMinSize;
		stage2SpriteSize = stageSpriteMaxSize;
		stage3SpriteSize = stageSpriteMinSize;
		stage4SpriteSize = stageSpriteMinSize;
		stage5SpriteSize = stageSpriteMinSize;
	}
	if (wholeScene->GetSelectNum() == static_cast<int>(WholeScene::STAGE_NUM::STAGE3))
	{
		stage1SpriteSize = stageSpriteMinSize;
		stage2SpriteSize = stageSpriteMinSize;
		stage3SpriteSize = stageSpriteMaxSize;
		stage4SpriteSize = stageSpriteMinSize;
		stage5SpriteSize = stageSpriteMinSize;
	}
	if (wholeScene->GetSelectNum() == static_cast<int>(WholeScene::STAGE_NUM::STAGE4))
	{
		stage1SpriteSize = stageSpriteMinSize;
		stage2SpriteSize = stageSpriteMinSize;
		stage3SpriteSize = stageSpriteMinSize;
		stage4SpriteSize = stageSpriteMaxSize;
		stage5SpriteSize = stageSpriteMinSize;
	}
	if (wholeScene->GetSelectNum() == static_cast<int>(WholeScene::STAGE_NUM::STAGE5))
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

	sizeX = wholeScene->WIN_WIDTH / wholeScene->HALF_SIZE;
	sizeY = wholeScene->WIN_HEIGHT / wholeScene->HALF_SIZE;
	t = 0;
	easingFlag = false;

	fadeOutSizeX = wholeScene->WIN_WIDTH * 5;
	fadeOutSizeY = wholeScene->WIN_HEIGHT * 5;
	fadeOutT = 0;
	fadeOutFlag = true;

	selectedStageFlag = false;
	goTitleFlag = false;

	playerRotationZ = 0;
	afterplayerRotZ = 0;

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

	for (int i = 0; i < cloud.size(); i++)
	{
		cloudPos[i].x -= 0.03f;
		if (cloud[i]->GetPosition().x < objPlayer->GetPosition().x - 40.0f)
		{
			cloudPos[i] = { 40.0f + 8.0f + (float)wholeScene->GetRand(-5,2),20 + (float)wholeScene->GetRand(-2,4),(float)wholeScene->GetRand(10,5) };
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
		for (int y = 0; y < TITLE_STAGE_Y; y++)
		{
			for (int x = 0; x < TITLE_STAGE_X; x++)
			{
				stageBoxPos[y][x].x += moveStageBlockSpeed;
				if (selectMap[y][x] == 1 && titleStageBox[y][x]->GetPosition().x > objPlayer->GetPosition().x + 25 && moveStageBlockSpeed == 0.06f)
				{
					if (x == 23)
					{
						stageBoxPos[y][x] = { titleStageBox[y][0]->GetPosition().x - wholeScene->OBJECT_SIZE, -wholeScene->OBJECT_SIZE * y + 10.0f, 0 };
					}
					else
					{
						stageBoxPos[y][x] = { titleStageBox[y][x + 1]->GetPosition().x - wholeScene->OBJECT_SIZE, -wholeScene->OBJECT_SIZE * y + 10.0f, 0 };
					}

				}

				if (selectMap[y][x] == 1 && titleStageBox[y][x]->GetPosition().x < objPlayer->GetPosition().x - 25 && moveStageBlockSpeed == moveStageBlockSpeed)
				{
					if (x == 0)
					{
						stageBoxPos[y][x] = { titleStageBox[y][TITLE_STAGE_X - 1]->GetPosition().x + wholeScene->OBJECT_SIZE, -wholeScene->OBJECT_SIZE * y + 10.0f, 0 };
					}
					else
					{
						stageBoxPos[y][x] = { titleStageBox[y][x - 1]->GetPosition().x + wholeScene->OBJECT_SIZE, -wholeScene->OBJECT_SIZE * y + 10.0f, 0 };
					}

				}
				titleStageBox[y][x]->SetPosition(stageBoxPos[y][x]);
			}
		}

		if (input->isKeyTrigger(DIK_ESCAPE) || controller->TriggerButton(static_cast<int>(Button::START)) == true)
		{
			audio->PlayLoadedSound(resources->GetSoundData(ResourcesName::soundData3), 0.05f);
			easingFlag = true;
			goTitleFlag = true;
		}
		//�X�e�[�W�Z���N�g
		if ((input->isKeyTrigger(DIK_A) || controller->TriggerButton(static_cast<int>(Button::LEFT)) == true)
			&& wholeScene->GetSelectNum() > 1 && selectMoveTime >= 0.2f)
		{
			audio->StopLoadedSound(resources->GetSoundData(ResourcesName::soundData5));
			audio->PlayLoadedSound(resources->GetSoundData(ResourcesName::soundData5), resources->soundData5Bol);
			selectMoveTime = 0;
			afterplayerRotZ += 180;
			selectNumber -= 1;
		}
		else if ((input->isKeyTrigger(DIK_D) || controller->TriggerButton(static_cast<int>(Button::RIGHT)) == true)
			&& wholeScene->GetSelectNum() < 5 && selectMoveTime >= 0.2f)
		{
			audio->StopLoadedSound(resources->GetSoundData(ResourcesName::soundData5));
			audio->PlayLoadedSound(resources->GetSoundData(ResourcesName::soundData5), resources->soundData5Bol);
			selectMoveTime = 0;
			afterplayerRotZ -= 180;
			selectNumber += 1;
		}
		else
		{
			audio->StopLoadedSound(resources->GetSoundData(ResourcesName::soundData5));
			selectMoveTime += 0.08f;
		}
	}
	easing::Updete(selectPos, selectInterval * wholeScene->GetSelectNum(), InSine, selectMoveTime);
	easing::Updete(playerRotationZ, afterplayerRotZ, InSine, selectMoveTime);
	objPlayer->SetRotation({ objPlayer->GetPosition().x, objPlayer->GetPosition().y, (float)playerRotationZ });

	//�^�C�g���ɖ߂�Ƃ���
	if (goTitleFlag == true)
	{
		if (sizeX > wholeScene->WIN_WIDTH * 15)
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
	if (wholeScene->GetSelectNum() == static_cast<int>(WholeScene::STAGE_NUM::STAGE1))
	{
		easing::Updete(stage1SpriteSize, stageSpriteMaxSize, InSine, selectMoveTime);
		easing::Updete(stage2SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
		easing::Updete(stage3SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
		easing::Updete(stage4SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
		easing::Updete(stage5SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
		wholeScene->SetStageFireNum(1);
	}
	if (wholeScene->GetSelectNum() == static_cast<int>(WholeScene::STAGE_NUM::STAGE2))
	{
		easing::Updete(stage1SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
		easing::Updete(stage2SpriteSize, stageSpriteMaxSize, InSine, selectMoveTime);
		easing::Updete(stage3SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
		easing::Updete(stage4SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
		easing::Updete(stage5SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
		wholeScene->SetStageFireNum(2);
	}
	if (wholeScene->GetSelectNum() == static_cast<int>(WholeScene::STAGE_NUM::STAGE3))
	{
		easing::Updete(stage1SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
		easing::Updete(stage2SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
		easing::Updete(stage3SpriteSize, stageSpriteMaxSize, InSine, selectMoveTime);
		easing::Updete(stage4SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
		easing::Updete(stage5SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
		wholeScene->SetStageFireNum(3);
	}
	if (wholeScene->GetSelectNum() == static_cast<int>(WholeScene::STAGE_NUM::STAGE4))
	{
		easing::Updete(stage1SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
		easing::Updete(stage2SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
		easing::Updete(stage3SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
		easing::Updete(stage4SpriteSize, stageSpriteMaxSize, InSine, selectMoveTime);
		easing::Updete(stage5SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
		wholeScene->SetStageFireNum(4);
	}
	if (wholeScene->GetSelectNum() == static_cast<int>(WholeScene::STAGE_NUM::STAGE5))
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
	for (int y = 0; y < TITLE_STAGE_Y; y++)
	{
		for (int x = 0; x < TITLE_STAGE_X; x++)
		{
			objPlayer->HitObjBase(titleStageBox[y][x].get());

			if (GameCollision::CollisionPlayerLeftToObj(objPlayer.get(), titleStageBox[y][x].get()))
			{
				objPlayer->HitObjLeft(titleStageBox[y][x].get(), audio);
			}
			else if (GameCollision::CollisionPlayerRightToObj(objPlayer.get(), titleStageBox[y][x].get()))
			{
				objPlayer->HitObjRight(titleStageBox[y][x].get(), audio);
			}
			else if (GameCollision::CollisionPlayerDownToObj(objPlayer.get(), titleStageBox[y][x].get()))
			{
				objPlayer->HitObjDown(titleStageBox[y][x].get());
			}
			else if (GameCollision::CollisionPlayerUpToObj(objPlayer.get(), titleStageBox[y][x].get()))
			{
				objPlayer->HitObjUp(titleStageBox[y][x].get());
			}
		}
	}

	for (const auto& oneCloud : cloud)
	{
		oneCloud->Update();
	}

	//�X�e�[�W�ԍ������炷
	Stage1Sprite->SetPosition({ WinApp::window_width / wholeScene->HALF_SIZE + selectInterval * static_cast<int>(WholeScene::STAGE_NUM::STAGE1) - (float)selectPos, WinApp::window_height / wholeScene->HALF_SIZE });
	Stage2Sprite->SetPosition({ WinApp::window_width / wholeScene->HALF_SIZE + selectInterval * static_cast<int>(WholeScene::STAGE_NUM::STAGE2) - (float)selectPos, WinApp::window_height / wholeScene->HALF_SIZE });
	Stage3Sprite->SetPosition({ WinApp::window_width / wholeScene->HALF_SIZE + selectInterval * static_cast<int>(WholeScene::STAGE_NUM::STAGE3) - (float)selectPos, WinApp::window_height / wholeScene->HALF_SIZE });
	Stage4Sprite->SetPosition({ WinApp::window_width / wholeScene->HALF_SIZE + selectInterval * static_cast<int>(WholeScene::STAGE_NUM::STAGE4) - (float)selectPos, WinApp::window_height / wholeScene->HALF_SIZE });
	Stage5Sprite->SetPosition({ WinApp::window_width / wholeScene->HALF_SIZE + selectInterval * static_cast<int>(WholeScene::STAGE_NUM::STAGE5) - (float)selectPos, WinApp::window_height / wholeScene->HALF_SIZE });

	//�X�^�[�̈ʒu�Ƒ傫��
	for (int i = 0; i < STAR_NUM; i++)
	{
		starSprite[i][0]->SetSize({ (float)stage1SpriteSize / 4,(float)stage1SpriteSize / 4 });
		starSprite[i][1]->SetSize({ (float)stage2SpriteSize / 4,(float)stage2SpriteSize / 4 });
		starSprite[i][2]->SetSize({ (float)stage3SpriteSize / 4,(float)stage3SpriteSize / 4 });
		starSprite[i][3]->SetSize({ (float)stage4SpriteSize / 4,(float)stage4SpriteSize / 4 });
		starSprite[i][4]->SetSize({ (float)stage5SpriteSize / 4,(float)stage5SpriteSize / 4 });

		noStarSprite[i][0]->SetSize({ (float)stage1SpriteSize / 4,(float)stage1SpriteSize / 4 });
		noStarSprite[i][1]->SetSize({ (float)stage2SpriteSize / 4,(float)stage2SpriteSize / 4 });
		noStarSprite[i][2]->SetSize({ (float)stage3SpriteSize / 4,(float)stage3SpriteSize / 4 });
		noStarSprite[i][3]->SetSize({ (float)stage4SpriteSize / 4,(float)stage4SpriteSize / 4 });
		noStarSprite[i][4]->SetSize({ (float)stage5SpriteSize / 4,(float)stage5SpriteSize / 4 });

		starSprite[i][0]->SetPosition({ WinApp::window_width / wholeScene->HALF_SIZE + selectInterval * static_cast<int>(WholeScene::STAGE_NUM::STAGE1) - (float)selectPos - (float)stage1SpriteSize / 4 + (((float)stage1SpriteSize / 4) * i), WinApp::window_height / wholeScene->HALF_SIZE - (float)stage1SpriteSize / 2 });
		starSprite[i][1]->SetPosition({ WinApp::window_width / wholeScene->HALF_SIZE + selectInterval * static_cast<int>(WholeScene::STAGE_NUM::STAGE2) - (float)selectPos - (float)stage2SpriteSize / 4 + (((float)stage2SpriteSize / 4) * i), WinApp::window_height / wholeScene->HALF_SIZE - (float)stage2SpriteSize / 2 });
		starSprite[i][2]->SetPosition({ WinApp::window_width / wholeScene->HALF_SIZE + selectInterval * static_cast<int>(WholeScene::STAGE_NUM::STAGE3) - (float)selectPos - (float)stage3SpriteSize / 4 + (((float)stage3SpriteSize / 4) * i), WinApp::window_height / wholeScene->HALF_SIZE - (float)stage3SpriteSize / 2 });
		starSprite[i][3]->SetPosition({ WinApp::window_width / wholeScene->HALF_SIZE + selectInterval * static_cast<int>(WholeScene::STAGE_NUM::STAGE4) - (float)selectPos - (float)stage4SpriteSize / 4 + (((float)stage4SpriteSize / 4) * i), WinApp::window_height / wholeScene->HALF_SIZE - (float)stage4SpriteSize / 2 });
		starSprite[i][4]->SetPosition({ WinApp::window_width / wholeScene->HALF_SIZE + selectInterval * static_cast<int>(WholeScene::STAGE_NUM::STAGE5) - (float)selectPos - (float)stage5SpriteSize / 4 + (((float)stage5SpriteSize / 4) * i), WinApp::window_height / wholeScene->HALF_SIZE - (float)stage5SpriteSize / 2 });

		noStarSprite[i][0]->SetPosition({ WinApp::window_width / wholeScene->HALF_SIZE + selectInterval * static_cast<int>(WholeScene::STAGE_NUM::STAGE1) - (float)selectPos - (float)stage1SpriteSize / 4 + (((float)stage1SpriteSize / 4) * i), WinApp::window_height / wholeScene->HALF_SIZE - (float)stage1SpriteSize / 2 });
		noStarSprite[i][1]->SetPosition({ WinApp::window_width / wholeScene->HALF_SIZE + selectInterval * static_cast<int>(WholeScene::STAGE_NUM::STAGE2) - (float)selectPos - (float)stage2SpriteSize / 4 + (((float)stage2SpriteSize / 4) * i), WinApp::window_height / wholeScene->HALF_SIZE - (float)stage2SpriteSize / 2 });
		noStarSprite[i][2]->SetPosition({ WinApp::window_width / wholeScene->HALF_SIZE + selectInterval * static_cast<int>(WholeScene::STAGE_NUM::STAGE3) - (float)selectPos - (float)stage3SpriteSize / 4 + (((float)stage3SpriteSize / 4) * i), WinApp::window_height / wholeScene->HALF_SIZE - (float)stage3SpriteSize / 2 });
		noStarSprite[i][3]->SetPosition({ WinApp::window_width / wholeScene->HALF_SIZE + selectInterval * static_cast<int>(WholeScene::STAGE_NUM::STAGE4) - (float)selectPos - (float)stage4SpriteSize / 4 + (((float)stage4SpriteSize / 4) * i), WinApp::window_height / wholeScene->HALF_SIZE - (float)stage4SpriteSize / 2 });
		noStarSprite[i][4]->SetPosition({ WinApp::window_width / wholeScene->HALF_SIZE + selectInterval * static_cast<int>(WholeScene::STAGE_NUM::STAGE5) - (float)selectPos - (float)stage5SpriteSize / 4 + (((float)stage5SpriteSize / 4) * i), WinApp::window_height / wholeScene->HALF_SIZE - (float)stage5SpriteSize / 2 });
	}
	//�X�^�[�̉�]
	for (int i = 0; i < STAR_STAGE_NUM; i++)
	{
		if (wholeScene->GetStarNum(i).x == 0)
		{
			starTotalRot[0][i] = 0;
		}
		if (wholeScene->GetStarNum(i).x == 1)
		{
			starTotalRot[0][i] += 1.0f;
			starSprite[0][i]->SetRotation(starTotalRot[0][i]);
		}

		if (wholeScene->GetStarNum(i).y == 0)
		{
			starTotalRot[1][i] = 0;
		}
		if (wholeScene->GetStarNum(i).y == 1)
		{
			starTotalRot[1][i] += 1.0f;
			starSprite[1][i]->SetRotation(starTotalRot[1][i]);
		}

		if (wholeScene->GetStarNum(i).z == 0)
		{
			starTotalRot[2][i] = 0;
		}
		if (wholeScene->GetStarNum(i).z == 1)
		{
			starTotalRot[2][i] += 1.0f;
			starSprite[2][i]->SetRotation(starTotalRot[2][i]);
		}
	}
	//�w��̈ʒu��Space�������Ƃ��̃X�e�[�W�ɂƂ�
	if ((input->isKeyTrigger(DIK_SPACE) || controller->TriggerButton(static_cast<int>(Button::A))) && fadeOutFlag == false)
	{
		audio->PlayLoadedSound(resources->GetSoundData(ResourcesName::soundData3), resources->soundData3Bol);
		easingFlag = true;
		selectedStageFlag = true;
	}

	if (easingFlag == true)
	{
		t += 0.01f;
		easing::Updete(sizeX, wholeScene->WIN_WIDTH * 17, 3, t);
		easing::Updete(sizeY, wholeScene->WIN_HEIGHT * 17, 3, t);

		fadeIN->SetSize({ (float)sizeX,(float)sizeY });
	}

	if (sizeX > wholeScene->WIN_WIDTH * 15 && selectedStageFlag == true)
	{
		if (wholeScene->GetSelectNum() == static_cast<int>(WholeScene::STAGE_NUM::STAGE1) && selectMoveTime >= 0.2f)
		{
			audio->StopLoadedSound(resources->GetSoundData(ResourcesName::soundData2));
			pEngine->changeState(new GamePlayScene(static_cast<int>(WholeScene::STAGE_NUM::STAGE1)));
		}
		else if (wholeScene->GetSelectNum() == static_cast<int>(WholeScene::STAGE_NUM::STAGE2) && selectMoveTime >= 0.2f)
		{
			audio->StopLoadedSound(resources->GetSoundData(ResourcesName::soundData2));
			pEngine->changeState(new GamePlayScene(static_cast<int>(WholeScene::STAGE_NUM::STAGE2)));
		}
		else if (wholeScene->GetSelectNum() == static_cast<int>(WholeScene::STAGE_NUM::STAGE3) && selectMoveTime >= 0.2f)
		{
			audio->StopLoadedSound(resources->GetSoundData(ResourcesName::soundData2));
			pEngine->changeState(new GamePlayScene(static_cast<int>(WholeScene::STAGE_NUM::STAGE3)));
		}
		else if (wholeScene->GetSelectNum() == static_cast<int>(WholeScene::STAGE_NUM::STAGE4) && selectMoveTime >= 0.2f)
		{
			audio->StopLoadedSound(resources->GetSoundData(ResourcesName::soundData2));
			pEngine->changeState(new GamePlayScene(static_cast<int>(WholeScene::STAGE_NUM::STAGE4)));
		}
		else if (wholeScene->GetSelectNum() == static_cast<int>(WholeScene::STAGE_NUM::STAGE5) && selectMoveTime >= 0.2f)
		{
			audio->StopLoadedSound(resources->GetSoundData(ResourcesName::soundData2));
			pEngine->changeState(new GamePlayScene(static_cast<int>(WholeScene::STAGE_NUM::STAGE5)));
		}
	}
	for (int y = 0; y < TITLE_STAGE_Y; y++)
	{
		for (int x = 0; x < TITLE_STAGE_X; x++)
		{
			titleStageBox[y][x]->Update();
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
	WholeScene *wholeScene = WholeScene::GetInstance();

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

	for (const auto &oneCloud : cloud)
	{
		oneCloud->Draw();
	}
	objPlayer->Draw();
	for (int y = 0; y < TITLE_STAGE_Y; y++)
	{
		for (int x = 0; x < TITLE_STAGE_X; x++)
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

	//�X�e�[�W�ԍ��̕`��
	Stage1Sprite->Draw();
	Stage2Sprite->Draw();
	Stage3Sprite->Draw();
	Stage4Sprite->Draw();
	Stage5Sprite->Draw();

	//�����ǂ̂��炢�Q�b�g�������`�悷��
	for (int i = 0; i < 5; i++)
	{
		if (wholeScene->GetStarNum(i).x == 1)
		{
			starSprite[0][i]->Draw();
		}
		if (wholeScene->GetStarNum(i).x == 0)
		{
			noStarSprite[0][i]->Draw();
		}

		if (wholeScene->GetStarNum(i).y == 1)
		{
			starSprite[1][i]->Draw();
		}
		if (wholeScene->GetStarNum(i).y == 0)
		{
			noStarSprite[1][i]->Draw();
		}

		if (wholeScene->GetStarNum(i).z == 1)
		{
			starSprite[2][i]->Draw();
		}
		if (wholeScene->GetStarNum(i).z == 0)
		{
			noStarSprite[2][i]->Draw();
		}
	}

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
