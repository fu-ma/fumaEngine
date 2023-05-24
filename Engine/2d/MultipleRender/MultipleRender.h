#pragma once
#include "Sprite.h"
#include"Engine/Input/Input.h"

class MultipleRender :
    public Sprite
{
private://静的メンバ
    //画面クリアカラー
    static const float clearColor[4];

private://メンバ変数
    //テクスチャバッファ
    ComPtr<ID3D12Resource> texBuff[2];
    //SRV用デスクリプタヒープ
    ComPtr<ID3D12DescriptorHeap> descHeapSRV;
    //深度バッファ
    ComPtr<ID3D12Resource> depthBuff;
    //RTV用デスクリプタヒープ
    ComPtr<ID3D12DescriptorHeap> descHeapRTV;
    //DSV用デスクリプタヒープ
    ComPtr<ID3D12DescriptorHeap> descHeapDSV;
    //グラフィックパイプライン
    ComPtr<ID3D12PipelineState> pipelineState;
    //ルートシグネチャ
    ComPtr<ID3D12RootSignature> rootSignature;
public://メンバ関数
    ///<summary>
    ///コンストラクタ
    ///</summary>
    MultipleRender();

    ///<summary>
    ///パイプライン生成
    ///</summary>
    void CreateGraphicsPipelineState();

    ///<summary>
    ///初期化
    ///</summary>
    void Initialize();

    ///<summary>
    ///シーン描画前処理
    ///</summary>
    ///<param name="cmdList">コマンドリスト</param>
    void PreDrawScene(ID3D12GraphicsCommandList *cmdList);

    ///<summary>
    ///描画コマンドの発行
    ///</summary>
    ///<param name="cmdList">コマンドリスト</param>
    void Draw(ID3D12GraphicsCommandList *cmdList);

    ///<summary>
    ///シーン描画後処理
    ///</summary>
    ///<param name="cmdList">コマンドリスト</param>
    void PostDrawScene(ID3D12GraphicsCommandList *cmdList);
};

