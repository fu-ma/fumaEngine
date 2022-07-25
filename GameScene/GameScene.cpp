#include "GameScene.h"
#include <cassert>
#include <sstream>
#include <iomanip>
#include"FbxLoader.h"

using namespace DirectX;

void GameScene::TitleInit()
{
	audio->PlayLoadedSound(soundData2, 0.05f);
	objFighter->SetPosition({ 1,1,0 });
	//objSphere->SetPosition({ -1,1,0 });
	// カメラ注視点をセット
	camera->SetTarget({ 0, 1, 0 });
	camera->SetDistance(3.0f);
}

void GameScene::TitleUpdate()
{
#pragma region 更新処理

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
	//objSkydome->Update();
	//objGround->Update();
	objFighter->Update();
	//objSphere->Update();
	for (int i = 0; i < 20; i++)
	{
		objStageBox[i]->Update();
	}
}

void GameScene::TitleDraw()
{
#pragma region 描画処理

	/*スプライト描画*/
	/*スプライト描画前処理*/
	Sprite::PreDraw(common->GetCmdList().Get());

	// 背景スプライト描画
	spriteBG->Draw();
	/*スプライト描画後処理*/
	Sprite::PostDraw();
	//深度バッファクリア
	common->ClearDepthBuffer();

	/*モデル描画*/
	/*モデル描画前処理*/
	ModelObj::PreDraw(common->GetCmdList().Get());

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
	debugText->DrawAll(common->GetCmdList().Get());

	/*スプライト描画後処理*/
	Sprite::PostDraw();
}

void GameScene::GamePlayInit()
{
	//音声再生
	audio->PlayLoadedSound(soundData1, 0.05f);
	//objFighter->SetPosition({ 1,1,0 });
	objFighter->SetScale({ 0.7f, 0.7f, 0.7f });
	//objSphere->SetScale({ 10, 10, 10 });
	objFighter->SetPosition({ 10,0,0 });
	// カメラ注視点をセット
	camera->SetTarget({ 10, 10, 0 });
	camera->SetDistance(20.0f);
	object1->SetPosition({ 0,5,0 });

	object1->PlayAnimation();
	for (int i = 0; i < 20; i++)
	{
		objStageBox[i]->SetPosition({ 2.0f * i, 0, 0 });
	}
}

void GameScene::GamePlayUpdate()
{
	//マテリアルパラメータをモデルに反映
	model1->SetBaseColor(XMFLOAT3(0,1,1));
	model1->SetMetalness(1.0f);
	model1->SetSpecular(0.5f);
	model1->SetRoughness(0.3f);
	model1->TransferMaterial();

	//objFighter->moveSphere(objStageBox);
	//camera->SetTarget(objFighter->GetPosition());

	//シーン遷移
	if (input->isKeyTrigger(DIK_N))
	{
		SceneTime = 0;
		audio->StopLoadedSound(soundData1);
		SceneNo = static_cast<int>(GameSceneNo::End);
	}

	for (int i = 0; i < 20; i++)
	{

		objFighter->CollisionObj(objStageBox[i]);
	}
	lightGroup->Update();
	particleMan->Update();
	camera->Update();
	//objSkydome->Update();
	//objGround->Update();
	objFighter->Update();
	//objSphere->Update();
	for (int i = 0; i < 20; i++)
	{

		objStageBox[i]->Update();
	}
	//FBX用のオブジェクトの更新
	object1->Update();
}

void GameScene::GamePlayDraw()
{
#pragma region 描画処理

	///*スプライト描画*/
	///*スプライト描画前処理*/
	//Sprite::PreDraw(common->GetCmdList().Get());

	//// 背景スプライト描画
	//spriteBG->Draw();
	///*スプライト描画後処理*/
	//Sprite::PostDraw();
	////深度バッファクリア
	//common->ClearDepthBuffer();

	/*モデル描画*/
	/*モデル描画前処理*/
	ModelObj::PreDraw(common->GetCmdList().Get());

	//objSkydome->Draw();
	//objGround->Draw();
	//FBX
	object1->Draw(common->GetCmdList().Get());
	objFighter->Draw();
	//objSphere->Draw();
	for (int i = 0; i < 20; i++)
	{

		objStageBox[i]->Draw();
	}
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
	//objSkydome->Update();
	//objGround->Update();
	objFighter->Update();
	//objSphere->Update();
	for (int i = 0; i < 20; i++)
	{

		objStageBox[i]->Update();
	}

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
	Sprite::LoadTexture(1, L"Resources/background.png");
	// 背景スプライト生成
	spriteBG = Sprite::Create(1, { 0.0f,0.0f });

	// モデル読み込み
	//modelSkydome = Model::CreateFromOBJ("skydome", true);
	//modelGround = Model::CreateFromOBJ("ground", true);
	modelFighter = Model::CreateFromOBJ("StageBox", true);
	//modelSphere = Model::CreateFromOBJ("sphere");
	modelStageBox = Model::CreateFromOBJ("StageBox", true);
	// 3Dオブジェクト生成
	objFighter = Player::Create(modelFighter);

	//objSkydome = ModelObj::Create(modelSkydome);
	//objGround = TouchableObject::Create(modelGround);
	//objSphere = ModelObj::Create(modelSphere);
	for (int i = 0; i < 20; i++)
	{
		objStageBox[i] = ModelObj::Create(modelStageBox);
	}
	//objFighter->SetParent(objSphere);

	// 3Dオブジェクトにカメラをセット
	ModelObj::SetCamera(camera.get());

	// モデル名を指定してファイル読み込み
	//FbxLoader::GetInstance()->LoadModelFromFile("cube");
	model1 = FbxLoader::GetInstance()->LoadModelFromFile("SpherePBR");
	//ライトグループをセット
	FBXObject3d::SetLightGroup(lightGroup.get());

	//FBX用の3Dオブジェクト生成とモデルのセット
	object1 = new FBXObject3d;
	object1->Initialize();
	object1->SetModel(model1);

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
