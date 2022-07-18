#include "GameScene.h"
#include"Collision.h"
#include"SphereCollider.h"
#include <cassert>
#include <sstream>
#include <iomanip>
#include "SphereCollider.h"
#include "MeshCollider.h"
#include"FbxLoader.h"

void GameScene::TitleInit()
{
	audio->PlayLoadedSound(soundData2, 0.05f);
	objFighter->SetPosition({ 1,1,0 });
	objSphere->SetPosition({ -1,1,0 });
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
	objSkydome->Update();
	//objGround->Update();
	objFighter->Update();
	objSphere->Update();
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

	//objSkydome->Draw();
	//objGround->Draw();
	objFighter->Draw();
	objSphere->Draw();


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
	objFighter->SetScale({ 1, 1, 1 });
	objSphere->SetScale({ 10, 10, 10 });
	objFighter->SetPosition({ 0,0,-objSphere->GetPosition().z - objSphere->GetScale().z });
	// カメラ注視点をセット
	camera->SetTarget({ 0, 0, 0 });
	camera->SetDistance(3.0f);
	object1->SetPosition({ 0,5,0 });

	object1->PlayAnimation();
}

void GameScene::GamePlayUpdate()
{
	//マテリアルパラメータをモデルに反映
	model1->SetBaseColor(XMFLOAT3(0,1,1));
	model1->SetMetalness(0.0f);
	model1->SetSpecular(1.0f);
	model1->SetRoughness(0.0f);
	model1->TransferMaterial();

	// パーティクル生成
	//CreateParticles();
	/*XMFLOAT3 rot=objSphere->GetRotation2();
	if (input->isKey(DIK_A))
	{
		rot.y++;
	}
	else if (input->isKey(DIK_D))
	{
		rot.y--;
	}
	if (input->isKey(DIK_W))
	{
		rot.x++;
	}
	if (input->isKey(DIK_S))
	{
		rot.x--;
	}
	objSphere->SetRotation2(rot);*/

	objFighter->moveSphere(objSphere);
	camera->SetTarget(objFighter->GetPosition());

	{
		/*lightGroup->SetPointLightPos(0, XMFLOAT3(pointLightPos));
		lightGroup->SetPointLightColor(0, XMFLOAT3(pointLightColor));
		lightGroup->SetPointLightAtten(0, XMFLOAT3(pointLightAtten));*/
		lightGroup->SetSpotLightDir(0, XMVECTOR({ spotLightDir[0],spotLightDir[1] , spotLightDir[2], 0 }));
		lightGroup->SetSpotLightPos(0, XMFLOAT3(spotLightPos));
		lightGroup->SetSpotLightColor(0, XMFLOAT3(spotLightColor));
		lightGroup->SetSpotLightAtten(0, XMFLOAT3(spotLightAtten));
		lightGroup->SetSpotLightFactorAngle(0, XMFLOAT2(spotLightFactorAngle));
		/*lightGroup->SetCircleShadowDir(0, XMVECTOR({ circleShadowDir[0],circleShadowDir[1],circleShadowDir[2],0 }));
		lightGroup->SetCircleShadowCasterPos(0, XMFLOAT3({ fighterPos[0],fighterPos[1],fighterPos[2] }));
		lightGroup->SetCircleShadowAtten(0, XMFLOAT3(circleShadowAtten));
		lightGroup->SetCircleShadowFactorAngle(0, XMFLOAT2(circleShadowFactorAngle));*/

		//objFighter->SetPosition(XMFLOAT3({ fighterPos[0],fighterPos[1] ,fighterPos[2] }));
	}

	//シーン遷移
	if (input->isKeyTrigger(DIK_N))
	{
		SceneTime = 0;
		audio->StopLoadedSound(soundData1);
		SceneNo = static_cast<int>(GameSceneNo::End);
	}

	lightGroup->Update();
	particleMan->Update();
	camera->Update();
	objSkydome->Update();
	//objGround->Update();
	objFighter->Update();
	objSphere->Update();
	//FBX用のオブジェクトの更新
	object1->Update();

	//全ての衝突をチェック
	collisionManager->CheckAllCollisions();
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

	objSkydome->Draw();
	//objGround->Draw();
	//FBX
	object1->Draw(common->GetCmdList().Get());
	objFighter->Draw();
	objSphere->Draw();

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
	objSkydome->Update();
	//objGround->Update();
	objFighter->Update();
	objSphere->Update();

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
	modelSkydome = Model::CreateFromOBJ("skydome", true);
	modelGround = Model::CreateFromOBJ("ground", true);
	modelFighter = Model::CreateFromOBJ("sphere", true);
	modelSphere = Model::CreateFromOBJ("sphere");

	// 3Dオブジェクト生成
	collisionManager = CollisionManager::GetInstance();
	objFighter = Player::Create(modelFighter);

	objSkydome = ModelObj::Create(modelSkydome);
	//objGround = TouchableObject::Create(modelGround);
	objSphere = ModelObj::Create(modelSphere);

	objFighter->SetParent(objSphere);
	//コライダーの追加
	objSphere->SetCollider(new SphereCollider({},1.0f));

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
