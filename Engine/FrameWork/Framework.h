#pragma once
#include"WindowAPI.h"
#include "DirectXApp.h"
#include "Engine/Input/Input.h"
#include "DebugText.h"
#include "DebugCamera.h"
#include "Audio.h"
#include "Particle.h"
#include"ModelObj.h"
#include"LightGroup.h"
#include"FbxLoader.h"
#include"FBXObject3d.h"
#include<memory>
#include"PostEffect.h"
#include"MultipleRender.h"
#include"MultipleTexture.h"
#include"Engine/Input/Controller.h"
#include"ImguiCommon.h"
#include"Resources.h"
#include"Json.h"
#include"ParticleManager.h"

/// <summary>
/// �t���[�����[�N
/// </summary>
class Framework
{
protected:
	using WinPtr = std::unique_ptr<WinApp>;
	using CommonPtr = std::unique_ptr<DirectXApp>;
	using AudioPtr = std::unique_ptr<Audio>;
	using DebugCamPtr = std::unique_ptr<DebugCamera>;
	using LightGroupPtr = std::unique_ptr<LightGroup>;
	using PostEffectPtr = std::unique_ptr<PostEffect>;
	using MultipleTexPtr = std::unique_ptr<MultipleTexture>;
	using MultipleRenderPtr = std::unique_ptr<MultipleRender>;
	using FpsPtr = std::unique_ptr<Fps>;

	enum class GameSceneNo
	{
		Title,
		StageSelect,
		Stage1,
		Stage2,
		Stage3,
		Stage4,
		Stage5,
		GameOver,
		Clear,
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
protected:
	WinPtr winApp;
	Input *input;
	Controller *controller;
	CommonPtr common;

	AudioPtr audio;
	DebugText *debugText;
	DebugCamPtr camera;
	LightGroupPtr lightGroup;
	MultipleTexPtr postEffect;
	FpsPtr fps;
	Resources *resources;
	Json *json;
	ParticleManager *particleMan;
};

