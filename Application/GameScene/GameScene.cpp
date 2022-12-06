#include "GameScene.h"
#include <cassert>
#include <sstream>
#include <iomanip>
#include"FbxLoader.h"

#pragma warning(disable : 4996)

using namespace DirectX;

//void GameScene::TitleInit()
//{
//	audio->PlayLoadedSound(soundData2, 0.05f);
//	objPlayer->Initialize();
//	for (int i = 0; i < 10; i++)
//	{
//		cloud[i]->SetPosition({(float)(8*i)-15.0f + (float)GetRand(-5,2),20 + (float)GetRand(-2,4),(float)GetRand(10,5) });
//		cloudPos[i] = cloud[i]->GetPosition();
//	}
//
//	for (int y = 0; y < 6; y++)
//	{
//		for (int x = 0; x < 24; x++)
//		{
//			if (selectMap[y][x] == 1)
//			{
//				titleStageBox[y][x]->SetPosition({ 2.0f * x , -2.0f * y + 10.0f, 0 });
//				stageBoxPos[y][x] = titleStageBox[y][x]->GetPosition();
//			}
//		}
//	}
//	// カメラ注視点をセット
//	camera->SetTarget({ objPlayer->GetPosition().x + 10, 10, 0 });
//	camera->SetDistance(20.0f);
//}
//
//void GameScene::TitleUpdate()
//{
//#pragma region 更新処理
//	//雲の移動
//	{
//		for (int i = 0; i < 10; i++)
//		{
//			cloudPos[i].x -= 0.01f;
//			if (cloud[i]->GetPosition().x < objPlayer->GetPosition().x - 25.0f)
//			{
//				if (i == 0)
//				{
//					cloudPos[i] = { cloud[9]->GetPosition().x + 8.0f + (float)GetRand(-5,2),20 + (float)GetRand(-2,4),(float)GetRand(10,5) };
//				}
//				else
//				{
//					cloudPos[i] = { cloud[i - 1]->GetPosition().x + 8.0f + (float)GetRand(-5,2),20 + (float)GetRand(-2,4),(float)GetRand(10,5) };
//				}
//			}
//			cloud[i]->SetPosition(cloudPos[i]);
//		}
//	}
//	//ブロックのスクロール
//	for (int y = 0; y < 6; y++)
//	{
//		for (int x = 0; x < 24; x++)
//		{
//			stageBoxPos[y][x].x -= 0.01f;
//			if (selectMap[y][x] == 1 && titleStageBox[y][x]->GetPosition().x < objPlayer->GetPosition().x - 15)
//			{
//				if (x == 0)
//				{
//					stageBoxPos[y][x] = { titleStageBox[y][24 - 1]->GetPosition().x + 2.0f, -2.0f * y + 10.0f, 0 };
//				}
//				else
//				{
//					stageBoxPos[y][x] = { titleStageBox[y][x - 1]->GetPosition().x + 2.0f, -2.0f * y + 10.0f, 0 };
//				}
//
//			}
//			titleStageBox[y][x]->SetPosition(stageBoxPos[y][x]);
//		}
//	}
//
//	//シーン遷移
//	if (input->isKeyTrigger(DIK_SPACE) || controller->TriggerButton(static_cast<int>(Button::A)) == true)
//	{
//		SceneTime = 0;
//		audio->StopLoadedSound(soundData2);
//		SceneNo = static_cast<int>(GameSceneNo::StageSelect);
//	}
//
//	lightGroup->Update();
//	camera->Update();
//	objPlayer->Update();
//	for (int y = 0; y < 6; y++)
//	{
//		for (int x = 0; x < 24; x++)
//		{
//			titleStageBox[y][x]->Update();
//		}
//	}
//
//	for (int i = 0; i < 10; i++)
//	{
//		cloud[i]->Update();
//	}
//}
//
//void GameScene::TitleDraw()
//{
//#pragma region 描画処理
//
//	/*スプライト描画*/
//	/*スプライト描画前処理*/
//	Sprite::PreDraw(common->GetCmdList().Get());
//
//	// 背景スプライト描画
//	backGround->Draw();
//	/*スプライト描画後処理*/
//	Sprite::PostDraw();
//	//深度バッファクリア
//	common->ClearDepthBuffer();
//
//	/*モデル描画*/
//	/*モデル描画前処理*/
//	ModelObj::PreDraw(common->GetCmdList().Get());
//
//	for (int i = 0; i < 10; i++)
//	{
//		cloud[i]->Draw();
//	}
//	objPlayer->Draw();
//	for (int y = 0; y < 6; y++)
//	{
//		for (int x = 0; x < 24; x++)
//		{
//			titleStageBox[y][x]->Draw();
//		}
//	}
//
//	/*モデル描画後処理*/
//	ModelObj::PostDraw();
//	// パーティクルの描画
//	//particleMan->Draw(common->GetCmdList().Get());
//
//	//深度バッファクリア
//	common->ClearDepthBuffer();
//
//	/*スプライト描画*/
//	/*スプライト描画前処理*/
//	Sprite::PreDraw(common->GetCmdList().Get());
//	// デバッグテキストの描画
//	//debugText->DrawAll(common->GetCmdList().Get());
//	titleSprite->Draw();
//
//	/*スプライト描画後処理*/
//	Sprite::PostDraw();
//}
//
//void GameScene::StageSelectInit()
//{
//	audio->PlayLoadedSound(soundData2, 0.05f);
//	objPlayer->Initialize();
//	objPlayer->SetRotation({0,0,0});
//	for (int i = 0; i < 10; i++)
//	{
//		cloud[i]->SetPosition({ (float)(8 * i) - 15.0f + (float)GetRand(-5,2),20 + (float)GetRand(-2,4),(float)GetRand(10,5) });
//		cloudPos[i] = cloud[i]->GetPosition();
//	}
//
//	for (int y = 0; y < 6; y++)
//	{
//		for (int x = 0; x < 24; x++)
//		{
//			if (selectMap[y][x] == 1)
//			{
//				titleStageBox[y][x]->SetPosition({ 2.0f * x - 10.0f, -2.0f * y + 10.0f, 0 });
//				stageBoxPos[y][x] = titleStageBox[y][x]->GetPosition();
//			}
//		}
//	}
//	// カメラ注視点をセット
//	camera->SetTarget({ objPlayer->GetPosition().x + 10, 10, 0 });
//	camera->SetDistance(20.0f);
//	gameTimer = 180 * 61;
//
//	if (selectNum == 0)
//	{
//		stage1SpriteSize = stageSpriteMaxSize;
//		stage2SpriteSize = stageSpriteMinSize;
//		stage3SpriteSize = stageSpriteMinSize;
//		stage4SpriteSize = stageSpriteMinSize;
//		stage5SpriteSize = stageSpriteMinSize;
//	}
//	if (selectNum == 1)
//	{
//		stage1SpriteSize = stageSpriteMinSize;
//		stage2SpriteSize = stageSpriteMaxSize;
//		stage3SpriteSize = stageSpriteMinSize;
//		stage4SpriteSize = stageSpriteMinSize;
//		stage5SpriteSize = stageSpriteMinSize;
//	}
//	if (selectNum == 2)
//	{
//		stage1SpriteSize = stageSpriteMinSize;
//		stage2SpriteSize = stageSpriteMinSize;
//		stage3SpriteSize = stageSpriteMaxSize;
//		stage4SpriteSize = stageSpriteMinSize;
//		stage5SpriteSize = stageSpriteMinSize;
//	}
//	if (selectNum == 3)
//	{
//		stage1SpriteSize = stageSpriteMinSize;
//		stage2SpriteSize = stageSpriteMinSize;
//		stage3SpriteSize = stageSpriteMinSize;
//		stage4SpriteSize = stageSpriteMaxSize;
//		stage5SpriteSize = stageSpriteMinSize;
//	}
//	if (selectNum == 4)
//	{
//		stage1SpriteSize = stageSpriteMinSize;
//		stage2SpriteSize = stageSpriteMinSize;
//		stage3SpriteSize = stageSpriteMinSize;
//		stage4SpriteSize = stageSpriteMinSize;
//		stage5SpriteSize = stageSpriteMaxSize;
//	}
//	selectMoveTime = 0.2f;
//	moveStageBlockSpeed = -0.02f;
//	stageSelectJumpFlag = false;
//}
//
//void GameScene::StageSelectUpdate()
//{
//#pragma region 更新処理
//	// カメラ注視点をセット
//	camera->SetTarget({ objPlayer->GetPosition().x, 10, 0 });
//	camera->SetDistance(20.0f);
//
//	//プレイヤーの総数を表示
//	debugText->SetPos(150, 64);
//	debugText->SetSize(5);
//	debugText->Printf("%d", totalPlayerNum);
//
//	//タイトルから来たときにジャンプを防ぐ
//	if (input->isKeyTrigger(DIK_SPACE) || controller->TriggerButton(static_cast<int>(Button::A)) == true)
//	{
//		stageSelectJumpFlag = true;
//	}
//
//	for (int i = 0; i < 10; i++)
//	{
//		cloudPos[i].x -= 0.01f;
//		if (cloud[i]->GetPosition().x < objPlayer->GetPosition().x - 40.0f)
//		{
//			if (i == 0)
//			{
//				cloudPos[i] = { cloud[9]->GetPosition().x + 8.0f + (float)GetRand(-5,2),20 + (float)GetRand(-2,4),(float)GetRand(10,5) };
//			}
//			else
//			{
//				cloudPos[i] = { cloud[i - 1]->GetPosition().x + 8.0f + (float)GetRand(-5,2),20 + (float)GetRand(-2,4),(float)GetRand(10,5) };
//			}
//		}
//		cloud[i]->SetPosition(cloudPos[i]);
//	}
//
//	//ブロックのスクロール
//	for (int y = 0; y < 6; y++)
//	{
//		for (int x = 0; x < 24; x++)
//		{
//			stageBoxPos[y][x].x += moveStageBlockSpeed;
//			if ((input->isKey(DIK_A) || controller->PushButton(static_cast<int>(Button::LEFT)) == true) &&
//				input->isKey(DIK_D) == false && controller->PushButton(static_cast<int>(Button::RIGHT)) == false)
//			{
//				moveStageBlockSpeed = 0.02f;
//				objPlayer->SetRotation({ 0,180,0 });
//			}
//			if ((input->isKey(DIK_D) || controller->PushButton(static_cast<int>(Button::RIGHT)) == true) &&
//				input->isKey(DIK_A) == false && controller->PushButton(static_cast<int>(Button::LEFT)) == false)
//			{
//				moveStageBlockSpeed = -0.02f;
//				objPlayer->SetRotation({ 0,0,0 });
//			}
//			if (selectMap[y][x] == 1 && titleStageBox[y][x]->GetPosition().x > objPlayer->GetPosition().x + 25 && moveStageBlockSpeed == 0.02f)
//			{
//				if (x == 23)
//				{
//					stageBoxPos[y][x] = { titleStageBox[y][0]->GetPosition().x - 2.0f, -2.0f * y + 10.0f, 0 };
//				}
//				else
//				{
//					stageBoxPos[y][x] = { titleStageBox[y][x + 1]->GetPosition().x - 2.0f, -2.0f * y + 10.0f, 0 };
//				}
//
//			}
//
//			if (selectMap[y][x] == 1 && titleStageBox[y][x]->GetPosition().x < objPlayer->GetPosition().x - 25 && moveStageBlockSpeed == -0.02f)
//			{
//				if (x == 0)
//				{
//					stageBoxPos[y][x] = { titleStageBox[y][24 - 1]->GetPosition().x + 2.0f, -2.0f * y + 10.0f, 0 };
//				}
//				else
//				{
//					stageBoxPos[y][x] = { titleStageBox[y][x - 1]->GetPosition().x + 2.0f, -2.0f * y + 10.0f, 0 };
//				}
//
//			}
//			titleStageBox[y][x]->SetPosition(stageBoxPos[y][x]);
//		}
//	}
//
//	if (input->isKeyTrigger(DIK_ESCAPE) || controller->TriggerButton(static_cast<int>(Button::START)) == true)
//	{
//		SceneTime = 0;
//		audio->StopLoadedSound(soundData2);
//		SceneNo = static_cast<int>(GameSceneNo::Title);
//	}
//	//ステージセレクト
//	if ((input->isKeyTrigger(DIK_A) || controller->TriggerButton(static_cast<int>(Button::LEFT)) == true)
//		&& selectNum > 0 && selectMoveTime >= 0.2f)
//	{
//		selectMoveTime = 0;
//		selectNum -= 1;
//	}
//	else if ((input->isKeyTrigger(DIK_D) || controller->TriggerButton(static_cast<int>(Button::RIGHT)) == true)
//		&& selectNum < 4 && selectMoveTime >= 0.2f)
//	{
//		selectMoveTime = 0;
//		selectNum += 1;
//	}
//	else
//	{
//		selectMoveTime += 0.008f;
//	}
//	easing::Updete(selectPos, selectInterval*selectNum,InSine, selectMoveTime);
//
//	//指定の位置にいるステージ番号の画像を大きくする
//	if (selectNum == 0)
//	{
//		easing::Updete(stage1SpriteSize, stageSpriteMaxSize, InSine, selectMoveTime);
//		easing::Updete(stage2SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
//		easing::Updete(stage3SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
//		easing::Updete(stage4SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
//		easing::Updete(stage5SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
//	}
//	if (selectNum == 1)
//	{
//		easing::Updete(stage1SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
//		easing::Updete(stage2SpriteSize, stageSpriteMaxSize, InSine, selectMoveTime);
//		easing::Updete(stage3SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
//		easing::Updete(stage4SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
//		easing::Updete(stage5SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
//	}
//	if (selectNum == 2)
//	{
//		easing::Updete(stage1SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
//		easing::Updete(stage2SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
//		easing::Updete(stage3SpriteSize, stageSpriteMaxSize, InSine, selectMoveTime);
//		easing::Updete(stage4SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
//		easing::Updete(stage5SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
//	}
//	if (selectNum == 3)
//	{
//		easing::Updete(stage1SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
//		easing::Updete(stage2SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
//		easing::Updete(stage3SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
//		easing::Updete(stage4SpriteSize, stageSpriteMaxSize, InSine, selectMoveTime);
//		easing::Updete(stage5SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
//	}
//	if (selectNum == 4)
//	{
//		easing::Updete(stage1SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
//		easing::Updete(stage2SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
//		easing::Updete(stage3SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
//		easing::Updete(stage4SpriteSize, stageSpriteMinSize, InSine, selectMoveTime);
//		easing::Updete(stage5SpriteSize, stageSpriteMaxSize, InSine, selectMoveTime);
//	}
//
//	Stage1Sprite->SetSize({ (float)stage1SpriteSize,(float)stage1SpriteSize });
//	Stage2Sprite->SetSize({ (float)stage2SpriteSize,(float)stage2SpriteSize });
//	Stage3Sprite->SetSize({ (float)stage3SpriteSize,(float)stage3SpriteSize });
//	Stage4Sprite->SetSize({ (float)stage4SpriteSize,(float)stage4SpriteSize });
//	Stage5Sprite->SetSize({ (float)stage5SpriteSize,(float)stage5SpriteSize });
//
//	//指定の位置でSpaceを押すとそのステージにとぶ
//	if (objPlayer->GetJumpTimer() > 30)
//	{
//		if (selectNum == 0 && selectMoveTime >= 0.2f)
//		{
//			SceneTime = 0;
//			audio->StopLoadedSound(soundData2);
//			SceneNo = static_cast<int>(GameSceneNo::Stage1);
//		}
//		if (selectNum == 1 && selectMoveTime >= 0.2f)
//		{
//			SceneTime = 0;
//			audio->StopLoadedSound(soundData2);
//			SceneNo = static_cast<int>(GameSceneNo::Stage2);
//		}
//		if (selectNum == 2 && selectMoveTime >= 0.2f)
//		{
//			SceneTime = 0;
//			audio->StopLoadedSound(soundData2);
//			SceneNo = static_cast<int>(GameSceneNo::Stage3);
//		}
//		if (selectNum == 3 && selectMoveTime >= 0.2f)
//		{
//			SceneTime = 0;
//			audio->StopLoadedSound(soundData2);
//			SceneNo = static_cast<int>(GameSceneNo::Stage4);
//		}
//		if (selectNum == 4 && selectMoveTime >= 0.2f)
//		{
//			SceneTime = 0;
//			audio->StopLoadedSound(soundData2);
//			SceneNo = static_cast<int>(GameSceneNo::Stage5);
//		}
//	}
//	if (stageSelectJumpFlag)
//	{
//		objPlayer->Jump();
//	}
//
//	lightGroup->Update();
//	camera->Update();
//	objPlayer->Update();
//	for (int y = 0; y < 6; y++)
//	{
//		for (int x = 0; x < 24; x++)
//		{
//			titleStageBox[y][x]->Update();
//			objPlayer->CollisionObj(titleStageBox[y][x]);
//		}
//	}
//
//	for (int i = 0; i < 10; i++)
//	{
//		cloud[i]->Update();
//	}
//
//	//ステージ番号をずらす
//	Stage1Sprite->SetPosition({ WinApp::window_width / 2.0f + selectInterval * 0 - (float)selectPos, WinApp::window_height / 2.0f });
//	Stage2Sprite->SetPosition({ WinApp::window_width / 2.0f + selectInterval * 1 - (float)selectPos, WinApp::window_height / 2.0f });
//	Stage3Sprite->SetPosition({ WinApp::window_width / 2.0f + selectInterval * 2 - (float)selectPos, WinApp::window_height / 2.0f });
//	Stage4Sprite->SetPosition({ WinApp::window_width / 2.0f + selectInterval * 3 - (float)selectPos, WinApp::window_height / 2.0f });
//	Stage5Sprite->SetPosition({ WinApp::window_width / 2.0f + selectInterval * 4 - (float)selectPos, WinApp::window_height / 2.0f });
//}
//
//void GameScene::StageSelectDraw()
//{
//#pragma region 描画処理
//
//	/*スプライト描画*/
//	/*スプライト描画前処理*/
//	Sprite::PreDraw(common->GetCmdList().Get());
//
//	// 背景スプライト描画
//	backGround->Draw();
//	/*スプライト描画後処理*/
//	Sprite::PostDraw();
//	//深度バッファクリア
//	common->ClearDepthBuffer();
//
//	/*モデル描画*/
//	/*モデル描画前処理*/
//	ModelObj::PreDraw(common->GetCmdList().Get());
//
//	for (int i = 0; i < 10; i++)
//	{
//		cloud[i]->Draw();
//	}
//	objPlayer->Draw();
//	for (int y = 0; y < 6; y++)
//	{
//		for (int x = 0; x < 24; x++)
//		{
//			titleStageBox[y][x]->Draw();
//		}
//	}
//
//	/*モデル描画後処理*/
//	ModelObj::PostDraw();
//
//	//深度バッファクリア
//	common->ClearDepthBuffer();
//
//	/*スプライト描画*/
//	/*スプライト描画前処理*/
//	Sprite::PreDraw(common->GetCmdList().Get());
//	// デバッグテキストの描画
//	debugText->DrawAll(common->GetCmdList().Get());
//	//プレイヤーアイコン表示
//	playerIconSprite->Draw();
//
//	Stage1Sprite->Draw();
//	Stage2Sprite->Draw();
//	Stage3Sprite->Draw();
//	Stage4Sprite->Draw();
//	Stage5Sprite->Draw();
//	/*スプライト描画後処理*/
//	Sprite::PostDraw();
//}
//
//void GameScene::GameOverInit()
//{
//	totalPlayerNum = 5;
//}
//
//void GameScene::GameOverUpdate()
//{
//	//シーン遷移
//	if (input->isKeyTrigger(DIK_SPACE) || controller->TriggerButton(static_cast<int>(Button::A)) == true)
//	{
//		audio->PlayLoadedSound(soundData3, 0.05f);
//		SceneTime = 0;
//		SceneNo = static_cast<int>(GameSceneNo::Title);
//	}
//}
//
//void GameScene::GameOverDraw()
//{
//	/*スプライト描画*/
//	/*スプライト描画前処理*/
//	Sprite::PreDraw(common->GetCmdList().Get());
//	EndSprite->Draw();
//	/*スプライト描画後処理*/
//	Sprite::PostDraw();
//	//深度バッファクリア
//	common->ClearDepthBuffer();
//
//}
//
//void GameScene::ClearInit()
//{
//}
//
//void GameScene::ClearUpdate()
//{
//	//シーン遷移
//	if (input->isKeyTrigger(DIK_SPACE) || controller->TriggerButton(static_cast<int>(Button::A)) == true)
//	{
//		audio->PlayLoadedSound(soundData3, 0.05f);
//		SceneTime = 0;
//		SceneNo = static_cast<int>(GameSceneNo::StageSelect);
//	}
//}
//
//void GameScene::ClearDraw()
//{
//	/*スプライト描画*/
//	/*スプライト描画前処理*/
//	Sprite::PreDraw(common->GetCmdList().Get());
//	StageClear->Draw();
//	/*スプライト描画後処理*/
//	Sprite::PostDraw();
//	//深度バッファクリア
//	common->ClearDepthBuffer();
//
//}
//
//void GameScene::EndInit()
//{
//	objPlayer->Initialize();
//}
//
//void GameScene::EndUpdate()
//{
//	//シーン遷移
//	if (input->isKeyTrigger(DIK_SPACE) || controller->TriggerButton(static_cast<int>(Button::A)) == true)
//	{
//		audio->PlayLoadedSound(soundData3, 0.05f);
//		SceneTime = 0;
//		SceneNo = static_cast<int>(GameSceneNo::Title);
//	}
//
//	lightGroup->Update();
//	camera->Update();
//
//}
//
//void GameScene::EndDraw()
//{
//	/*スプライト描画*/
//	/*スプライト描画前処理*/
//	Sprite::PreDraw(common->GetCmdList().Get());
//
//	/*スプライト描画後処理*/
//	Sprite::PostDraw();
//	//深度バッファクリア
//	common->ClearDepthBuffer();
//}
//
//void GameScene::StageSet(const int Map[Y_MAX][X_MAX], const int stageNum)
//{
//	for (int y = 0; y < Y_MAX; y++)
//	{
//		for (int x = 0; x < X_MAX; x++)
//		{
//			map[y][x] = Map[y][x];
//		}
//	}
//	objPlayer->Initialize();
//	gimmickCenterNum = 0;
//	enemyNum = 0;
//
//	for (int y = 0; y < Y_MAX; y++)
//	{
//		for (int x = 0; x < X_MAX; x++)
//		{
//			
//			objStageBox[y][x]->SetPosition({ -100, 0, 0 });
//			enemy[y][x]->Initialize();
//			enemy[y][x]->SetPosition({ -100, 0, 0 });
//			enemy[y][x]->SetRotation({ 0,180,0 });
//			objRedBlock[y][x]->SetPosition({ -100,0,0 });
//			objBlueBlock[y][x]->SetPosition({ -100,0,0 });
//
//			//ブロック
//			if (map[y][x] == 1)
//			{
//				objStageBox[y][x]->SetPosition({ 2.0f * x, -2.0f * y + Y_MAX * 2.0f, 0 });
//			}
//			//敵
//			if (map[y][x] == 2)
//			{
//				enemy[y][x]->SetPosition({ 2.0f * x, -2.0f * y + Y_MAX * 2.0f + 0.5f, 0 });
//			}
//			//赤ブロック
//			if (map[y][x] == 4)
//			{
//				objRedBlock[y][x]->SetPosition({ 2.0f * x, -2.0f * y + Y_MAX * 2.0f, 0 });
//			}
//			//青ブロック
//			if (map[y][x] == 5)
//			{
//				objBlueBlock[y][x]->SetPosition({ 2.0f * x, -2.0f * y + Y_MAX * 2.0f, 0 });
//			}
//			//ゴール
//			if (map[y][x] == 10)
//			{
//				objGoal->SetPosition({ 2.0f * x, -2.0f * y + Y_MAX * 2.0f - 0.5f, 0 });
//				objGoal->SetScale({ 1.0f,3.0f,1.0f });
//				objGoal->SetRotation({ 0, 90,0 });
//			}
//		}
//	}
//
//	for (int x = 0; x < X_MAX; x++)
//	{
//		for (int y = 0; y < Y_MAX; y++)
//		{
//			gimmickCenter[x] = { -100,0,0 };
//			//ファイアーバー
//			if (map[y][x] == 3)
//			{
//				gimmickCenter[gimmickCenterNum] = { 2.0f * x, -2.0f * y + Y_MAX * 2.0f, 0 };
//				gimmickCenterNum++;
//			}
//		}
//	}
//
//	fire.clear();
//	for (int i = 0; i < gimmickCenterNum; i++)
//	{
//		stageData = stageDatas[stageNum - 1][i];
//		firebar = new Firebar(gimmickCenter[i].x, gimmickCenter[i].y, stageData.firebarNum,stageData.direction,stageData.firebarSpeed);
//		firebar->StaticInit();
//		fire.push_back(firebar);
//	}
//
//
//	for (auto &fireBar : fire)
//	{
//		fireBar->Initialize();
//	}
//
//	gameTimer = (int)fps->GetFrame() * 60 * 2;
//
//	//カウントダウン用の画像の初期値の設定
//	countDown->Initialize();
//
//	gameOverFlag = false;
//	skullSizeX = 1280 * 5;
//	skullSizeY = 720 * 5;
//	gameOverTime = 0;
//
//	stopFlag = false;
//	stopNum = 0;
//	stopMoveTime = 0;
//	if (stopNum == 0)
//	{
//		goTitleSpriteSize = stopSpriteMinSize;
//		reStartSpriteSize = stopSpriteMinSize;
//		ReturnSpriteSize = stopSpriteMaxSize;
//	}
//
//	clearStopFlag = false;
//	audio->PlayLoadedSound(soundData1, 0.05f);
//}
//
//void GameScene::StageUpdate()
//{
//	// カメラ注視点をセット
//	camera->SetTarget({ objPlayer->GetPosition().x + 10, 12, 0 });
//	camera->SetDistance(20.0f);
//	//シーン遷移
//	if ((playerParticle->GetFlag() == false && objPlayer->GetHP() == 0) || objPlayer->GetPosition().y < -Y_MAX * 2.0f - 10 || gameTimer < 0)
//	{
//		gameOverFlag = true;
//	}
//
//	//Escかスタートボタン（コントローラー）を押したときに一時停止する
//	if (input->isKeyTrigger(DIK_ESCAPE) || controller->TriggerButton(static_cast<int>(Button::START)) == true)
//	{
//		stopFlag = !stopFlag;
//	}
//
//	if (stopFlag == true)
//	{
//		if (input->isKeyTrigger(DIK_W) || controller->TriggerButton(static_cast<int>(Button::UP)) == true)
//		{
//			if (stopNum < 2 && stopMoveTime >= 0.2f)
//			{
//				stopMoveTime = 0;
//				stopNum++;
//			}
//		}
//		else if (input->isKeyTrigger(DIK_S) || controller->TriggerButton(static_cast<int>(Button::DOWN)) == true)
//		{
//			if (stopNum > 0 && stopMoveTime >= 0.2f)
//			{
//				stopMoveTime = 0;
//				stopNum--;
//			}
//		}
//		else
//		{
//			stopMoveTime += 0.008f;
//		}
//	}
//	if (stopNum == 0)
//	{
//		easing::Updete(goTitleSpriteSize, stopSpriteMinSize, InSine, stopMoveTime);
//		easing::Updete(reStartSpriteSize, stopSpriteMinSize, InSine, stopMoveTime);
//		easing::Updete(ReturnSpriteSize, stopSpriteMaxSize, InSine, stopMoveTime);
//	}
//	if (stopNum == 1)
//	{
//		easing::Updete(goTitleSpriteSize, stopSpriteMinSize, InSine, stopMoveTime);
//		easing::Updete(reStartSpriteSize, stopSpriteMaxSize, InSine, stopMoveTime);
//		easing::Updete(ReturnSpriteSize, stopSpriteMinSize, InSine, stopMoveTime);
//	}
//	if (stopNum == 2)
//	{
//		easing::Updete(goTitleSpriteSize, stopSpriteMaxSize, InSine, stopMoveTime);
//		easing::Updete(reStartSpriteSize, stopSpriteMinSize, InSine, stopMoveTime);
//		easing::Updete(ReturnSpriteSize, stopSpriteMinSize, InSine, stopMoveTime);
//	}
//
//	if (input->isKeyTrigger(DIK_SPACE) || controller->TriggerButton(static_cast<int>(Button::A)) == true)
//	{
//		//モドルボタンを押したとき
//		if (stopNum == 0 && stopMoveTime >= 0.2f)
//		{
//			stopFlag = false;
//		}
//
//		//リスタートボタンを押したとき
//		if (stopNum == 1 && stopMoveTime >= 0.2f)
//		{
//			SceneTime = 0;
//		}
//
//		//セレクトに戻るボタンを押したとき
//		if (stopNum == 2 && stopMoveTime >= 0.2f)
//		{
//			SceneTime = 0;
//			audio->StopLoadedSound(soundData1);
//			SceneNo = static_cast<int>(GameSceneNo::StageSelect);
//		}
//	}
//
//	//デス時の画面遷移
//	if (gameOverFlag == true)
//	{
//		easing::Updete(skullSizeX, 1280, 3, gameOverTime);
//		easing::Updete(skullSizeY, 720, 3, gameOverTime);
//		gameOverTime += 0.001f;
//		if (gameOverTime > 0.2)
//		{
//			SceneTime = 0;
//			audio->StopLoadedSound(soundData1);
//			if (totalPlayerNum == 0)
//			{
//				SceneNo = static_cast<int>(GameSceneNo::GameOver);
//			}
//			else
//			{
//				SceneNo = static_cast<int>(GameSceneNo::StageSelect);
//			}
//			//残機を減らす
//			totalPlayerNum--;
//		}
//		GameOver->SetSize({ (float)skullSizeX, (float)skullSizeY });
//	}
//
//	//3,2,1,スタート
//	if (stopFlag == false)
//	{
//		countDown->Update();
//	}
//
//	//ゴールしたときに時間計測を止める
//	if (objPlayer->GetPlayerStop() == true)
//	{
//		clearStopFlag = true;
//	}
//	//スターと表示がされてからしばらくして
//	if (countDown->GetStart() >= 0.8)
//	{
//		//一時停止していなかったら
//		if (stopFlag == false && clearStopFlag == false)
//		{
//			gameTimer--;
//		}
//	}
//
//	//タイマーを表示
//	debugText->SetPos(1200, 50);
//	debugText->SetSize(3);
//	debugText->Printf("%d", gameTimer / (int)fps->GetFrame() / 2);
//
//	//プレイヤーの総数を表示
//	debugText->SetPos(150, 64);
//	debugText->SetSize(5);
//	debugText->Printf("%d", totalPlayerNum);
//
//	//雲の移動
//	{
//		for (int i = 0; i < 10; i++)
//		{
//			cloudPos[i].x -= 0.01f;
//			if (cloud[i]->GetPosition().x < objPlayer->GetPosition().x - 25.0f)
//			{
//				if (i == 0)
//				{
//					cloudPos[i] = { cloud[9]->GetPosition().x + 8.0f + (float)GetRand(-5,2),20 + (float)GetRand(-2,4),(float)GetRand(10,5) };
//				}
//				else
//				{
//					cloudPos[i] = { cloud[i - 1]->GetPosition().x + 8.0f + (float)GetRand(-5,2),20 + (float)GetRand(-2,4),(float)GetRand(10,5) };
//				}
//			}
//			cloud[i]->SetPosition(cloudPos[i]);
//		}
//	}
//
//	//動くようになる
//	if (countDown->GetStart() >= 0.2 && stopFlag == false)
//	{
//		if (playerParticle->GetFlag() == false)
//		{
//			objPlayer->notOnCollision();
//		}
//		if (objPlayer->GetHP() > 0 && gameOverFlag == false)
//		{
//			objPlayer->Move();
//		}
//
//		for (int y = 0; y < Y_MAX; y++)
//		{
//			for (int x = 0; x < X_MAX; x++)
//			{
//				if (enemy[y][x]->GetPosition().x >= 0)
//				{
//					enemy[y][x]->Move();
//					for (int w = 0; w < Y_MAX; w++)
//					{
//						for (int z = 0; z < X_MAX; z++)
//						{
//							enemy[y][x]->CollisionObject(objStageBox[w][z]);
//						}
//					}
//				}
//			}
//		}
//
//		for (auto &fireBar : fire)
//		{
//			fireBar->Move();
//		}
//	}
//
//	//あたり判定
//	for (int y = 0; y < Y_MAX; y++)
//	{
//		for (int x = 0; x < X_MAX; x++)
//		{
//			objPlayer->CollisionObj(objStageBox[y][x]);
//			objPlayer->CollisionEnemy(enemy[y][x]);
//			if (objPlayer->GetJumpChangeBlockFlag() == false)
//			{
//				objPlayer->CollisionObj(objRedBlock[y][x]);
//			}
//			if (objPlayer->GetJumpChangeBlockFlag() == true)
//			{
//				objPlayer->CollisionObj(objBlueBlock[y][x]);
//			}
//		}
//	}
//
//	for (auto &fireBar : fire)
//	{
//		fireBar->Move();
//		objPlayer->CollisionObj(fireBar->GetCenter());
//		for (int i = 0; i < fireBar->GetNum(); i++)
//		{
//			if (i != 0)
//			{
//				objPlayer->CollisionGimmick(fireBar->GetFire(i));
//			}
//		}
//		fireBar->Update();
//	}
//
//	//ゴールとのあたり判定
//	if (objPlayer->CollisionGoal(objGoal) == true)
//	{
//		SceneTime = 0;
//		audio->StopLoadedSound(soundData1);
//		SceneNo = static_cast<int>(GameSceneNo::Clear);
//		//ステージ番号を次のステージの番号にする
//		if (selectNum < 4)
//		{
//			selectNum += 1;
//		}
//	}
//
//	if (objPlayer->GetOnCollision())
//	{
//		playerParticle->SetFlag(true);
//	}
//
//	lightGroup->Update();
//	camera->Update();
//	for (int i = 0; i < 10; i++)
//	{
//		cloud[i]->Update();
//	}
//
//	objPlayer->Update();
//	for (int y = 0; y < Y_MAX; y++)
//	{
//		for (int x = 0; x < X_MAX; x++)
//		{
//			if (objStageBox[y][x]->GetPosition().x >= 0)
//			{
//				objStageBox[y][x]->Update();
//			}
//			if (enemy[y][x]->GetPosition().x >= 0)
//			{
//				enemy[y][x]->Update();
//			}
//			if (objRedBlock[y][x]->GetPosition().x >= 0)
//			{
//				objRedBlock[y][x]->Update();
//			}
//			if (objBlueBlock[y][x]->GetPosition().x >= 0)
//			{
//				objBlueBlock[y][x]->Update();
//			}
//		}
//	}
//
//	objGoal->Update();
//	playerParticle->Update(0, { objPlayer->GetPosition().x,objPlayer->GetPosition().y , 0 });
//
//	goTitle->SetSize({ (float)goTitleSpriteSize * 3,(float)goTitleSpriteSize });
//	reStart->SetSize({ (float)reStartSpriteSize * 3,(float)reStartSpriteSize });
//	Return->SetSize({ (float)ReturnSpriteSize * 3,(float)ReturnSpriteSize });
//}
//
//void GameScene::StageDraw()
//{
//	///*スプライト描画*/
//	///*スプライト描画前処理*/
//	Sprite::PreDraw(common->GetCmdList().Get());
//
//	//// 背景スプライト描画
//	backGround->Draw();
//	///*スプライト描画後処理*/
//	Sprite::PostDraw();
//	////深度バッファクリア
//	common->ClearDepthBuffer();
//#pragma region 描画処理
//	/*モデル描画*/
//	/*モデル描画前処理*/
//	ModelObj::PreDraw(common->GetCmdList().Get());
//
//	for (int i = 0; i < 10; i++)
//	{
//		cloud[i]->Draw();
//	}
//	for (int y = 0; y < Y_MAX; y++)
//	{
//		for (int x = 0; x < X_MAX; x++)
//		{
//			if (enemy[y][x]->GetPosition().x >= 0)
//			{
//				enemy[y][x]->Draw();
//			}
//			if (objStageBox[y][x]->GetPosition().x >= 0)
//			{
//				objStageBox[y][x]->Draw();
//			}
//			//あたり判定なしのワイヤーブロックを表示
//			if (objRedBlock[y][x]->GetPosition().x >= 0 && objPlayer->GetJumpChangeBlockFlag() == true)
//			{
//				objRedBlock[y][x]->SetModel(modelWireBlock);
//				objRedBlock[y][x]->Draw();
//			}
//			//あたり判定ありのレッドブロックを表示
//			if (objRedBlock[y][x]->GetPosition().x >= 0 && objPlayer->GetJumpChangeBlockFlag() == false)
//			{
//				objRedBlock[y][x]->SetModel(modelRedBlock);
//				objRedBlock[y][x]->Draw();
//			}
//			//あたり判定なしのワイヤーブロックを表示
//			if (objBlueBlock[y][x]->GetPosition().x >= 0 && objPlayer->GetJumpChangeBlockFlag() == false)
//			{
//				objBlueBlock[y][x]->SetModel(modelWireBlock);
//				objBlueBlock[y][x]->Draw();
//			}
//			//あたり判定ありのブルーブロックを表示
//			if (objBlueBlock[y][x]->GetPosition().x >= 0 && objPlayer->GetJumpChangeBlockFlag() == true)
//			{
//				objBlueBlock[y][x]->SetModel(modelBlueBlock);
//				objBlueBlock[y][x]->Draw();
//			}
//		}
//	}
//
//	for (auto &fireBar : fire)
//	{
//		fireBar->Draw();
//	}
//
//	objGoal->Draw();
//	objPlayer->Draw();
//	// パーティクルの描画
//	playerParticle->Draw();
//
//	/*モデル描画後処理*/
//	ModelObj::PostDraw();
//
//	//深度バッファクリア
//	common->ClearDepthBuffer();
//
//	/*スプライト描画*/
///*スプライト描画前処理*/
//	Sprite::PreDraw(common->GetCmdList().Get());
//	// デバッグテキストの描画
//	debugText->DrawAll(common->GetCmdList().Get());
//
//	//カウントダウン描画
//	if (stopFlag == false)
//	{
//		countDown->Draw();
//	}
//	//プレイヤーアイコン表示
//	playerIconSprite->Draw();
//
//	//一時停止したら
//	if (stopFlag == true)
//	{
//		goTitle->Draw();
//		reStart->Draw();
//		Return->Draw();
//	}
//
//	//ゲームオーバーの遷移
//	if (gameOverFlag == true)
//	{
//		GameOver->Draw();
//	}
//	/*スプライト描画後処理*/
//	Sprite::PostDraw();
//}

