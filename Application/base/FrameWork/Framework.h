#pragma once
#include"WindowAPI.h"
#include "DirectXApp.h"
#include"ImguiCommon.h"
#include "GameSceneManager.h"
#include"WholeScene.h"
#include "Engine/base/Input/Input.h"
#include"Engine/base/Input/Controller.h"

/// <summary>
/// フレームワーク
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
	/// 実行
	/// </summary>
	void GameRun();

	/// <summary>
	/// 最初だけ初期化
	/// </summary>
	void staticInit();

	/// <summary>
	/// 初期化
	/// </summary>
	void Init();

	/// <summary>
	/// 毎フレーム更新
	/// </summary>
	bool Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// 終了処理
	/// </summary>
	void SceneDelete()
	{
#pragma region 解放処理
		//XAudio2解放
		Audio::xAudio2.Reset();
		//スプライトの解放処理
		debugText->deleteSprite();
		//GameScene
		delete manager;
		manager = nullptr;

		//FBXの解放処理
		FbxLoader::GetInstance()->Finalize();

		//XAudio2解放
		Audio::xAudio2.Reset();
		//WindowsAPIの終了処理
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

