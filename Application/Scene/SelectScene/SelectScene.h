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
	static const int STAR_STAGE_NUM = 5;
	static const int STAR_NUM = 3;
	static const int CLOUD_MAX = 10;
	static const int TITLE_STAGE_Y = 6;
	static const int TITLE_STAGE_X = 24;
	static const int backObjNum = 10;
	const int stageSpriteMinSize = 256;
	const int stageSpriteMaxSize = 512;
	const int selectInterval = 512;
private:
	std::unique_ptr<Sprite> backGround;
	std::unique_ptr<Sprite> Stage1Sprite;
	std::unique_ptr<Sprite> Stage2Sprite;
	std::unique_ptr<Sprite> Stage3Sprite;
	std::unique_ptr<Sprite> Stage4Sprite;
	std::unique_ptr<Sprite> Stage5Sprite;
	std::unique_ptr<Sprite> playerIconSprite;
	std::unique_ptr<Sprite> fadeIN;
	std::unique_ptr<Sprite> fadeOut;
	std::array<std::array<std::unique_ptr<Sprite>, STAR_STAGE_NUM>, STAR_NUM> starSprite;
	std::array<std::array<std::unique_ptr<Sprite>, STAR_STAGE_NUM>, STAR_NUM> noStarSprite;

	//�X�^�[�p�̉�]�̐��l
	std::array<std::array<float, STAR_STAGE_NUM>, STAR_NUM> starTotalRot;

	//�_
	std::array<std::unique_ptr<ModelObj>, CLOUD_MAX> cloud;
	std::array<XMFLOAT3, CLOUD_MAX> cloudPos;

	//�p�[�e�B�N��
	ParticleManager *particleMan = nullptr;

	//�v���C���[
	std::unique_ptr<Player> objPlayer;

	//�v���C���[�̉�]
	double playerRotationZ;
	double afterplayerRotZ;

	//�X�e�[�W�u���b�N
	std::array<std::array<std::unique_ptr<ModelObj>, TITLE_STAGE_X>, TITLE_STAGE_Y> titleStageBox;
	std::array<std::array<XMFLOAT3, TITLE_STAGE_X>, TITLE_STAGE_Y> stageBoxPos;

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

	double selectPos;
	double selectMoveTime;

	//�X�e�[�W�I���̔ԍ��̃T�C�Y
	double stage1SpriteSize;
	double stage2SpriteSize;
	double stage3SpriteSize;
	double stage4SpriteSize;
	double stage5SpriteSize;

	//�X�e�[�W�u���b�N�̈ړ���
	float moveStageBlockSpeed;

	//�^�C�g������X�e�[�W�Z���N�g�ɍs�����Ƃ��ɃW�����v��h��
	bool stageSelectJumpFlag;

	//�X�e�[�W�I���𔻒f
	int selectNumber;

	//�X�e�[�W�I����̔��f�p�t���O
	bool selectedStageFlag;

	//�^�C�g���ɖ߂������𔻒f����t���O
	bool goTitleFlag;
	//�C�[�W���O�p�̍��W
	double sizeX;
	double sizeY;
	double t;
	bool easingFlag;

	//�J�n���̃t�F�C�h�A�E�g�p�ϐ�
	double fadeOutSizeX;
	double fadeOutSizeY;
	double fadeOutT;
	bool fadeOutFlag;

	//�X�e�[�W�I����ʂ̔z��
	const int selectMap[TITLE_STAGE_Y][TITLE_STAGE_X] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
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
	}
	void Initialize(GameSceneManager *pEngine, DebugCamera *camera, Audio *audio, Fps *fps);
	void Update(GameSceneManager *pEngine, Audio *audio, DebugText *debugText, LightGroup *lightGroup, DebugCamera *camera, Fps *fps);
	void Draw(GameSceneManager *pEngine, DirectXApp *common, DebugText *debugText);
};