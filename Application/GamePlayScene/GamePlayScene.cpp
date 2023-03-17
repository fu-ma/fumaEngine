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

	// 背景スプライト生成
	backGround = Sprite::Create(1, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	playerIconSprite = Sprite::Create(12, { 64,64 });
	GameOver = Sprite::Create(4, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	goTitle = Sprite::Create(14, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f - WinApp::window_height / 6.0f });
	reStart = Sprite::Create(15, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	Return = Sprite::Create(16, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f + WinApp::window_height / 6.0f });
	ClearStageSprite = Sprite::Create(17, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	fadeOut = Sprite::Create(19, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	fadeIn = Sprite::Create(18, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	escUI = Sprite::Create(21, { WinApp::window_width - 64,WinApp::window_height - 64 });
	homeUI = Sprite::Create(22, { WinApp::window_width - 64,WinApp::window_height - 64 });

	// 3Dオブジェクト生成
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
			thornStick[y][x] = ThornStick::Create(resources->GetModel(ResourcesName::modelThornStick));
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

	//チュートリアル用の看板
	objJumpSignA = ModelObj::Create(resources->GetModel(ResourcesName::modelJumpSignSpace));
	objWallSignA = ModelObj::Create(resources->GetModel(ResourcesName::modelWallSignSpace));

	//背景用の見栄え用オブジェクト
	for (int i = 0; i < backObjNum; i++)
	{
		backObj1[i] = ModelObj::Create(resources->GetModel(ResourcesName::modelBackObj1));
		backObj2[i] = ModelObj::Create(resources->GetModel(ResourcesName::modelBackObj2));
		backObj3[i] = ModelObj::Create(resources->GetModel(ResourcesName::modelBackObj3));
	}

	playerParticle = new Particle();
	playerParticle->Initialize(resources->GetModel(ResourcesName::modelEggShell));

	//カウントダウンクラス初期化
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

			thornStick[y][x]->Initialize();
			thornStick[y][x]->SetPosition({ -100, 0, 0 });

			objRedBlock[y][x]->SetPosition({ -100,0,0 });
			objBlueBlock[y][x]->SetPosition({ -100,0,0 });

			//ブロック
			if (map[y][x] == 1)
			{
				objStageBox[y][x]->SetPosition({ 2.0f * x, -2.0f * y + Y_MAX * 2.0f, 0 });
			}
			//敵
			if (map[y][x] == 2)
			{
				enemy[y][x]->SetPosition({ 2.0f * x, -2.0f * y + Y_MAX * 2.0f + 0.5f, 0 });
				if (stageNum == 2)
				{
					if (x == 12)
					{
						enemy[y][x]->SetAction("NORMAL");
					}
					if (x == 23 || x == 26)
					{

					}
					if (x == 67 || x == 70)
					{
						enemy[y][x]->SetAction("JUMP");
					}
				}
				if (stageNum == 3)
				{
					if (x == 9 || x == 12 || x == 15)
					{
						enemy[y][x]->SetAction("NORMAL");
					}
				}
				if (stageNum == 4)
				{
					if (x == 12)
					{
						enemy[y][x]->SetAction("NORMAL");
					}
					if (x == 23 || x == 26)
					{

					}
					if (x == 67 || x == 70)
					{
						enemy[y][x]->SetAction("JUMP");
					}
				}
				if (stageNum == 5)
				{

				}
			}
			//赤ブロック
			if (map[y][x] == 4)
			{
				objRedBlock[y][x]->SetPosition({ 2.0f * x, -2.0f * y + Y_MAX * 2.0f, 0 });
			}
			//青ブロック
			if (map[y][x] == 5)
			{
				objBlueBlock[y][x]->SetPosition({ 2.0f * x, -2.0f * y + Y_MAX * 2.0f, 0 });
			}
			//チュートリアル用の看板1
			if (map[y][x] == 6)
			{
				objJumpSignA->SetPosition({ 2.0f * x, -2.0f * y + Y_MAX * 2.0f, 10 });
				objJumpSignA->SetRotation({ 0,90,0 });
				objJumpSignA->SetScale({ 1,5,5 });
			}
			//チュートリアル用の看板2
			if (map[y][x] == 7)
			{
				objWallSignA->SetPosition({ 2.0f * x, -2.0f * y + Y_MAX * 2.0f, 10 });
				objWallSignA->SetRotation({ 0,90,0 });
				objWallSignA->SetScale({ 1,5,5 });
			}
			//とげこん棒
			if (map[y][x] == 8)
			{
				thornStick[y][x]->SetPosition({ 2.0f * x, -2.0f * y + Y_MAX * 2.0f-6, 0 });
				thornStick[y][x]->SetOldStickPos(thornStick[y][x]->GetPosition());
			}
			//ゴール
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
			//ファイアーバー
			if (map[y][x] == 3)
			{
				gimmickCenter[gimmickCenterNum] = { 2.0f * x, -2.0f * y + Y_MAX * 2.0f, 0 };
				gimmickCenterNum++;
			}
		}
	}

	//背景用の見栄え用オブジェクト
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
		wholeScene->SetStageData(wholeScene->GetStageDatas(stageNum - 1,i));
		firebar = new Firebar(gimmickCenter[i].x, gimmickCenter[i].y, wholeScene->GetStageData().firebarNum, wholeScene->GetStageData().direction, wholeScene->GetStageData().firebarSpeed);
		firebar->StaticInit();
		fire.push_back(firebar);
	}


	for (auto &fireBar : fire)
	{
		fireBar->Initialize();
	}

	gameTimer = (int)60 * 60;

	//カウントダウン用の画像の初期値の設定
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
}

