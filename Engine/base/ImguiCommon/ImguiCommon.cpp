#include "ImguiCommon.h"

template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

ComPtr<ID3D12DescriptorHeap> ImguiCommon::_heapForImgui;

ComPtr<ID3D12DescriptorHeap> ImguiCommon::CreateDescriptorHeapForImgui(ID3D12Device *device)
{
	ComPtr<ID3D12DescriptorHeap> ret;

	D3D12_DESCRIPTOR_HEAP_DESC desc = {};
	desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	desc.NodeMask = 0;
	desc.NumDescriptors = 1;
	desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;

	device->CreateDescriptorHeap(&desc, IID_PPV_ARGS(ret.ReleaseAndGetAddressOf()));

	return ret;
}

void ImguiCommon::Initialize(ID3D12Device *device, HWND hwnd)
{
	_heapForImgui = CreateDescriptorHeapForImgui(device);

	if (ImGui::CreateContext() == nullptr)
	{
		assert(0);
	}

	bool blenResult = ImGui_ImplWin32_Init(hwnd);
	if (!blenResult)
	{
		assert(0);
	}

	blenResult = ImGui_ImplDX12_Init
	(
		device,
		3,
		DXGI_FORMAT_R8G8B8A8_UNORM,
		GetHeapForImgui().Get(),
		GetHeapForImgui().Get()->GetCPUDescriptorHandleForHeapStart(),
		GetHeapForImgui().Get()->GetGPUDescriptorHandleForHeapStart()
	);
}

void ImguiCommon::PreDraw()
{
	//imgui•`‰æ‘Oˆ—
	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Rendering Test Menu");
	ImGui::SetWindowSize(ImVec2(400, 500), ImGuiCond_::ImGuiCond_FirstUseEver);
}

void ImguiCommon::Draw(ID3D12GraphicsCommandList* cmdList)
{
	ImGui::End();

	ImGui::Render();
	cmdList->SetDescriptorHeaps(1, GetHeapForImgui().GetAddressOf());
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), cmdList);
}
