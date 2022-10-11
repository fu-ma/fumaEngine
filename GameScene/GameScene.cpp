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
	// カメラ注視点をセット
	camera->SetTarget({ objPlayer->GetPosition().x + 10, 10, 0 });
	camera->SetDistance(20.0f);
	gameTimer = 180 * 61;
}

void GameScene::TitleUpdate()
{
#pragma region 更新処理
	//雲の移動
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
	//ブロックのスクロール
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

	//シーン遷移
	if (input->isKeyTrigger(DIK_SPACE) || controller->TriggerButton(static_cast<int>(Button::A)) == true)
	{
		SceneTime = 0;
		audio->StopLoadedSound(soundData2);
		SceneNo = static_cast<int>(GameSceneNo::StageSelect);
	}

	lightGroup->Update();
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
	// パーティクルの描画
	//particleMan->Draw(common->GetCmdList().Get());

	//深度バッファクリア
	common->ClearDepthBuffer();

	/*スプライト描画*/
	/*スプライト描画前処理*/
	Sprite::PreDraw(common->GetCmdList().Get());
	// デバッグテキストの描画
	//debugText->DrawAll(common->GetCmdList().Get());
	titleSprite->Draw();

	/*スプライト描画後処理*/
	Sprite::PostDraw();
}

void GameScene::StageSelectInit()
{
	audio->PlayLoadedSound(soundData2, 0.05f);
	objPlayer->Initialize();
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
				titleStageBox[y][x]->SetPosition({ 2.0f * x , -2.0f * y + 10.0f, 0 });
				stageBoxPos[y][x] = titleStageBox[y][x]->GetPosition();
			}
		}
	}
	// カメラ注視点をセット
	camera->SetTarget({ objPlayer->GetPosition().x + 10, 10, 0 });
	camera->SetDistance(20.0f);
	gameTimer = 180 * 61;
}

void GameScene::StageSelectUpdate()
{
#pragma region 更新処理
	
	//指定の位置にいるステージ番号の画像を大きくする
	if (selectPos == selectInterval * 0)
	{
		Stage1Sprite->SetSize({ 512,512 });
		Stage2Sprite->SetSize({ 128,128 });
		Stage3Sprite->SetSize({ 128,128 });
		Stage4Sprite->SetSize({ 128,128 });
		Stage5Sprite->SetSize({ 128,128 });
	}
	if (selectPos == selectInterval * 1)
	{
		Stage1Sprite->SetSize({ 128,128 });
		Stage2Sprite->SetSize({ 512,512 });
		Stage3Sprite->SetSize({ 128,128 });
		Stage4Sprite->SetSize({ 128,128 });
		Stage5Sprite->SetSize({ 128,128 });
	}
	if (selectPos == selectInterval * 2)
	{
		Stage1Sprite->SetSize({ 128,128 });
		Stage2Sprite->SetSize({ 128,128 });
		Stage3Sprite->SetSize({ 512,512 });
		Stage4Sprite->SetSize({ 128,128 });
		Stage5Sprite->SetSize({ 128,128 });
	}
	if (selectPos == selectInterval * 3)
	{
		Stage1Sprite->SetSize({ 128,128 });
		Stage2Sprite->SetSize({ 128,128 });
		Stage3Sprite->SetSize({ 128,128 });
		Stage4Sprite->SetSize({ 512,512 });
		Stage5Sprite->SetSize({ 128,128 });
	}
	if (selectPos == selectInterval * 4)
	{
		Stage1Sprite->SetSize({ 128,128 });
		Stage2Sprite->SetSize({ 128,128 });
		Stage3Sprite->SetSize({ 128,128 });
		Stage4Sprite->SetSize({ 128,128 });
		Stage5Sprite->SetSize({ 512,512 });
	}

	//ステージセレクト
	if ((input->isKeyTrigger(DIK_A) || controller->TriggerButton(static_cast<int>(Button::LEFT)) == true)
		&& selectPos > selectInterval * 0)
	{
		selectPos -= selectInterval;
	}
	if ((input->isKeyTrigger(DIK_D) || controller->TriggerButton(static_cast<int>(Button::RIGHT)) == true)
		&& selectPos < selectInterval * 4)
	{
		selectPos += selectInterval;
	}

	//シーン遷移
	//if (input->isKeyTrigger(DIK_SPACE) || controller->TriggerButton(static_cast<int>(Button::A)) == true)
	//{
	//	SceneTime = 0;
	//	audio->StopLoadedSound(soundData2);
	//	SceneNo = static_cast<int>(GameSceneNo::Stage1);
	//}

	lightGroup->Update();
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

	//ステージ番号をずらす
	Stage1Sprite->SetPosition({ WinApp::window_width / 2.0f + selectInterval * 0 - selectPos, WinApp::window_height / 2.0f });
	Stage2Sprite->SetPosition({ WinApp::window_width / 2.0f + selectInterval * 1 - selectPos, WinApp::window_height / 2.0f });
	Stage3Sprite->SetPosition({ WinApp::window_width / 2.0f + selectInterval * 2 - selectPos, WinApp::window_height / 2.0f });
	Stage4Sprite->SetPosition({ WinApp::window_width / 2.0f + selectInterval * 3 - selectPos, WinApp::window_height / 2.0f });
	Stage5Sprite->SetPosition({ WinApp::window_width / 2.0f + selectInterval * 4 - selectPos, WinApp::window_height / 2.0f });
}

