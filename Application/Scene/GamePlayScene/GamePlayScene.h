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
	//ゲーム用の操作のクラス
	std::shared_ptr <GameControl> gameControl;

	//スプライト
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
	//スプライトサイズ
	XMFLOAT2 eggSpriteSize;
	XMFLOAT2 startToGoalSize;
	XMFLOAT2 goalSpriteSize;

	//ゲージ用のタイム
	float gaugeSpriteTime;
	//ゲージ用
	GaugeStatus gaugeStatus;
	const int GaugeSpriteMaxNum = 17;

	//雲
	std::array<std::unique_ptr<ModelObj>, 10> cloud;
	std::array<XMFLOAT3, 10> cloudPos = {};
	std::array<float, 10> cloudSpeed;

	//敵
	std::vector<std::unique_ptr<Enemy>> enemy;

	//ジュゲム
	std::vector<std::unique_ptr<Zyugemu>> zyugemu;

	//スター（収集物）
	std::vector<std::unique_ptr<Star>> star;
	//とげこん棒
	std::vector<std::unique_ptr<ThornStick>> thornStick;

	//プレイヤー
	std::unique_ptr<Player> objPlayer;

	//チュートリアル用の看板
	std::array<std::unique_ptr<ModelObj>, 2> objSignboard;

	//ステージブロック
	std::vector<std::unique_ptr<ModelObj>> objStageBox;

	//ギミック
	std::vector<std::unique_ptr<Firebar>> fire;

	XMFLOAT3 gimmickCenter[GIMMICK_NUM];
	int gimmickCenterNum;

	//一定時間で切り替わる床
	std::vector<std::unique_ptr<ModelObj>> objRedBlock;
	std::vector<std::unique_ptr<ModelObj>> objBlueBlock;

	//ゴール
	std::unique_ptr<ModelObj> objGoal;

	//背景用の見栄え用オブジェクト
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

	//パーティクル
	std::unique_ptr<Particle> playerParticle;

	ParticleManager *particleMan = nullptr;

	//カウントダウンクラス
	std::unique_ptr<CountDown> countDown;

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
	std::array<bool, 2> operationDrawButton;
	//動かなくなるフラグ
	bool tutorialMoveFlag;

	//タイマーの位置
	double timerPosX;
	double timerPosY;
	double timerMoveT;
	double timerSize;
	double timerSizeT;
	double timerEmphasisSize;
	double timerEmphasisSizeT;

	//スターの位置をソートする用の変数
	std::array<float, 3> starPosX;
	float tmp;
	int swapI;
	XMFLOAT3 starToget;
	XMFLOAT3 oldStarToGet;

	//画面シェイク用の変数
	XMFLOAT3 enemyHitShakePos;
	bool enemyHitShakeFlag;
	int enemyHitShakeTimer;

	//ステージの配列
	std::array<std::array<int, X_MAX>, Y_MAX> mapData;

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
	}

private:
#pragma region ステージセット
	void StageSet(const std::array<std::array<int, X_MAX>, Y_MAX> Map, const int stageNum, Audio *audio, Fps *fps);

#pragma region 共通更新関数
	void StageUpdate(GameSceneManager *pEngine, Audio *audio, DebugText *debugText, LightGroup *lightGroup, DebugCamera *camera, Fps *fps);

#pragma region 共通描画関数
	void StageDraw(DirectXApp* common,DebugText *debugText);
};

