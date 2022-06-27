#include "Framework.h"

void Framework::GameRun()
{
	staticInit();
	while (true)//�Q�[�����[�v
	{
		if (SceneTime == 0)
		{
			Init();
		}
		if (Update() == false)
		{
			break;
		}
		if (SceneTime)
		{
			//�����_�[�e�N�X�`���ւ̕`��
			postEffect->PreDrawScene(common->GetCmdList().Get());
			Draw();
			postEffect->PostDrawScene(common->GetCmdList().Get());

			//�`��J�n
			common->PreDraw();
			//�|�X�g�G�t�F�N�g�̕`��
			postEffect->Draw(common->GetCmdList().Get());
			//�`��I��
			common->PostDraw();
		}
	}
	SceneDelete();
}

void Framework::staticInit()
{
	winApp = std::make_unique<WinApp>();
	common = std::make_unique<DirectXCommon>(winApp.get());
	winApp->Innitialize();
	common->Initialize();
	input = Input::GetInstance();
	input->Initialize(winApp->GetHInstance(), winApp->GetHwnd());
	Audio::Init();
	//���C�g�ÓI������
	LightGroup::StaticInitialize(common->GetDev().Get());
	/*�X�v���C�g������*/
	Sprite::StaticInitialize(common->GetDev().Get(), WinApp::window_width, WinApp::window_height);
	Sprite::LoadTexture(0, L"Resources/debugfont.png");
	debugText = DebugText::GetInstance();
	debugText->Initialize(0);

	//�|�X�g�G�t�F�N�g�p�e�N�X�`���̓ǂݍ���
	//Sprite::LoadTexture(100, L"Resources/backGround3.png");
	//�|�X�g�G�t�F�N�g�̏�����
	postEffect = std::make_unique<PostEffect>();
	postEffect->Initialize();

	/*FBX������*/
	FbxLoader::GetInstance()->Initialize(common->GetDev().Get());
	//�f�o�C�X���Z�b�g
	FBXObject3d::SetDevice(common->GetDev().Get());

	/*���f��������*/
	ModelObj::StaticInitialize(common->GetDev().Get());
	// �J��������
	camera = std::make_unique<DebugCamera>(WinApp::window_width, WinApp::window_height, input);
	// �p�[�e�B�N���}�l�[�W��������
	ParticleManager::GetInstance()->Initialize(common->GetDev().Get());
	particleMan = ParticleManager::GetInstance();
	particleMan->SetCamera(camera.get());

	//�J�������Z�b�g
	FBXObject3d::SetCamera(camera.get());
	//�O���t�B�b�N�X�p�C�v���C������
	FBXObject3d::CreateGraphicsPipeline();
}

void Framework::Init()
{
}

bool Framework::Update()
{
	//�L�[�{�[�h���̎擾�J�n
	input->Update();
	if (winApp->ProcessMessage() || input->isKeyTrigger(DIK_ESCAPE))
	{
		return false;
	}

	return true;
}

void Framework::Draw()
{
}
