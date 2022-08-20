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
	objPlayer->SetPosition({ 1,1,0 });
	for (int i = 0; i < 10; i++)
	{
		cloud[i]->SetPosition({(float)(8*i)-15.0f + (float)GetRand(-5,2),15 + (float)GetRand(-2,4),(float)GetRand(-2,0) });
		cloudPos[i] = cloud[i]->GetPosition();
	}
	objPlayer->SetPosition({ 10,2,0 });

	for (int y = 0; y < Y_MAX; y++)
	{
		for (int x = 0; x < X_MAX; x++)
		{
			if (selectMap[y][x] == 1)
			{
				objStageBox[y][x]->SetPosition({ 2.0f * x , -2.0f * y + 10.0f, 0 });
				stageBoxPos[y][x] = objStageBox[y][x]->GetPosition();
			}
		}
	}
	// カメラ注視点をセット
	camera->SetTarget({ objPlayer->GetPosition().x + 10, 10, 0 });
	camera->SetDistance(20.0f);
}

void GameScene::TitleUpdate()
{
#pragma region 更新処理
	//雲の移動
	{
		for (int i = 0; i < 10; i++)
		{
			cloudPos[i].x -= 0.01f;
			if (cloud[i]->GetPosition().x < objPlayer->GetPosition().x - 15.0f)
			{
				if (i == 0)
				{
					cloudPos[i] = { cloud[9]->GetPosition().x + 8.0f + (float)GetRand(-5,2),15 + (float)GetRand(-2,4),(float)GetRand(-2,0) };
				}
				else
				{
					cloudPos[i] = { cloud[i - 1]->GetPosition().x + 8.0f + (float)GetRand(-5,2),15 + (float)GetRand(-2,4),(float)GetRand(-2,0) };
				}
			}
			cloud[i]->SetPosition(cloudPos[i]);
		}
	}
	//ブロックのスクロール
	for (int y = 0; y < Y_MAX; y++)
	{
		for (int x = 0; x < X_MAX; x++)
		{
			stageBoxPos[y][x].x -= 0.01f;
			if (selectMap[y][x] == 1 && objStageBox[y][x]->GetPosition().x < objPlayer->GetPosition().x - 15)
			{
				if (x == 0)
				{
					stageBoxPos[y][x] = { objStageBox[y][X_MAX - 1]->GetPosition().x + 2.0f, -2.0f * y + 10.0f, 0 };
				}
				else
				{
					stageBoxPos[y][x] = { objStageBox[y][x - 1]->GetPosition().x + 2.0f, -2.0f * y + 10.0f, 0 };
				}

			}
			objStageBox[y][x]->SetPosition(stageBoxPos[y][x]);
		}
	}

	//シーン遷移
	if (input->isKeyTrigger(DIK_N))
	{
		SceneTime = 0;
		audio->StopLoadedSound(soundData2);
		SceneNo = static_cast<int>(GameSceneNo::GamePlay);
	}

	lightGroup->Update();
	particleMan->Update();
	camera->Update();
	objPlayer->Update();
	for (int y = 0; y < Y_MAX; y++)
	{
		for (int x = 0; x < X_MAX; x++)
		{
			objStageBox[y][x]->Update();
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
	for (int y = 0; y < Y_MAX; y++)
	{
		for (int x = 0; x < X_MAX; x++)
		{
			objStageBox[y][x]->Draw();
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

void GameScene::GamePlayInit()
{
	//音声再生
	audio->PlayLoadedSound(soundData1, 0.05f);
	objPlayer->Initialize();
	for (int y = 0; y < Y_MAX; y++)
	{
		for (int x = 0; x < X_MAX; x++)
		{
			enemy[y][x]->Initialize();
			enemy[y][x]->SetPosition({ -100.0f, -100.0f, 0 });
		}
	}
	objPlayer->SetPosition({ 10,2,0 });
	
	for (int y = 0; y < Y_MAX; y++)
	{
		for (int x = 0; x < X_MAX; x++)
		{
			if (map1[y][x] == 1)
			{
				objStageBox[y][x]->SetPosition({ 2.0f * x, -2.0f * y + 10.0f, 0 });
			}
			if (map1[y][x] == 2)
			{
				enemy[y][x]->SetPosition({ 2.0f * x, -2.0f * y + 10.0f, 0 });
			}
		}
	}
	gameTimer = 10980;
}

void GameScene::GamePlayUpdate()
{
	//objPlayer->moveSphere(objStageBox);
	//camera->SetTarget(objPlayer->GetPosition());
	// カメラ注視点をセット
	camera->SetTarget({ objPlayer->GetPosition().x + 10, 10, 0});
	camera->SetDistance(20.0f);
	//シーン遷移
	if (objPlayer->GetHP() == 0 || objPlayer->GetPosition().y < -10 || gameTimer < 0)
	{
		SceneTime = 0;
		audio->StopLoadedSound(soundData1);
		SceneNo = static_cast<int>(GameSceneNo::End);
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
			if (cloud[i]->GetPosition().x < objPlayer->GetPosition().x - 20.0f)
			{
				if (i == 0)
				{
					cloudPos[i] = { cloud[9]->GetPosition().x + 8.0f + (float)GetRand(-5,2),15 + (float)GetRand(-2,4),(float)GetRand(-2,0) };
				}
				else
				{
					cloudPos[i] = { cloud[i - 1]->GetPosition().x + 8.0f + (float)GetRand(-5,2),15 + (float)GetRand(-2,4),(float)GetRand(-2,0) };
				}
			}
			cloud[i]->SetPosition(cloudPos[i]);
		}
	}

	if (gameTimer < 7200)
	{
		objPlayer->Move();
	}

	for (int y = 0; y < Y_MAX; y++)
	{
		for (int x = 0; x < X_MAX; x++)
		{
			objPlayer->CollisionObj(objStageBox[y][x]);
			objPlayer->CollisionEnemy(enemy[y][x]);
		}
	}

	lightGroup->Update();
	particleMan->Update();
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
			enemy[y][x]->Update();
			objStageBox[y][x]->Update();
		}
	}
}

void GameScene::GamePlayDraw()
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
	objPlayer->Draw();
	for (int y = 0; y < Y_MAX; y++)
	{
		for (int x = 0; x < X_MAX; x++)
		{
			enemy[y][x]->Draw();
			objStageBox[y][x]->Draw();
		}
	}
	//objSphere->Draw();
	// パーティクルの描画
	particleMan->Draw(common->GetCmdList().Get());

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

void GameScene::EndInit()
{
}

void GameScene::EndUpdate()
{
	//シーン遷移
	if (input->isKeyTrigger(DIK_N))
	{
		audio->PlayLoadedSound(soundData3, 0.05f);
		SceneTime = 0;
		SceneNo = static_cast<int>(GameSceneNo::Title);
	}

	lightGroup->Update();
	particleMan->Update();
	camera->Update();
	objPlayer->Update();

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
	// 背景スプライト生成
	backGround = Sprite::Create(1, { WinApp::window_width/2.0f,WinApp::window_height/2.0f });
	titleSprite= Sprite::Create(2, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	// モデル読み込み
	modelPlayer = Model::CreateFromOBJ("player", true);
	modelEnemy = Model::CreateFromOBJ("player", true);
	modelStageBox = Model::CreateFromOBJ("StageBox", true);
	modelCloud = Model::CreateFromOBJ("cloud", true);
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

	// 3Dオブジェクトにカメラをセット
	ModelObj::SetCamera(camera.get());

	//ライトグループをセット
	FBXObject3d::SetLightGroup(lightGroup.get());

	// パーティクルマネージャ生成
	// パーティクルマネージャ初期化
	particleMan->SetCamera(camera.get());
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
	case static_cast<int>(GameScene::GameSceneNo::GamePlay):
		GamePlayInit();
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
	case static_cast<int>(GameScene::GameSceneNo::GamePlay):
		SceneTime = 1;
		GamePlayUpdate();
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
	case static_cast<int>(GameScene::GameSceneNo::GamePlay):
		GamePlayDraw();
		break;
	case static_cast<int>(GameScene::GameSceneNo::End):
		EndDraw();
		break;
	default:
		break;
	}
}
