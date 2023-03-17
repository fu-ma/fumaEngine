#pragma once
#include <DirectXMath.h>
#include<stdlib.h>
#include<time.h>

class WholeScene
{
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
private:
	struct StageData
	{
		int firebarNum;//�t�@�C�A�[�̌�
		bool direction;//�t�@�C�A�[�o�[�̉�]����
		float firebarSpeed;//�t�@�C�A�[�o�[�̉�]�X�s�[�h
	};

	StageData stageDatas[5][20] =
	{
		{{4,false,0.2f},{2,false,0.2f},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}},
		{{6,false,0.4f},{6,true,0.4f},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}},
		{{6,false,0.2f},{4,false,0.2f},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}},
		{{4,false,0.2f},{4,false,0.2f},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}},
		{{4,false,0.2f},{4,false,0.2f},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}},
	};

	StageData stageData;

public: // �ÓI�����o�ϐ�
	static WholeScene *GetInstance();
	void StaticInit();

	float GetRand(float min, float max)
	{
		static int check;
		if (check == 0)
		{
			srand((unsigned int)time(NULL));
			check = 1;
		}

		return min + (float)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
	}

	const int &GetSelectNum() { return selectNum; }
	const int &GetStageFireNum() { return stageNum; }
	const int &GetTotalPlayerNum() { return totalPlayerNum; }
	const StageData &GetStageDatas(const int &y,const int &x) { return stageDatas[y][x]; }
	const StageData &GetStageData() { return stageData; }
	const bool &GetGoTitleFlag() { return goTileEaseFlag; }

	void SetTotalPlayerNum(const int &totalPlayerNum) { this->totalPlayerNum = totalPlayerNum; }
	void SetSelectNum(const int &selectNum) { this->selectNum = selectNum; }
	void SetStageFireNum(const int &stageNum) { this->stageNum = stageNum; }
	void SetStageData(const StageData &stageData) { this->stageData = stageData; }
	void SetGoTitleFlag(const bool &goTileEaseFlag) { this->goTileEaseFlag = goTileEaseFlag; }
private:
	static const int X_MAX = 100;
	static const int Y_MAX = 10;
	static const int GIMMICK_NUM = 100;

	/// <summary>
	/// �Q�[���V�[���p
	/// </summary>

	//�v���C���[�̎c�@
	int totalPlayerNum;

	//���̃X�e�[�W��I��������
	int selectNum;

	//�t�@�C�A�[�o�[�p�̃X�e�[�W�ԍ�
	int stageNum;

	//�Z���N�g��ʂ���title�ɖ߂������p�̃C�[�W���O�t���O
	bool goTileEaseFlag;

private:
	WholeScene() = default;
	~WholeScene() = default;
};