void GameScene::StageSelectDraw()
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
	// パーティクルの描画
	//particleMan->Draw(common->GetCmdList().Get());

	//深度バッファクリア
	common->ClearDepthBuffer();

	/*スプライト描画*/
	/*スプライト描画前処理*/
	Sprite::PreDraw(common->GetCmdList().Get());
	// デバッグテキストの描画
	//debugText->DrawAll(common->GetCmdList().Get());
	Stage1Sprite->Draw();
	Stage2Sprite->Draw();
	Stage3Sprite->Draw();
	Stage4Sprite->Draw();
	Stage5Sprite->Draw();
	/*スプライト描画後処理*/
	Sprite::PostDraw();
}

void GameScene::Stage1Init()
{
	//音声再生
	audio->PlayLoadedSound(soundData1, 0.05f);
	objPlayer->Initialize();
	gimmickCenterNum = 0;

	for (int y = 0; y < Y_MAX; y++)
	{
		for (int x = 0; x < X_MAX; x++)
		{
			objStageBox[y][x]->SetPosition({ -100, 0, 0 });
			enemy[y][x]->Initialize();
			enemy[y][x]->SetPosition({ -100, 0, 0 });
			enemy[y][x]->SetRotation({ 0,180,0 });
			gimmickCenter[gimmickCenterNum] = { -100, -100, 0 };

			if (map1[y][x] == 1)
			{
				objStageBox[y][x]->SetPosition({ 2.0f * x, -2.0f * y + Y_MAX * 2.0f, 0 });
			}
			if (map1[y][x] == 2)
			{
				enemy[y][x]->SetPosition({ 2.0f * x, -2.0f * y + Y_MAX * 2.0f + 0.5f, 0 });
			}
			if (map1[y][x] == 3)
			{
				gimmickCenter[gimmickCenterNum] = { 2.0f * x, -2.0f * y + Y_MAX * 2.0f, 0 };
				gimmickCenterNum++;
			}
			if (map1[y][x] == 10)
			{
				objGoal->SetPosition({ 2.0f * x, -2.0f * y + Y_MAX * 2.0f - 0.5f, 0 });
				objGoal->SetScale({ 1.0f,3.0f,1.0f });
				objGoal->SetRotation({ 0, 90,0 });
			}
		}
	}

	for (int i = 0; i < GIMMICK_NUM; i++)
	{
		firebar[i]->SetPosition({ -100,-100,0 });
		firebar[i]->SetScale({ 0.5f,0.5f,0.5f });
	}
}

