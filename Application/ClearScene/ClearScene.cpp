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

	//fadeout���I�������I���ł���
	if (fadeOutFlag == false)
	{
		egg->Update();
		gameClear->Update();
		camera->Update();
		//�V�[���J��
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
	}
}

void ClearScene::Draw(GameSceneManager *pEngine, DirectXApp *common, DebugText *debugText)
{
	/*�X�v���C�g�`��*/
	/*�X�v���C�g�`��O����*/
	Sprite::PreDraw(common->GetCmdList().Get());
	StageClear->Draw();
	/*�X�v���C�g�`��㏈��*/
	//fadeout
	if (fadeOutFlag == true)
	{
		fadeOut->Draw();
	}

	Sprite::PostDraw();
	//�[�x�o�b�t�@�N���A
	common->ClearDepthBuffer();
	/*���f���`��O����*/
	ModelObj::PreDraw(common->GetCmdList().Get());
	egg->Draw(common->GetCmdList().Get());
	gameClear->Draw(common->GetCmdList().Get());
	ModelObj::PostDraw();
	Sprite::PreDraw(common->GetCmdList().Get());
	/*�X�v���C�g�`��㏈��*/
	//fadein
	if (fadeInFlag == true)
	{
		fadeIn->Draw();
	}
	Sprite::PostDraw();
	//�[�x�o�b�t�@�N���A
	common->ClearDepthBuffer();
}
