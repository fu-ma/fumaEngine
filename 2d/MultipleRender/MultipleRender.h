#pragma once
#include "Sprite.h"
#include"Input.h"

class MultipleRender :
    public Sprite
{
private://�ÓI�����o
    //��ʃN���A�J���[
    static const float clearColor[4];

private://�����o�ϐ�
    //�e�N�X�`���o�b�t�@
    ComPtr<ID3D12Resource> texBuff[2];
    //SRV�p�f�X�N���v�^�q�[�v
    ComPtr<ID3D12DescriptorHeap> descHeapSRV;
    //�[�x�o�b�t�@
    ComPtr<ID3D12Resource> depthBuff;
    //RTV�p�f�X�N���v�^�q�[�v
    ComPtr<ID3D12DescriptorHeap> descHeapRTV;
    //DSV�p�f�X�N���v�^�q�[�v
    ComPtr<ID3D12DescriptorHeap> descHeapDSV;
    //�O���t�B�b�N�p�C�v���C��
    ComPtr<ID3D12PipelineState> pipelineState;
    //���[�g�V�O�l�`��
    ComPtr<ID3D12RootSignature> rootSignature;
public://�����o�֐�
    ///<summary>
    ///�R���X�g���N�^
    ///</summary>
    MultipleRender();

    ///<summary>
    ///�p�C�v���C������
    ///</summary>
    void CreateGraphicsPipelineState();

    ///<summary>
    ///������
    ///</summary>
    void Initialize();

    ///<summary>
    ///�V�[���`��O����
    ///</summary>
    ///<param name="cmdList">�R�}���h���X�g</param>
    void PreDrawScene(ID3D12GraphicsCommandList *cmdList);

    ///<summary>
    ///�`��R�}���h�̔��s
    ///</summary>
    ///<param name="cmdList">�R�}���h���X�g</param>
    void Draw(ID3D12GraphicsCommandList *cmdList);

    ///<summary>
    ///�V�[���`��㏈��
    ///</summary>
    ///<param name="cmdList">�R�}���h���X�g</param>
    void PostDrawScene(ID3D12GraphicsCommandList *cmdList);
};

