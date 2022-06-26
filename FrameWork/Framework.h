#pragma once
#include"WindowAPI.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "DebugText.h"
#include "DebugCamera.h"
#include "Audio.h"
#include "ParticleManager.h"
#include"ModelObj.h"
#include"LightGroup.h"
#include"FbxLoader.h"
#include"FBXObject3d.h"
#include<memory>
#include"PostEffect.h"
#include"MultipleRender.h"
#include"MultipleTexture.h"

/// <summary>
/// �t���[�����[�N
/// </summary>
class Framework
{
protected:
	using WinPtr = std::unique_ptr<WinApp>;
	using CommonPtr = std::unique_ptr<DirectXCommon>;
	using AudioPtr = std::unique_ptr<Audio>;
	using DebugCamPtr = std::unique_ptr<DebugCamera>;
	using LightGroupPtr = std::unique_ptr<LightGroup>;
	using PostEffectPtr = std::unique_ptr<MultipleTexture>;

	enum class GameSceneNo
	{
		Title,
		GamePlay,
		End,
	};

public:

	/// <summary>
	/// ���s
	/// </summary>
	void GameRun();

	/// <summary>
	/// �ŏ�����������
	/// </summary>
	virtual void staticInit();

	/// <summary>
	/// ������
	/// </summary>
	virtual void Init();

	/// <summary>
	/// ���t���[���X�V
	/// </summary>
	virtual bool Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	virtual void Draw() = 0;

	/// <summary>
	/// �I������
	/// </summary>
	virtual void SceneDelete()
	{
#pragma region �������
		//FBX�̉������
		FbxLoader::GetInstance()->Finalize();

		//XAudio2���
		Audio::xAudio2.Reset();
		//WindowsAPI�̏I������
		winApp->Finalize();
	};

	const int &SceneTimeGetter() { return SceneTime; }
protected:
	WinPtr winApp;
	Input* input;
	CommonPtr common;

	AudioPtr audio;
	DebugText *debugText;
	ParticleManager *particleMan;
	DebugCamPtr camera;
	LightGroupPtr lightGroup;
	PostEffectPtr postEffect;

	//���݂̃V�[���̔ԍ�
	int SceneNo = static_cast<int>(GameSceneNo::GamePlay);
	//�������̂��߂̌v��
	int SceneTime = 0;
};

