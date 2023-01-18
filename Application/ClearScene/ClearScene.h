#pragma once
#include "GameSceneManagerState.h"

class ClearScene : public GameSceneManagerState
{
private:
	Sprite *StageClear = nullptr;
	Sprite *fadeOut = nullptr;
	Sprite *fadeIn = nullptr;

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
	}
	void Initialize(GameSceneManager *pEngine, DebugCamera *camera, Audio *audio, Fps *fps);
	void Update(GameSceneManager *pEngine, Audio *audio, DebugText *debugText, LightGroup *lightGroup, DebugCamera *camera, Fps *fps);
	void Draw(GameSceneManager *pEngine, DirectXApp *common, DebugText *debugText);
};
