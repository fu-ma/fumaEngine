#pragma once
#include"Framework.h"
#include"GameSceneManagerState.h"

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

