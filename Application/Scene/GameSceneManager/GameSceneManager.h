#pragma once
#include"GameSceneManagerState.h"
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
#include"Zyugemu.h"

class GameSceneManagerState;

class GameSceneManager
{
public:
	//コンストラクタ
	GameSceneManager();
	//デストラクタ
	~GameSceneManager();

	void Initialize(DebugCamera *camera, Audio *audio, Fps *fps);
	void Update(DebugText *debugText, Audio *audio, LightGroup *lightGroup, DebugCamera *camera, Fps *fps);
	void Draw(DirectXApp *common, DebugText *debugText);

	void changeState(GameSceneManagerState* newState);
	void newState();
	void StateDelete();
private:
	GameSceneManagerState *state;
	//保存用
	GameSceneManagerState *keepState;

	//削除するかどうかのフラグ
	bool deleteFlag;
	//初期化処理が通ったかのフラグ
	bool inputFlag;
};

