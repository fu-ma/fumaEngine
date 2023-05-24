#pragma once
#include "GameSceneManagerState.h"
#include"ParticleManager.h"

class ClearScene : public GameSceneManagerState
{
	using XMFLOAT3 = DirectX::XMFLOAT3;
private:
	Sprite *StageClear = nullptr;
	Sprite *fadeOut = nullptr;
	Sprite *fadeIn = nullptr;
	FBXObject3d *egg = nullptr;
	FBXObject3d *gameClear = nullptr;
	ParticleManager *particleMan = nullptr;

	//�J�n���̃t�F�C�h�A�E�g�p�ϐ�
	double fadeOutSizeX;
	double fadeOutSizeY;
	double fadeOutT;
	bool fadeOutFlag;

	//�J�n���̃t�F�C�h�C���p�ϐ�
	double fadeInSizeX;
	double fadeInSizeY;
	double fadeInT;
	bool fadeInFlag;

	//�X�e�[�W�Z���N�g�ɍs���������f���邽�߂̃t���O
	bool goSelectFlag;

	//�p�[�e�B�N���p�̍��W
	XMFLOAT3 parPosLeft;
	XMFLOAT3 parPosRight;
	float saveVel;
	int particleTimer;
public:
	ClearScene(const int stageNum = 0) { }
	~ClearScene()
	{
		delete StageClear;
		StageClear = nullptr;
		delete fadeOut;
		fadeOut = nullptr;
		delete fadeIn;
		fadeIn = nullptr;
		delete egg;
		egg = nullptr;
		delete gameClear;
		gameClear = nullptr;
	}
	void Initialize(GameSceneManager *pEngine, DebugCamera *camera, Audio *audio, Fps *fps);
	void Update(GameSceneManager *pEngine, Audio *audio, DebugText *debugText, LightGroup *lightGroup, DebugCamera *camera, Fps *fps);
	void Draw(GameSceneManager *pEngine, DirectXApp *common, DebugText *debugText);
};

