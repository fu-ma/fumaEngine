#include"FBXModel.h"

void FBXModel::CreateBuffers(ID3D12Device *device)
{
	//���_�f�[�^�S�̂̃T�C�Y
	HRESULT result;
	UINT sizeVB = static_cast<UINT>(sizeof(VertexPosNormalUvSkin) * vertices.size());
	//���_�o�b�t�@����
	result = device->CreateCommittedResource
	(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(sizeVB),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&vertBuff)
	);

	//���_�o�b�t�@�ւ̃f�[�^�]��
	VertexPosNormalUvSkin *vertMap = nullptr;
	result = vertBuff->Map(0, nullptr, (void **)&vertMap);
	if (SUCCEEDED(result))
	{
		std::copy(vertices.begin(), vertices.end(), vertMap);
		vertBuff->Unmap(0, nullptr);
	}

	//���_�o�b�t�@�r���[(VBV)�̍쐬
	vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
	vbView.SizeInBytes = sizeVB;
	vbView.StrideInBytes = sizeof(vertices[0]);

	//���_�C���f�b�N�X�S�̂̃T�C�Y
	UINT sizeIB = static_cast<UINT>(sizeof(unsigned short) * indices.size());
	//�C���f�b�N�X�o�b�t�@����
	result = device->CreateCommittedResource
	(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(sizeIB),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&indexBuff)
	);

	//�C���f�b�N�X�o�b�t�@�ւ̃f�[�^�]��
	unsigned short *indexMap = nullptr;
	result = indexBuff->Map(0, nullptr, (void **)&indexMap);
	if (SUCCEEDED(result))
	{
		std::copy(indices.begin(), indices.end(), indexMap);
		indexBuff->Unmap(0, nullptr);
	}

	//�C���f�b�N�X�o�b�t�@�r���[�iIBV�j�̍쐬
	ibView.BufferLocation = indexBuff->GetGPUVirtualAddress();
	ibView.Format = DXGI_FORMAT_R16_UINT;
	ibView.SizeInBytes = sizeIB;

	//�萔�o�b�t�@�̐���
	result = device->CreateCommittedResource
	(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferDataMaterial) + 0xff) & ~0xff),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuffMaterial)
	);

	//SRV�p�f�X�N���v�^�q�[�v�𐶐�
	D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc{};
	descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;//�V�F�[�_���猩����悤��
	descHeapDesc.NumDescriptors = MAX_TEXTURES;//�e�N�X�`������
	result = device->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&descHeapSRV));//����

	//�e�p�����[�^�p�e�N�X�`���̃o�b�t�@�𐶐�
	CreateTexture(baseTexture, device, 0);
	CreateTexture(metalnessTexture, device, 1);
	CreateTexture(normalTexture, device, 2);
	CreateTexture(roughnessTexture, device, 3);
}

void FBXModel::Draw(ID3D12GraphicsCommandList *cmdList)
{
	//���_�o�b�t�@���Z�b�g(VBV)
	cmdList->IASetVertexBuffers(0, 1, &vbView);
	//�C���f�b�N�X�o�b�t�@���Z�b�g(IBV)
	cmdList->IASetIndexBuffer(&ibView);

	//�f�X�N���v�^�q�[�v�̃Z�b�g
	ID3D12DescriptorHeap *ppHeaps[] = { descHeapSRV.Get() };
	cmdList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
	//�V�F�[�_�[���\�[�X�r���[���Z�b�g
	cmdList->SetGraphicsRootDescriptorTable(1, descHeapSRV->GetGPUDescriptorHandleForHeapStart());

	//�萔�o�b�t�@�r���[���Z�b�g
	cmdList->SetGraphicsRootConstantBufferView(3, constBuffMaterial->GetGPUVirtualAddress());
	//�`��R�}���h
	cmdList->DrawIndexedInstanced((UINT)indices.size(), 1, 0, 0, 0);
}

void FBXModel::TransferMaterial()
{
	HRESULT result;
	//�萔�o�b�t�@�ւ̃f�[�^�]��
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
	//�e�N�X�`���f�[�^���Ȃ��ꍇ�͂Ȃɂ������I��
	if (texture.scratchImg.GetImageCount() == 0)
	{
		return;
	}

	HRESULT result;
	//�e�N�X�`���摜�f�[�^
	const DirectX::Image *img = texture.scratchImg.GetImage(0, 0, 0);//���f�[�^�E�o
	assert(img);

	//���\�[�X�ݒ�
	CD3DX12_RESOURCE_DESC texresDesc = CD3DX12_RESOURCE_DESC::Tex2D
	(
		texture.metadata.format,
		texture.metadata.width,
		(UINT)texture.metadata.height,
		(UINT16)texture.metadata.arraySize,
		(UINT16)texture.metadata.mipLevels
	);

	//�e�N�X�`���p�o�b�t�@�̐���
	result = device->CreateCommittedResource
	(
		&CD3DX12_HEAP_PROPERTIES
		(
			D3D12_CPU_PAGE_PROPERTY_WRITE_BACK,
			D3D12_MEMORY_POOL_L0
		),
		D3D12_HEAP_FLAG_NONE,
		&texresDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,//�e�N�X�`���p�w��
		nullptr,
		IID_PPV_ARGS(&texture.texbuff)
	);

	//�e�N�X�`���o�b�t�@�Ƀf�[�^�]��
	result = texture.texbuff->WriteToSubresource
	(
		0,
		nullptr,//�S�̈�փR�s�[
		img->pixels,//���f�[�^�A�h���X
		(UINT)img->rowPitch,//1���C���T�C�Y
		(UINT)img->slicePitch//1���T�C�Y
	);

	//�V�F�[�_���\�[�X�r���[(SRV)�쐬
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};//�ݒ�\����
	D3D12_RESOURCE_DESC resDesc = texture.texbuff->GetDesc();

	srvDesc.Format = resDesc.Format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;//2D�e�N�X�`��
	srvDesc.Texture2D.MipLevels = 1;

	device->CreateShaderResourceView
	(
		texture.texbuff.Get(),//�r���[�Ɗ֘A�t����o�b�t�@
		&srvDesc,//�e�N�X�`���ݒ���
		descHeapSRV->GetCPUDescriptorHandleForHeapStart()//�q�[�v�̐擪�A�h���X
	);

	//GPU�n���h���擾
	texture.gpuHandle = CD3DX12_GPU_DESCRIPTOR_HANDLE
	(
		descHeapSRV->GetGPUDescriptorHandleForHeapStart(),
		srvIndex,
		device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV)
	);
}

FBXModel::~FBXModel()
{
	//FBX�V�[���̉��
	fbxScene->Destroy();
}