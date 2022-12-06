#include"SelectScene.h"
#include "TitleScene.h"
#include "GamePlayScene.h"
#include "EndScene.h"
#include"ClearScene.h"
#include"EndScene.h"
#include"GameOverScene.h"
#include"StaticInitScene.h"
#include"GamePlayScene.h"

void SelectScene::Initialize(GameSceneManager *pEngine, DebugCamera *camera, Audio *audio, Fps *fps)
{
	audio->PlayLoadedSound(soundData2, 0.05f);
	objPlayer->Initialize();
	objPlayer->SetRotation({ 0,0,0 });
	for (int i = 0; i < 10; i++)
	{
		cloud[i]->SetPosition({ (float)(8 * i) - 15.0f + (float)GetRand(-5,2),20 + (float)GetRand(-2,4),(float)GetRand(10,5) });
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

	if (selectNum == 0)
	{
		stage1SpriteSize = stageSpriteMaxSize;
		stage2SpriteSize = stageSpriteMinSize;
		stage3SpriteSize = stageSpriteMinSize;
		stage4SpriteSize = stageSpriteMinSize;
		stage5SpriteSize = stageSpriteMinSize;
	}
	if (selectNum == 1)
	{
		stage1SpriteSize = stageSpriteMinSize;
		stage2SpriteSize = stageSpriteMaxSize;
		stage3SpriteSize = stageSpriteMinSize;
		stage4SpriteSize = stageSpriteMinSize;
		stage5SpriteSize = stageSpriteMinSize;
	}
	if (selectNum == 2)
	{
		stage1SpriteSize = stageSpriteMinSize;
		stage2SpriteSize = stageSpriteMinSize;
		stage3SpriteSize = stageSpriteMaxSize;
		stage4SpriteSize = stageSpriteMinSize;
		stage5SpriteSize = stageSpriteMinSize;
	}
	if (selectNum == 3)
	{
		stage1SpriteSize = stageSpriteMinSize;
		stage2SpriteSize = stageSpriteMinSize;
		stage3SpriteSize = stageSpriteMinSize;
		stage4SpriteSize = stageSpriteMaxSize;
		stage5SpriteSize = stageSpriteMinSize;
	}
	if (selectNum == 4)
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
}

void SelectScene::Update(GameSceneManager *pEngine, Audio *audio, DebugText *debugText, LightGroup *lightGroup, DebugCamera *camera, Fps *fps)
{
	Input *input = Input::GetInstance();
	Controller *controller = Controller::GetInstance();
#pragma region 更新処理
	// カメラ注視点をセット
	camera->SetTarget({ objPlayer->GetPosition().x, 10, 0 });
	camera->SetDistance(20.0f);

	//プレイヤーの総数を表示
	debugText->SetPos(150, 64);
	debugText->SetSize(5);
	debugText->Printf("%d", totalPlayerNum);

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
				cloudPos[i] = { cloud[9]->GetPosition().x + 8.0f + (float)GetRand(-5,2),20 + (float)GetRand(-2,4),(float)GetRand(10,5) };
			}
			else
			{
				cloudPos[i] = { cloud[i - 1]->GetPosition().x + 8.0f + (float)GetRand(-5,2),20 + (float)GetRand(-2,4),(float)GetRand(10,5) };
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
		audio->StopLoadedSound(soundData2);
		pEngine->changeState(new TitleScene(), camera, audio, fps);
	}
	//ステージセレクト
	if ((input->isKeyTrigger(DIK_A) || controller->TriggerButton(static_cast<int>(Button::LEFT)) == true)
		&& selectNum > 0 && selectMoveTime >= 0.2f)
	{
		selectMoveTime = 0;
		selectNum -= 1;
	}
	else if ((input->isKeyTrigger(DIK_D) || controller->TriggerButton(static_cast<int>(Button::RIGHT)) == true)
		&& selectNum < 4 && selectMoveTime >= 0.2f)
	{
		selectMoveTime = 0;
		selectNum += 1;
	}
	else
	{
		selectMoveTime += 0.008f;
	}
	easing::Updete(selectPos, selectInterval * selectNum, InSine, selectMoveTime);

	//指定の位置にいるステージ番号の画像を大きくする
	if (selectNum == 0)
	{
		easing::Updete(stage1SpriteSize, stageSpriteMaxSize, InSine, selectMoveTime);
		easing::Updete(stage2SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
		easing::Updete(stage3SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
		easing::Updete(stage4SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
		easing::Updete(stage5SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
	}
	if (selectNum == 1)
	{
		easing::Updete(stage1SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
		easing::Updete(stage2SpriteSize, stageSpriteMaxSize, InSine, selectMoveTime);
		easing::Updete(stage3SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
		easing::Updete(stage4SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
		easing::Updete(stage5SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
	}
	if (selectNum == 2)
	{
		easing::Updete(stage1SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
		easing::Updete(stage2SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
		easing::Updete(stage3SpriteSize, stageSpriteMaxSize, InSine, selectMoveTime);
		easing::Updete(stage4SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
		easing::Updete(stage5SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
	}
	if (selectNum == 3)
	{
		easing::Updete(stage1SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
		easing::Updete(stage2SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
		easing::Updete(stage3SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
		easing::Updete(stage4SpriteSize, stageSpriteMaxSize, InSine, selectMoveTime);
		easing::Updete(stage5SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
	}
	if (selectNum == 4)
	{
		easing::Updete(stage1SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
		easing::Updete(stage2SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
		easing::Updete(stage3SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
		easing::Updete(stage4SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
		easing::Updete(stage5SpriteSize, stageSpriteMaxSize, InSine, selectMoveTime);
	}

	Stage1Sprite->SetSize({ (float)stage1SpriteSize,(float)stage1SpriteSize });
	Stage2Sprite->SetSize({ (float)stage2SpriteSize,(float)stage2SpriteSize });
	Stage3Sprite->SetSize({ (float)stage3SpriteSize,(float)stage3SpriteSize });
	Stage4Sprite->SetSize({ (float)stage4SpriteSize,(float)stage4SpriteSize });
	Stage5Sprite->SetSize({ (float)stage5SpriteSize,(float)stage5SpriteSize });

	//指定の位置でSpaceを押すとそのステージにとぶ
	if (objPlayer->GetJumpTimer() > 30)
	{
		if (selectNum == 0 && selectMoveTime >= 0.2f)
		{
			audio->StopLoadedSound(soundData2);
			pEngine->changeState(new GamePlayScene(1), camera, audio, fps);
		}
		if (selectNum == 1 && selectMoveTime >= 0.2f)
		{
			audio->StopLoadedSound(soundData2);
			pEngine->changeState(new GamePlayScene(2), camera, audio, fps);
		}
		if (selectNum == 2 && selectMoveTime >= 0.2f)
		{
			audio->StopLoadedSound(soundData2);
			pEngine->changeState(new GamePlayScene(3), camera, audio, fps);
		}
		if (selectNum == 3 && selectMoveTime >= 0.2f)
		{
			audio->StopLoadedSound(soundData2);
			pEngine->changeState(new GamePlayScene(4), camera, audio, fps);
		}
		if (selectNum == 4 && selectMoveTime >= 0.2f)
		{
			audio->StopLoadedSound(soundData2);
			pEngine->changeState(new GamePlayScene(5), camera, audio, fps);
		}
	}
	if (stageSelectJumpFlag)
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
	/*スプライト描画後処理*/
	Sprite::PostDraw();
}