void GameScene::Stage1Update()
{
	//objPlayer->moveSphere(objStageBox);
	//camera->SetTarget(objPlayer->GetPosition());
	// カメラ注視点をセット
	camera->SetTarget({ objPlayer->GetPosition().x + 10, 12, 0});
	camera->SetDistance(20.0f);
	//シーン遷移
	if ((playerParticle->GetFlag() == false && objPlayer->GetHP() == 0) || objPlayer->GetPosition().y < -Y_MAX * 2.0f-10 || gameTimer < 0)
	{
		SceneTime = 0;
		audio->StopLoadedSound(soundData1);
		SceneNo = static_cast<int>(GameSceneNo::GameOver);
	}

	gameTimer--;
	debugText->SetPos(1200, 50);
	debugText->SetSize(3);
	debugText->Printf("%d", gameTimer/180);

	//雲の移動
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

	//動くようになる
	if (gameTimer < 180 * 60)
	{
		for (int i = 0; i < GIMMICK_NUM; i++)
		{
			if (firebar[i]->GetPosition().x >= 0.0f)
			{
				firebar[i]->SetMoveFlag(true);
			}
		}
		if (playerParticle->GetFlag() == false)
		{
			objPlayer->notOnCollision();
		}
		if (objPlayer->GetHP() > 0)
		{
			objPlayer->Move();
		}
	}

	//あたり判定
	for (int y = 0; y < Y_MAX; y++)
	{
		for (int x = 0; x < X_MAX; x++)
		{
			objPlayer->CollisionObj(objStageBox[y][x]);
			objPlayer->CollisionEnemy(enemy[y][x]);
		}
	}

	//あたり判定
	for (int i = 0; i < GIMMICK_NUM; i++)
	{
		if (firebar[i]->GetLength() == 0.0f)
		{
			objPlayer->CollisionObj(firebar[i]);
		}
		if (firebar[i]->GetLength() > 0.0f)
		{
			objPlayer->CollisionGimmick(firebar[i]);
		}
	}

	if (objPlayer->CollisionGoal(objGoal) == true)
	{
		SceneTime = 0;
		audio->StopLoadedSound(soundData1);
		SceneNo = static_cast<int>(GameSceneNo::Clear);
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
		}
	}

	for (int i = 0; i < GIMMICK_NUM; i++)
	{
		const int FIRE1_MAX = 5;
		const int FIRE2_MAX = 8;
		if (i < FIRE1_MAX)
		{
			firebar[i]->Move(gimmickCenter[0].x, gimmickCenter[0].y, (2.0f * (i - 0)));
			if (firebar[i]->GetLength() == 0.0f)
			{
				firebar[i]->SetScale({ 0.75f,0.75f,0.75f });
				firebar[i]->SetModel(modelGimmickCenter);
			}
			firebar[i]->Update();
		}
		else if (i < FIRE1_MAX + FIRE2_MAX)
		{
			firebar[i]->Move(gimmickCenter[1].x, gimmickCenter[0].y, (2.0f * (i - FIRE1_MAX)),true);
			if (firebar[i]->GetLength() == 0.0f)
			{
				firebar[i]->SetScale({ 0.75f,0.75f,0.75f });
				firebar[i]->SetModel(modelGimmickCenter);
			}
			firebar[i]->Update();
		}
	}

	objGoal->Update();
	playerParticle->Update(0, { objPlayer->GetPosition().x,objPlayer->GetPosition().y , 0 });
}

void GameScene::Stage1Draw()
{
#pragma region 描画処理

	///*スプライト描画*/
	///*スプライト描画前処理*/
	Sprite::PreDraw(common->GetCmdList().Get());

	//// 背景スプライト描画
	backGround->Draw();
	///*スプライト描画後処理*/
	Sprite::PostDraw();
	////深度バッファクリア
	common->ClearDepthBuffer();

	/*モデル描画*/
	/*モデル描画前処理*/
	ModelObj::PreDraw(common->GetCmdList().Get());

	//objSkydome->Draw();
	//objGround->Draw();
	//FBX
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
		}
	}

	for (int i = 0; i < GIMMICK_NUM; i++)
	{
		if (firebar[i]->GetPosition().x >= 0)
		{
			firebar[i]->Draw();
		}
	}

	objGoal->Draw();
	playerParticle->Draw();
	objPlayer->Draw();
	//objSphere->Draw();
	// パーティクルの描画

	/*モデル描画後処理*/
	ModelObj::PostDraw();

	//深度バッファクリア
	common->ClearDepthBuffer();

	/*スプライト描画*/
	/*スプライト描画前処理*/
	Sprite::PreDraw(common->GetCmdList().Get());
	// デバッグテキストの描画
	debugText->DrawAll(common->GetCmdList().Get());
	/*スプライト描画後処理*/
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
	//シーン遷移
	if (input->isKeyTrigger(DIK_SPACE) || controller->TriggerButton(static_cast<int>(Button::A)) == true)
	{
		audio->PlayLoadedSound(soundData3, 0.05f);
		SceneTime = 0;
		SceneNo = static_cast<int>(GameSceneNo::Title);
	}
}

void GameScene::GameOverDraw()
{
	/*スプライト描画*/
	/*スプライト描画前処理*/
	Sprite::PreDraw(common->GetCmdList().Get());
	GameOver->Draw();
	/*スプライト描画後処理*/
	Sprite::PostDraw();
	//深度バッファクリア
	common->ClearDepthBuffer();

}

void GameScene::ClearInit()
{
}

void GameScene::ClearUpdate()
{
	//シーン遷移
	if (input->isKeyTrigger(DIK_SPACE) || controller->TriggerButton(static_cast<int>(Button::A)) == true)
	{
		audio->PlayLoadedSound(soundData3, 0.05f);
		SceneTime = 0;
		SceneNo = static_cast<int>(GameSceneNo::Title);
	}
}

