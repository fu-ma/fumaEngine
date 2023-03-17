#pragma once
#include"Sprite.h"
#include"Audio.h"
#include"Model.h"
#include"FBXLoader.h"

enum class ResourcesName
{
	soundData1,
	soundData2,
	soundData3,
	modelPlayer,
	modelCloud,
	modelStageBox,
	modelEnemy,
	modelRedBlock,
	modelBlueBlock,
	modelWireBlock,
	modelGoal,
	modelJumpSignA,
	modelJumpSignSpace,
	modelWallSignA,
	modelWallSignSpace,
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
private:
	SoundData soundData1;
	SoundData soundData2;
	SoundData soundData3;

	//�v���C���[
	Model *modelPlayer;

	//�`���[�g���A���p�̊Ŕ�
	Model *modelJumpSignA;
	Model *modelJumpSignSpace;
	Model *modelWallSignA;
	Model *modelWallSignSpace;

	//�_
	Model *modelCloud;

	//�X�e�[�W�u���b�N
	Model *modelStageBox;
	//�G
	Model *modelEnemy;

	//��莞�ԂŐ؂�ւ�鏰
	Model *modelRedBlock;
	Model *modelBlueBlock;
	Model *modelWireBlock;

	//�S�[��
	Model *modelGoal;

	//�w�i�p�̌��h�����悭���邽�߂̂���
	Model *modelBackObj1;
	Model *modelBackObj2;
	Model *modelBackObj3;

	//�G�t�F�N�g�p�̗��̊k
	Model *modelEggShell;

	//�v���C���[�̈ړ����̃p�[�e�B�N��
	Model *modelParticle;

	//�ǃL�b�N���̃p�[�e�B�N��
	Model *modelExplosionLeftParticle;
	Model *modelExplosionRightParticle;

	//�W�����v���̃p�[�e�B�N��
	Model *modelExplosionUpParticle;

	//�Ƃ�����_�p
	Model *modelThornStick;
	//�ݒ肵�����\�[�X��ǂݍ��܂Ȃ������ꍇ�G���[���o��悤�ɂ���
	SoundData sound;
	Model *model;

	//egg�p�̃��f��
	FBXModel *modelEgg;

	//GameClear�p�̃��f��
	FBXModel *modelStageClear;
private:
	Resources() = default;
	~Resources() = default;
};

