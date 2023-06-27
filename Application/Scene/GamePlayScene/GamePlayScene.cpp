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
	Json *json = Json::GetInstance();

	//�X�v���C�g�T�C�Y�ύX
	eggSpriteSize = { 32,32 };
	startToGoalSize = { 1000,64 };
	goalSpriteSize = { 64,64 };

	//�X�v���C�g����
	backGround.reset(Sprite::Create(1, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f }));
	playerIconSprite.reset(Sprite::Create(12, { 64,64 }));
	GameOver.reset(Sprite::Create(4, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f }));
	goTitle.reset(Sprite::Create(14, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f - WinApp::window_height / 6.0f }));
	reStart.reset(Sprite::Create(15, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f }));
	Return.reset(Sprite::Create(16, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f + WinApp::window_height / 6.0f }));
	ClearStageSprite.reset(Sprite::Create(17, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f }));
	fadeOut.reset(Sprite::Create(19, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f }));
	fadeIn.reset(Sprite::Create(18, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f }));
	escUI.reset(Sprite::Create(21, { WinApp::window_width - 64,WinApp::window_height - 64 }));
	homeUI.reset(Sprite::Create(22, { WinApp::window_width - 64,WinApp::window_height - 64 }));
	eggSprite.reset(Sprite::Create(23, { WinApp::window_width / 2 - startToGoalSize.x/2 ,150 }));
	startToGoal.reset(Sprite::Create(24, { WinApp::window_width / 2,150 }));
	goalSprite.reset(Sprite::Create(25, { WinApp::window_width / 2 + startToGoalSize.x / 2,150 }));

	for (int i = 0; i < 17; i++)
	{
		gaugeSprite[i].reset(Sprite::Create(28, { WinApp::window_width / 2,WinApp::window_height / 2 },{1,1,1,0.5f}));
		gaugeSprite[i]->SetSize({ 32,128 });
		gaugeSprite[i]->SetTextureRect({ (float)(128 * i),(float)(0) }, { 128,512 });
	}
	buttonA.reset(Sprite::Create(29, { WinApp::window_width / 2 - 200,WinApp::window_height / 2 + 200 }, { 1,1,1,1 }));
	buttonSpace.reset(Sprite::Create(30, { WinApp::window_width / 2 - 200,WinApp::window_height / 2 + 200 }, { 1,1,1,1 }));
	tutorialSprite[0].reset(Sprite::Create(31, { WinApp::window_width / 2,WinApp::window_height / 2 }, { 1,1,1,0.8f }));
	tutorialSprite[1].reset(Sprite::Create(32, { WinApp::window_width / 2,WinApp::window_height / 2 }, { 1,1,1,0.8f }));

	//�X�v���C�g�T�C�Y�ύX
	eggSprite->SetSize(eggSpriteSize);
	startToGoal->SetSize(startToGoalSize);
	goalSprite->SetSize(goalSpriteSize);

	// 3D�I�u�W�F�N�g����
	objPlayer = std::make_unique<Player>();
	objPlayer.reset(Player::Create(resources->GetModel(ResourcesName::modelPlayer)));

	for (int i = 0; i < cloud.size(); i++)
	{
		cloud[i].reset(ModelObj::Create(resources->GetModel(ResourcesName::modelCloud)));
	}

	for (int i = 0; i < 10; i++)
	{
		cloud[i]->SetPosition({ (float)(8 * i) - 15.0f + (float)wholeScene->GetRand(-5,2),20 + (float)wholeScene->GetRand(-2,4),(float)wholeScene->GetRand(10,5) });
		cloudPos[i] = cloud[i]->GetPosition();
		cloudSpeed[i] = (float)wholeScene->GetRand(10, 30);
	}

	objGoal.reset(ModelObj::Create(resources->GetModel(ResourcesName::modelGoal)));

	//�`���[�g���A���p�̊Ŕ�
	for (auto &oneSigboard : objSignboard)
	{
		oneSigboard.reset(ModelObj::Create(resources->GetModel(ResourcesName::modelSignboard)));
	}

	//�w�i�p�̌��h���p�I�u�W�F�N�g
	for (int i = 0; i < backObjNum; i++)
	{
		backObj1[i].reset(ModelObj::Create(resources->GetModel(ResourcesName::modelBackObj1)));
		backObj2[i].reset(ModelObj::Create(resources->GetModel(ResourcesName::modelBackObj2)));
		backObj3[i].reset(ModelObj::Create(resources->GetModel(ResourcesName::modelBackObj3)));
	}

	playerParticle = std::make_unique<Particle>();
	playerParticle->Initialize(resources->GetModel(ResourcesName::modelEggShell));

	//�J�E���g�_�E���N���X������
	countDown = std::make_unique<CountDown>();
	if (wholeScene->GetSelectNum() == 0)
	{
		json->ReadFile("Resources/data.json", "map1");
		for (int y = 0; y < Y_MAX; y++)
		{
			for (int x = 0; x < X_MAX; x++)
			{
				mapData[y][x] = json->GetMapData(y, x);
			}
		}
		StageSet(mapData, wholeScene->GetStageFireNum(), audio, fps);
	}
	if (wholeScene->GetSelectNum() == 1)
	{
		json->ReadFile("Resources/data.json", "map2");
		for (int y = 0; y < Y_MAX; y++)
		{
			for (int x = 0; x < X_MAX; x++)
			{
				mapData[y][x] = json->GetMapData(y, x);
			}
		}
		StageSet(mapData, wholeScene->GetStageFireNum(), audio, fps);
	}
	if (wholeScene->GetSelectNum() == 2)
	{
		json->ReadFile("Resources/data.json", "map3");
		for (int y = 0; y < Y_MAX; y++)
		{
			for (int x = 0; x < X_MAX; x++)
			{
				mapData[y][x] = json->GetMapData(y, x);
			}
		}
		StageSet(mapData, wholeScene->GetStageFireNum(), audio, fps);
	}
	if (wholeScene->GetSelectNum() == 3)
	{
		json->ReadFile("Resources/data.json", "map4");
		for (int y = 0; y < Y_MAX; y++)
		{
			for (int x = 0; x < X_MAX; x++)
			{
				mapData[y][x] = json->GetMapData(y, x);
			}
		}
		StageSet(mapData, wholeScene->GetStageFireNum(), audio, fps);
	}
	if (wholeScene->GetSelectNum() == 4)
	{
		json->ReadFile("Resources/data.json", "map5");
		for (int y = 0; y < Y_MAX; y++)
		{
			for (int x = 0; x < X_MAX; x++)
			{
				mapData[y][x] = json->GetMapData(y, x);
			}
		}
		StageSet(mapData, wholeScene->GetStageFireNum(), audio, fps);
	}

	objPlayer->SetPosition({ 10, 5, 0 });
	fadeOutSizeX = 1280 * 5;
	fadeOutSizeY = 720 * 5;
	fadeOutT = 0;
	fadeOutFlag = true;

	fadeInSizeX = 1280 / 2;
	fadeInSizeY = 720 / 2;
	fadeInT = 0;
	fadeInFlag = false;
	operationButton = false;
	for (int i = 0; i < 2; i++)
	{
		operationDrawButton[i] = false;
	}
	tutorialMoveFlag = false;

	tmp = 0;
	swapI = 0;
	starToget = wholeScene->GetStarNum(wholeScene->GetSelectNum());

	//�X�^�[���擾���Ă���Z���N�g�ɖ߂������ɖ߂���悤�ɉ��ϐ��ɕۑ����Ă���
	oldStarToGet = starToget;
	gaugeStatus = GamePlayScene::GaugeStatus::PUSHOK;

	particleMan = ParticleManager::GetInstance();
}

