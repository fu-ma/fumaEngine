#include "Resources.h"

Resources *Resources::GetInstance()
{
	static Resources instance;

	return &instance;
}

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
	Sprite::LoadTexture(18, L"Resources/img/fadeIN.png");
	Sprite::LoadTexture(19, L"Resources/img/fadeOUT.png");
	Sprite::LoadTexture(20, L"Resources/img/TitleUI.png");

	// モデル読み込み
	modelPlayer = Model::CreateFromOBJ("player", true);
	modelEnemy = Model::CreateFromOBJ("enemy", true);
	modelStageBox = Model::CreateFromOBJ("StageBox", true);
	modelCloud = Model::CreateFromOBJ("cloud", true);
	modelGoal = Model::CreateFromOBJ("goal", true);
	modelRedBlock = Model::CreateFromOBJ("redBlock", true);
	modelBlueBlock = Model::CreateFromOBJ("blueBlock", true);
	modelWireBlock = Model::CreateFromOBJ("wireBlock", true);
	modelJumpSignA = Model::CreateFromOBJ("jumpSignA", true);
	modelWallSignA = Model::CreateFromOBJ("wallSignA", true);
	modelBackObj1 = Model::CreateFromOBJ("backObj1", true);
	modelBackObj2 = Model::CreateFromOBJ("backObj2", true);
	modelBackObj3 = Model::CreateFromOBJ("backObj3", true);
	modelEggShell = Model::CreateFromOBJ("eggShell", true);
}

SoundData &Resources::GetSoundData(ResourcesName resourcesName)
{
	if (resourcesName == ResourcesName::soundData1)
	{
		return soundData1;
	}
	else if (resourcesName == ResourcesName::soundData2)
	{
		return soundData2;
	}
	else if (resourcesName == ResourcesName::soundData3)
	{
		return soundData3;
	}
	else
	{
		return sound;
	}
}

Model *Resources::GetModel(ResourcesName resourcesName)
{
	if (resourcesName == ResourcesName::modelPlayer)
	{
		return modelPlayer;
	}
	else if (resourcesName == ResourcesName::modelCloud)
	{
		return modelCloud;
	}
	else if (resourcesName == ResourcesName::modelStageBox)
	{
		return modelStageBox;
	}
	else if (resourcesName == ResourcesName::modelEnemy)
	{
		return modelEnemy;
	}
	else if (resourcesName == ResourcesName::modelRedBlock)
	{
		return modelRedBlock;
	}
	else if (resourcesName == ResourcesName::modelBlueBlock)
	{
		return modelBlueBlock;
	}
	else if (resourcesName == ResourcesName::modelWireBlock)
	{
		return modelWireBlock;
	}
	else if (resourcesName == ResourcesName::modelGoal)
	{
		return modelGoal;
	}
	else if (resourcesName == ResourcesName::modelJumpSignA)
	{
		return modelJumpSignA;
	}
	else if (resourcesName == ResourcesName::modelWallSignA)
	{
		return modelWallSignA;
	}
	else if (resourcesName == ResourcesName::modelBackObj1)
	{
		return modelBackObj1;
	}
	else if (resourcesName == ResourcesName::modelBackObj2)
	{
		return modelBackObj2;
	}
	else if (resourcesName == ResourcesName::modelBackObj3)
	{
		return modelBackObj3;
	}
	else if (resourcesName == ResourcesName::modelEggShell)
	{
		return modelEggShell;
	}

	else
	{
		return model;
	}
}
