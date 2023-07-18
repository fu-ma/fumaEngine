#include "TitleScene.h"
#include "GamePlayScene.h"
#include "EndScene.h"
#include"ClearScene.h"
#include"EndScene.h"
#include"SelectScene.h"
#include"GameOverScene.h"
#include"GamePlayScene.h"
#include"Resources.h"
#include"WholeScene.h"

void TitleScene::Initialize(GameSceneManager *pEngine, DebugCamera *camera, Audio *audio, Fps *fps)
{
	Resources *resources = Resources::GetInstance();
	WholeScene *wholeScene = WholeScene::GetInstance();
	Json *json = Json::GetInstance();

	// 背景スプライト生成
	backGround.reset(Sprite::Create(ResourcesNo::backGround3, { WinApp::window_width / wholeScene->HALF_SIZE,WinApp::window_height / wholeScene->HALF_SIZE }));
	titleSprite.reset(Sprite::Create(ResourcesNo::titleSprite, { WinApp::window_width / wholeScene->HALF_SIZE,WinApp::window_height / wholeScene->HALF_SIZE }));
	fadeOut.reset(Sprite::Create(ResourcesNo::fadeOUT, { WinApp::window_width / wholeScene->HALF_SIZE,WinApp::window_height / wholeScene->HALF_SIZE }));
	fadeIn.reset(Sprite::Create(ResourcesNo::fadeIN, { WinApp::window_width / wholeScene->HALF_SIZE,WinApp::window_height / wholeScene->HALF_SIZE }));
	titleUI.reset(Sprite::Create(ResourcesNo::TitleUI, { WinApp::window_width / wholeScene->HALF_SIZE,WinApp::window_height / wholeScene->HALF_SIZE }));

	// 3Dオブジェクト生成
	objPlayer.reset(Player::Create(resources->GetModel(ResourcesName::modelPlayer)));

	for (int i = 0; i < CLOUD_NUM; i++)
	{
		cloud[i].reset(ModelObj::Create(resources->GetModel(ResourcesName::modelCloud)));
	}

	for (int y = 0; y < TITLE_STAGE_Y; y++)
	{
		for (int x = 0; x < TITLE_STAGE_X; x++)
		{
			titleStageBox[y][x].reset(ModelObj::Create(resources->GetModel(ResourcesName::modelStageBox)));
		}
	}
	//背景用の見栄え用オブジェクト
	for (int i = 0; i < backObjNum; i++)
	{
		backObj1[i].reset(ModelObj::Create(resources->GetModel(ResourcesName::modelBackObj1)));
		backObj2[i].reset(ModelObj::Create(resources->GetModel(ResourcesName::modelBackObj2)));
		backObj3[i].reset(ModelObj::Create(resources->GetModel(ResourcesName::modelBackObj3)));
	}

	audio->PlayLoadedSound(resources->GetSoundData(ResourcesName::soundData2), resources->soundData2Bol);
	objPlayer->Initialize();
	for (int i = 0; i < CLOUD_NUM; i++)
	{
		cloud[i]->SetPosition({ (float)(8 * i) - 15.0f + (float)wholeScene->GetRand(-5,2),20 + (float)wholeScene->GetRand(-2,4),(float)wholeScene->GetRand(10,5) });
		cloudPos[i] = cloud[i]->GetPosition();
	}
	cloudSpeed = 0.03f;

	//背景用の見栄え用オブジェクト
	for (int i = 0; i < backObjNum; i++)
	{
		if (i == 0)
		{
			backObj1Pos[i] = { (float)wholeScene->GetRand(0,30),-40 + (float)wholeScene->GetRand(10,13),(float)wholeScene->GetRand(30,40) };
			backObj2Pos[i] = { (float)wholeScene->GetRand(0,30),-40 + (float)wholeScene->GetRand(10,12),(float)wholeScene->GetRand(40,50) };
			backObj3Pos[i] = { (float)wholeScene->GetRand(0,30),-40 + (float)wholeScene->GetRand(5,10),(float)wholeScene->GetRand(30,40) };
		}
		else
		{
			backObj1Pos[i] = { backObj1Pos[i - 1].x + (float)wholeScene->GetRand(20,100),-40 + (float)wholeScene->GetRand(10,13),(float)wholeScene->GetRand(30,40) };
			backObj2Pos[i] = { backObj2Pos[i - 1].x + (float)wholeScene->GetRand(20,100),-40 + (float)wholeScene->GetRand(10,12),(float)wholeScene->GetRand(40,50) };
			backObj3Pos[i] = { backObj3Pos[i - 1].x + (float)wholeScene->GetRand(20,100),-40 + (float)wholeScene->GetRand(5,10),(float)wholeScene->GetRand(30,40) };
		}

		backObj1[i]->SetPosition(backObj1Pos[i]);
		backObj2[i]->SetPosition(backObj2Pos[i]);
		backObj3[i]->SetPosition(backObj3Pos[i]);

		backObj1Size[i] = (float)wholeScene->GetRand(3, 10);
		backObj2Size[i] = (float)wholeScene->GetRand(5, 14);
		backObj3Size[i] = (float)wholeScene->GetRand(5, 8);

		backObj1[i]->SetScale({ backObj1Size[i],15,backObj1Size[i] });
		backObj2[i]->SetScale({ backObj2Size[i],20,backObj2Size[i] });
		backObj3[i]->SetScale({ backObj3Size[i],10,backObj3Size[i] });
	}
	backObj1Speed = 0.06f;
	backObj2Speed = 0.03f;
	backObj3Speed = 0.12f;

	for (int y = 0; y < TITLE_STAGE_Y; y++)
	{
		for (int x = 0; x < TITLE_STAGE_X; x++)
		{
			if (selectMap[y][x] == 1)
			{
				titleStageBox[y][x]->SetPosition({ wholeScene->OBJECT_SIZE * x , -wholeScene->OBJECT_SIZE * y + 10.0f, 0 });
				stageBoxPos[y][x] = titleStageBox[y][x]->GetPosition();
			}
		}
	}
	stageBoxSpeed = 0.06f;
	// カメラ注視点をセット
	camera->SetUp({ 0, 1, 0 });
	camera->SetEye({ objPlayer->GetPosition().x + 10, 10, -20 });
	camera->SetTarget({ objPlayer->GetPosition().x + 10, 10, 0 });

	fadeInSizeX = wholeScene->WIN_WIDTH / 2;
	fadeInSizeY = wholeScene->WIN_HEIGHT / 2;
	fadeInT = 0;
	fadeInFlag = false;
	goSelectFlag = false;
	fadeInSpeed = 0.005f;

	if (wholeScene->GetGoTitleFlag() == true)
	{
		fadeOutSizeX = wholeScene->WIN_WIDTH * 5;
		fadeOutSizeY = wholeScene->WIN_HEIGHT * 5;
		fadeOutT = 0;
		fadeOutFlag = true;
		fadeOutSpeed = 0.005f;
	}
	else
	{
		fadeOutSizeX = 0;
		fadeOutSizeY = 0;
		fadeOutT = 0;
		fadeOutFlag = false;
		fadeOutSpeed = 0;
	}

	titleUICount = 0;

	playerRot = 0;
	playerRotSpeed = 2.0f;
}

