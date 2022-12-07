#pragma once
#include "GameSceneManagerState.h"

class GamePlayScene : public GameSceneManagerState
{
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
private:
	Sprite *backGround = nullptr;
	Sprite *goTitle = nullptr;
	Sprite *reStart = nullptr;
	Sprite *Return = nullptr;
	Sprite *playerIconSprite = nullptr;
	Sprite *ClearStageSprite = nullptr;
	Sprite *GameOver = nullptr;

	//�_
	ModelObj *cloud[10] = { nullptr };
	XMFLOAT3 cloudPos[10] = {};

	//�G
	Enemy *enemy[Y_MAX][X_MAX] = { nullptr };

	//�v���C���[
	Player *objPlayer = nullptr;


	//�X�e�[�W�u���b�N
	ModelObj *objStageBox[Y_MAX][X_MAX] = { nullptr };
	ModelObj *titleStageBox[6][24] = { nullptr };
	XMFLOAT3 stageBoxPos[6][24];

	//�M�~�b�N
	Firebar *firebar;
	std::vector<Firebar *> fire;

	XMFLOAT3 gimmickCenter[GIMMICK_NUM];
	int gimmickCenterNum;

	//��莞�ԂŐ؂�ւ�鏰
	ModelObj *objRedBlock[Y_MAX][X_MAX];
	ModelObj *objBlueBlock[Y_MAX][X_MAX];

	//�S�[��
	ModelObj *objGoal = nullptr;

	//�p�[�e�B�N��
	Particle *playerParticle = nullptr;

	//�J�E���g�_�E���N���X
	CountDown *countDown = nullptr;

public:
	GamePlayScene(const int stageNum = 0) { this->stageNum = stageNum; }
	void Initialize(GameSceneManager *pEngine, DebugCamera *camera, Audio *audio, Fps *fps);
	void Update(GameSceneManager *pEngine, Audio *audio, DebugText *debugText, LightGroup *lightGroup, DebugCamera * camera, Fps *fps);
	void Draw(GameSceneManager *pEngine, DirectXApp *common, DebugText *debugText);

private:
#pragma region �X�e�[�W�Z�b�g
	void StageSet(const int Map[Y_MAX][X_MAX], const int stageNum, Audio *audio, Fps *fps);

#pragma region ���ʍX�V�֐�
	void StageUpdate(GameSceneManager *pEngine, Audio *audio, DebugText *debugText, LightGroup *lightGroup, DebugCamera *camera, Fps *fps);

#pragma region ���ʕ`��֐�
	void StageDraw(DirectXApp* common,DebugText *debugText);

private:
	int stageNum;
};