void GameScene::staticInit()
{
	//基底クラスの初期化
	Framework::staticInit();

	//ライト生成
	lightGroup.reset(LightGroup::Create());
	//3Dオブジェクトにライトをセット
	ModelObj::SetLightGroup(lightGroup.get());
	lightGroup->SetDirLightActive(0, true);
	lightGroup->SetDirLightActive(1, true);
	lightGroup->SetDirLightActive(2, true);

	lightGroup->SetSpotLightActive(0, true);
	lightGroup->SetCircleShadowActive(0, true);

	////音声読み込み
	//soundData1 = audio->SoundLoadWave("Resources/sound/GAMEBGM.wav",true);
	//soundData2 = audio->SoundLoadWave("Resources/sound/TITLEBGM.wav",true);
	//soundData3 = audio->SoundLoadWave("Resources/sound/SPACESE.wav", false);

	//// テクスチャ読み込み
	//Sprite::LoadTexture(1, L"Resources/img/backGround3.png");
	//Sprite::LoadTexture(2, L"Resources/img/titleSprite.png");
	//Sprite::LoadTexture(3, L"Resources/img/StageClear.png");
	//Sprite::LoadTexture(4, L"Resources/img/skull.png");
	//Sprite::LoadTexture(5, L"Resources/img/e1.png");
	//Sprite::LoadTexture(6, L"Resources/img/Stage1.png");
	//Sprite::LoadTexture(7, L"Resources/img/Stage2.png");
	//Sprite::LoadTexture(8, L"Resources/img/Stage3.png");
	//Sprite::LoadTexture(9, L"Resources/img/Stage4.png");
	//Sprite::LoadTexture(10, L"Resources/img/Stage5.png");
	//Sprite::LoadTexture(11, L"Resources/img/CountStart.png");
	//Sprite::LoadTexture(12, L"Resources/img/playerIcon.png");
	//Sprite::LoadTexture(13, L"Resources/img/GameOver.png");
	//Sprite::LoadTexture(14, L"Resources/img/title.png");
	//Sprite::LoadTexture(15, L"Resources/img/restart.png");
	//Sprite::LoadTexture(16, L"Resources/img/Return.png");
	//Sprite::LoadTexture(17, L"Resources/img/ClearStage.png");

	//// 背景スプライト生成
	//backGround = Sprite::Create(1, { WinApp::window_width/2.0f,WinApp::window_height/2.0f });
	//titleSprite= Sprite::Create(2, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	//StageClear = Sprite::Create(3, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	//GameOver = Sprite::Create(4, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	//Stage1Sprite = Sprite::Create(6, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	//Stage2Sprite = Sprite::Create(7, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	//Stage3Sprite = Sprite::Create(8, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	//Stage4Sprite = Sprite::Create(9, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	//Stage5Sprite = Sprite::Create(10, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	//playerIconSprite = Sprite::Create(12, { 64,64 });
	//EndSprite = Sprite::Create(13, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	//goTitle = Sprite::Create(14, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f - WinApp::window_height / 6.0f });
	//reStart = Sprite::Create(15, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	//Return = Sprite::Create(16, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f + WinApp::window_height / 6.0f });
	//ClearStageSprite = Sprite::Create(17, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });

	////カウントダウンクラス初期化
	//countDown = new CountDown();

	//// モデル読み込み
	//modelPlayer = Model::CreateFromOBJ("player", true);
	//modelEnemy = Model::CreateFromOBJ("enemy", true);
	//modelStageBox = Model::CreateFromOBJ("StageBox", true);
	//modelCloud = Model::CreateFromOBJ("cloud", true);
	//modelGoal = Model::CreateFromOBJ("goal", true);
	//modelRedBlock = Model::CreateFromOBJ("redBlock", true);
	//modelBlueBlock = Model::CreateFromOBJ("blueBlock", true);
	//modelWireBlock = Model::CreateFromOBJ("wireBlock", true);

	//// 3Dオブジェクト生成
	//objPlayer = Player::Create(modelPlayer);

	//for (int i = 0; i < 10; i++)
	//{
	//	cloud[i] = ModelObj::Create(modelCloud);
	//}
	//for (int y = 0; y < Y_MAX; y++)
	//{
	//	for (int x = 0; x < X_MAX; x++)
	//	{
	//		objStageBox[y][x] = ModelObj::Create(modelStageBox);
	//		enemy[y][x] = Enemy::Create(modelEnemy);
	//		objRedBlock[y][x] = ModelObj::Create(modelRedBlock);
	//		objBlueBlock[y][x] = ModelObj::Create(modelBlueBlock);
	//	}
	//}

	//for (int y = 0; y < 6; y++)
	//{
	//	for (int x = 0; x < 24; x++)
	//	{
	//		titleStageBox[y][x] = ModelObj::Create(modelStageBox);
	//	}
	//}

	//objGoal = ModelObj::Create(modelGoal);

	//playerParticle = new Particle();
	//playerParticle->Initialize(modelEnemy);

	// 3Dオブジェクトにカメラをセット
	ModelObj::SetCamera(camera.get());

	//ライトグループをセット
	FBXObject3d::SetLightGroup(lightGroup.get());

	manager = new GameSceneManager();
	////残機を設定
	//totalPlayerNum = 5;
}

