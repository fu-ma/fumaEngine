#include"FBXModel.h"

void FBXModel::CreateBuffers(ID3D12Device *device)
{
	//頂点データ全体のサイズ
	HRESULT result;
	UINT sizeVB = static_cast<UINT>(sizeof(VertexPosNormalUvSkin) * vertices.size());
	//頂点バッファ生成
	result = device->CreateCommittedResource
	(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(sizeVB),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&vertBuff)
	);

	//頂点バッファへのデータ転送
	VertexPosNormalUvSkin *vertMap = nullptr;
	result = vertBuff->Map(0, nullptr, (void **)&vertMap);
	if (SUCCEEDED(result))
	{
		std::copy(vertices.begin(), vertices.end(), vertMap);
		vertBuff->Unmap(0, nullptr);
	}

	//頂点バッファビュー(VBV)の作成
	vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
	vbView.SizeInBytes = sizeVB;
	vbView.StrideInBytes = sizeof(vertices[0]);

	//頂点インデックス全体のサイズ
	UINT sizeIB = static_cast<UINT>(sizeof(unsigned short) * indices.size());
	//インデックスバッファ生成
	result = device->CreateCommittedResource
	(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(sizeIB),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&indexBuff)
	);

	//インデックスバッファへのデータ転送
	unsigned short *indexMap = nullptr;
	result = indexBuff->Map(0, nullptr, (void **)&indexMap);
	if (SUCCEEDED(result))
	{
		std::copy(indices.begin(), indices.end(), indexMap);
		indexBuff->Unmap(0, nullptr);
	}

	//インデックスバッファビュー（IBV）の作成
	ibView.BufferLocation = indexBuff->GetGPUVirtualAddress();
	ibView.Format = DXGI_FORMAT_R16_UINT;
	ibView.SizeInBytes = sizeIB;

	//定数バッファの生成
	result = device->CreateCommittedResource
	(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferDataMaterial) + 0xff) & ~0xff),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuffMaterial)
	);

	//SRV用デスクリプタヒープを生成
	D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc{};
	descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;//シェーダから見えるように
	descHeapDesc.NumDescriptors = MAX_TEXTURES;//テクスチャ枚数
	result = device->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&descHeapSRV));//生成

	//各パラメータ用テクスチャのバッファを生成
	CreateTexture(baseTexture, device, 0);
	CreateTexture(metalnessTexture, device, 1);
	CreateTexture(normalTexture, device, 2);
	CreateTexture(roughnessTexture, device, 3);
}

void FBXModel::Draw(ID3D12GraphicsCommandList *cmdList)
{
	//頂点バッファをセット(VBV)
	cmdList->IASetVertexBuffers(0, 1, &vbView);
	//インデックスバッファをセット(IBV)
	cmdList->IASetIndexBuffer(&ibView);

	//デスクリプタヒープのセット
	ID3D12DescriptorHeap *ppHeaps[] = { descHeapSRV.Get() };
	cmdList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
	//シェーダーリソースビューをセット
	cmdList->SetGraphicsRootDescriptorTable(1, descHeapSRV->GetGPUDescriptorHandleForHeapStart());

	//定数バッファビューをセット
	cmdList->SetGraphicsRootConstantBufferView(3, constBuffMaterial->GetGPUVirtualAddress());
	//描画コマンド
	cmdList->DrawIndexedInstanced((UINT)indices.size(), 1, 0, 0, 0);
}

void FBXModel::TransferMaterial()
{
	HRESULT result;
	//定数バッファへのデータ転送
	ConstBufferDataMaterial *constMapMaterial = nullptr;
	result = constBuffMaterial->Map(0, nullptr, (void **)&constMapMaterial);
	if (SUCCEEDED(result))
	{
		constMapMaterial->baseColor = baseColor;
		constMapMaterial->metalness = metalness;
		constMapMaterial->specular = specular;
		constMapMaterial->roughness = roughness;
		constBuffMaterial->Unmap(0, nullptr);
	}

}

void FBXModel::CreateTexture(TextureData &texture, ID3D12Device *device, int srvIndex)
{
	//テクスチャデータがない場合はなにもせず終了
	if (texture.scratchImg.GetImageCount() == 0)
	{
		return;
	}

	HRESULT result;
	//テクスチャ画像データ
	const DirectX::Image *img = texture.scratchImg.GetImage(0, 0, 0);//生データ摘出
	assert(img);

	//リソース設定
	CD3DX12_RESOURCE_DESC texresDesc = CD3DX12_RESOURCE_DESC::Tex2D
	(
		texture.metadata.format,
		texture.metadata.width,
		(UINT)texture.metadata.height,
		(UINT16)texture.metadata.arraySize,
		(UINT16)texture.metadata.mipLevels
	);

	//テクスチャ用バッファの生成
	result = device->CreateCommittedResource
	(
		&CD3DX12_HEAP_PROPERTIES
		(
			D3D12_CPU_PAGE_PROPERTY_WRITE_BACK,
			D3D12_MEMORY_POOL_L0
		),
		D3D12_HEAP_FLAG_NONE,
		&texresDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,//テクスチャ用指定
		nullptr,
		IID_PPV_ARGS(&texture.texbuff)
	);

	//テクスチャバッファにデータ転送
	result = texture.texbuff->WriteToSubresource
	(
		0,
		nullptr,//全領域へコピー
		img->pixels,//元データアドレス
		(UINT)img->rowPitch,//1ラインサイズ
		(UINT)img->slicePitch//1枚サイズ
	);

	//シェーダリソースビュー(SRV)作成
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};//設定構造体
	D3D12_RESOURCE_DESC resDesc = texture.texbuff->GetDesc();

	srvDesc.Format = resDesc.Format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;//2Dテクスチャ
	srvDesc.Texture2D.MipLevels = 1;

	device->CreateShaderResourceView
	(
		texture.texbuff.Get(),//ビューと関連付けるバッファ
		&srvDesc,//テクスチャ設定情報
		descHeapSRV->GetCPUDescriptorHandleForHeapStart()//ヒープの先頭アドレス
	);

	//GPUハンドル取得
	texture.gpuHandle = CD3DX12_GPU_DESCRIPTOR_HANDLE
	(
		descHeapSRV->GetGPUDescriptorHandleForHeapStart(),
		srvIndex,
		device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV)
	);
}

FBXModel::~FBXModel()
{
	//FBXシーンの解放
	fbxScene->Destroy();
}
