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

	//雲
	ModelObj *cloud[10] = { nullptr };
	XMFLOAT3 cloudPos[10] = {};

	//プレイヤー
	Player *objPlayer = nullptr;

	//playerの動きが欲しいから回転させる
	float playerRot;

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

	//開始時のフェイドイン用変数
	double fadeInSizeX;
	double fadeInSizeY;
	double fadeInT;
	bool fadeInFlag;

	//開始時のフェイドアウト用変数
	double fadeOutSizeX;
	double fadeOutSizeY;
	double fadeOutT;
	bool fadeOutFlag;

	//セレクト画面に行くかを確認するためのフラグ
	bool goSelectFlag;

	//UI用カウント
	int titleUICount;

	//ステージ選択画面の配列
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

