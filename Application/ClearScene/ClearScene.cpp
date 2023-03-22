#include "ClearScene.h"
#include "TitleScene.h"
#include "GamePlayScene.h"
#include "EndScene.h"
#include"EndScene.h"
#include"SelectScene.h"
#include"GameOverScene.h"
#include"GamePlayScene.h"
#include"Resources.h"

void ClearScene::Initialize(GameSceneManager *pEngine, DebugCamera *camera, Audio *audio, Fps *fps)
{
	Resources *resources = Resources::GetInstance();
	StageClear = Sprite::Create(1, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	fadeOut = Sprite::Create(19, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	fadeIn = Sprite::Create(18, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });


	egg = new FBXObject3d;
	egg->Initialize();
	egg->SetModel(resources->GetFBXModel(ResourcesName::modelEgg));
	egg->PlayAnimation();
	egg->SetRotation({ 0,180,0 });
	egg->SetScale({ 0.1f,0.1f,0.1f });

	gameClear = new FBXObject3d;
	gameClear->Initialize();
	gameClear->SetModel(resources->GetFBXModel(ResourcesName::modelStageClear));
	//gameClear->PlayAnimation();
	gameClear->SetPosition({ 0,30,-10 });
	gameClear->SetRotation({ 90,0,0 });
	gameClear->SetScale({ 0.1f,0.1f,0.1f });

	fadeOutSizeX = 1280 * 5;
	fadeOutSizeY = 720 * 5;
	fadeOutT = 0;
	fadeOutFlag = true;

	fadeInSizeX = 1280 / 2;
	fadeInSizeY = 720 / 2;
	fadeInT = 0;
	fadeInFlag = false;

	goSelectFlag = false;

	camera->SetUp({ 0, 1, 0 });
	camera->SetEye({ egg->GetPosition().x, 20, -50 });
	camera->SetTarget({ egg->GetPosition().x, 20, 0 });

	particleMan = ParticleManager::GetInstance();
	particleTimer = 0;
	parPosLeft = {};
	parPosRight = {};
	saveVel = 0;
}

void ClearScene::Update(GameSceneManager *pEngine, Audio *audio, DebugText *debugText, LightGroup *lightGroup, DebugCamera *camera, Fps *fps)
{
	Input *input = Input::GetInstance();
	Controller *controller = Controller::GetInstance();
	Resources *resources = Resources::GetInstance();

	//fadein
	if (fadeInFlag == true)
	{
		fadeInT += 0.005f;
		easing::Updete(fadeInSizeX, 1280 * 17, 3, fadeInT);
		easing::Updete(fadeInSizeY, 720 * 17, 3, fadeInT);

		fadeIn->SetSize({ (float)fadeInSizeX,(float)fadeInSizeY });
	}
	//fadeout
	if (fadeOutFlag == true)
	{
		fadeOutT += 0.005f;
		easing::Updete(fadeOutSizeX, 0, 3, fadeOutT);
		easing::Updete(fadeOutSizeY, 0, 3, fadeOutT);
		if (fadeOutT > 0.3f)
		{
			fadeOutFlag = false;
		}

		fadeOut->SetSize({ (float)fadeOutSizeX,(float)fadeOutSizeY });
	}

	//fadeoutが終わったら選択できる
	if (fadeOutFlag == false)
	{
		egg->Update();
		gameClear->Update();
		camera->Update();
		//シーン遷移
		if (input->isKeyTrigger(DIK_SPACE) || controller->TriggerButton(static_cast<int>(Button::A)) == true)
		{
			fadeInFlag = true;
			goSelectFlag = true;
		}

		if (goSelectFlag == true)
		{
			if (fadeInSizeX > 1280 * 15)
			{
				audio->PlayLoadedSound(resources->GetSoundData(ResourcesName::soundData3), 0.05f);
				pEngine->changeState(new SelectScene());
			}
		}

		if (particleTimer == 0)
		{
			//左側のパーティクル
			for (int i = 0; i < 1; ++i)
			{
				const float rnd_vel = 2.5f;
				XMFLOAT3 vel{};
				vel.y = 2.5f / 4.0f;
				//下の計算のために保存する
				saveVel = vel.y;

				const float rnd_pos = 20.0f;
				XMFLOAT3 pos{};
				pos.x = -40;
				pos.y = 0;
				pos.z = 0;

				parPosLeft = pos;

				ParticleManager::GetInstance()->Add(60, pos, vel, XMFLOAT3(), 5.0f, 0.0f);
			}
			//右側のパーティクル
			for (int i = 0; i < 1; ++i)
			{
				const float rnd_vel = 2.5f;
				XMFLOAT3 vel{};
				vel.y = 2.5f / 4.0f;
				//下の計算のために保存する
				saveVel = vel.y;

				const float rnd_pos = 20.0f;
				XMFLOAT3 pos{};
				pos.x = 40;
				pos.y = 0;
				pos.z = 0;

				parPosRight = pos;

				ParticleManager::GetInstance()->Add(60, pos, vel, XMFLOAT3(), 5.0f, 0.0f);
			}

		}
		if (particleTimer == 60)
		{
			//左側のパーティクル
			for (int i = 0; i < 30; ++i)
			{
				const float rnd_vel = 1.2f;
				XMFLOAT3 vel{};
				vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
				vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
				vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;

				ParticleManager::GetInstance()->Add(60, { parPosRight.x,parPosRight.y + (saveVel * 60) ,parPosRight.z }, vel, XMFLOAT3(), 5.0f, 0.0f);
			}
			//右側のパーティクル
			for (int i = 0; i < 30; ++i)
			{
				const float rnd_vel = 1.2f;
				XMFLOAT3 vel{};
				vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
				vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
				vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;

				ParticleManager::GetInstance()->Add(60, { parPosLeft.x,parPosLeft.y + (saveVel * 60) ,parPosLeft.z }, vel, XMFLOAT3(), 5.0f, 0.0f);
			}
		}
		particleTimer++;
		if (particleTimer > 90)
		{
			particleTimer = 0;
		}
		particleMan->Update();
	}
}

void ClearScene::Draw(GameSceneManager *pEngine, DirectXApp *common, DebugText *debugText)
{
	/*スプライト描画*/
	/*スプライト描画前処理*/
	Sprite::PreDraw(common->GetCmdList().Get());
	StageClear->Draw();
	/*スプライト描画後処理*/
	//fadeout
	if (fadeOutFlag == true)
	{
		fadeOut->Draw();
	}

	Sprite::PostDraw();
	//深度バッファクリア
	common->ClearDepthBuffer();
	/*モデル描画前処理*/
	ModelObj::PreDraw(common->GetCmdList().Get());
	egg->Draw(common->GetCmdList().Get());
	gameClear->Draw(common->GetCmdList().Get());
	ModelObj::PostDraw();

	particleMan->Draw(common->GetCmdList().Get());

	Sprite::PreDraw(common->GetCmdList().Get());
	/*スプライト描画後処理*/
	//fadein
	if (fadeInFlag == true)
	{
		fadeIn->Draw();
	}
	Sprite::PostDraw();
	//深度バッファクリア
	common->ClearDepthBuffer();
}
