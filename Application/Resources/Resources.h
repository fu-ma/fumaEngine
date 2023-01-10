#pragma once
#include"Sprite.h"
#include"Audio.h"
#include"Model.h"

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
	modelWallSignA,
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
private:
	SoundData soundData1;
	SoundData soundData2;
	SoundData soundData3;

	//�v���C���[
	Model *modelPlayer;

	//�`���[�g���A���p�̊Ŕ�
	Model *modelJumpSignA;
	Model *modelWallSignA;

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

	//�ݒ肵�����\�[�X��ǂݍ��܂Ȃ������ꍇ�G���[���o��悤�ɂ���
	SoundData sound;
	Model *model;
private:
	Resources() = default;
	~Resources() = default;
};