void GameScene::Init()
{
	//基底クラスの初期化
	Framework::Init();

	manager->Initialize(camera.get(), audio.get(), fps.get());
	//switch (SceneNo)
	//{
	//case static_cast<int>(GameScene::GameSceneNo::Title):
	//	TitleInit();
	//	break;
	//case static_cast<int>(GameScene::GameSceneNo::StageSelect):
	//	StageSelectInit();
	//	break;
	//case static_cast<int>(GameScene::GameSceneNo::Stage1):
	//	//音声再生
	//	StageSet(map1,1);
	//	break;
	//case static_cast<int>(GameScene::GameSceneNo::Stage2):
	//	StageSet(map2,2);
	//	break;
	//case static_cast<int>(GameScene::GameSceneNo::Stage3):
	//	StageSet(map3,3);
	//	break;
	//case static_cast<int>(GameScene::GameSceneNo::Stage4):
	//	StageSet(map4,4);
	//	break;
	//case static_cast<int>(GameScene::GameSceneNo::Stage5):
	//	StageSet(map5,5);
	//	break;
	//case static_cast<int>(GameScene::GameSceneNo::GameOver):
	//	GameOverInit();
	//	break;
	//case static_cast<int>(GameScene::GameSceneNo::Clear):
	//	ClearInit();
	//	break;
	//case static_cast<int>(GameScene::GameSceneNo::End):
	//	EndInit();
	//	break;
	//default:
	//	break;
	//}
}

