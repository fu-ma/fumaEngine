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
	//ゲーム用の操作のクラス
	GameControl *gameControl = nullptr;

	//スプライト
	Sprite *backGround = nullptr;
	Sprite *goTitle = nullptr;
	Sprite *reStart = nullptr;
	Sprite *Return = nullptr;
	Sprite *playerIconSprite = nullptr;
	Sprite *ClearStageSprite = nullptr;
	Sprite *GameOver = nullptr;
	Sprite *fadeOut = nullptr;
	Sprite *fadeIn = nullptr;
	Sprite *escUI = nullptr;
	Sprite *homeUI = nullptr;
	Sprite *eggSprite = nullptr;
	Sprite *startToGoal = nullptr;
	Sprite *goalSprite = nullptr;

	//スプライトサイズ
	XMFLOAT2 eggSpriteSize;
	XMFLOAT2 startToGoalSize;
	XMFLOAT2 goalSpriteSize;

	//雲
	ModelObj *cloud[10] = { nullptr };
	XMFLOAT3 cloudPos[10] = {};

	//敵
	Enemy *enemy[Y_MAX][X_MAX] = { nullptr };

	//スター（収集物）
	Star *star[Y_MAX][X_MAX] = { nullptr };
	//とげこん棒
	ThornStick *thornStick[Y_MAX][X_MAX] = { nullptr };

	//プレイヤー
	Player *objPlayer = nullptr;

	//チュートリアル用の看板
	ModelObj *objJumpSignA = nullptr;
	ModelObj *objWallSignA = nullptr;

	//ステージブロック
	ModelObj *objStageBox[Y_MAX][X_MAX] = { nullptr };

	//ギミック
	Firebar *firebar;
	std::vector<Firebar *> fire;

	XMFLOAT3 gimmickCenter[GIMMICK_NUM];
	int gimmickCenterNum;

	//一定時間で切り替わる床
	ModelObj *objRedBlock[Y_MAX][X_MAX];
	ModelObj *objBlueBlock[Y_MAX][X_MAX];

	//ゴール
	ModelObj *objGoal = nullptr;

	//背景用の見栄え用オブジェクト
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

	//パーティクル
	Particle *playerParticle = nullptr;

	ParticleManager *particleMan = nullptr;

	//カウントダウンクラス
	CountDown *countDown = nullptr;

	//ゲームオーバーフラグ
	bool gameOverFlag;
	double skullSizeX;
	double skullSizeY;
	double gameOverTime;

	//一時停止
	bool stopFlag;
	double stopMoveTime;
	int stopNum;

	//クリアしたかのフラグ
	bool clearStopFlag;

	//サブメニュー用の画像サイズなどの変数
	double goTitleSpriteSize;
	double reStartSpriteSize;
	double ReturnSpriteSize;
	const int stopSpriteMaxSize = 128;
	const int stopSpriteMinSize = 64;

	bool goTitleFlag;
	bool reStartFlag;
	bool clearFlag;

	//敵の行動パターンを切り替えるための敵のカウント
	int enemyNum;

	//開始時のフェイドアウト用変数
	double fadeOutSizeX;
	double fadeOutSizeY;
	double fadeOutT;
	bool fadeOutFlag;

	//開始時のフェイドイン用変数
	double fadeInSizeX;
	double fadeInSizeY;
	double fadeInT;
	bool fadeInFlag;

	//操作しているのがキーボードかコントローラーか判定するフラグ（falseでキーボード、trueでコントローラー）
	bool operationButton;

	//タイマーの位置
	double timerPosX;
	double timerPosY;
	double timerMoveT;
	double timerSize;
	double timerSizeT;
	double timerEmphasisSize;
	double timerEmphasisSizeT;

	//スターの位置をソートする用の変数
	float starPosX[3];
	float tmp;
	int swapI;
	XMFLOAT3 starToget;

	//画面シェイク用の変数
	XMFLOAT3 enemyHitShakePos;
	bool enemyHitShakeFlag;
	int enemyHitShakeTimer;

	//ステージの配列
	int mapData[Y_MAX][X_MAX];

	//代入用の配列
	int map[Y_MAX][X_MAX];

	//プレイヤー総数（代入用）
	int totalPlayer;
	//ステージ選択用の数字（代入用）
	int selectNum;

public:
	GamePlayScene(const int stageNum = 0) { }
	void Initialize(GameSceneManager *pEngine, DebugCamera *camera, Audio *audio, Fps *fps);
	void Update(GameSceneManager *pEngine, Audio *audio, DebugText *debugText, LightGroup *lightGroup, DebugCamera * camera, Fps *fps);
	void Draw(GameSceneManager *pEngine, DirectXApp *common, DebugText *debugText);
	~GamePlayScene()
	{
		//ゲームの操作クラス
		delete gameControl;
		gameControl = nullptr;
		//スプライト
		delete backGround;
		backGround = nullptr;
		delete goTitle;
		goTitle = nullptr;
		delete reStart;
		reStart = nullptr;
		delete Return;
		Return = nullptr;
		delete playerIconSprite;
		playerIconSprite = nullptr;
		delete ClearStageSprite;
		ClearStageSprite = nullptr;
		delete GameOver;
		GameOver = nullptr;
		delete fadeOut;
		fadeOut = nullptr;
		delete fadeIn;
		fadeIn = nullptr;
		delete escUI;
		escUI = nullptr;
		delete homeUI;
		homeUI = nullptr;
		delete eggSprite;
		eggSprite = nullptr;
		delete startToGoal;
		startToGoal = nullptr;
		delete goalSprite;
		goalSprite = nullptr;

		for (int i = 0; i < 10; i++)
		{
			delete cloud[i];
			cloud[i] = nullptr;
		}
		for (int y = 0; y < Y_MAX; y++)
		{
			for (int x = 0; x < X_MAX; x++)
			{
				delete enemy[y][x];
				enemy[y][x] = nullptr;
				delete star[y][x];
				star[y][x] = nullptr;
				delete thornStick[y][x];
				thornStick[y][x] = nullptr;
				delete objStageBox[y][x];
				objStageBox[y][x] = nullptr;
				delete objRedBlock[y][x];
				objRedBlock[y][x] = nullptr;
				delete objBlueBlock[y][x];
				objBlueBlock[y][x] = nullptr;
			}
		}
		delete objPlayer;
		objPlayer = nullptr;
		delete objJumpSignA;
		objJumpSignA = nullptr;
		delete objWallSignA;
		objWallSignA = nullptr;
		delete firebar;
		firebar = nullptr;
		delete objGoal;
		objGoal = nullptr;
		for (int i = 0; i < backObjNum; i++)
		{
			delete backObj1[i];
			backObj1[i] = nullptr;
			delete backObj2[i];
			backObj2[i] = nullptr;
			delete backObj3[i];
			backObj3[i] = nullptr;
		}

		delete playerParticle;
		playerParticle = nullptr;
		delete countDown;
		countDown = nullptr;
	}

private:
#pragma region ステージセット
	void StageSet(const int Map[Y_MAX][X_MAX], const int stageNum, Audio *audio, Fps *fps);

#pragma region 共通更新関数
	void StageUpdate(GameSceneManager *pEngine, Audio *audio, DebugText *debugText, LightGroup *lightGroup, DebugCamera *camera, Fps *fps);

#pragma region 共通描画関数
	void StageDraw(DirectXApp* common,DebugText *debugText);
};

