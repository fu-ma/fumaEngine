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
	soundData4 = audio->SoundLoadWave("Resources/sound/JumpSE.wav", false);
	soundData5 = audio->SoundLoadWave("Resources/sound/MenuMoveSE.wav", false);
	soundData6 = audio->SoundLoadWave("Resources/sound/wallSlide.wav", false);
	soundData7 = audio->SoundLoadWave("Resources/sound/wallKick.wav", false);
	soundData8 = audio->SoundLoadWave("Resources/sound/getStar.wav", false);
	soundData9 = audio->SoundLoadWave("Resources/sound/selectSE.wav", false);
	soundData10 = audio->SoundLoadWave("Resources/sound/gameClear.wav", false);
	soundData11 = audio->SoundLoadWave("Resources/sound/damage.wav", false);
	soundData12 = audio->SoundLoadWave("Resources/sound/killEnemy.wav", false);
	soundData13 = audio->SoundLoadWave("Resources/sound/moveSE.wav",true);
	soundData14 = audio->SoundLoadWave("Resources/sound/panicBgm.wav", false);

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
	modelPlayer.reset(Model::CreateFromOBJ("player", true));
	modelEnemy.reset(Model::CreateFromOBJ("enemy", true));
	modelStageBox.reset(Model::CreateFromOBJ("StageBox", true));
	modelCloud.reset(Model::CreateFromOBJ("cloud", true));
	modelGoal.reset(Model::CreateFromOBJ("goal", true));
	modelRedBlock.reset(Model::CreateFromOBJ("redBlock", true));
	modelBlueBlock.reset(Model::CreateFromOBJ("blueBlock", true));
	modelWireBlock.reset(Model::CreateFromOBJ("wireBlock", true));
	modelSignboard.reset(Model::CreateFromOBJ("signboard", true));
	modelSignboardA.reset(Model::CreateFromOBJ("signboardA", true));
	modelSignboardSpace.reset(Model::CreateFromOBJ("signboardSpace", true));
	modelBackObj1.reset(Model::CreateFromOBJ("backObj1", true));
	modelBackObj2.reset(Model::CreateFromOBJ("backObj2", true));
	modelBackObj3.reset(Model::CreateFromOBJ("backObj3", true));
	modelEggShell.reset(Model::CreateFromOBJ("eggShell", true));
	modelParticle.reset(Model::CreateFromOBJ("player", true));
	modelExplosionLeftParticle.reset(Model::CreateFromOBJ("eggShell", true));
	modelExplosionRightParticle.reset(Model::CreateFromOBJ("eggShell", true));
	modelExplosionUpParticle.reset(Model::CreateFromOBJ("eggShell", true));
	modelThornStick.reset(Model::CreateFromOBJ("thornStick", true));
	modelFire.reset(Model::CreateFromOBJ("gimmick", true));
	modelStar.reset(Model::CreateFromOBJ("star", true));
	modelBluePlayer.reset(Model::CreateFromOBJ("bluePlayer", true));
	modelRedPlayer.reset(Model::CreateFromOBJ("redPlayer", true));

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
	else if (resourcesName == ResourcesName::soundData4)
	{
		return soundData4;
	}
	else if (resourcesName == ResourcesName::soundData5)
	{
		return soundData5;
	}
	else if (resourcesName == ResourcesName::soundData6)
	{
		return soundData6;
	}
	else if (resourcesName == ResourcesName::soundData7)
	{
		return soundData7;
	}
	else if (resourcesName == ResourcesName::soundData8)
	{
		return soundData8;
	}
	else if (resourcesName == ResourcesName::soundData9)
	{
		return soundData9;
	}
	else if (resourcesName == ResourcesName::soundData10)
	{
		return soundData10;
	}
	else if (resourcesName == ResourcesName::soundData11)
	{
		return soundData11;
	}
	else if (resourcesName == ResourcesName::soundData12)
	{
		return soundData12;
	}
	else if (resourcesName == ResourcesName::soundData13)
	{
		return soundData13;
	}
	else if (resourcesName == ResourcesName::soundData14)
	{
		return soundData14;
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
		return modelPlayer.get();
	}
	else if (resourcesName == ResourcesName::modelCloud)
	{
		return modelCloud.get();
	}
	else if (resourcesName == ResourcesName::modelStageBox)
	{
		return modelStageBox.get();
	}
	else if (resourcesName == ResourcesName::modelEnemy)
	{
		return modelEnemy.get();
	}
	else if (resourcesName == ResourcesName::modelRedBlock)
	{
		return modelRedBlock.get();
	}
	else if (resourcesName == ResourcesName::modelBlueBlock)
	{
		return modelBlueBlock.get();
	}
	else if (resourcesName == ResourcesName::modelWireBlock)
	{
		return modelWireBlock.get();
	}
	else if (resourcesName == ResourcesName::modelGoal)
	{
		return modelGoal.get();
	}
	else if (resourcesName == ResourcesName::modelSignboard)
	{
		return modelSignboard.get();
	}
	else if (resourcesName == ResourcesName::modelSignboardA)
	{
		return modelSignboardA.get();
	}
	else if (resourcesName == ResourcesName::modelSignboardSpace)
	{
		return modelSignboardSpace.get();
	}
	else if (resourcesName == ResourcesName::modelBackObj1)
	{
		return modelBackObj1.get();
	}
	else if (resourcesName == ResourcesName::modelBackObj2)
	{
		return modelBackObj2.get();
	}
	else if (resourcesName == ResourcesName::modelBackObj3)
	{
		return modelBackObj3.get();
	}
	else if (resourcesName == ResourcesName::modelEggShell)
	{
		return modelEggShell.get();
	}
	else if (resourcesName == ResourcesName::modelParticle)
	{
		return modelParticle.get();
	}
	else if (resourcesName == ResourcesName::modelExplosionLeftParticle)
	{
		return modelExplosionLeftParticle.get();
	}
	else if (resourcesName == ResourcesName::modelExplosionRightParticle)
	{
		return modelExplosionRightParticle.get();
	}
	else if (resourcesName == ResourcesName::modelExplosionUpParticle)
	{
		return modelExplosionUpParticle.get();
	}
	else if (resourcesName == ResourcesName::modelThornStick)
	{
		return modelThornStick.get();
	}
	else if (resourcesName == ResourcesName::modelFire)
	{
		return modelFire.get();
	}
	else if (resourcesName == ResourcesName::modelStar)
	{
		return modelStar.get();
	}
	else if (resourcesName == ResourcesName::modelBluePlayer)
	{
		return modelBluePlayer.get();
	}
	else if (resourcesName == ResourcesName::modelRedPlayer)
	{
		return modelRedPlayer.get();
	}
	else
	{
		return model.get();
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
