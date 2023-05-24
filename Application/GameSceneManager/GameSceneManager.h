#pragma once
#include"Framework.h"
#include"GameSceneManagerState.h"

class GameSceneManagerState;

class GameSceneManager
{
public:
	//�R���X�g���N�^
	GameSceneManager();
	//�f�X�g���N�^
	~GameSceneManager();

	void Initialize(DebugCamera *camera, Audio *audio, Fps *fps);
	void Update(DebugText *debugText, Audio *audio, LightGroup *lightGroup, DebugCamera *camera, Fps *fps);
	void Draw(DirectXApp *common, DebugText *debugText);

	void changeState(GameSceneManagerState* newState);
	void newState();
	void StateDelete();
private:
	GameSceneManagerState *state;
	//�ۑ��p
	GameSceneManagerState *keepState;

	//�폜���邩�ǂ����̃t���O
	bool deleteFlag;
	//�������������ʂ������̃t���O
	bool inputFlag;
};