void GamePlayScene::Update(GameSceneManager *pEngine, Audio* audio,DebugText *debugText, LightGroup *lightGroup, DebugCamera *camera, Fps *fps)
{
	StageUpdate(pEngine, audio, debugText, lightGroup, camera, fps);
}

void GamePlayScene::Draw(GameSceneManager *pEngine, DirectXApp *common, DebugText *debugText)
{
	StageDraw(common, debugText);
}

void GamePlayScene::StageSet(const std::array<std::array<int, X_MAX>, Y_MAX> Map, const int stageNum, Audio *audio, Fps *fps)
{
	Resources *resources = Resources::GetInstance();
	WholeScene *wholeScene = WholeScene::GetInstance();

	objPlayer->Initialize();
	gimmickCenterNum = 0;
	enemyNum = 0;

	for (int y = 0; y < Y_MAX; y++)
	{
		for (int x = 0; x < X_MAX; x++)
		{
			//�u���b�N
			if (Map[y][x] == static_cast<int>(StageSet::BLOCK))
			{
				objStageBox.push_back(std::make_unique<ModelObj>());
				objStageBox[objStageBox.size() - 1].reset(ModelObj::Create(resources->GetModel(ResourcesName::modelStageBox)));
				objStageBox[objStageBox.size() - 1]->Initialize();
				objStageBox[objStageBox.size() - 1]->SetPosition({ 2.0f * x, -2.0f * y + Y_MAX * 2.0f, 0 });
			}
			//�G
			if (Map[y][x] == static_cast<int>(StageSet::ENEMY))
			{
				enemy.push_back(std::make_unique<Enemy>());
				enemy[enemy.size() - 1].reset(Enemy::Create(resources->GetModel(ResourcesName::modelEnemy)));
				if (stageNum == 2)
				{
					if (x == 12)
					{
						enemy[enemy.size() - 1]->SetAction("TOGEZOU");
					}
					if (x == 23 || x == 26)
					{

					}
					if (x == 67 || x == 70)
					{
						enemy[enemy.size() - 1]->SetAction("JUMP");
					}
				}
				if (stageNum == 3)
				{
					if (x == 9 || x == 12 || x == 15)
					{
						enemy[enemy.size() - 1]->SetAction("NORMAL");
					}
				}
				if (stageNum == 4)
				{
					if (x == 12)
					{
						enemy[enemy.size() - 1]->SetAction("NORMAL");
					}
					if (x == 23 || x == 26)
					{

					}
					if (x == 67 || x == 70)
					{
						enemy[enemy.size() - 1]->SetAction("JUMP");
					}
				}
				if (stageNum == 5)
				{

				}
				enemy[enemy.size() - 1]->Initialize();
				enemy[enemy.size() - 1]->SetRotation({ 0,180,0 });
				enemy[enemy.size() - 1]->SetPosition({ 2.0f * x, -2.0f * y + Y_MAX * 2.0f + 0.5f, 0 });
			}
			//�ԃu���b�N
			if (Map[y][x] == static_cast<int>(StageSet::REDBLOCK))
			{
				objRedBlock.push_back(std::make_unique<ModelObj>());
				objRedBlock[objRedBlock.size() - 1].reset(ModelObj::Create(resources->GetModel(ResourcesName::modelRedBlock)));
				objRedBlock[objRedBlock.size() - 1]->Initialize();
				objRedBlock[objRedBlock.size() - 1]->SetPosition({ 2.0f * x, -2.0f * y + Y_MAX * 2.0f, 0 });
			}
			//�u���b�N
			if (Map[y][x] == static_cast<int>(StageSet::BLUEBLOCK))
			{
				objBlueBlock.push_back(std::make_unique<ModelObj>());
				objBlueBlock[objBlueBlock.size() - 1].reset(ModelObj::Create(resources->GetModel(ResourcesName::modelBlueBlock)));
				objBlueBlock[objBlueBlock.size() - 1]->Initialize();
				objBlueBlock[objBlueBlock.size() - 1]->SetPosition({ 2.0f * x, -2.0f * y + Y_MAX * 2.0f, 0 });
			}
			//�`���[�g���A���p�̊Ŕ�1
			if (Map[y][x] == static_cast<int>(StageSet::JUMPBORD))
			{
				objSignboard[0]->SetPosition({2.0f * x, -2.0f * y + Y_MAX * 2.0f + 1.0f, 1.0f });
				objSignboard[0]->SetRotation({ 0,90,0 });
				objSignboard[0]->SetScale({ 1,1,1 });
			}
			//�`���[�g���A���p�̊Ŕ�2
			if (Map[y][x] == static_cast<int>(StageSet::WALLKICKBORD))
			{
				objSignboard[1]->SetPosition({ 2.0f * x, -2.0f * y + Y_MAX * 2.0f + 1.0f, 1.0f });
				objSignboard[1]->SetRotation({ 0,90,0 });
				objSignboard[1]->SetScale({ 1,1,1 });
			}
			//�Ƃ�����_
			if (Map[y][x] == static_cast<int>(StageSet::THORNSTICK))
			{
				thornStick.push_back(std::make_unique<ThornStick>());
				thornStick[thornStick.size() - 1].reset(ThornStick::Create(resources->GetModel(ResourcesName::modelThornStick)));
				thornStick[thornStick.size() - 1]->Initialize();
				thornStick[thornStick.size() - 1]->SetDirection(ThornDirection::UP);
				thornStick[thornStick.size() - 1]->RollingStick();
				if (thornStick[thornStick.size() - 1]->GetDirection() == ThornDirection::DOWN || thornStick[thornStick.size() - 1]->GetDirection() == ThornDirection::UP)
				{
					thornStick[thornStick.size() - 1]->SetPosition({ 2.0f * x, -2.0f * y + Y_MAX * 2.0f - 6, 0 });
					thornStick[thornStick.size() - 1]->SetOldStickPos(thornStick[thornStick.size() - 1]->GetPosition());
				}
				if (thornStick[thornStick.size() - 1]->GetDirection() == ThornDirection::LEFT || thornStick[thornStick.size() - 1]->GetDirection() == ThornDirection::RIGHT)
				{
					thornStick[thornStick.size() - 1]->SetPosition({ 2.0f * x - 6, -2.0f * y + Y_MAX * 2.0f, 0 });
					thornStick[thornStick.size() - 1]->SetOldStickPos(thornStick[thornStick.size() - 1]->GetPosition());
				}
			}
			//�X�^�[�i���W���j
			if (Map[y][x] == static_cast<int>(StageSet::STAR))
			{
				star.push_back(std::make_unique<Star>());
				star[star.size() - 1].reset(Star::Create(resources->GetModel(ResourcesName::modelStar)));
				star[star.size() - 1]->Initialize();
				star[star.size() - 1]->SetRotation({ 90,0,0 });
				star[star.size() - 1]->SetPosition({ 2.0f * x, -2.0f * y + Y_MAX * 2.0f, 0 });
			}
			//�S�[��
			if (Map[y][x] == static_cast<int>(StageSet::GOAL))
			{
				objGoal->SetPosition({ 2.0f * x, -2.0f * y + Y_MAX * 2.0f - 0.5f, 0 });
				objGoal->SetScale({ 1.0f,3.0f,1.0f });
				objGoal->SetRotation({ 0, 90,0 });
			}
			//�W���Q��
			if (Map[y][x] == static_cast<int>(StageSet::ZYUGEMU))
			{
				zyugemu.push_back(std::make_unique<Zyugemu>());
				zyugemu[zyugemu.size() - 1].reset(Zyugemu::Create(resources->GetModel(ResourcesName::modelZyugemu)));
				zyugemu[zyugemu.size() - 1]->Initialize();
				zyugemu[zyugemu.size() - 1]->SetRotation({ 0,180,0 });
				zyugemu[zyugemu.size() - 1]->SetPosition({ 2.0f * x, -2.0f * y + Y_MAX * 2.0f + 0.5f, 0 });

			}
		}
	}

	//�Ƃ��̓G��������Model��ύX
	for (auto &oneEnemy : enemy)
	{
		if (oneEnemy->GetAction() == "TOGEZOU")
		{
			oneEnemy->SetModel(resources->GetModel(ResourcesName::modelThornEnemy));
		}
	}
	for (int x = 0; x < X_MAX; x++)
	{
		for (int y = 0; y < Y_MAX; y++)
		{
			gimmickCenter[x] = { -100,0,0 };
			//�t�@�C�A�[�o�[
			if (Map[y][x] == 3)
			{
				gimmickCenter[gimmickCenterNum] = { 2.0f * x, -2.0f * y + Y_MAX * 2.0f, 0 };
				gimmickCenterNum++;
			}
		}
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
	fire.clear();
	for (int i = 0; i < gimmickCenterNum; i++)
	{
		wholeScene->SetStageData(wholeScene->GetStageDatas(stageNum - 1, i));
		fire.push_back(std::make_unique<Firebar>(gimmickCenter[i].x, gimmickCenter[i].y, wholeScene->GetStageData().firebarNum, wholeScene->GetStageData().direction, wholeScene->GetStageData().firebarSpeed));
		fire[fire.size() - 1]->StaticInit();
	}


	for (auto &fireBar : fire)
	{
		fireBar->Initialize();
	}

	gameTimer = (int)60 * 60;

	//�J�E���g�_�E���p�̉摜�̏����l�̐ݒ�
	countDown->Initialize();

	gameOverFlag = false;
	skullSizeX = 1280 * 10;
	skullSizeY = 720 * 10;
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

	goTitleFlag = false;
	reStartFlag = false;
	clearFlag = false;

	enemyHitShakeFlag = false;
	enemyHitShakeTimer = 0;

	timerPosX = 1280 / 2 - 20;
	timerPosY = 720 / 2 - 45;
	timerSize = 0;
	timerMoveT = 0;
	timerSizeT = 0;

	timerEmphasisSize = 0;
	timerEmphasisSizeT = 0;

	for (const auto &oneStar : star)
	{
		if (oneStar->GetPosition().x >= 0)
		{
			//���l������U�ڂ�
			starPosX[swapI] = oneStar->GetPosition().x;
			if (swapI < 2)
			{
				swapI++;
			}
		}
	}
	//�X�^�[�̈ʒu�������\�[�g����
	for (int i = 0; i < 3; ++i)
	{
		for (int j = i + 1; j < 3; ++j)
		{
			if (starPosX[i] > starPosX[j] && starPosX[j] != 0)
			{
				tmp = starPosX[i];
				starPosX[i] = starPosX[j];
				starPosX[j] = tmp;
			}
		}
	}
}

void GamePlayScene::StageUpdate(GameSceneManager *pEngine, Audio *audio, DebugText *debugText, LightGroup *lightGroup, DebugCamera *camera, Fps *fps)
{
	Resources *resources = Resources::GetInstance();
	WholeScene *wholeScene = WholeScene::GetInstance();
	
	lightGroup->SetCircleShadowDir(0, XMVECTOR({ 0,-1,0 }));
	lightGroup->SetCircleShadowCasterPos(0, objPlayer->GetPosition());
	lightGroup->SetCircleShadowAtten(0, XMFLOAT3({ objPlayer->GetShadowSize().x,objPlayer->GetShadowSize().y,0.0f }));
	lightGroup->SetCircleShadowFactorAngle(0, objPlayer->GetShadowSize());
	// �J���������_���Z�b�g
	camera->SetUp({ 0, 1, 0 });
	camera->SetEye({ objPlayer->GetPosition().x + 10, 12 + objPlayer->GetCameraMoveY(), -20 });
	camera->SetTarget({ objPlayer->GetPosition().x + 10 + enemyHitShakePos.x, 12 + enemyHitShakePos.y + objPlayer->GetCameraMoveY(), 0});

	//��ʃV�F�C�N
	if (objPlayer->GetEnemyHitShakeFlag() == true)
	{
		enemyHitShakeFlag = true;
	}
	if (enemyHitShakeFlag == false)
	{
		enemyHitShakePos = { 0,0,0 };
		enemyHitShakeTimer = 0;
	}
	if (enemyHitShakeFlag == true)
	{
		if (enemyHitShakeTimer == 0)
		{
			audio->PlayLoadedSound(resources->GetSoundData(ResourcesName::soundData11), 0.05f);
		}
		enemyHitShakeTimer++;
		enemyHitShakePos.x = (float)wholeScene->GetRand(0, 0.2f);
		enemyHitShakePos.y = (float)wholeScene->GetRand(0, 0.2f);
		if (enemyHitShakeTimer > 5)
		{
			enemyHitShakeFlag = false;
			objPlayer->SetNotEnemyHitShakeFlag();
		}
	}
	//fadein
	if (fadeInFlag == true)
	{
		fadeInT += 0.005f;
		easing::Updete(fadeInSizeX, 1280 * 17, 3, fadeInT);
		easing::Updete(fadeInSizeY, 720 * 17, 3, fadeInT);

		fadeIn->SetSize({ (float)fadeInSizeX,(float)fadeInSizeY });
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

	//�V�[���J��
	if ((playerParticle->GetFlag() == false && objPlayer->GetHP() == 0) || objPlayer->GetPosition().y < -Y_MAX * 2.0f - 10 || gameTimer <= 0)
	{
		gameOverFlag = true;
	}

	if (gameControl->menuControl(Menu::ANYKEYBORD))
	{
		operationButton = false;
	}

	if (gameControl->menuControl(Menu::ANYPAD))
	{
		operationButton = true;
	}

	//Esc���X�^�[�g�{�^���i�R���g���[���[�j���������Ƃ��Ɉꎞ��~����
	if (gameControl->menuControl(Menu::ESCAPETRIGGER))
	{
		audio->PlayLoadedSound(resources->GetSoundData(ResourcesName::soundData3), 0.05f);
		stopFlag = !stopFlag;
	}

	//�ꎞ��~�����Ƃ�
	if (stopFlag == true)
	{
		if (gameControl->menuControl(Menu::UPTRIGGER))
		{
			audio->StopLoadedSound(resources->GetSoundData(ResourcesName::soundData9));
			audio->PlayLoadedSound(resources->GetSoundData(ResourcesName::soundData9), 0.03f);
			if (stopNum < 2 && stopMoveTime >= 0.2f)
			{
				stopMoveTime = 0;
				stopNum++;
			}
		}
		else if (gameControl->menuControl(Menu::DOWNTRIGGER))
		{
			audio->StopLoadedSound(resources->GetSoundData(ResourcesName::soundData9));
			audio->PlayLoadedSound(resources->GetSoundData(ResourcesName::soundData9), 0.03f);
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

	if (gameControl->menuControl(Menu::SPACETRIGGER))
	{
		//���h���{�^�����������Ƃ�
		if (stopNum == 0 && stopMoveTime >= 0.2f)
		{
			audio->PlayLoadedSound(resources->GetSoundData(ResourcesName::soundData3), 0.05f);
			stopFlag = false;
		}

		//���X�^�[�g�{�^�����������Ƃ�
		if (stopNum == 1 && stopMoveTime >= 0.2f)
		{
			audio->PlayLoadedSound(resources->GetSoundData(ResourcesName::soundData3), 0.05f);
			//fadein
			fadeInFlag = true;
			//fadein���I������烊�X�^�[�g
			reStartFlag = true;
		}

		//�Z���N�g�ɖ߂�{�^�����������Ƃ�
		if (stopNum == 2 && stopMoveTime >= 0.2f)
		{
			audio->PlayLoadedSound(resources->GetSoundData(ResourcesName::soundData3), 0.05f);
			//fadein
			fadeInFlag = true;
			//fadein���I�������Z���N�g��ʂ�
			goTitleFlag = true;
		}
	}

	//���X�^�[�g����Ƃ�
	if (reStartFlag == true)
	{
		if (fadeInSizeX > 1280 * 15)
		{
			audio->StopLoadedSound(resources->GetSoundData(ResourcesName::soundData1));
			wholeScene->SetStarNum(oldStarToGet, wholeScene->GetStageFireNum() - 1);
			fire.clear();
			pEngine->changeState(new GamePlayScene());
		}
		return;
	}

	//�Z���N�g��ʂɖ߂�Ƃ�
	if (goTitleFlag == true)
	{
		if (fadeInSizeX > 1280 * 15)
		{
			audio->StopLoadedSound(resources->GetSoundData(ResourcesName::soundData1));
			wholeScene->SetStarNum(oldStarToGet, wholeScene->GetStageFireNum() - 1);
			fire.clear();
			pEngine->changeState(new SelectScene());
		}
		return;
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
			audio->StopLoadedSound(resources->GetSoundData(ResourcesName::soundData14));
			//�c�@�����炷
			totalPlayer--;
			wholeScene->SetTotalPlayerNum(totalPlayer);
			wholeScene->SetStarNum(oldStarToGet, wholeScene->GetStageFireNum() - 1);

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
	if (stopFlag == false && fadeOutFlag == false)
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
		//�ŏ��ɐ������Ԃ�^�񒆂ɏo��
		if (timerSizeT <= 0.5)
		{
			timerSizeT += 0.008f;
			easing::Updete(timerSize, 1, 3, timerSizeT);
		}
		if (timerSizeT > 0.5)
		{
			timerMoveT += 0.008f;
			easing::Updete(timerPosX, 1200, 3, timerMoveT);
			easing::Updete(timerPosY, 50, 3, timerMoveT);
			easing::Updete(timerSize, 0.3, 3, timerMoveT);
		}
		if (timerMoveT > 0.2)
		{
			timerMoveT = 0.21f;
			//�ꎞ��~���Ă��Ȃ�������
			if (stopFlag == false && clearStopFlag == false && tutorialMoveFlag == false)
			{
				if (gameTimer > 0)
				{
					gameTimer--;
				}
			}
		}
	}

	//�S�[���܂ł̋����𑪂�
	startToGoalSize.x = objGoal->GetPosition().x * 4.0f;
	eggSprite->SetPosition({ WinApp::window_width / 2 - startToGoalSize.x / 2 + objPlayer->GetPosition().x * 4.0f , 150 });
	goalSprite->SetPosition({ WinApp::window_width / 2 - startToGoalSize.x / 2 + objGoal->GetPosition().x * 4.0f , 150 });

	//�^�C�}�[��\��
	debugText->SetPos((float)timerPosX, (float)timerPosY);
	if ((float)gameTimer / 60.0f == 11 || (float)gameTimer / 60.0f == 10 || (float)gameTimer / 60.0f == 9 || (float)gameTimer / 60.0f == 8 ||
		(float)gameTimer / 60.0f == 7 || (float)gameTimer / 60.0f == 6 || (float)gameTimer / 60.0f == 5 || (float)gameTimer / 60.0f == 4||
		(float)gameTimer / 60.0f == 3|| (float)gameTimer / 60.0f == 2|| (float)gameTimer / 60.0f == 1)
	{
		timerEmphasisSize = 0.5f;
		timerEmphasisSizeT = 0;
	}
	if (gameTimer / 60 <= 10)
	{
		if (gameTimer / 60 == 10)
		{
			audio->StopLoadedSound(resources->GetSoundData(ResourcesName::soundData1));
			audio->PlayLoadedSound(resources->GetSoundData(ResourcesName::soundData14), 0.05f);
		}
		timerEmphasisSizeT += 0.002f;
		easing::Updete(timerEmphasisSize, 0, 3, timerEmphasisSizeT);
	}
	debugText->SetSize((float)timerSize+(float)timerEmphasisSize);
	debugText->Printf("%d", gameTimer / 60);

	//�v���C���[�̑�����\��
	debugText->SetPos(150, 64);
	debugText->SetSize(0.5f);
	debugText->Printf("%d", wholeScene->GetTotalPlayerNum());

	//�_�̈ړ�
	{
		for (int i = 0; i < 10; i++)
		{
			cloudPos[i].x -= cloudSpeed[i] * 0.001f;
			if (cloud[i]->GetPosition().x < objPlayer->GetPosition().x - 25.0f)
			{
				if (i == 0)
				{
					cloudPos[i] = { objPlayer->GetPosition().x + 45.0f + (float)wholeScene->GetRand(-5,2),20 + (float)wholeScene->GetRand(-2,4),(float)wholeScene->GetRand(10,5) };
				}
				else
				{
					cloudPos[i] = { objPlayer->GetPosition().x + 45.0f + (float)wholeScene->GetRand(-5,2),20 + (float)wholeScene->GetRand(-2,4),(float)wholeScene->GetRand(10,5)};
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
		if (objPlayer->GetHP() > 0 && gameOverFlag == false && tutorialMoveFlag == false)
		{
			objPlayer->Move(audio,operationDrawButton[0] || operationDrawButton[1]);
		}
		for (const auto &oneThornStick : thornStick)
		{
			oneThornStick->Move();
		}

		if (gameControl->moveControl(Move::JUMP) && gaugeStatus == GamePlayScene::GaugeStatus::PUSHOK)
		{
			if (gaugeSpriteTime < 32)
			{
				gaugeSpriteTime++;
			}
		}
		else if (!gameControl->moveControl(Move::JUMP))
		{
			gaugeStatus = GamePlayScene::GaugeStatus::PUSHED;
		}

		for (const auto &oneEnemy : enemy)
		{
			if ((objPlayer->GetPosition().x + 2.0 * 13 > oneEnemy->GetPosition().x))
			{
				oneEnemy->Move(objPlayer->GetPosition());
				for (const auto &oneStageBox : objStageBox)
				{
					oneEnemy->CollisionObject(oneStageBox.get());
				}
			}
		}

		for (const auto &oneZyugemu : zyugemu)
		{
			if ((objPlayer->GetPosition().x + 2.0 * 13 > oneZyugemu->GetPosition().x))
			{
				oneZyugemu->Move(objPlayer->GetPosition());
				for (const auto &oneStageBox : objStageBox)
				{
					oneZyugemu->CollisionObject(oneStageBox.get());
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
		for (const auto &oneStageBox : objStageBox)
		{
			//�u���b�N�ƃv���C���[�̓����蔻��
			objPlayer->HitObjBase(oneStageBox.get());
			if (GameCollision::CollisionPlayerLeftToObj(objPlayer.get(), oneStageBox.get()))
			{
				objPlayer->HitObjLeft(oneStageBox.get(), audio);
			}
			if (GameCollision::CollisionPlayerRightToObj(objPlayer.get(), oneStageBox.get()))
			{
				objPlayer->HitObjRight(oneStageBox.get(), audio);
			}
			if (GameCollision::CollisionPlayerDownToObj(objPlayer.get(), oneStageBox.get()))
			{
				objPlayer->HitObjDown(oneStageBox.get());
				gaugeSpriteTime = 0;
				gaugeStatus = GamePlayScene::GaugeStatus::PUSHOK;
			}
			if (GameCollision::CollisionPlayerUpToObj(objPlayer.get(), oneStageBox.get()))
			{
				objPlayer->HitObjUp(oneStageBox.get());
			}
		}

		for (const auto &oneEnemy : enemy)
		{
			//�G�ƃv���C���[�̓����蔻��
			if (GameCollision::CollisionPlayerLeftAndRightToEnemy(objPlayer.get(), oneEnemy.get()) && !(oneEnemy->GetAction() == "TOGEZOU"))
			{
				objPlayer->HitEnemyLeftAndRight(oneEnemy.get());
			}
			if (GameCollision::CollisionPlayerDownToEnemy(objPlayer.get(), oneEnemy.get()) && !(oneEnemy->GetAction() == "TOGEZOU"))
			{
				objPlayer->HitEnemyDown(oneEnemy.get());
			}
			if (GameCollision::CollisionPlayerUpToEnemy(objPlayer.get(), oneEnemy.get()) && !(oneEnemy->GetAction() == "TOGEZOU"))
			{
				objPlayer->HitEnemyUp(oneEnemy.get());
			}
			//�Ƃ������ƃv���C���[�̓����蔻��
			if (GameCollision::CollisionPlayerLeftAndRightToEnemy(objPlayer.get(), oneEnemy.get()) && (oneEnemy->GetAction() == "TOGEZOU"))
			{
				objPlayer->HitGimmick(oneEnemy.get());
			}
			if (GameCollision::CollisionPlayerDownToEnemy(objPlayer.get(), oneEnemy.get()) && (oneEnemy->GetAction() == "TOGEZOU"))
			{
				objPlayer->HitGimmick(oneEnemy.get());
			}
			if (GameCollision::CollisionPlayerUpToEnemy(objPlayer.get(), oneEnemy.get()) && (oneEnemy->GetAction() == "TOGEZOU"))
			{
				objPlayer->HitGimmick(oneEnemy.get());
			}

			//�G���o���t�@�C�A�[�ƃv���C���[�̓����蔻��
			if (GameCollision::CollisionPlayerToGimmick(objPlayer.get(), oneEnemy->GetFire(), oneEnemy.get()->GetFire()->GetScale()))
			{
				if (oneEnemy.get()->GetFire()->GetScale().x >= 0.1f)
				{
					objPlayer->HitGimmick(oneEnemy.get()->GetFire());
				}
			}
		}
		//�W���Q���������珈������
		if (zyugemu.size() > 0)
		{
			for (int i = 0; i < zyugemu[zyugemu.size() - 1]->GetALLEnemy(); i++)
			{
				if (GameCollision::CollisionPlayerLeftAndRightToEnemy(objPlayer.get(), zyugemu[zyugemu.size() - 1]->GetEnemy(i)) && (zyugemu[zyugemu.size() - 1]->GetEnemy(i)->GetAction() == "TOGEZOU"))
				{
					objPlayer->HitGimmick(zyugemu[zyugemu.size() - 1]->GetEnemy(i));
				}
				if (GameCollision::CollisionPlayerDownToEnemy(objPlayer.get(), zyugemu[zyugemu.size() - 1]->GetEnemy(i)) && (zyugemu[zyugemu.size() - 1]->GetEnemy(i)->GetAction() == "TOGEZOU"))
				{
					objPlayer->HitGimmick(zyugemu[zyugemu.size() - 1]->GetEnemy(i));
				}
				if (GameCollision::CollisionPlayerUpToEnemy(objPlayer.get(), zyugemu[zyugemu.size() - 1]->GetEnemy(i)) && (zyugemu[zyugemu.size() - 1]->GetEnemy(i)->GetAction() == "TOGEZOU"))
				{
					objPlayer->HitGimmick(zyugemu[zyugemu.size() - 1]->GetEnemy(i));
				}
			}
		}
		for (const auto &oneRedBlock : objRedBlock)
		{
			if (objPlayer->GetJumpChangeBlockFlag() == false)
			{
				objPlayer->HitObjBase(oneRedBlock.get());

				if (GameCollision::CollisionPlayerLeftToObj(objPlayer.get(), oneRedBlock.get()))
				{
					objPlayer->HitObjLeft(oneRedBlock.get(), audio);
				}
				if (GameCollision::CollisionPlayerRightToObj(objPlayer.get(), oneRedBlock.get()))
				{
					objPlayer->HitObjRight(oneRedBlock.get(), audio);
				}
				if (GameCollision::CollisionPlayerDownToObj(objPlayer.get(), oneRedBlock.get()))
				{
					objPlayer->HitObjDown(oneRedBlock.get());
				}
				if (GameCollision::CollisionPlayerUpToObj(objPlayer.get(), oneRedBlock.get()))
				{
					objPlayer->HitObjUp(oneRedBlock.get());
				}

			}

		}
		for (const auto &oneBlueBlock : objBlueBlock)
		{
			if (objPlayer->GetJumpChangeBlockFlag() == true)
			{
				objPlayer->HitObjBase(oneBlueBlock.get());

				if (GameCollision::CollisionPlayerLeftToObj(objPlayer.get(), oneBlueBlock.get()))
				{
					objPlayer->HitObjLeft(oneBlueBlock.get(), audio);
				}
				if (GameCollision::CollisionPlayerRightToObj(objPlayer.get(), oneBlueBlock.get()))
				{
					objPlayer->HitObjRight(oneBlueBlock.get(), audio);
				}
				if (GameCollision::CollisionPlayerDownToObj(objPlayer.get(), oneBlueBlock.get()))
				{
					objPlayer->HitObjDown(oneBlueBlock.get());
				}
				if (GameCollision::CollisionPlayerUpToObj(objPlayer.get(), oneBlueBlock.get()))
				{
					objPlayer->HitObjUp(oneBlueBlock.get());
				}
			}
		}
	}
	
	//�X�^�[�ƃv���C���[�̓����蔻��
	for (const auto &oneStar : star)
	{
		if (GameCollision::CollisionPlayerToStar(objPlayer.get(), oneStar.get()))
		{
			if (oneStar->GetMoveingFlag() == false)
			{
				audio->PlayLoadedSound(resources->GetSoundData(ResourcesName::soundData8), 0.08f);
			}
			oneStar->GetStar();
			//�X�^�[�̖��������ׂ�
			if (oneStar->GetPosition().x == starPosX[0])
			{
				starToget.x = 1;
			}
			if (oneStar->GetPosition().x == starPosX[1])
			{
				starToget.y = 1;
			}
			if (oneStar->GetPosition().x == starPosX[2])
			{
				starToget.z = 1;
			}
			wholeScene->SetStarNum(starToget, wholeScene->GetStageFireNum() - 1);
		}
	}
	for (int i = 0; i < objSignboard.size(); i++)
	{
		if (GameCollision::CollisionPlayerToGimmick(objPlayer.get(), objSignboard[i].get(), objSignboard[i]->GetScale()) == true)
		{
			operationDrawButton[i] = true;
			if (gameControl->moveControl(Move::JUMPTRIGGER))
			{
				audio->PlayLoadedSound(resources->GetSoundData(ResourcesName::soundData3), 0.05f);
				tutorialMoveFlag = !tutorialMoveFlag;
			}
		}
		if (GameCollision::CollisionPlayerToGimmick(objPlayer.get(), objSignboard[i].get(), objSignboard[i]->GetScale()) == false)
		{
			operationDrawButton[i] = false;
		}
	}
	for (auto &fireBar : fire)
	{

		if (GameCollision::CollisionPlayerLeftToObj(objPlayer.get(), fireBar->GetCenter()))
		{
			objPlayer->HitObjLeft(fireBar->GetCenter(), audio);
		}
		if (GameCollision::CollisionPlayerRightToObj(objPlayer.get(), fireBar->GetCenter()))
		{
			objPlayer->HitObjRight(fireBar->GetCenter(), audio);
		}
		if (GameCollision::CollisionPlayerUpToObj(objPlayer.get(), fireBar->GetCenter()))
		{
			objPlayer->HitObjUp(fireBar->GetCenter());
		}
		if (GameCollision::CollisionPlayerDownToObj(objPlayer.get(), fireBar->GetCenter()) && !gameControl->moveControl(Move::JUMPTRIGGER))
		{
			objPlayer->HitObjDown(fireBar->GetCenter());
		}
		objPlayer->HitObjBase(fireBar->GetCenter());

		for (int i = 0; i < fireBar->GetNum(); i++)
		{
			if (i != 0)
			{
				if (GameCollision::CollisionPlayerToGimmick(objPlayer.get(), fireBar->GetFire(i),fireBar->GetFire(i)->GetScale()))
				{
					objPlayer->HitGimmick(fireBar->GetFire(i));
				}
			}
		}
		fireBar->Update();
	}

	//�Ƃ�����_�Ƃ̓����蔻��
	for (const auto &oneThornStick : thornStick)
	{
		if (oneThornStick->GetDirection() == ThornDirection::DOWN || oneThornStick->GetDirection() == ThornDirection::UP)
		{
			if (GameCollision::CollisionPlayerToGimmick(objPlayer.get(), oneThornStick.get(),
				XMFLOAT3(oneThornStick->GetScale().x, oneThornStick->GetScale().y * 5, oneThornStick->GetScale().z)))
			{
				objPlayer->HitGimmick(oneThornStick.get());
			}
		}
		if (oneThornStick->GetDirection() == ThornDirection::LEFT || oneThornStick->GetDirection() == ThornDirection::RIGHT)
		{
			if (GameCollision::CollisionPlayerToGimmick(objPlayer.get(), oneThornStick.get(),
				XMFLOAT3(oneThornStick->GetScale().x * 5, oneThornStick->GetScale().y, oneThornStick->GetScale().z)))
			{
				objPlayer->HitGimmick(oneThornStick.get());
			}
		}
	}
	//�S�[���Ƃ̂����蔻��
	if (GameCollision::CollisionPlayerToGoalflag(objPlayer.get(),objGoal.get()))
	{
		objPlayer->HitGoal(objGoal.get());
		if (GameCollision::CollisionPlayerToGoal(objPlayer.get(), objGoal.get()))
		{
			fadeInFlag = true;
			clearFlag = true;
		}
	}

	//�N���A�[��ʂɍs�����߂̏���
	if (clearFlag == true && fadeInSizeX > 1280 * 15)
	{
		audio->StopLoadedSound(resources->GetSoundData(ResourcesName::soundData1));
		audio->StopLoadedSound(resources->GetSoundData(ResourcesName::soundData14));
		fire.clear();
		pEngine->changeState(new ClearScene());
		//�X�e�[�W�ԍ������̃X�e�[�W�̔ԍ��ɂ���
		if (wholeScene->GetSelectNum() < 4)
		{
			selectNum += 1;
			if (selectNum > 4)
			{
				selectNum = 4;
			}
			wholeScene->SetSelectNum(selectNum);
		}
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
	for (const auto &oneStageBox : objStageBox)
	{
		oneStageBox->Update();
	}
	for (const auto &oneEnemy : enemy)
	{
		oneEnemy->Update();
	}
	for (const auto &oneZyugemu : zyugemu)
	{
		oneZyugemu->Update();
	}
	for (const auto &oneRedBlock : objRedBlock)
	{
		oneRedBlock->Update();
	}
	for (const auto &oneBlueBlock : objBlueBlock)
	{
		oneBlueBlock->Update();
	}

	//�X�^�[�̍X�V
	for (const auto &oneStar : star)
	{
		oneStar->Update();
	}

	//�Ƃ�����_�̍X�V
	for (const auto &oneThornStick : thornStick)
	{
		oneThornStick->Update();
	}

	objGoal->Update();
	//�`���[�g���A���p�̊Ŕ�
	for (const auto &oneSignboard : objSignboard)
	{
		oneSignboard->Update();
	}

	//�w�i�p�̌��h���p�I�u�W�F�N�g
	for (int i = 0; i < backObjNum; i++)
	{
		backObj1[i]->Update();
		backObj2[i]->Update();
		backObj3[i]->Update();
	}
	particleMan->Update();
	playerParticle->Update(TYPE::explosion, { objPlayer->GetPosition().x,objPlayer->GetPosition().y , 0 });
	//�ړ����Ă�Ƃ��̂ݗ��̉摜����]������
	eggSprite->SetRotation(-(objPlayer->GetRotation().z));

	startToGoal->SetSize(startToGoalSize);

	goTitle->SetSize({ (float)goTitleSpriteSize * 3,(float)goTitleSpriteSize });
	reStart->SetSize({ (float)reStartSpriteSize * 3,(float)reStartSpriteSize });
	Return->SetSize({ (float)ReturnSpriteSize * 3,(float)ReturnSpriteSize });
	for (int i = 0; i < 17; i++)
	{
		gaugeSprite[i]->SetPosition({ WinApp::window_width / 2 - 256,WinApp::window_height / 2 + 200 - (objPlayer->GetPosition().y*20)});
	}
}

void GamePlayScene::StageDraw(DirectXApp *common, DebugText *debugText)
{
	Resources *resources = Resources::GetInstance();
	///*�X�v���C�g�`��*/
///*�X�v���C�g�`��O����*/
	Sprite::PreDraw(common->GetCmdList().Get());

	// �w�i�X�v���C�g�`��
	backGround->Draw();
	///*�X�v���C�g�`��㏈��*/
	Sprite::PostDraw();
	//�[�x�o�b�t�@�N���A
	common->ClearDepthBuffer();
#pragma region �`�揈��
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

	//�_�̕`��
	for (int i = 0; i < 10; i++)
	{
		cloud[i]->Draw();
	}
	//�}�b�v�̕`��
	for (const auto &oneStageBox : objStageBox)
	{
		oneStageBox->Draw();
	}
	//�G�̕`��
	for (const auto &oneEnemy : enemy)
	{
		oneEnemy->Draw();
	}
	for (const auto &oneZyugemu : zyugemu)
	{
		oneZyugemu->Draw();
	}

	//�Ԃ��u���b�N
	for (const auto &oneRedBlock : objRedBlock)
	{
		//�����蔻��Ȃ��̃��C���[�u���b�N��\��
		if (objPlayer->GetJumpChangeBlockFlag() == true)
		{
			oneRedBlock->SetModel(resources->GetModel(ResourcesName::modelWireBlock));
			oneRedBlock->Draw();
		}
		//�����蔻�肠��̃��b�h�u���b�N��\��
		if (objPlayer->GetJumpChangeBlockFlag() == false)
		{
			oneRedBlock->SetModel(resources->GetModel(ResourcesName::modelRedBlock));
			oneRedBlock->Draw();
		}
	}
	//���u���b�N
	for (const auto &oneBlueBlock : objBlueBlock)
	{
		//�����蔻��Ȃ��̃��C���[�u���b�N��\��
		if (objPlayer->GetJumpChangeBlockFlag() == false)
		{
			oneBlueBlock->SetModel(resources->GetModel(ResourcesName::modelWireBlock));
			oneBlueBlock->Draw();
		}
		//�����蔻�肠��̃u���[�u���b�N��\��
		if (objPlayer->GetJumpChangeBlockFlag() == true)
		{
			oneBlueBlock->SetModel(resources->GetModel(ResourcesName::modelBlueBlock));
			oneBlueBlock->Draw();
		}
	}

	//�X�^�[�̕`��
	for (const auto &oneStar : star)
	{
		oneStar->Draw();
	}

	//�Ƃ�����_�̕`��
	for (const auto &oneThornStick : thornStick)
	{
		oneThornStick->Draw();
	}

	//�t�@�C�A�[�o�[�̕`��
	for (auto &fireBar : fire)
	{
		fireBar->Draw();
	}
	//�S�[���̕`��
	objGoal->Draw();
	//�Ŕ̕`��
	for (int i = 0; i < 2; i++)
	{
		if (objSignboard[i]->GetPosition().x >= 0)
		{
			if (operationDrawButton[i] == false)
			{
				objSignboard[i]->SetModel(resources->GetModel(ResourcesName::modelSignboard));
			}
			if (operationButton == false && operationDrawButton[i] == true)
			{
				objSignboard[i]->SetModel(resources->GetModel(ResourcesName::modelSignboardSpace));
			}
			if (operationButton == true && operationDrawButton[i] == true)
			{
				objSignboard[i]->SetModel(resources->GetModel(ResourcesName::modelSignboardA));
			}
			objSignboard[i]->Draw();
		}
	}
	//�v���C���[�̕`��
	objPlayer->Draw();
	// �p�[�e�B�N���̕`��
	playerParticle->Draw();

	/*���f���`��㏈��*/
	ModelObj::PostDraw();

	particleMan->Draw(common->GetCmdList().Get());

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
	if (operationButton == false)
	{
		escUI->Draw();
		for (int i = 0; i < 2; i++)
		{
			if (operationDrawButton[i] == true)
			{
				buttonSpace->Draw();
			}
		}
	}
	if (operationButton == true)
	{
		homeUI->Draw();
		for (int i = 0; i < 2; i++)
		{
			if (operationDrawButton[i] == true)
			{
				buttonA->Draw();
			}
		}
	}

	//�S�[���܂ł̈ʒu��\������X�v���C�g
	startToGoal->Draw();
	eggSprite->Draw();
	goalSprite->Draw();

	//�W�����v���̃Q�[�W�X�v���C�g
	gaugeSprite[(int)(gaugeSpriteTime / 2)]->Draw();

	for (int i = 0; i < 2; i++)
	{
		if (tutorialMoveFlag == true && operationDrawButton[i] == true)
		{
			tutorialSprite[i]->Draw();
		}
	}

	//�Q�[���I�[�o�[�̑J��
	if (gameOverFlag == true)
	{
		GameOver->Draw();
	}

	//fadein
	if (fadeInFlag == true)
	{
		fadeIn->Draw();
	}
	//fadeout
	if (fadeOutFlag == true)
	{
		fadeOut->Draw();
	}
	/*�X�v���C�g�`��㏈��*/
	Sprite::PostDraw();
}
