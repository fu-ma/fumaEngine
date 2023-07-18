#pragma once
#include "GameSceneManagerState.h"
#include"Json.h"
#include"GameControl.h"
#include"GameCollision.h"

class GamePlayScene : public GameSceneManagerState
{
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

private:
	enum class GaugeStatus
	{
		PUSHOK,
		PUSHED,
	};

	enum class StageSet
	{
		BLOCK = 1,
		ENEMY,
		FIREBAR,
		REDBLOCK,
		BLUEBLOCK,
		JUMPBORD,
		WALLKICKBORD,
		THORNSTICK,
		STAR,
		GOAL,
		ZYUGEMU,
	};

private:
	//�Q�[���p�̑���̃N���X
	std::shared_ptr <GameControl> gameControl;

	//�X�v���C�g
	std::unique_ptr <Sprite> backGround;
	std::unique_ptr <Sprite> goTitle;
	std::unique_ptr <Sprite> reStart;
	std::unique_ptr <Sprite> Return;
	std::unique_ptr <Sprite> playerIconSprite;
	std::unique_ptr <Sprite> ClearStageSprite;
	std::unique_ptr <Sprite> GameOver;
	std::unique_ptr <Sprite> fadeOut;
	std::unique_ptr <Sprite> fadeIn;
	std::unique_ptr <Sprite> escUI;
	std::unique_ptr <Sprite> homeUI;
	std::unique_ptr <Sprite> eggSprite;
	std::unique_ptr <Sprite> startToGoal;
	std::unique_ptr <Sprite> goalSprite;
	std::array<std::unique_ptr <Sprite>, 17> gaugeSprite;
	std::unique_ptr <Sprite> buttonA;
	std::unique_ptr <Sprite> buttonSpace;
	std::array<std::unique_ptr <Sprite>, 2> tutorialSprite;
	//�X�v���C�g�T�C�Y
	XMFLOAT2 eggSpriteSize;
	XMFLOAT2 startToGoalSize;
	XMFLOAT2 goalSpriteSize;

	//�Q�[�W�p�̃^�C��
	float gaugeSpriteTime;
	//�Q�[�W�p
	GaugeStatus gaugeStatus;
	const int GaugeSpriteMaxNum = 17;

	//�_
	std::array<std::unique_ptr<ModelObj>, 10> cloud;
	std::array<XMFLOAT3, 10> cloudPos = {};
	std::array<float, 10> cloudSpeed;

	//�G
	std::vector<std::unique_ptr<Enemy>> enemy;

	//�W���Q��
	std::vector<std::unique_ptr<Zyugemu>> zyugemu;

	//�X�^�[�i���W���j
	std::vector<std::unique_ptr<Star>> star;
	//�Ƃ�����_
	std::vector<std::unique_ptr<ThornStick>> thornStick;

	//�v���C���[
	std::unique_ptr<Player> objPlayer;

	//�`���[�g���A���p�̊Ŕ�
	std::array<std::unique_ptr<ModelObj>, 2> objSignboard;

	//�X�e�[�W�u���b�N
	std::vector<std::unique_ptr<ModelObj>> objStageBox;

	//�M�~�b�N
	std::vector<std::unique_ptr<Firebar>> fire;

	XMFLOAT3 gimmickCenter[GIMMICK_NUM];
	int gimmickCenterNum;

	//��莞�ԂŐ؂�ւ�鏰
	std::vector<std::unique_ptr<ModelObj>> objRedBlock;
	std::vector<std::unique_ptr<ModelObj>> objBlueBlock;

	//�S�[��
	std::unique_ptr<ModelObj> objGoal;

	//�w�i�p�̌��h���p�I�u�W�F�N�g
	static const int backObjNum = 10;
	std::array<std::unique_ptr<ModelObj>, backObjNum> backObj1;
	std::array<std::unique_ptr<ModelObj>, backObjNum> backObj2;
	std::array<std::unique_ptr<ModelObj>, backObjNum> backObj3;
	std::array<XMFLOAT3, backObjNum> backObj1Pos;
	std::array<XMFLOAT3, backObjNum> backObj2Pos;
	std::array<XMFLOAT3, backObjNum> backObj3Pos;
	std::array<float, backObjNum> backObj1Size;
	std::array<float, backObjNum> backObj2Size;
	std::array<float, backObjNum> backObj3Size;

	//�p�[�e�B�N��
	std::unique_ptr<Particle> playerParticle;

	ParticleManager *particleMan = nullptr;

	//�J�E���g�_�E���N���X
	std::unique_ptr<CountDown> countDown;

	//�Q�[���I�[�o�[�t���O
	bool gameOverFlag;
	double skullSizeX;
	double skullSizeY;
	double gameOverTime;

	//�ꎞ��~
	bool stopFlag;
	double stopMoveTime;
	int stopNum;

	//�N���A�������̃t���O
	bool clearStopFlag;

	//�T�u���j���[�p�̉摜�T�C�Y�Ȃǂ̕ϐ�
	double goTitleSpriteSize;
	double reStartSpriteSize;
	double ReturnSpriteSize;
	const int stopSpriteMaxSize = 128;
	const int stopSpriteMinSize = 64;

	bool goTitleFlag;
	bool reStartFlag;
	bool clearFlag;

	//�G�̍s���p�^�[����؂�ւ��邽�߂̓G�̃J�E���g
	int enemyNum;

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

	//���삵�Ă���̂��L�[�{�[�h���R���g���[���[�����肷��t���O�ifalse�ŃL�[�{�[�h�Atrue�ŃR���g���[���[�j
	bool operationButton;
	std::array<bool, 2> operationDrawButton;
	//�����Ȃ��Ȃ�t���O
	bool tutorialMoveFlag;

	//�^�C�}�[�̈ʒu
	double timerPosX;
	double timerPosY;
	double timerMoveT;
	double timerSize;
	double timerSizeT;
	double timerEmphasisSize;
	double timerEmphasisSizeT;

	//�X�^�[�̈ʒu���\�[�g����p�̕ϐ�
	std::array<float, 3> starPosX;
	float tmp;
	int swapI;
	XMFLOAT3 starToget;
	XMFLOAT3 oldStarToGet;

	//��ʃV�F�C�N�p�̕ϐ�
	XMFLOAT3 enemyHitShakePos;
	bool enemyHitShakeFlag;
	int enemyHitShakeTimer;

	//�X�e�[�W�̔z��
	std::array<std::array<int, X_MAX>, Y_MAX> mapData;

	//�v���C���[�����i����p�j
	int totalPlayer;
	//�X�e�[�W�I��p�̐����i����p�j
	int selectNum;

public:
	GamePlayScene(const int stageNum = 0) { }
	void Initialize(GameSceneManager *pEngine, DebugCamera *camera, Audio *audio, Fps *fps);
	void Update(GameSceneManager *pEngine, Audio *audio, DebugText *debugText, LightGroup *lightGroup, DebugCamera * camera, Fps *fps);
	void Draw(GameSceneManager *pEngine, DirectXApp *common, DebugText *debugText);
	~GamePlayScene()
	{
	}

private:
#pragma region �X�e�[�W�Z�b�g
	void StageSet(const std::array<std::array<int, X_MAX>, Y_MAX> Map, const int stageNum, Audio *audio, Fps *fps);

#pragma region ���ʍX�V�֐�
	void StageUpdate(GameSceneManager *pEngine, Audio *audio, DebugText *debugText, LightGroup *lightGroup, DebugCamera *camera, Fps *fps);

#pragma region ���ʕ`��֐�
	void StageDraw(DirectXApp* common,DebugText *debugText);
};