bool GameScene::Update()
{
	//基底クラスの更新
	if (Framework::Update() == false)
	{
		return false;
	}

	manager->Update(debugText,audio.get(), lightGroup.get(), camera.get(), fps.get());
	//if (SceneNo == static_cast<int>(GameScene::GameSceneNo::Title))
	//{
	//	SceneTime = 1;
	//	TitleUpdate();
	//}
	//else if (SceneNo == static_cast<int>(GameScene::GameSceneNo::StageSelect))
	//{
	//	SceneTime = 1;
	//	StageSelectUpdate();
	//}
	//else if (SceneNo == static_cast<int>(GameScene::GameSceneNo::GameOver))
	//{
	//	SceneTime = 1;
	//	GameOverUpdate();
	//}
	//else if (SceneNo == static_cast<int>(GameScene::GameSceneNo::Clear))
	//{
	//	SceneTime = 1;
	//	ClearUpdate();
	//}
	//else if (SceneNo == static_cast<int>(GameScene::GameSceneNo::End))
	//{
	//	SceneTime = 1;
	//	EndUpdate();
	//}
	//else
	//{
	//	SceneTime = 1;
	//	StageUpdate();
	//}

	return true;
}

void GameScene::Draw()
{
	manager->Draw(common.get(), debugText);
	//if (SceneNo == static_cast<int>(GameScene::GameSceneNo::Title))
	//{
	//	TitleDraw();
	//}
	//else if (SceneNo == static_cast<int>(GameScene::GameSceneNo::StageSelect))
	//{
	//	StageSelectDraw();
	//}
	//else if (SceneNo == static_cast<int>(GameScene::GameSceneNo::GameOver))
	//{
	//	GameOverDraw();
	//}
	//else if (SceneNo == static_cast<int>(GameScene::GameSceneNo::Clear))
	//{
	//	ClearDraw();
	//}
	//else if (SceneNo == static_cast<int>(GameScene::GameSceneNo::End))
	//{
	//	EndDraw();
	//}
	//else
	//{
	//	StageDraw();
	//}
}