#pragma once
#include "GameSceneManagerState.h"

class SelectScene : public GameSceneManagerState
{
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
private:
	Sprite *backGround = nullptr;
	Sprite *Stage1Sprite = nullptr;
	Sprite *Stage2Sprite = nullptr;
	Sprite *Stage3Sprite = nullptr;
	Sprite *Stage4Sprite = nullptr;
	Sprite *Stage5Sprite = nullptr;
	Sprite *playerIconSprite = nullptr;

	//�_
	ModelObj *cloud[10] = { nullptr };
	XMFLOAT3 cloudPos[10] = {};

	//�v���C���[
	Player *objPlayer = nullptr;

	//�X�e�[�W�u���b�N
	ModelObj *titleStageBox[6][24] = { nullptr };
	XMFLOAT3 stageBoxPos[6][24];

	double selectPos;
	double selectMoveTime;
	const int selectInterval = 512;

	//�X�e�[�W�I���̔ԍ��̃T�C�Y
	double stage1SpriteSize;
	double stage2SpriteSize;
	double stage3SpriteSize;
	double stage4SpriteSize;
	double stage5SpriteSize;
	const int stageSpriteMinSize = 256;
	const int stageSpriteMaxSize = 512;

	//�X�e�[�W�u���b�N�̈ړ���
	float moveStageBlockSpeed;

	//�^�C�g������X�e�[�W�Z���N�g�ɍs�����Ƃ��ɃW�����v��h��
	bool stageSelectJumpFlag;

	//�X�e�[�W�I����ʂ̔z��
	const int selectMap[6][24] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	};
public:
	SelectScene(const int stageNum = 0) {  }
	~SelectScene()
	{
		delete backGround;
		backGround = nullptr;
		delete Stage1Sprite;
		Stage1Sprite = nullptr;
		delete Stage2Sprite;
		Stage2Sprite = nullptr;
		delete Stage3Sprite;
		Stage3Sprite = nullptr;
		delete Stage4Sprite;
		Stage4Sprite = nullptr;
		delete Stage5Sprite;
		Stage5Sprite = nullptr;
		delete playerIconSprite;
		playerIconSprite = nullptr;
		for (int i = 0; i < 10; i++)
		{
			delete cloud[i];
			cloud[i] = nullptr;
		}
		for (int y = 0; y < 6; y++)
		{
			for (int x = 0; x < 24; x++)
			{
				delete titleStageBox[y][x];
				titleStageBox[y][x] = nullptr;
			}
		}
		delete objPlayer;
		objPlayer = nullptr;
	}
	void Initialize(GameSceneManager *pEngine, DebugCamera *camera, Audio *audio, Fps *fps);
	void Update(GameSceneManager *pEngine, Audio *audio, DebugText *debugText, LightGroup *lightGroup, DebugCamera *camera, Fps *fps);
	void Draw(GameSceneManager *pEngine, DirectXApp *common, DebugText *debugText);
};