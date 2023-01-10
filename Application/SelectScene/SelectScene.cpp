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

	// 背景スプライト生成
	backGround = Sprite::Create(1, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	Stage1Sprite = Sprite::Create(6, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	Stage2Sprite = Sprite::Create(7, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	Stage3Sprite = Sprite::Create(8, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	Stage4Sprite = Sprite::Create(9, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	Stage5Sprite = Sprite::Create(10, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	playerIconSprite = Sprite::Create(12, { 64,64 });
	fadeIN = Sprite::Create(18, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });

	// 3Dオブジェクト生成
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
	// カメラ注視点をセット
	camera->SetTarget({ objPlayer->GetPosition().x + 10, 10, 0 });
	camera->SetDistance(20.0f);
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
	moveStageBlockSpeed = -0.02f;
	stageSelectJumpFlag = false;

	selectNumber = wholeScene->GetSelectNum();

	sizeX = 1280/2;
	sizeY = 720/2;
	t = 0;
	easingFlag = false;
}

void SelectScene::Update(GameSceneManager *pEngine, Audio *audio, DebugText *debugText, LightGroup *lightGroup, DebugCamera *camera, Fps *fps)
{
	Input *input = Input::GetInstance();
	Controller *controller = Controller::GetInstance();
	Resources *resources = Resources::GetInstance();
	WholeScene *wholeScene = WholeScene::GetInstance();

#pragma region 更新処理
	// カメラ注視点をセット
	camera->SetTarget({ objPlayer->GetPosition().x, 10, 0 });
	camera->SetDistance(20.0f);

	//プレイヤーの総数を表示
	debugText->SetPos(150, 64);
	debugText->SetSize(5);
	debugText->Printf("%d", wholeScene->GetTotalPlayerNum());

	//タイトルから来たときにジャンプを防ぐ
	if (input->isKeyTrigger(DIK_SPACE) || controller->TriggerButton(static_cast<int>(Button::A)) == true)
	{
		stageSelectJumpFlag = true;
	}

	for (int i = 0; i < 10; i++)
	{
		cloudPos[i].x -= 0.01f;
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

	//ブロックのスクロール
	for (int y = 0; y < 6; y++)
	{
		for (int x = 0; x < 24; x++)
		{
			stageBoxPos[y][x].x += moveStageBlockSpeed;
			if ((input->isKey(DIK_A) || controller->PushButton(static_cast<int>(Button::LEFT)) == true) &&
				input->isKey(DIK_D) == false && controller->PushButton(static_cast<int>(Button::RIGHT)) == false)
			{
				moveStageBlockSpeed = 0.02f;
				objPlayer->SetRotation({ 0,180,0 });
			}
			if ((input->isKey(DIK_D) || controller->PushButton(static_cast<int>(Button::RIGHT)) == true) &&
				input->isKey(DIK_A) == false && controller->PushButton(static_cast<int>(Button::LEFT)) == false)
			{
				moveStageBlockSpeed = -0.02f;
				objPlayer->SetRotation({ 0,0,0 });
			}
			if (selectMap[y][x] == 1 && titleStageBox[y][x]->GetPosition().x > objPlayer->GetPosition().x + 25 && moveStageBlockSpeed == 0.02f)
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

			if (selectMap[y][x] == 1 && titleStageBox[y][x]->GetPosition().x < objPlayer->GetPosition().x - 25 && moveStageBlockSpeed == -0.02f)
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
		audio->StopLoadedSound(resources->GetSoundData(ResourcesName::soundData2));
		pEngine->changeState(new TitleScene());
		return;
	}
	//ステージセレクト
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
		selectMoveTime += 0.008f;
	}
	easing::Updete(selectPos, selectInterval * wholeScene->GetSelectNum(), InSine, selectMoveTime);

	//ステージを判断する数字をセット
	wholeScene->SetSelectNum(selectNumber);

	//指定の位置にいるステージ番号の画像を大きくする
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

	if (stageSelectJumpFlag && easingFlag == false)
	{
		objPlayer->Jump();
	}

	lightGroup->Update();
	camera->Update();
	objPlayer->Update();
	for (int y = 0; y < 6; y++)
	{
		for (int x = 0; x < 24; x++)
		{
			titleStageBox[y][x]->Update();
			objPlayer->CollisionObj(titleStageBox[y][x]);
		}
	}

	for (int i = 0; i < 10; i++)
	{
		cloud[i]->Update();
	}

	//ステージ番号をずらす
	Stage1Sprite->SetPosition({ WinApp::window_width / 2.0f + selectInterval * 0 - (float)selectPos, WinApp::window_height / 2.0f });
	Stage2Sprite->SetPosition({ WinApp::window_width / 2.0f + selectInterval * 1 - (float)selectPos, WinApp::window_height / 2.0f });
	Stage3Sprite->SetPosition({ WinApp::window_width / 2.0f + selectInterval * 2 - (float)selectPos, WinApp::window_height / 2.0f });
	Stage4Sprite->SetPosition({ WinApp::window_width / 2.0f + selectInterval * 3 - (float)selectPos, WinApp::window_height / 2.0f });
	Stage5Sprite->SetPosition({ WinApp::window_width / 2.0f + selectInterval * 4 - (float)selectPos, WinApp::window_height / 2.0f });

	//指定の位置でSpaceを押すとそのステージにとぶ
	if (objPlayer->GetJumpTimer() > 5)
	{
		easingFlag = true;
	}

	if (easingFlag == true)
	{
		t += 0.001f;
		easing::Updete(sizeX, 1280 * 17, 3, t);
		easing::Updete(sizeY, 720 * 17, 3, t);
		if (sizeX > 1280 * 15)
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

		fadeIN->SetSize({ (float)sizeX,(float)sizeY });
	}
}

void SelectScene::Draw(GameSceneManager *pEngine, DirectXApp *common, DebugText *debugText)
{
#pragma region 描画処理

	/*スプライト描画*/
	/*スプライト描画前処理*/
	Sprite::PreDraw(common->GetCmdList().Get());

	// 背景スプライト描画
	backGround->Draw();
	/*スプライト描画後処理*/
	Sprite::PostDraw();
	//深度バッファクリア
	common->ClearDepthBuffer();

	/*モデル描画*/
	/*モデル描画前処理*/
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

	/*モデル描画後処理*/
	ModelObj::PostDraw();

	//深度バッファクリア
	common->ClearDepthBuffer();

	/*スプライト描画*/
	/*スプライト描画前処理*/
	Sprite::PreDraw(common->GetCmdList().Get());
	// デバッグテキストの描画
	debugText->DrawAll(common->GetCmdList().Get());
	//プレイヤーアイコン表示
	playerIconSprite->Draw();

	Stage1Sprite->Draw();
	Stage2Sprite->Draw();
	Stage3Sprite->Draw();
	Stage4Sprite->Draw();
	Stage5Sprite->Draw();

	if (easingFlag == true)
	{
		fadeIN->Draw();
	}
	/*スプライト描画後処理*/
	Sprite::PostDraw();
}
