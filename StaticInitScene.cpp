#include "StaticInitScene.h"
#include "TitleScene.h"
#include "GamePlayScene.h"
#include "EndScene.h"
#include"ClearScene.h"
#include"EndScene.h"
#include"SelectScene.h"
#include"GameOverScene.h"
#include"GamePlayScene.h"

void StaticInitScene::Initialize(GameSceneManager *pEngine, DebugCamera *camera, Audio *audio, Fps *fps)
{
	//音声読み込み
	soundData1 = audio->SoundLoadWave("Resources/sound/GAMEBGM.wav", true);
	soundData2 = audio->SoundLoadWave("Resources/sound/TITLEBGM.wav", true);
	soundData3 = audio->SoundLoadWave("Resources/sound/SPACESE.wav", false);

	// テクスチャ読み込み
	Sprite::LoadTexture(1, L"Resources/img/backGround3.png");
	Sprite::LoadTexture(2, L"Resources/img/titleSprite.png");
	Sprite::LoadTexture(3, L"Resources/img/StageClear.png");
	Sprite::LoadTexture(4, L"Resources/img/skull.png");
	Sprite::LoadTexture(5, L"Resources/img/e1.png");
	Sprite::LoadTexture(6, L"Resources/img/Stage1.png");
	Sprite::LoadTexture(7, L"Resources/img/Stage2.png");
	Sprite::LoadTexture(8, L"Resources/img/Stage3.png");
	Sprite::LoadTexture(9, L"Resources/img/Stage4.png");
	Sprite::LoadTexture(10, L"Resources/img/Stage5.png");
	Sprite::LoadTexture(11, L"Resources/img/CountStart.png");
	Sprite::LoadTexture(12, L"Resources/img/playerIcon.png");
	Sprite::LoadTexture(13, L"Resources/img/GameOver.png");
	Sprite::LoadTexture(14, L"Resources/img/title.png");
	Sprite::LoadTexture(15, L"Resources/img/restart.png");
	Sprite::LoadTexture(16, L"Resources/img/Return.png");
	Sprite::LoadTexture(17, L"Resources/img/ClearStage.png");

	// 背景スプライト生成
	backGround = Sprite::Create(1, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	titleSprite = Sprite::Create(2, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	StageClear = Sprite::Create(3, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	GameOver = Sprite::Create(4, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	Stage1Sprite = Sprite::Create(6, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	Stage2Sprite = Sprite::Create(7, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	Stage3Sprite = Sprite::Create(8, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	Stage4Sprite = Sprite::Create(9, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	Stage5Sprite = Sprite::Create(10, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	playerIconSprite = Sprite::Create(12, { 64,64 });
	EndSprite = Sprite::Create(13, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	goTitle = Sprite::Create(14, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f - WinApp::window_height / 6.0f });
	reStart = Sprite::Create(15, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	Return = Sprite::Create(16, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f + WinApp::window_height / 6.0f });
	ClearStageSprite = Sprite::Create(17, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });

	//カウントダウンクラス初期化
	countDown = new CountDown();

	// モデル読み込み
	modelPlayer = Model::CreateFromOBJ("player", true);
	modelEnemy = Model::CreateFromOBJ("enemy", true);
	modelStageBox = Model::CreateFromOBJ("StageBox", true);
	modelCloud = Model::CreateFromOBJ("cloud", true);
	modelGoal = Model::CreateFromOBJ("goal", true);
	modelRedBlock = Model::CreateFromOBJ("redBlock", true);
	modelBlueBlock = Model::CreateFromOBJ("blueBlock", true);
	modelWireBlock = Model::CreateFromOBJ("wireBlock", true);

	// 3Dオブジェクト生成
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
			objRedBlock[y][x] = ModelObj::Create(modelRedBlock);
			objBlueBlock[y][x] = ModelObj::Create(modelBlueBlock);
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

	playerParticle = new Particle();
	playerParticle->Initialize(modelEnemy);

	//残機を設定
	totalPlayerNum = 5;
}

void StaticInitScene::Update(GameSceneManager *pEngine, Audio *audio, DebugText *debugText, LightGroup *lightGroup, DebugCamera *camera, Fps *fps)
{
	pEngine->changeState(new TitleScene(),camera,audio,fps);
}

void StaticInitScene::Draw(GameSceneManager *pEngine, DirectXApp *common, DebugText *debugText)
{
}
