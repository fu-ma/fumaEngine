#include "Resources.h"
SoundData Resources::soundData1;
SoundData Resources::soundData2;
SoundData Resources::soundData3;
Model * Resources::modelPlayer = nullptr;
Model *Resources::modelCloud = nullptr;
Model *Resources::modelStageBox = nullptr;
Model *Resources::modelEnemy = nullptr;
Model *Resources::modelRedBlock = nullptr;
Model *Resources::modelBlueBlock = nullptr;
Model *Resources::modelWireBlock = nullptr;
Model *Resources::modelGoal = nullptr;

void Resources::StaticInit(Audio *audio)
{
	//音声読み込み
	soundData1 = audio->SoundLoadWave("Resources/sound/GAMEBGM.wav", true);
	soundData2 = audio->SoundLoadWave("Resources/sound/TITLEBGM.wav", true);
	soundData3 = audio->SoundLoadWave("Resources/sound/SPACESE.wav", false);

	// テクスチャ読み込み
	Sprite::LoadTexture(1, L"Resources/img/backGround3.png");
	Sprite::LoadTexture(2, L"Resources/img/titleSprite.png");
	Sprite::LoadTexture(3, L"Resources/img/StageClear.png");
	Sprite::LoadTexture(4, L"Resources/img/skull.png");
	Sprite::LoadTexture(5, L"Resources/img/e1.png");
	Sprite::LoadTexture(6, L"Resources/img/Stage1.png");
	Sprite::LoadTexture(7, L"Resources/img/Stage2.png");
	Sprite::LoadTexture(8, L"Resources/img/Stage3.png");
	Sprite::LoadTexture(9, L"Resources/img/Stage4.png");
	Sprite::LoadTexture(10, L"Resources/img/Stage5.png");
	Sprite::LoadTexture(11, L"Resources/img/CountStart.png");
	Sprite::LoadTexture(12, L"Resources/img/playerIcon.png");
	Sprite::LoadTexture(13, L"Resources/img/GameOver.png");
	Sprite::LoadTexture(14, L"Resources/img/title.png");
	Sprite::LoadTexture(15, L"Resources/img/restart.png");
	Sprite::LoadTexture(16, L"Resources/img/Return.png");
	Sprite::LoadTexture(17, L"Resources/img/ClearStage.png");

	// モデル読み込み
	modelPlayer = Model::CreateFromOBJ("player", true);
	modelEnemy = Model::CreateFromOBJ("enemy", true);
	modelStageBox = Model::CreateFromOBJ("StageBox", true);
	modelCloud = Model::CreateFromOBJ("cloud", true);
	modelGoal = Model::CreateFromOBJ("goal", true);
	modelRedBlock = Model::CreateFromOBJ("redBlock", true);
	modelBlueBlock = Model::CreateFromOBJ("blueBlock", true);
	modelWireBlock = Model::CreateFromOBJ("wireBlock", true);
}