void GameScene::ClearDraw()
{
	/*スプライト描画*/
	/*スプライト描画前処理*/
	Sprite::PreDraw(common->GetCmdList().Get());
	StageClear->Draw();
	/*スプライト描画後処理*/
	Sprite::PostDraw();
	//深度バッファクリア
	common->ClearDepthBuffer();

}

void GameScene::EndInit()
{
	objPlayer->Initialize();
}

void GameScene::EndUpdate()
{
	//シーン遷移
	if (input->isKeyTrigger(DIK_SPACE) || controller->TriggerButton(static_cast<int>(Button::A)) == true)
	{
		audio->PlayLoadedSound(soundData3, 0.05f);
		SceneTime = 0;
		SceneNo = static_cast<int>(GameSceneNo::Title);
	}

	lightGroup->Update();
	camera->Update();

}

void GameScene::EndDraw()
{
	/*スプライト描画*/
	/*スプライト描画前処理*/
	Sprite::PreDraw(common->GetCmdList().Get());

	/*スプライト描画後処理*/
	Sprite::PostDraw();
	//深度バッファクリア
	common->ClearDepthBuffer();
}

void GameScene::staticInit()
{
	//基底クラスの初期化
	Framework::staticInit();

	//ライト生成
	lightGroup.reset(LightGroup::Create());
	//3Dオブジェクトにライトをセット
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

	//音声読み込み
	soundData1 = audio->SoundLoadWave("Resources/GAMEBGM.wav",true);
	soundData2 = audio->SoundLoadWave("Resources/TITLEBGM.wav",true);
	soundData3 = audio->SoundLoadWave("Resources/SPACESE.wav", false);

	// テクスチャ読み込み
	Sprite::LoadTexture(1, L"Resources/backGround3.png");
	Sprite::LoadTexture(2, L"Resources/titleSprite.png");
	Sprite::LoadTexture(3, L"Resources/StageClear.png");
	Sprite::LoadTexture(4, L"Resources/GameOver.png");
	Sprite::LoadTexture(5, L"Resources/e1.png");
	Sprite::LoadTexture(6, L"Resources/Stage1.png");
	Sprite::LoadTexture(7, L"Resources/Stage2.png");
	Sprite::LoadTexture(8, L"Resources/Stage3.png");
	Sprite::LoadTexture(9, L"Resources/Stage4.png");
	Sprite::LoadTexture(10, L"Resources/Stage5.png");

	// 背景スプライト生成
	backGround = Sprite::Create(1, { WinApp::window_width/2.0f,WinApp::window_height/2.0f });
	titleSprite= Sprite::Create(2, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	StageClear = Sprite::Create(3, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	GameOver = Sprite::Create(4, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	Stage1Sprite = Sprite::Create(6, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	Stage2Sprite = Sprite::Create(7, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	Stage3Sprite = Sprite::Create(8, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	Stage4Sprite = Sprite::Create(9, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	Stage5Sprite = Sprite::Create(10, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });

	// モデル読み込み
	modelPlayer = Model::CreateFromOBJ("player", true);
	modelEnemy = Model::CreateFromOBJ("enemy", true);
	modelStageBox = Model::CreateFromOBJ("StageBox", true);
	modelCloud = Model::CreateFromOBJ("cloud", true);
	modelGoal = Model::CreateFromOBJ("goal", true);
	modelGimmick = Model::CreateFromOBJ("gimmick", true);
	modelGimmickCenter = Model::CreateFromOBJ("gimmickCenter", true);
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
		}
	}

	for (int i = 0; i < GIMMICK_NUM; i++)
	{
		firebar[i] = Firebar::Create(modelGimmick);
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

	// 3Dオブジェクトにカメラをセット
	ModelObj::SetCamera(camera.get());

	//ライトグループをセット
	FBXObject3d::SetLightGroup(lightGroup.get());

}

void GameScene::Init()
{
	//基底クラスの初期化
	Framework::Init();

	switch (SceneNo)
	{
	case static_cast<int>(GameScene::GameSceneNo::Title):
		TitleInit();
		break;
	case static_cast<int>(GameScene::GameSceneNo::StageSelect):
		StageSelectInit();
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
	//基底クラスの更新
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
	case static_cast<int>(GameScene::GameSceneNo::StageSelect):
		SceneTime = 1;
		StageSelectUpdate();
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
	case static_cast<int>(GameScene::GameSceneNo::StageSelect):
		StageSelectDraw();
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