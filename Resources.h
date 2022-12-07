#pragma once
#include "Singleton.h"
#include"Sprite.h"
#include"Audio.h"
#include"Model.h"

class Resources : public Singleton<Resources>
{
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	friend class Singleton<Resources>;

public:
	static void StaticInit(Audio *audio);

public:
	static SoundData soundData1;
	static SoundData soundData2;
	static SoundData soundData3;

	//�v���C���[
	static Model *modelPlayer;

	//�_
	static Model *modelCloud;

	//�X�e�[�W�u���b�N
	static Model *modelStageBox;
	//�G
	static Model *modelEnemy;

	//��莞�ԂŐ؂�ւ�鏰
	static Model *modelRedBlock;
	static Model *modelBlueBlock;
	static Model *modelWireBlock;

	//�S�[��
	static Model *modelGoal;

protected:
	Resources();
	virtual ~Resources();
};

