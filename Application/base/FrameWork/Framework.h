#pragma once
#include"WindowAPI.h"
#include "DirectXApp.h"
#include"ImguiCommon.h"
#include "GameSceneManager.h"
#include"WholeScene.h"
#include "Engine/base/Input/Input.h"
#include"Engine/base/Input/Controller.h"

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
	using InputPtr = std::shared_ptr<Input>;
public:

	/// <summary>
	/// ���s
	/// </summary>
	void GameRun();

	/// <summary>
	/// �ŏ�����������
	/// </summary>
	void staticInit();

	/// <summary>
	/// ������
	/// </summary>
	void Init();

	/// <summary>
	/// ���t���[���X�V
	/// </summary>
	bool Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();

	/// <summary>
	/// �I������
	/// </summary>
	void SceneDelete()
	{
#pragma region �������
		//XAudio2���
		Audio::xAudio2.Reset();
		//�X�v���C�g�̉������
		debugText->deleteSprite();
		//GameScene
		delete manager;
		manager = nullptr;

		//FBX�̉������
		FbxLoader::GetInstance()->Finalize();

		//XAudio2���
		Audio::xAudio2.Reset();
		//WindowsAPI�̏I������
		winApp->Finalize();
	};
private:
	WinPtr winApp;
	Input *input;
	Controller *controller;
	CommonPtr common;

	AudioPtr audio;
	DebugText *debugText;
	DebugCamPtr camera;
	LightGroupPtr lightGroup;
	PostEffectPtr postEffect;
	FpsPtr fps;
	Resources *resources;
	Json *json;
	ParticleManager *particleMan;

	GameSceneManager *manager;
	WholeScene *wholeScene;
};

