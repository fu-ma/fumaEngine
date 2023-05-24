#include "GameOverScene.h"
#include "TitleScene.h"
#include "GamePlayScene.h"
#include "EndScene.h"
#include"ClearScene.h"
#include"EndScene.h"
#include"SelectScene.h"
#include"GamePlayScene.h"
#include"Resources.h"
#include"WholeScene.h"

void GameOverScene::Initialize(GameSceneManager *pEngine, DebugCamera *camera, Audio *audio, Fps *fps)
{
	WholeScene *wholeScene = WholeScene::GetInstance();

	EndSprite = Sprite::Create(13, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
	wholeScene->SetTotalPlayerNum(5);
}

void GameOverScene::Update(GameSceneManager *pEngine, Audio *audio, DebugText *debugText, LightGroup *lightGroup, DebugCamera *camera, Fps *fps)
{
	Input *input = Input::GetInstance();
	Controller *controller = Controller::GetInstance();
	Resources *resources = Resources::GetInstance();

	//�V�[���J��
	if (input->isKeyTrigger(DIK_SPACE) || controller->TriggerButton(static_cast<int>(Button::A)) == true)
	{
		audio->PlayLoadedSound(resources->GetSoundData(ResourcesName::soundData3), 0.05f);
		pEngine->changeState(new TitleScene());
		return;
	}
}

void GameOverScene::Draw(GameSceneManager *pEngine, DirectXApp *common, DebugText *debugText)
{
	/*�X�v���C�g�`��*/
/*�X�v���C�g�`��O����*/
	Sprite::PreDraw(common->GetCmdList().Get());
	EndSprite->Draw();
	/*�X�v���C�g�`��㏈��*/
	Sprite::PostDraw();
	//�[�x�o�b�t�@�N���A
	common->ClearDepthBuffer();
}
