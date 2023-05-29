#include "Resources.h"

Resources *Resources::GetInstance()
{
	static Resources instance;

	return &instance;
}

void Resources::StaticInit(Audio *audio)
{
	//�����ǂݍ���
	soundData1 = audio->SoundLoadWave("Resources/sound/GAMEBGM.wav", true);
	soundData2 = audio->SoundLoadWave("Resources/sound/TITLEBGM.wav", true);
	soundData3 = audio->SoundLoadWave("Resources/sound/SPACESE.wav", false);

	// �e�N�X�`���ǂݍ���
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
	Sprite::LoadTexture(23, L"Resources/image/egg.dds");
	Sprite::LoadTexture(24, L"Resources/image/startToGoal.dds");
	Sprite::LoadTexture(25, L"Resources/image/goal.dds");
	Sprite::LoadTexture(26, L"Resources/image/starSprite.dds");
	Sprite::LoadTexture(27, L"Resources/image/noStarSprite.dds");
	Sprite::LoadTexture(28, L"Resources/image/gauge.dds");
	Sprite::LoadTexture(29, L"Resources/image/ButtonA.dds");
	Sprite::LoadTexture(30, L"Resources/image/ButtonSpace.dds");
	Sprite::LoadTexture(31, L"Resources/image/tutorial1.dds");
	Sprite::LoadTexture(32, L"Resources/image/tutorial2.dds");

	// ���f���ǂݍ���
	modelPlayer = Model::CreateFromOBJ("player", true);
	modelEnemy = Model::CreateFromOBJ("enemy", true);
	modelStageBox = Model::CreateFromOBJ("StageBox", true);
	modelCloud = Model::CreateFromOBJ("cloud", true);
	modelGoal = Model::CreateFromOBJ("goal", true);
	modelRedBlock = Model::CreateFromOBJ("redBlock", true);
	modelBlueBlock = Model::CreateFromOBJ("blueBlock", true);
	modelWireBlock = Model::CreateFromOBJ("wireBlock", true);
	modelSignboard = Model::CreateFromOBJ("signboard", true);
	modelSignboardA = Model::CreateFromOBJ("signboardA", true);
	modelSignboardSpace = Model::CreateFromOBJ("signboardSpace", true);
	modelBackObj1 = Model::CreateFromOBJ("backObj1", true);
	modelBackObj2 = Model::CreateFromOBJ("backObj2", true);
	modelBackObj3 = Model::CreateFromOBJ("backObj3", true);
	modelEggShell = Model::CreateFromOBJ("eggShell", true);
	modelParticle = Model::CreateFromOBJ("player", true);
	modelExplosionLeftParticle = Model::CreateFromOBJ("eggShell", true);
	modelExplosionRightParticle = Model::CreateFromOBJ("eggShell", true);
	modelExplosionUpParticle = Model::CreateFromOBJ("eggShell", true);
	modelThornStick = Model::CreateFromOBJ("thornStick", true);
	modelFire = Model::CreateFromOBJ("gimmick", true);
	modelStar = Model::CreateFromOBJ("star", true);
	modelBluePlayer = Model::CreateFromOBJ("bluePlayer", true);
	modelRedPlayer = Model::CreateFromOBJ("redPlayer", true);

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
	else if (resourcesName == ResourcesName::modelSignboard)
	{
		return modelSignboard;
	}
	else if (resourcesName == ResourcesName::modelSignboardA)
	{
		return modelSignboardA;
	}
	else if (resourcesName == ResourcesName::modelSignboardSpace)
	{
		return modelSignboardSpace;
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
	else if (resourcesName == ResourcesName::modelFire)
	{
		return modelFire;
	}
	else if (resourcesName == ResourcesName::modelStar)
	{
		return modelStar;
	}
	else if (resourcesName == ResourcesName::modelBluePlayer)
	{
		return modelBluePlayer;
	}
	else if (resourcesName == ResourcesName::modelRedPlayer)
	{
		return modelRedPlayer;
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
