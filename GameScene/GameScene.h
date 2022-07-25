#pragma once
#include"ModelObj.h"
#include"Model.h"
#include <DirectXMath.h>
#include "Sprite.h"
#include"LightGroup.h"
#include"Framework.h"
#include "Player.h"
#include "TouchableObject.h"
#include"Collision.h"

class GameScene : public Framework
{
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

private:

	SoundData soundData1;
	SoundData soundData2;
	SoundData soundData3;

	/// <summary>
	/// �Q�[���V�[���p
	/// </summary>

	Sprite *spriteBG = nullptr;

	//Model *modelSkydome = nullptr;
	//Model *modelGround = nullptr;
	Model *modelFighter = nullptr;
	//Model *modelSphere = nullptr;
	Model *modelStageBox = nullptr;

	//ModelObj *objSkydome = nullptr;
	TouchableObject *objGround = nullptr;
	Player *objFighter = nullptr;
	Player *objFighter2 = nullptr;

	//ModelObj *objSphere = nullptr;
	ModelObj *objStageBox[20] = { nullptr };
	FBXModel *model1 = nullptr;
	FBXObject3d *object1 = nullptr;

	float pointLightPos[3] = { 0,0,0 };
	float pointLightColor[3] = { 1,1,1 };
	float pointLightAtten[3] = { 0.3f,0.1f,0.1f };

	float spotLightDir[3] = { 0,-1,0 };
	float spotLightPos[3] = { 0,5,0 };
	float spotLightColor[3] = { 1,1,1 };
	float spotLightAtten[3] = { 0.0f,0.0f,0.0f };
	float spotLightFactorAngle[2] = { 20.0f,30.0f };

	float circleShadowDir[3] = { 0,-1,0 };
	float circleShadowAtten[3] = { 0.5f,0.6f,0.0f };
	float circleShadowFactorAngle[2] = { 0.0f,0.5f };

	float fighterPos[3] = { 1,1.0f,0 };

	bool hitFlag = false;
#pragma region �^�C�g���V�[��
	void TitleInit();
	void TitleUpdate();
	void TitleDraw();

#pragma region �Q�[���v���C�V�[��
	void GamePlayInit();
	void GamePlayUpdate();
	void GamePlayDraw();

#pragma region �G���h�V�[��
	void EndInit();
	void EndUpdate();
	void EndDraw();

public:
	GameScene() {};
	void SceneDelete() override
	{
#pragma region �������
		//XAudio2���
		Audio::xAudio2.Reset();
		//DirectXCommon�������
		//�X�v���C�g�̉������
		debugText->deleteSprite();
		delete spriteBG;
		spriteBG = nullptr;
		//modelObj�������
		//delete objSkydome;
		//objSkydome = nullptr;
		delete objGround;
		objGround = nullptr;
		delete objFighter;
		objFighter = nullptr;
		for (int i = 0; i < 20; i++)
		{
			delete objStageBox[i];
			objStageBox[i] = nullptr;
		}
		//model�������
		//delete modelSkydome;
		//modelSkydome = nullptr;
		//delete modelGround;
		//modelGround = nullptr;
		//delete modelFighter;
		//modelFighter = nullptr;
		delete modelStageBox;
		modelStageBox = nullptr;
		//FBX�p�̃I�u�W�F�N�g���
		delete object1;
		object1 = nullptr;
		delete model1;
		model1 = nullptr;
		//���N���X�������
		Framework::SceneDelete();
	};

	void staticInit() override;
	void Init() override;
	bool Update() override;
	void Draw() override;
};

