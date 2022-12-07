#include "ClearScene.h"
#include "TitleScene.h"
#include "GamePlayScene.h"
#include "EndScene.h"
#include"EndScene.h"
#include"SelectScene.h"
#include"GameOverScene.h"
#include"GamePlayScene.h"

void ClearScene::Initialize(GameSceneManager *pEngine, DebugCamera *camera, Audio *audio, Fps *fps)
{
	StageClear = Sprite::Create(3, { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f });
}

void ClearScene::Update(GameSceneManager *pEngine, Audio *audio, DebugText *debugText, LightGroup *lightGroup, DebugCamera *camera, Fps *fps)
{
	Input *input = Input::GetInstance();
	Controller *controller = Controller::GetInstance();
	//シーン遷移
	if (input->isKeyTrigger(DIK_SPACE) || controller->TriggerButton(static_cast<int>(Button::A)) == true)
	{
		audio->PlayLoadedSound(Resources::soundData3, 0.05f);
		pEngine->changeState(new SelectScene(), camera, audio, fps);
		return;
	}
}

void ClearScene::Draw(GameSceneManager *pEngine, DirectXApp *common, DebugText *debugText)
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
