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

	//スター用の回転の数値
	std::array<std::array<float, STAR_STAGE_NUM>, STAR_NUM> starTotalRot;

	//雲
	std::array<std::unique_ptr<ModelObj>, CLOUD_MAX> cloud;
	std::array<XMFLOAT3, CLOUD_MAX> cloudPos;

	//パーティクル
	ParticleManager *particleMan = nullptr;

	//プレイヤー
	std::unique_ptr<Player> objPlayer;

	//プレイヤーの回転
	double playerRotationZ;
	double afterplayerRotZ;

	//ステージブロック
	std::array<std::array<std::unique_ptr<ModelObj>, TITLE_STAGE_X>, TITLE_STAGE_Y> titleStageBox;
	std::array<std::array<XMFLOAT3, TITLE_STAGE_X>, TITLE_STAGE_Y> stageBoxPos;

	//背景用の見栄え用オブジェクト
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

	//ステージ選択の番号のサイズ
	double stage1SpriteSize;
	double stage2SpriteSize;
	double stage3SpriteSize;
	double stage4SpriteSize;
	double stage5SpriteSize;

	//ステージブロックの移動量
	float moveStageBlockSpeed;

	//タイトルからステージセレクトに行ったときにジャンプを防ぐ
	bool stageSelectJumpFlag;

	//ステージ選択を判断
	int selectNumber;

	//ステージ選択後の判断用フラグ
	bool selectedStageFlag;

	//タイトルに戻ったかを判断するフラグ
	bool goTitleFlag;
	//イージング用の座標
	double sizeX;
	double sizeY;
	double t;
	bool easingFlag;

	//開始時のフェイドアウト用変数
	double fadeOutSizeX;
	double fadeOutSizeY;
	double fadeOutT;
	bool fadeOutFlag;

	//ステージ選択画面の配列
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