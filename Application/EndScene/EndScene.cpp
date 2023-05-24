#include "EndScene.h"
#include "TitleScene.h"
#include "GamePlayScene.h"
#include"ClearScene.h"
#include"EndScene.h"
#include"SelectScene.h"
#include"GameOverScene.h"
#include"GamePlayScene.h"
#include"Resources.h"

void EndScene::Initialize(GameSceneManager *pEngine, DebugCamera *camera, Audio *audio, Fps *fps)
{
}

void EndScene::Update(GameSceneManager *pEngine, Audio *audio, DebugText *debugText, LightGroup *lightGroup, DebugCamera *camera, Fps *fps)
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

	lightGroup->Update();
	camera->Update();
}

void EndScene::Draw(GameSceneManager *pEngine, DirectXApp *common, DebugText *debugText)
{
	/*�X�v���C�g�`��*/
/*�X�v���C�g�`��O����*/
	Sprite::PreDraw(common->GetCmdList().Get());

	/*�X�v���C�g�`��㏈��*/
	Sprite::PostDraw();
	//�[�x�o�b�t�@�N���A
	common->ClearDepthBuffer();
}
