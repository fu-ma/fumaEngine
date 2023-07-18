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
	static const int CLOUD_NUM = 10;
	static const int TITLE_STAGE_X = 24;
	static const int TITLE_STAGE_Y = 6;
	static const int backObjNum = 10;
	static const int backGroundObjRandMin = 5;
	static const int backGroundObjRandMax = 14;
private:
	std::unique_ptr<Sprite> backGround;
	std::unique_ptr<Sprite> titleSprite;
	std::unique_ptr<Sprite> fadeOut;
	std::unique_ptr<Sprite> fadeIn;
	std::unique_ptr<Sprite> titleUI;

	//�_
	std::array<std::unique_ptr<ModelObj>, CLOUD_NUM> cloud;
	std::array<XMFLOAT3, CLOUD_NUM> cloudPos;
	float cloudSpeed;

	//�v���C���[
	std::unique_ptr<Player> objPlayer;

	//player�̓������~���������]������
	float playerRot;
	float playerRotSpeed;

	//�X�e�[�W�u���b�N
	std::array<std::array<std::unique_ptr<ModelObj>, TITLE_STAGE_X> , TITLE_STAGE_Y> titleStageBox;
	std::array<std::array<XMFLOAT3, TITLE_STAGE_X>, TITLE_STAGE_Y> stageBoxPos;
	float stageBoxSpeed;

	//�w�i�p�̌��h���p�I�u�W�F�N�g
	std::array<std::unique_ptr<ModelObj>, backObjNum> backObj1;
	std::array<std::unique_ptr<ModelObj>, backObjNum> backObj2;
	std::array<std::unique_ptr<ModelObj>, backObjNum> backObj3;
	std::array<XMFLOAT3, backObjNum> backObj1Pos;
	std::array<XMFLOAT3, backObjNum> backObj2Pos;
	std::array<XMFLOAT3, backObjNum> backObj3Pos;
	std::array<float, backObjNum> backObj1Size;
	std::array<float, backObjNum> backObj2Size;
	std::array<float, backObjNum> backObj3Size;
	float backObj1Speed;
	float backObj2Speed;
	float backObj3Speed;

	//�J�n���̃t�F�C�h�C���p�ϐ�
	double fadeInSizeX;
	double fadeInSizeY;
	double fadeInT;
	bool fadeInFlag;
	float fadeInSpeed;

	//�J�n���̃t�F�C�h�A�E�g�p�ϐ�
	double fadeOutSizeX;
	double fadeOutSizeY;
	double fadeOutT;
	bool fadeOutFlag;
	float fadeOutSpeed;

	//�Z���N�g��ʂɍs�������m�F���邽�߂̃t���O
	bool goSelectFlag;

	//UI�p�J�E���g
	int titleUICount;

	//�X�e�[�W�I����ʂ̔z��
	const int selectMap[TITLE_STAGE_Y][TITLE_STAGE_X] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	};
public:
	~TitleScene()
	{
	}
	TitleScene(const int stageNum = 0) { }
	void Initialize(GameSceneManager* pEngine, DebugCamera *camera, Audio *audio, Fps *fps);
	void Update(GameSceneManager *pEngine, Audio *audio, DebugText *debugText, LightGroup *lightGroup, DebugCamera *camera, Fps *fps);
	void Draw(GameSceneManager *pEngine, DirectXApp *common, DebugText *debugText);
};

