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
	Sprite::LoadTexture(1, L"Resources/image/backGround3.dds");
	Sprite::LoadTexture(2, L"Resources/image/titleSprite.dds");
	Sprite::LoadTexture(3, L"Resources/image/StageClear.dds");
	Sprite::LoadTexture(4, L"Resources/image/skull.dds");
	Sprite::LoadTexture(5, L"Resources/image/e1.dds");
	Sprite::LoadTexture(6, L"Resources/image/Stage1.dds");
	Sprite::LoadTexture(7, L"Resources/image/Stage2.dds");
	Sprite::LoadTexture(8, L"Resources/image/Stage3.dds");
	Sprite::LoadTexture(9, L"Resources/image/Stage4.dds");
	Sprite::LoadTexture(10, L"Resources/image/Stage5.dds");
	Sprite::LoadTexture(11, L"Resources/image/CountStart.dds");
	Sprite::LoadTexture(12, L"Resources/image/playerIcon.dds");
	Sprite::LoadTexture(13, L"Resources/image/GameOver.dds");
	Sprite::LoadTexture(14, L"Resources/image/title.dds");
	Sprite::LoadTexture(15, L"Resources/image/restart.dds");
	Sprite::LoadTexture(16, L"Resources/image/Return.dds");
	Sprite::LoadTexture(17, L"Resources/image/ClearStage.dds");
	Sprite::LoadTexture(18, L"Resources/image/fadeIN.dds");
	Sprite::LoadTexture(19, L"Resources/image/fadeOUT.dds");
	Sprite::LoadTexture(20, L"Resources/image/TitleUI.dds");
	Sprite::LoadTexture(21, L"Resources/image/ESCUI.dds");
	Sprite::LoadTexture(22, L"Resources/image/HOMEUI.dds");

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
	modelJumpSignSpace = Model::CreateFromOBJ("jumpSignSpace", true);
	modelWallSignA = Model::CreateFromOBJ("wallSignA", true);
	modelWallSignSpace = Model::CreateFromOBJ("wallSignSpace", true);
	modelBackObj1 = Model::CreateFromOBJ("backObj1", true);
	modelBackObj2 = Model::CreateFromOBJ("backObj2", true);
	modelBackObj3 = Model::CreateFromOBJ("backObj3", true);
	modelEggShell = Model::CreateFromOBJ("eggShell", true);
	modelParticle = Model::CreateFromOBJ("player", true);
	modelExplosionLeftParticle = Model::CreateFromOBJ("eggShell", true);
	modelExplosionRightParticle = Model::CreateFromOBJ("eggShell", true);
	modelExplosionUpParticle = Model::CreateFromOBJ("eggShell", true);
	modelThornStick = Model::CreateFromOBJ("thornStick", true);

	modelEgg = FbxLoader::GetInstance()->LoadModelFromFile("egg");
	modelEgg->SetBaseColor(XMFLOAT3(1, 1, 1));
	modelEgg->SetMetalness(1.0f);
	modelEgg->SetSpecular(1.0f);
	modelEgg->SetRoughness(0.5f);
	modelEgg->TransferMaterial();

	modelStageClear = FbxLoader::GetInstance()->LoadModelFromFile("StageClear");
	modelStageClear->SetBaseColor(XMFLOAT3(1, 0, 0));
	modelStageClear->SetMetalness(0.2f);
	modelStageClear->SetSpecular(0.5f);
	modelStageClear->SetRoughness(1.0f);
	modelStageClear->TransferMaterial();
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
	else if (resourcesName == ResourcesName::modelJumpSignSpace)
	{
		return modelJumpSignSpace;
	}
	else if (resourcesName == ResourcesName::modelWallSignA)
	{
		return modelWallSignA;
	}
	else if (resourcesName == ResourcesName::modelWallSignSpace)
	{
		return modelWallSignSpace;
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
	else if (resourcesName == ResourcesName::modelParticle)
	{
		return modelParticle;
	}
	else if (resourcesName == ResourcesName::modelExplosionLeftParticle)
	{
		return modelExplosionLeftParticle;
	}
	else if (resourcesName == ResourcesName::modelExplosionRightParticle)
	{
		return modelExplosionRightParticle;
	}
	else if (resourcesName == ResourcesName::modelExplosionUpParticle)
	{
		return modelExplosionUpParticle;
	}
	else if (resourcesName == ResourcesName::modelThornStick)
	{
		return modelThornStick;
	}
	else
	{
		return model;
	}
}

FBXModel *Resources::GetFBXModel(ResourcesName resourcesName)
{
	if (resourcesName == ResourcesName::modelEgg)
	{
		return modelEgg;
	}
	else if (resourcesName == ResourcesName::modelStageClear)
	{
		return modelStageClear;
	}
	else
	{
		return 0;
	}

}
