#include "Framework.h"

void Framework::GameRun()
{
	staticInit();
	while (true)//�Q�[�����[�v
	{
		//������(�����ň��̂ݓǂݍ��ނ悤�ɂ��Ă���)
		Init();
		//�X�V����
		if (Update() == false)
		{
			break;
		}
		//�`�揈��
		Draw();
	}
	SceneDelete();
}

void Framework::staticInit()
{
	winApp = std::make_unique<WinApp>();
	common = std::make_unique<DirectXApp>(winApp.get());
	winApp->Innitialize();
	common->Initialize();

	input = Input::GetInstance();
	input->Initialize(winApp->GetHInstance(), winApp->GetHwnd());
	controller = Controller::GetInstance();
	controller->Initialize(0);

	Audio::Init();
	//���C�g�ÓI������
	LightGroup::StaticInitialize(common->GetDev().Get());
	/*�X�v���C�g������*/
	Sprite::StaticInitialize(common->GetDev().Get(), WinApp::window_width, WinApp::window_height);
	Sprite::LoadTexture(0, L"Resources/image/BoxFont.dds");
	debugText = DebugText::GetInstance();
	debugText->Initialize(0);

	//�|�X�g�G�t�F�N�g�p�e�N�X�`���̓ǂݍ���
	//Sprite::LoadTexture(100, L"Resources/backGround3.png");
	//�|�X�g�G�t�F�N�g�̏�����
	postEffect = std::make_unique<MultipleTexture>();
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

	//Imgui������
	ImguiCommon::Initialize(common->GetDev().Get(),winApp->GetHwnd());

	fps = std::make_unique<Fps>();

	resources = Resources::GetInstance();
	resources->StaticInit(audio.get());

	json = Json::GetInstance();
}

void Framework::Init()
{
}

bool Framework::Update()
{
	//�L�[�{�[�h���̎擾�J�n
	input->Update();
	controller->Update(0);

	if (winApp->ProcessMessage())
	{
		return false;
	}

	return true;
}

void Framework::Draw()
{
}
