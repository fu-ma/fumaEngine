#include "Framework.h"

void Framework::GameRun()
{
	staticInit();
	while (true)//ゲームループ
	{
		//初期化(内部で一回のみ読み込むようにしている)
		Init();
		//更新処理
		if (Update() == false)
		{
			break;
		}
		//描画処理
		//描画開始
		common->PreDraw();
		Draw();
		//描画終了
		common->PostDraw();
		////レンダーテクスチャへの描画
		//postEffect->PreDrawScene(common->GetCmdList().Get());
		////ポストエフェクトの描画
		//postEffect->Draw(common->GetCmdList().Get());
		////Imguiの描画処理
		//postEffect->PostDrawScene(common->GetCmdList().Get());

	}
	SceneDelete();
}

void Framework::staticInit()
{
	winApp = std::make_unique<WinApp>();
	common = std::make_unique<DirectXApp>(winApp.get());
	winApp->Innitialize();
	common->Initialize();

	input = Input::GetInstance();
	input->Initialize(winApp->GetHInstance(), winApp->GetHwnd());
	controller = Controller::GetInstance();
	controller->Initialize(0);

	Audio::Init();
	//ライト静的初期化
	LightGroup::StaticInitialize(common->GetDev().Get());
	/*スプライト初期化*/
	Sprite::StaticInitialize(common->GetDev().Get(), WinApp::window_width, WinApp::window_height);
	Sprite::LoadTexture(0, L"Resources/image/BoxFont.dds");
	debugText = DebugText::GetInstance();
	debugText->Initialize(0);

	//ポストエフェクト用テクスチャの読み込み
	//Sprite::LoadTexture(100, L"Resources/backGround3.png");
	//ポストエフェクトの初期化
	postEffect = std::make_unique<PostEffect>();
	postEffect->Initialize();

	/*FBX初期化*/
	FbxLoader::GetInstance()->Initialize(common->GetDev().Get());
	//デバイスをセット
	FBXObject3d::SetDevice(common->GetDev().Get());

	/*モデル初期化*/
	ModelObj::StaticInitialize(common->GetDev().Get());
	// カメラ生成
	camera = std::make_unique<DebugCamera>(WinApp::window_width, WinApp::window_height, input);

	// パーティクルマネージャ初期化
	ParticleManager::GetInstance()->Initialize(common->GetDev().Get());
	particleMan = ParticleManager::GetInstance();
	particleMan->SetCamera(camera.get());

	//カメラをセット
	FBXObject3d::SetCamera(camera.get());
	//グラフィックスパイプライン生成
	FBXObject3d::CreateGraphicsPipeline();

	//Imgui初期化
	ImguiCommon::Initialize(common->GetDev().Get(),winApp->GetHwnd());

	fps = std::make_unique<Fps>();

	resources = Resources::GetInstance();
	resources->StaticInit(audio.get());

	json = Json::GetInstance();

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

void Framework::Init()
{
	manager->Initialize(camera.get(), audio.get(), fps.get());
}

bool Framework::Update()
{
	//キーボード情報の取得開始
	input->Update();
	controller->Update(0);

	if (winApp->ProcessMessage())
	{
		return false;
	}

	manager->Update(debugText, audio.get(), lightGroup.get(), camera.get(), fps.get());

	return true;
}

void Framework::Draw()
{
	//描画開始
	//common->PreDraw();
	manager->Draw(common.get(), debugText);
	//描画終了
	//common->PostDraw();
	manager->StateDelete();
}
