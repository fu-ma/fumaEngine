#pragma once
#include<array>

#include "GameSceneManager.h"
#include"ModelObj.h"
#include"Model.h"
#include <DirectXMath.h>
#include "Sprite.h"
#include"LightGroup.h"
#include "Player.h"
#include"DebugCamera.h"
#include"FBXObject3d.h"
#include"DebugText.h"
#include "TouchableObject.h"
#include"Collision.h"
#include"Enemy.h"
#include"Firebar.h"
#include"Particle.h"
#include<stdlib.h>
#include<time.h>
#include"CountDown.h"
#include"Resources.h"
#include"Json.h"
#include"ThornStick.h"
#include"Star.h"
#include "Engine/base/Input/Input.h"
#include "Audio.h"
#include"FbxLoader.h"
#include<memory>
#include"PostEffect.h"
#include"MultipleRender.h"
#include"MultipleTexture.h"
#include"Engine/base/Input/Controller.h"
#include"Resources.h"
#include"Json.h"
#include"ParticleManager.h"
#include"WholeScene.h"
#include"DirectXApp.h"


class GameSceneManager;

class GameSceneManagerState
{
public:
	virtual void Initialize(GameSceneManager *pEngine, DebugCamera * camera, Audio *audio, Fps *fps) = 0;
	virtual void Update(GameSceneManager *pEngine, Audio *audio, DebugText* debugText, LightGroup *lightGroup, DebugCamera *camera, Fps *fps) = 0;
	virtual void Draw(GameSceneManager *pEngine, DirectXApp *common, DebugText *debugText) = 0;

private:
private: // �G�C���A�X
// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

protected:

	static const int X_MAX = 100;
	static const int Y_MAX = 10;
	static const int GIMMICK_NUM = 100;

	//��������
	int gameTimer = 10980;
};