void GamePlayScene::StageUpdate(GameSceneManager *pEngine, Audio *audio, DebugText *debugText, LightGroup *lightGroup, DebugCamera *camera, Fps *fps)
{
	Resources *resources = Resources::GetInstance();
	WholeScene *wholeScene = WholeScene::GetInstance();

	lightGroup->SetCircleShadowDir(0, XMVECTOR({ 0,-1,0 }));
	lightGroup->SetCircleShadowCasterPos(0, objPlayer->GetPosition());
	lightGroup->SetCircleShadowAtten(0, XMFLOAT3({ objPlayer->GetShadowSize().x,objPlayer->GetShadowSize().y,0.0f }));
	lightGroup->SetCircleShadowFactorAngle(0, objPlayer->GetShadowSize());
	// カメラ注視点をセット
	camera->SetUp({ 0, 1, 0 });
	camera->SetEye({ objPlayer->GetPosition().x + 10, 12 + objPlayer->GetCameraMoveY(), -20 });
	camera->SetTarget({ objPlayer->GetPosition().x + 10 + enemyHitShakePos.x, 12 + enemyHitShakePos.y + objPlayer->GetCameraMoveY(), 0});

	//画面シェイク
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

	//シーン遷移
	if ((playerParticle->GetFlag() == false && objPlayer->GetHP() == 0) || objPlayer->GetPosition().y < -Y_MAX * 2.0f - 10 || gameTimer <= 0)
	{
		gameOverFlag = true;
	}

	if (gameControl->menuControl(Menu::ANYKEYBORD))
	{
		objJumpSignA->SetModel(resources->GetModel(ResourcesName::modelJumpSignSpace));
		objWallSignA->SetModel(resources->GetModel(ResourcesName::modelWallSignSpace));
		operationButton = false;
	}

	if (gameControl->menuControl(Menu::ANYPAD))
	{
		objJumpSignA->SetModel(resources->GetModel(ResourcesName::modelJumpSignA));
		objWallSignA->SetModel(resources->GetModel(ResourcesName::modelWallSignA));
		operationButton = true;
	}

	//Escかスタートボタン（コントローラー）を押したときに一時停止する
	if (gameControl->menuControl(Menu::ESCAPETRIGGER))
	{
		stopFlag = !stopFlag;
	}

	//一時停止したとき
	if (stopFlag == true)
	{
		if (gameControl->menuControl(Menu::UPTRIGGER))
		{
			if (stopNum < 2 && stopMoveTime >= 0.2f)
			{
				stopMoveTime = 0;
				stopNum++;
			}
		}
		else if (gameControl->menuControl(Menu::DOWNTRIGGER))
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

	if (gameControl->menuControl(Menu::SPACETRIGGER))
	{
		//モドルボタンを押したとき
		if (stopNum == 0 && stopMoveTime >= 0.2f)
		{
			stopFlag = false;
		}

		//リスタートボタンを押したとき
		if (stopNum == 1 && stopMoveTime >= 0.2f)
		{
			//fadein
			fadeInFlag = true;
			//fadeinが終わったらリスタート
			reStartFlag = true;
		}

		//セレクトに戻るボタンを押したとき
		if (stopNum == 2 && stopMoveTime >= 0.2f)
		{
			//fadein
			fadeInFlag = true;
			//fadeinが終わったらセレクト画面に
			goTitleFlag = true;
		}
	}

	//リスタートするとき
	if (reStartFlag == true)
	{
		if (fadeInSizeX > 1280 * 15)
		{
			audio->StopLoadedSound(resources->GetSoundData(ResourcesName::soundData1));
			fire.clear();
			pEngine->changeState(new GamePlayScene());
		}
		return;
	}

	//セレクト画面に戻るとき
	if (goTitleFlag == true)
	{
		if (fadeInSizeX > 1280 * 15)
		{
			audio->StopLoadedSound(resources->GetSoundData(ResourcesName::soundData1));
			fire.clear();
			pEngine->changeState(new SelectScene());
		}
		return;
	}

	//デス時の画面遷移
	if (gameOverFlag == true)
	{
		easing::Updete(skullSizeX, 1280, 3, gameOverTime);
		easing::Updete(skullSizeY, 720, 3, gameOverTime);
		gameOverTime += 0.001f;
		if (gameOverTime > 0.2)
		{
			audio->StopLoadedSound(resources->GetSoundData(ResourcesName::soundData1));
			//残機を減らす
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

	//3,2,1,スタート
	if (stopFlag == false && fadeOutFlag == false)
	{
		countDown->Update();
	}

	//ゴールしたときに時間計測を止める
	if (objPlayer->GetPlayerStop() == true)
	{
		clearStopFlag = true;
	}
	//スターと表示がされてからしばらくして
	if (countDown->GetStart() >= 0.8)
	{
		//最初に制限時間を真ん中に出す
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
			//一時停止していなかったら
			if (stopFlag == false && clearStopFlag == false)
			{
				if (gameTimer > 0)
				{
					gameTimer--;
				}
			}
		}
	}

	//タイマーを表示
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
		timerEmphasisSizeT += 0.002f;
		easing::Updete(timerEmphasisSize, 0, 3, timerEmphasisSizeT);
	}
	debugText->SetSize((float)timerSize+(float)timerEmphasisSize);
	debugText->Printf("%d", gameTimer / 60);

	//プレイヤーの総数を表示
	debugText->SetPos(150, 64);
	debugText->SetSize(0.5f);
	debugText->Printf("%d", wholeScene->GetTotalPlayerNum());

	//雲の移動
	{
		for (int i = 0; i < 10; i++)
		{
			cloudPos[i].x -= 0.03f;
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
	//動くようになる
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
				thornStick[y][x]->Move();
			}
		}

		for (int y = 0; y < Y_MAX; y++)
		{
			for (int x = 0; x < X_MAX; x++)
			{
				if (enemy[y][x]->GetPosition().x >= 0 && (objPlayer->GetPosition().x + 2.0 * 13 > enemy[y][x]->GetPosition().x))
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

	//あたり判定
	if (countDown->GetStart() >= 0.2 && stopFlag == false)
	{
		for (int y = 0; y < Y_MAX; y++)
		{
			for (int x = 0; x < X_MAX; x++)
			{
				//ブロックとプレイヤーの当たり判定
				objPlayer->HitObjBase(objStageBox[y][x]);
				if (GameCollision::CollisionPlayerLeftToObj(objPlayer, objStageBox[y][x]))
				{
					objPlayer->HitObjLeft(objStageBox[y][x]);
				}
				if (GameCollision::CollisionPlayerRightToObj(objPlayer, objStageBox[y][x]))
				{
					objPlayer->HitObjRight(objStageBox[y][x]);
				}
				if (GameCollision::CollisionPlayerDownToObj(objPlayer, objStageBox[y][x]))
				{
					objPlayer->HitObjDown(objStageBox[y][x]);
				}
				if (GameCollision::CollisionPlayerUpToObj(objPlayer, objStageBox[y][x]))
				{
					objPlayer->HitObjUp(objStageBox[y][x]);
				}

				//敵とプレイヤーの当たり判定
				if (GameCollision::CollisionPlayerLeftAndRightToEnemy(objPlayer, enemy[y][x]))
				{
					objPlayer->HitEnemyLeftAndRight(enemy[y][x]);
				}
				if (GameCollision::CollisionPlayerDownToEnemy(objPlayer, enemy[y][x]))
				{
					objPlayer->HitEnemyDown(enemy[y][x]);
				}
				if (GameCollision::CollisionPlayerUpToEnemy(objPlayer, enemy[y][x]))
				{
					objPlayer->HitEnemyUp(enemy[y][x]);
				}

				if (objPlayer->GetJumpChangeBlockFlag() == false)
				{
					objPlayer->HitObjBase(objRedBlock[y][x]);

					if (GameCollision::CollisionPlayerLeftToObj(objPlayer, objRedBlock[y][x]))
					{
						objPlayer->HitObjLeft(objRedBlock[y][x]);
					}
					if (GameCollision::CollisionPlayerRightToObj(objPlayer, objRedBlock[y][x]))
					{
						objPlayer->HitObjRight(objRedBlock[y][x]);
					}
					if (GameCollision::CollisionPlayerDownToObj(objPlayer, objRedBlock[y][x]))
					{
						objPlayer->HitObjDown(objRedBlock[y][x]);
					}
					if (GameCollision::CollisionPlayerUpToObj(objPlayer, objRedBlock[y][x]))
					{
						objPlayer->HitObjUp(objRedBlock[y][x]);
					}

				}
				if (objPlayer->GetJumpChangeBlockFlag() == true)
				{
					objPlayer->HitObjBase(objBlueBlock[y][x]);

					if (GameCollision::CollisionPlayerLeftToObj(objPlayer, objBlueBlock[y][x]))
					{
						objPlayer->HitObjLeft(objBlueBlock[y][x]);
					}
					if (GameCollision::CollisionPlayerRightToObj(objPlayer, objBlueBlock[y][x]))
					{
						objPlayer->HitObjRight(objBlueBlock[y][x]);
					}
					if (GameCollision::CollisionPlayerDownToObj(objPlayer, objBlueBlock[y][x]))
					{
						objPlayer->HitObjDown(objBlueBlock[y][x]);
					}
					if (GameCollision::CollisionPlayerUpToObj(objPlayer, objBlueBlock[y][x]))
					{
						objPlayer->HitObjUp(objBlueBlock[y][x]);
					}
				}
			}
		}
	}

	for (auto &fireBar : fire)
	{
		fireBar->Move();
		objPlayer->HitObjBase(fireBar->GetCenter());

		if (GameCollision::CollisionPlayerLeftToObj(objPlayer, fireBar->GetCenter()))
		{
			objPlayer->HitObjLeft(fireBar->GetCenter());
		}
		if (GameCollision::CollisionPlayerRightToObj(objPlayer, fireBar->GetCenter()))
		{
			objPlayer->HitObjRight(fireBar->GetCenter());
		}
		if (GameCollision::CollisionPlayerDownToObj(objPlayer, fireBar->GetCenter()))
		{
			objPlayer->HitObjDown(fireBar->GetCenter());
		}
		if (GameCollision::CollisionPlayerUpToObj(objPlayer, fireBar->GetCenter()))
		{
			objPlayer->HitObjUp(fireBar->GetCenter());
		}

		for (int i = 0; i < fireBar->GetNum(); i++)
		{
			if (i != 0)
			{
				if (GameCollision::CollisionPlayerToGimmick(objPlayer, fireBar->GetFire(i),fireBar->GetFire(i)->GetScale()))
				{
					objPlayer->HitGimmick(fireBar->GetFire(i));
				}
			}
		}
		fireBar->Update();
	}

	//とげこん棒との当たり判定
	for (int y = 0; y < Y_MAX; y++)
	{
		for (int x = 0; x < X_MAX; x++)
		{
			if (GameCollision::CollisionPlayerToGimmick(objPlayer, thornStick[y][x],
				XMFLOAT3(thornStick[y][x]->GetScale().x, thornStick[y][x]->GetScale().y*6, thornStick[y][x]->GetScale().z)))
			{
				objPlayer->HitGimmick(thornStick[y][x]);
			}
		}
	}
	//ゴールとのあたり判定
	if (GameCollision::CollisionPlayerToGoalflag(objPlayer,objGoal))
	{
		objPlayer->HitGoal(objGoal);
		if (GameCollision::CollisionPlayerToGoal(objPlayer, objGoal))
		{
			fadeInFlag = true;
			clearFlag = true;
		}
	}

	//クリアー画面に行くための処理
	if (clearFlag == true && fadeInSizeX > 1280 * 15)
	{
		audio->StopLoadedSound(resources->GetSoundData(ResourcesName::soundData1));
		fire.clear();
		pEngine->changeState(new ClearScene());
		//ステージ番号を次のステージの番号にする
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
			if (thornStick[y][x]->GetPosition().x >= 0)
			{
				thornStick[y][x]->Update();
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
	//チュートリアル用の看板
	objJumpSignA->Update();
	objWallSignA->Update();
	//背景用の見栄え用オブジェクト
	for (int i = 0; i < backObjNum; i++)
	{
		backObj1[i]->Update();
		backObj2[i]->Update();
		backObj3[i]->Update();
	}
	particleMan->Update();
	playerParticle->Update(TYPE::explosion, { objPlayer->GetPosition().x,objPlayer->GetPosition().y , 0 });

	goTitle->SetSize({ (float)goTitleSpriteSize * 3,(float)goTitleSpriteSize });
	reStart->SetSize({ (float)reStartSpriteSize * 3,(float)reStartSpriteSize });
	Return->SetSize({ (float)ReturnSpriteSize * 3,(float)ReturnSpriteSize });
}

void GamePlayScene::StageDraw(DirectXApp *common, DebugText *debugText)
{
	Resources *resources = Resources::GetInstance();
	///*スプライト描画*/
///*スプライト描画前処理*/
	Sprite::PreDraw(common->GetCmdList().Get());

	//// 背景スプライト描画
	backGround->Draw();
	///*スプライト描画後処理*/
	Sprite::PostDraw();
	////深度バッファクリア
	common->ClearDepthBuffer();
#pragma region 描画処理
	/*モデル描画*/
	/*モデル描画前処理*/
	ModelObj::PreDraw(common->GetCmdList().Get());
	
	//背景用の見栄え用オブジェクトの描画
	for (int i = 0; i < backObjNum; i++)
	{
		backObj1[i]->Draw();
		backObj2[i]->Draw();
		backObj3[i]->Draw();
	}

	//雲の描画
	for (int i = 0; i < 10; i++)
	{
		cloud[i]->Draw();
	}
	//マップの描画
	for (int y = 0; y < Y_MAX; y++)
	{
		for (int x = 0; x < X_MAX; x++)
		{
			if (enemy[y][x]->GetPosition().x >= 0)
			{
				enemy[y][x]->Draw();
			}
			if (thornStick[y][x]->GetPosition().x >= 0)
			{
				thornStick[y][x]->Draw();
			}
			if (objStageBox[y][x]->GetPosition().x >= 0)
			{
				objStageBox[y][x]->Draw();
			}
			//あたり判定なしのワイヤーブロックを表示
			if (objRedBlock[y][x]->GetPosition().x >= 0 && objPlayer->GetJumpChangeBlockFlag() == true)
			{
				objRedBlock[y][x]->SetModel(resources->GetModel(ResourcesName::modelWireBlock));
				objRedBlock[y][x]->Draw();
			}
			//あたり判定ありのレッドブロックを表示
			if (objRedBlock[y][x]->GetPosition().x >= 0 && objPlayer->GetJumpChangeBlockFlag() == false)
			{
				objRedBlock[y][x]->SetModel(resources->GetModel(ResourcesName::modelRedBlock));
				objRedBlock[y][x]->Draw();
			}
			//あたり判定なしのワイヤーブロックを表示
			if (objBlueBlock[y][x]->GetPosition().x >= 0 && objPlayer->GetJumpChangeBlockFlag() == false)
			{
				objBlueBlock[y][x]->SetModel(resources->GetModel(ResourcesName::modelWireBlock));
				objBlueBlock[y][x]->Draw();
			}
			//あたり判定ありのブルーブロックを表示
			if (objBlueBlock[y][x]->GetPosition().x >= 0 && objPlayer->GetJumpChangeBlockFlag() == true)
			{
				objBlueBlock[y][x]->SetModel(resources->GetModel(ResourcesName::modelBlueBlock));
				objBlueBlock[y][x]->Draw();
			}
		}
	}
	//ファイアーバーの描画
	for (auto &fireBar : fire)
	{
		fireBar->Draw();
	}
	//ゴールの描画
	objGoal->Draw();
	//看板の描画
	if (objJumpSignA->GetPosition().x >= 0)
	{
		objJumpSignA->Draw();
	}
	if (objWallSignA->GetPosition().x >= 0)
	{
		objWallSignA->Draw();
	}
	//プレイヤーの描画
	objPlayer->Draw();
	// パーティクルの描画
	playerParticle->Draw();

	/*モデル描画後処理*/
	ModelObj::PostDraw();

	particleMan->Draw(common->GetCmdList().Get());

	//深度バッファクリア
	common->ClearDepthBuffer();

	/*スプライト描画*/
/*スプライト描画前処理*/
	Sprite::PreDraw(common->GetCmdList().Get());
	// デバッグテキストの描画
	debugText->DrawAll(common->GetCmdList().Get());

	//カウントダウン描画
	if (stopFlag == false)
	{
		countDown->Draw();
	}
	//プレイヤーアイコン表示
	playerIconSprite->Draw();

	//一時停止したら
	if (stopFlag == true)
	{
		goTitle->Draw();
		reStart->Draw();
		Return->Draw();
	}
	if (operationButton == false)
	{
		escUI->Draw();
	}
	if (operationButton == true)
	{
		homeUI->Draw();
	}

	//ゲームオーバーの遷移
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
	/*スプライト描画後処理*/
	Sprite::PostDraw();
}
