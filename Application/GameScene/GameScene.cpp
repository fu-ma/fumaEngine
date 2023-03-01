#include "GameScene.h"
#include <cassert>
#include <sstream>
#include <iomanip>
#include"FbxLoader.h"

#pragma warning(disable : 4996)

using namespace DirectX;

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

	lightGroup->SetSpotLightActive(0, false);
	lightGroup->SetCircleShadowActive(0, true);

	// 3Dオブジェクトにカメラをセット
	ModelObj::SetCamera(camera.get());

	//ライトグループをセット
	FBXObject3d::SetLightGroup(lightGroup.get());

	manager = new GameSceneManager();
	////残機を設定
	wholeScene = WholeScene::GetInstance();
	wholeScene->StaticInit();
}

void GameScene::Init()
{
	//基底クラスの初期化
	Framework::Init();

	manager->Initialize(camera.get(), audio.get(), fps.get());
}

bool GameScene::Update()
{
	//基底クラスの更新
	if (Framework::Update() == false)
	{
		return false;
	}

	manager->Update(debugText,audio.get(), lightGroup.get(), camera.get(), fps.get());

	return true;
}

void GameScene::Draw()
{
	//描画開始
	common->PreDraw();
	manager->Draw(common.get(), debugText);
	//描画終了
	common->PostDraw();
	manager->StateDelete();
}