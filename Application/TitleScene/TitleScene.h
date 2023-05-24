#pragma once
#include "GameSceneManagerState.h"

class TitleScene : public GameSceneManagerState
{
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
private:
	Sprite *backGround = nullptr;
	Sprite *titleSprite = nullptr;
	Sprite *fadeOut = nullptr;
	Sprite *fadeIn = nullptr;
	Sprite *titleUI = nullptr;

	//�_
	ModelObj *cloud[10] = { nullptr };
	XMFLOAT3 cloudPos[10] = {};

	//�v���C���[
	Player *objPlayer = nullptr;

	//player�̓������~���������]������
	float playerRot;

	//�X�e�[�W�u���b�N
	ModelObj *titleStageBox[6][24] = { nullptr };
	XMFLOAT3 stageBoxPos[6][24];

	//�w�i�p�̌��h���p�I�u�W�F�N�g
	static const int backObjNum = 10;
	ModelObj *backObj1[backObjNum] = { nullptr };
	ModelObj *backObj2[backObjNum] = { nullptr };
	ModelObj *backObj3[backObjNum] = { nullptr };
	XMFLOAT3 backObj1Pos[backObjNum];
	XMFLOAT3 backObj2Pos[backObjNum];
	XMFLOAT3 backObj3Pos[backObjNum];
	float backObj1Size[backObjNum];
	float backObj2Size[backObjNum];
	float backObj3Size[backObjNum];

	//�J�n���̃t�F�C�h�C���p�ϐ�
	double fadeInSizeX;
	double fadeInSizeY;
	double fadeInT;
	bool fadeInFlag;

	//�J�n���̃t�F�C�h�A�E�g�p�ϐ�
	double fadeOutSizeX;
	double fadeOutSizeY;
	double fadeOutT;
	bool fadeOutFlag;

	//�Z���N�g��ʂɍs�������m�F���邽�߂̃t���O
	bool goSelectFlag;

	//UI�p�J�E���g
	int titleUICount;

	//�X�e�[�W�I����ʂ̔z��
	const int selectMap[6][24] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	};
public:
	~TitleScene()
	{
		delete backGround;
		backGround = nullptr;
		delete titleSprite;
		titleSprite = nullptr;
		delete fadeOut;
		fadeOut = nullptr;
		delete fadeIn;
		fadeIn = nullptr;
		delete titleUI;
		titleUI = nullptr;
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
		for (int i = 0; i < backObjNum; i++)
		{
			delete backObj1[i];
			backObj1[i] = nullptr;
			delete backObj2[i];
			backObj2[i] = nullptr;
			delete backObj3[i];
			backObj3[i] = nullptr;
		}

		delete objPlayer;
		objPlayer = nullptr;
	}
	TitleScene(const int stageNum = 0) { }
	void Initialize(GameSceneManager* pEngine, DebugCamera *camera, Audio *audio, Fps *fps);
	void Update(GameSceneManager *pEngine, Audio *audio, DebugText *debugText, LightGroup *lightGroup, DebugCamera *camera, Fps *fps);
	void Draw(GameSceneManager *pEngine, DirectXApp *common, DebugText *debugText);
};

