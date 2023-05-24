#pragma once
#include<d3d12.h>
#include<d3dx12.h>
#include<dxgi1_6.h>
#include<wrl.h>
#include<vector>
#include<string>
#include"WindowAPI.h"
#include"Fps.h"

//DirectX���
class DirectXApp
{
private: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

private://�����o�ϐ�

	// �E�B���h�E�Y�A�v���P�[�V�����Ǘ�
	WinApp *winApp;

	// Direct3D�֘A
	ComPtr<IDXGIFactory6> dxgiFactory;
	ComPtr<ID3D12Device> dev;
	ComPtr<ID3D12GraphicsCommandList> cmdList;
	ComPtr<ID3D12CommandAllocator> cmdAllocator;
	ComPtr<ID3D12CommandQueue> cmdQueue;
	ComPtr<IDXGISwapChain4> swapchain;
	std::vector<ComPtr<ID3D12Resource>> backBuffers;
	ComPtr<ID3D12Resource> depthBuffer;
	ComPtr<ID3D12DescriptorHeap> rtvHeaps;
	ComPtr<ID3D12DescriptorHeap> dsvHeap;
	ComPtr<ID3D12Fence> fence;
	UINT64 fenceVal = 0;
	Fps *fps;
private://�����o�֐�

	/// <summary>
	/// DXGI�f�o�C�X������
	/// </summary>
	/// <returns>����</returns>
	bool InitializeDevice();

	/// <summary>
	/// �X���b�v�`�F�[���̐���
	/// </summary>
	/// <returns>����</returns>
	bool InitializeCommand();

	/// <summary>
	/// �R�}���h�֘A������
	/// </summary>
	/// <returns>����</returns>
	bool InitializeSwapchain();

	/// <summary>
	/// �����_�[�^�[�Q�b�g����
	/// </summary>
	/// <returns>����</returns>
	bool InitializeRenderTargetView();

	/// <summary>
	/// �[�x�o�b�t�@����
	/// </summary>
	/// <returns>����</returns>
	bool InitializeDepthBuffer();

	/// <summary>
	/// �t�F���X����
	/// </summary>
	/// <returns>����</returns>
	bool InitializeFence();

public://Getter

	/// <summary>
	/// �f�o�C�X�̎擾
	/// </summary>
	/// <returns>�f�o�C�X</returns>
	const ComPtr<ID3D12Device> &GetDev()
	{
		return dev;
	}

	/// <summary>
	/// �`��R�}���h���X�g�̎擾
	/// </summary>
	/// <returns>�`��R�}���h���X�g</returns>
	const ComPtr<ID3D12GraphicsCommandList> &GetCmdList()
	{
		return cmdList;
	}

public://�����o�֐�

	//�R���X�g���N�^
	DirectXApp();
	
	//�����t���R���X�g���N�^
	DirectXApp(WinApp *winApp);

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �`��O����
	/// </summary>
	void PreDraw();

	/// <summary>
	/// �`��㏈��
	/// </summary>
	void PostDraw();

	/// <summary>
	/// ��ʃN���A
	/// </summary>
	void ClearScreen();

	/// <summary>
	/// �[�x�o�b�t�@�̃N���A
	/// </summary>
	void ClearDepthBuffer();

};
