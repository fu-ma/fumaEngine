#pragma once
#include<wrl.h>
#include"Engine/imgui/imgui.h"
#include"Engine/imgui/imgui_impl_win32.h"
#include"Engine/imgui/imgui_impl_dx12.h"
#include"DirectXApp.h"

class ImguiCommon
{
	//Microsoft::WRL::���ȗ�
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	static ComPtr<ID3D12DescriptorHeap> CreateDescriptorHeapForImgui(ID3D12Device *device);
	//����������
	static void Initialize(ID3D12Device *device, HWND hwnd);
	//�`��O����
	static void PreDraw();
	//�`�揈��
	static void Draw(ID3D12GraphicsCommandList *cmdList);

	//imgui�p�̃q�[�v�A�N�Z�T
	static ComPtr<ID3D12DescriptorHeap> GetHeapForImgui() { return _heapForImgui; }

	ImguiCommon(const ImguiCommon &) = delete;
	ImguiCommon &operator=(const ImguiCommon &) = delete;
private:
	static ComPtr<ID3D12DescriptorHeap> _heapForImgui;//�q�[�v�ێ��p
};