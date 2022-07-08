#pragma once
#include<wrl.h>
#include"imgui/imgui.h"
#include"imgui/imgui_impl_win32.h"
#include"imgui/imgui_impl_dx12.h"
#include"DirectXCommon.h"

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
private:
	static ComPtr<ID3D12DescriptorHeap> _heapForImgui;//�q�[�v�ێ��p
};