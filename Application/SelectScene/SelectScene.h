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
	Sprite *fadeIN = nullptr;
	Sprite *fadeOut = nullptr;

	//雲
	ModelObj *cloud[10] = { nullptr };
	XMFLOAT3 cloudPos[10] = {};

	//パーティクル
	ParticleManager *particleMan = nullptr;

	//プレイヤー
	Player *objPlayer = nullptr;

	//ステージブロック
	ModelObj *titleStageBox[6][24] = { nullptr };
	XMFLOAT3 stageBoxPos[6][24];

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

	double selectPos;
	double selectMoveTime;
	const int selectInterval = 512;

	//ステージ選択の番号のサイズ
	double stage1SpriteSize;
	double stage2SpriteSize;
	double stage3SpriteSize;
	double stage4SpriteSize;
	double stage5SpriteSize;
	const int stageSpriteMinSize = 256;
	const int stageSpriteMaxSize = 512;

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
		delete fadeIN;
		fadeIN = nullptr;
		delete fadeOut;
		fadeOut = nullptr;
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
	void Initialize(GameSceneManager *pEngine, DebugCamera *camera, Audio *audio, Fps *fps);
	void Update(GameSceneManager *pEngine, Audio *audio, DebugText *debugText, LightGroup *lightGroup, DebugCamera *camera, Fps *fps);
	void Draw(GameSceneManager *pEngine, DirectXApp *common, DebugText *debugText);
};