void TitleScene::Update(GameSceneManager *pEngine, Audio *audio, DebugText *debugText, LightGroup *lightGroup, DebugCamera *camera, Fps *fps)
{
	Input *input = Input::GetInstance();
	Controller *controller = Controller::GetInstance();
	Resources *resources = Resources::GetInstance();
	WholeScene *wholeScene = WholeScene::GetInstance();

#pragma region 更新処理
	//影の位置
	lightGroup->SetCircleShadowDir(0, XMVECTOR({ 0,-1,0 }));
	lightGroup->SetCircleShadowCasterPos(0, objPlayer->GetPosition());
	lightGroup->SetCircleShadowAtten(0, XMFLOAT3({ objPlayer->GetShadowSize().x,objPlayer->GetShadowSize().y,0.0f }));
	lightGroup->SetCircleShadowFactorAngle(0, objPlayer->GetShadowSize());

	//fadein
	if (fadeInFlag == true)
	{
		fadeInT += fadeInSpeed;
		easing::Updete(fadeInSizeX, wholeScene->WIN_WIDTH * 17, 3, fadeInT);
		easing::Updete(fadeInSizeY, wholeScene->WIN_HEIGHT * 17, 3, fadeInT);

		fadeIn->SetSize({ (float)fadeInSizeX,(float)fadeInSizeY });
	}
	//fadeout
	if (fadeOutFlag == true)
	{
		fadeOutT += fadeOutSpeed;
		easing::Updete(fadeOutSizeX, 0, 3, fadeOutT);
		easing::Updete(fadeOutSizeY, 0, 3, fadeOutT);
		if (fadeOutT > 0.3f)
		{
			fadeOutFlag = false;
		}

		fadeOut->SetSize({ (float)fadeOutSizeX,(float)fadeOutSizeY });
	}

	//fadeoutがあったらそれが終わってから動くようにする
	if (fadeOutFlag == false)
	{
		//UI用カウントの増加
		titleUICount++;
		//オーバーフローしないように
		if (titleUICount >= wholeScene->ONE_SEC)
		{
			titleUICount = 0;
		}

		playerRot -= playerRotSpeed;
		objPlayer->SetRotation({0,0,playerRot});
		//背景用の見栄え用オブジェクト
		for (int i = 0; i < backObjNum; i++)
		{
			backObj1Pos[i].x -= backObj1Speed;
			backObj2Pos[i].x -= backObj2Speed;
			backObj3Pos[i].x -= backObj3Speed;

			if (backObj1[i]->GetPosition().x < objPlayer->GetPosition().x - 100.0f)
			{
				if (i == 0)
				{
					backObj1Pos[i] = { backObj1Pos[backObjNum - 1].x + (float)wholeScene->GetRand(20,100),-40 + (float)wholeScene->GetRand(10,12),(float)wholeScene->GetRand(40,50) };
				}
				else
				{
					backObj1Pos[i] = { backObj1Pos[i - 1].x + (float)wholeScene->GetRand(20,100),-40 + (float)wholeScene->GetRand(10,12),(float)wholeScene->GetRand(40,50) };
				}

				backObj1Size[i] = (float)wholeScene->GetRand(backGroundObjRandMin, backGroundObjRandMax);
			}

			if (backObj2[i]->GetPosition().x < objPlayer->GetPosition().x - 100.0f)
			{
				if (i == 0)
				{
					backObj2Pos[i] = { backObj2Pos[backObjNum - 1].x + (float)wholeScene->GetRand(20,100),-40 + (float)wholeScene->GetRand(10,12),(float)wholeScene->GetRand(40,50) };
				}
				else
				{
					backObj2Pos[i] = { backObj2Pos[i - 1].x + (float)wholeScene->GetRand(20,100),-40 + (float)wholeScene->GetRand(10,12),(float)wholeScene->GetRand(40,50) };
				}

				backObj2Size[i] = (float)wholeScene->GetRand(backGroundObjRandMin, backGroundObjRandMax);
			}

			if (backObj3[i]->GetPosition().x < objPlayer->GetPosition().x - 100.0f)
			{
				if (i == 0)
				{
					backObj3Pos[i] = { backObj3Pos[backObjNum - 1].x + (float)wholeScene->GetRand(20,100),-40 + (float)wholeScene->GetRand(10,12),(float)wholeScene->GetRand(40,50) };
				}
				else
				{
					backObj3Pos[i] = { backObj3Pos[i - 1].x + (float)wholeScene->GetRand(20,100),-40 + (float)wholeScene->GetRand(10,12),(float)wholeScene->GetRand(40,50) };
				}

				backObj3Size[i] = (float)wholeScene->GetRand(backGroundObjRandMin, backGroundObjRandMax);
			}

			backObj1[i]->SetPosition(backObj1Pos[i]);
			backObj2[i]->SetPosition(backObj2Pos[i]);
			backObj3[i]->SetPosition(backObj3Pos[i]);

			backObj1[i]->SetScale({ backObj1Size[i],15,backObj1Size[i] });
			backObj2[i]->SetScale({ backObj2Size[i],20,backObj2Size[i] });
			backObj3[i]->SetScale({ backObj3Size[i],10,backObj3Size[i] });
		}

		//雲の移動
		{
			for (int i = 0; i < CLOUD_NUM; i++)
			{
				cloudPos[i].x -= cloudSpeed;
				if (cloud[i]->GetPosition().x < objPlayer->GetPosition().x - 25.0f)
				{
					if (i == 0)
					{
						cloudPos[i] = { cloud[CLOUD_NUM - 1]->GetPosition().x + 8.0f + (float)wholeScene->GetRand(-5,2),20 + (float)wholeScene->GetRand(-2,4),(float)wholeScene->GetRand(10,5) };
					}
					else
					{
						cloudPos[i] = { cloud[i - 1]->GetPosition().x + 8.0f + (float)wholeScene->GetRand(-5,2),20 + (float)wholeScene->GetRand(-2,4),(float)wholeScene->GetRand(10,5) };
					}
				}
				cloud[i]->SetPosition(cloudPos[i]);
			}
		}
		//ブロックのスクロール
		for (int y = 0; y < TITLE_STAGE_Y; y++)
		{
			for (int x = 0; x < TITLE_STAGE_X; x++)
			{
				stageBoxPos[y][x].x -= stageBoxSpeed;
				if (selectMap[y][x] == 1 && titleStageBox[y][x]->GetPosition().x < objPlayer->GetPosition().x - 15)
				{
					if (x == 0)
					{
						stageBoxPos[y][x] = { titleStageBox[y][TITLE_STAGE_X - 1]->GetPosition().x + wholeScene->OBJECT_SIZE, -wholeScene->OBJECT_SIZE * y + 10.0f, 0 };
					}
					else
					{
						stageBoxPos[y][x] = { titleStageBox[y][x - 1]->GetPosition().x + wholeScene->OBJECT_SIZE, -wholeScene->OBJECT_SIZE * y + 10.0f, 0 };
					}

				}
				titleStageBox[y][x]->SetPosition(stageBoxPos[y][x]);
			}
		}

		//シーン遷移
		if (input->isKeyTrigger(DIK_SPACE) || controller->TriggerButton(static_cast<int>(Button::A)) == true)
		{
			audio->PlayLoadedSound(resources->GetSoundData(ResourcesName::soundData3), resources->soundData3Bol);
			fadeInFlag = true;
			goSelectFlag = true;
		}

		if (fadeInSizeX > wholeScene->WIN_WIDTH * 15 && goSelectFlag == true)
		{
			audio->StopLoadedSound(resources->GetSoundData(ResourcesName::soundData2));
			pEngine->changeState(new SelectScene());
		}
	}
	lightGroup->Update();
	camera->Update();
	objPlayer->Update();
	for (int y = 0; y < TITLE_STAGE_Y; y++)
	{
		for (int x = 0; x < TITLE_STAGE_X; x++)
		{
			titleStageBox[y][x]->Update();
		}
	}

	for (int i = 0; i < CLOUD_NUM; i++)
	{
		cloud[i]->Update();
	}
	//背景用の見栄え用オブジェクト
	for (int i = 0; i < backObjNum; i++)
	{
		backObj1[i]->Update();
		backObj2[i]->Update();
		backObj3[i]->Update();
	}
}

void TitleScene::Draw(GameSceneManager *pEngine, DirectXApp *common, DebugText *debugText)
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

	//背景用の見栄え用オブジェクトの描画
	for (int i = 0; i < backObjNum; i++)
	{
		backObj1[i]->Draw();
		backObj2[i]->Draw();
		backObj3[i]->Draw();
	}

	for (int i = 0; i < CLOUD_NUM; i++)
	{
		cloud[i]->Draw();
	}
	objPlayer->Draw();
	for (int y = 0; y < TITLE_STAGE_Y; y++)
	{
		for (int x = 0; x < TITLE_STAGE_X; x++)
		{
			titleStageBox[y][x]->Draw();
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

	//title
	titleSprite->Draw();
	//UI
	if (titleUICount % 60 >= 0 && titleUICount % 60 <= 30)
	{
		titleUI->Draw();
	}

	//fadein
	if (fadeInFlag == true)
	{
		fadeIn->Draw();
	}
	//fadeout
	if (fadeOutFlag == true)
	{
		fadeOut->Draw();
	}
	/*スプライト描画後処理*/
	Sprite::PostDraw();
}
