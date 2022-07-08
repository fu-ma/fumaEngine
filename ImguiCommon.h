#pragma once
#include<wrl.h>
#include"imgui/imgui.h"
#include"imgui/imgui_impl_win32.h"
#include"imgui/imgui_impl_dx12.h"
#include"DirectXCommon.h"

class ImguiCommon
{
	//Microsoft::WRL::を省略
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	static ComPtr<ID3D12DescriptorHeap> CreateDescriptorHeapForImgui(ID3D12Device *device);
	//初期化処理
	static void Initialize(ID3D12Device *device, HWND hwnd);
	//描画前処理
	static void PreDraw();
	//描画処理
	static void Draw(ID3D12GraphicsCommandList *cmdList);

	//imgui用のヒープアクセサ
	static ComPtr<ID3D12DescriptorHeap> GetHeapForImgui() { return _heapForImgui; }
private:
	static ComPtr<ID3D12DescriptorHeap> _heapForImgui;//ヒープ保持用
};