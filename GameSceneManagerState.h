#pragma once
#include "GameSceneManager.h"
#include"ModelObj.h"
#include"Model.h"
#include <DirectXMath.h>
#include "Sprite.h"
#include"LightGroup.h"
#include"Framework.h"
#include "Player.h"
#include"DebugCamera.h"
#include "TouchableObject.h"
#include"Collision.h"
#include"Enemy.h"
#include"Firebar.h"
#include"Particle.h"
#include<stdlib.h>
#include<time.h>
#include"CountDown.h"
#include"Resources.h"

class GameSceneManager;

class GameSceneManagerState
{
public:
	virtual void Initialize(GameSceneManager *pEngine, DebugCamera * camera, Audio *audio, Fps *fps) = 0;
	virtual void Update(GameSceneManager *pEngine, Audio *audio, DebugText* debugText, LightGroup *lightGroup, DebugCamera *camera, Fps *fps) = 0;
	virtual void Draw(GameSceneManager *pEngine, DirectXApp *common, DebugText *debugText) = 0;

private:
private: // �G�C���A�X
// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
	using ObjPtr = std::unique_ptr<ModelObj>;
	using ModelPtr = std::unique_ptr<Model>;
	using SpritePtr = std::unique_ptr<Sprite>;

protected:

	static const int X_MAX = 100;
	static const int Y_MAX = 10;
	static const int GIMMICK_NUM = 100;

	struct StageData
	{
		int firebarNum;//�t�@�C�A�[�̌�
		bool direction;//�t�@�C�A�[�o�[�̉�]����
		float firebarSpeed;//�t�@�C�A�[�o�[�̉�]�X�s�[�h
	};

	StageData stageDatas[5][20] =
	{
		{{4,false,0.2f},{2,false,0.2f},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}},
		{{3,false,0.2f},{6,true,0.3f},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}},
		{{10,false,0.2f},{12,false,0.2f},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}},
		{{10,false,0.2f},{12,false,0.2f},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}},
		{{10,false,0.2f},{12,false,0.2f},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}},
	};

	StageData stageData;

	/// <summary>
	/// �Q�[���V�[���p
	/// </summary>

	//�v���C���[�̎c�@
	int totalPlayerNum;

	//��������
	int gameTimer = 10980;

	//���̃X�e�[�W��I��������
	int selectNum;

	//�t�@�C�A�[�o�[�p�̃X�e�[�W�ԍ�
	int stageNum = 1;

	int GetRand(int min, int max)
	{
		static int check;
		if (check == 0)
		{
			srand((unsigned int)time(NULL));
			check = 1;
		}

		return min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
	}
};

