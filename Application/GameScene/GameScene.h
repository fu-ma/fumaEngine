#pragma once
#include <DirectXMath.h>
#include"LightGroup.h"
#include"Framework.h"
#include "GameSceneManager.h"
#include"WholeScene.h"

class GameScene : public Framework
{
private: // エイリアス
// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
	using ObjPtr = std::unique_ptr<ModelObj>;
	using ModelPtr = std::unique_ptr<Model>;
	using SpritePtr = std::unique_ptr<Sprite>;

private:
	GameSceneManager *manager;
	WholeScene *wholeScene;
public:
	GameScene() {};
	void SceneDelete() override
	{
#pragma region 解放処理
		//XAudio2解放
		Audio::xAudio2.Reset();
		//スプライトの解放処理
		debugText->deleteSprite();
		//GameScene
		delete manager;
		manager = nullptr;

		//基底クラス解放処理
		Framework::SceneDelete();
	};

	void staticInit() override;
	void Init() override;
	bool Update() override;
	void Draw() override;
};

