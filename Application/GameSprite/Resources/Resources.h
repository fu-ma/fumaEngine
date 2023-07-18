#pragma once
#include"Sprite.h"
#include"Audio.h"
#include"Model.h"
#include"FBXLoader.h"

enum ResourcesNo
{
	backGround3 = 1,
	titleSprite,
	StageClear,
	skull,
	e1,
	Stage1,
	Stage2,
	Stage3,
	Stage4,
	Stage5,
	CountStart,
	playerIcon,
	GameOver,
	title,
	restart,
	Return,
	ClearStage,
	fadeIN,
	fadeOUT,
	TitleUI,
	ESCUI,
	HOMEUI,
	egg,
	startToGoal,
	goal,
	starSprite,
	noStarSprite,
	gauge,
	ButtonA,
	ButtonSpace,
	tutorial1,
	tutorial2,
};

enum class ResourcesName
{
	soundData1,
	soundData2,
	soundData3,
	soundData4,
	soundData5,
	soundData6,
	soundData7,
	soundData8,
	soundData9,
	soundData10,
	soundData11,
	soundData12,
	soundData13,
	soundData14,
	modelPlayer,
	modelCloud,
	modelStageBox,
	modelEnemy,
	modelThornEnemy,
	modelRedBlock,
	modelBlueBlock,
	modelWireBlock,
	modelGoal,
	modelSignboard,
	modelSignboardA,
	modelSignboardSpace,
	modelBackObj1,
	modelBackObj2,
	modelBackObj3,
	modelEggShell,
	modelParticle,
	modelExplosionLeftParticle,
	modelExplosionRightParticle,
	modelExplosionUpParticle,
	modelEgg,
	modelStageClear,
	modelThornStick,
	modelFire,
	modelStar,
	modelBluePlayer,
	modelRedPlayer,
	modelZyugemu,
};

class Resources
{
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public: // �ÓI�����o�ϐ�
	static Resources *GetInstance();

public:
	void StaticInit(Audio *audio);
	SoundData &GetSoundData(ResourcesName resourcesName);
	Model *GetModel(ResourcesName resourcesName);
	FBXModel *GetFBXModel(ResourcesName resourcesName);
public:
	const float soundData1Bol = 0.05f;
	const float soundData2Bol = 0.05f;
	const float soundData3Bol = 0.05f;
	const float soundData4Bol = 0.05f;
	const float soundData5Bol = 0.2f;
	const float soundData6Bol = 0.05f;
	const float soundData7Bol = 0.05f;
	const float soundData8Bol = 0.08f;
	const float soundData9Bol = 0.03f;
	const float soundData10Bol = 0.05f;
	const float soundData11Bol = 0.05f;
	const float soundData12Bol = 0.05f;
	const float soundData13Bol = 0.05f;
	const float soundData14Bol = 0.05f;
private:
	SoundData soundData1;
	SoundData soundData2;
	SoundData soundData3;
	SoundData soundData4;
	SoundData soundData5;
	SoundData soundData6;
	SoundData soundData7;
	SoundData soundData8;
	SoundData soundData9;
	SoundData soundData10;
	SoundData soundData11;
	SoundData soundData12;
	SoundData soundData13;
	SoundData soundData14;

	//�v���C���[
	std::unique_ptr<Model> modelPlayer;
	std::unique_ptr<Model> modelBluePlayer;
	std::unique_ptr<Model> modelRedPlayer;

	//�`���[�g���A���p�̊Ŕ�
	std::unique_ptr<Model> modelSignboard;
	std::unique_ptr<Model> modelSignboardA;
	std::unique_ptr<Model> modelSignboardSpace;

	//�W���Q��
	std::unique_ptr<Model> modelZyugemu;
	//�_
	std::unique_ptr<Model> modelCloud;

	//�X�e�[�W�u���b�N
	std::unique_ptr<Model> modelStageBox;
	//�G
	std::unique_ptr<Model> modelEnemy;
	std::unique_ptr<Model> modelThornEnemy;

	//��莞�ԂŐ؂�ւ�鏰
	std::unique_ptr<Model> modelRedBlock;
	std::unique_ptr<Model> modelBlueBlock;
	std::unique_ptr<Model> modelWireBlock;

	//�S�[��
	std::unique_ptr<Model> modelGoal;

	//�w�i�p�̌��h�����悭���邽�߂̂���
	std::unique_ptr<Model> modelBackObj1;
	std::unique_ptr<Model> modelBackObj2;
	std::unique_ptr<Model> modelBackObj3;

	//�G�t�F�N�g�p�̗��̊k
	std::unique_ptr<Model> modelEggShell;

	//�v���C���[�̈ړ����̃p�[�e�B�N��
	std::unique_ptr<Model> modelParticle;

	//�ǃL�b�N���̃p�[�e�B�N��
	std::unique_ptr<Model> modelExplosionLeftParticle;
	std::unique_ptr<Model> modelExplosionRightParticle;

	//�W�����v���̃p�[�e�B�N��
	std::unique_ptr<Model> modelExplosionUpParticle;

	//�΂̋ʂ̃��f��
	std::unique_ptr<Model> modelFire;
	
	//�Ƃ�����_�p
	std::unique_ptr<Model> modelThornStick;

	//���p�̃��f��
	std::unique_ptr<Model> modelStar;

	//�ݒ肵�����\�[�X��ǂݍ��܂Ȃ������ꍇ�G���[���o��悤�ɂ���
	SoundData sound;
	std::unique_ptr<Model> model;

	//egg�p�̃��f��
	FBXModel *modelEgg;

	//GameClear�p�̃��f��
	FBXModel *modelStageClear;
private:
	Resources() = default;
	~Resources() = default;
};

