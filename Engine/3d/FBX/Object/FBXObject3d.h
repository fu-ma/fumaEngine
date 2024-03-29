#pragma once

#include"FBXModel.h"
#include"Camera.h"
#include"FbxLoader.h"

#include<Windows.h>
#include<wrl.h>
#include<d3d12.h>
#include<d3dx12.h>
#include<DirectXMath.h>
#include<string>
#include"LightGroup.h"

class FBXObject3d
{
protected://エイリアス
	//Microsoft::WRL::を省略
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public://定数
	//ボーンの最大数
	static const int MAX_BONES = 32;

public://サブクラス
	//定数バッファ用データ構造体
	struct ConstBufferDataTransform
	{
		XMMATRIX viewproj;//ビュープロジェクション行列
		XMMATRIX world;//ワールド行列
		XMFLOAT3 cameraPos;//カメラ座標
	};

	//定数バッファ用データ構造体(スキニング)
	struct ConstBufferDataSkin
	{
		XMMATRIX bones[MAX_BONES];
	};

public://静的メンバ関数
	//setter
	static void SetDevice(ID3D12Device *device) { FBXObject3d::device = device; }
	static void SetCamera(Camera *camera) { FBXObject3d::camera = camera; }
	/// <summary>
	/// モデルのセット
	/// </summary>
	/// <param name="model">モデル</param>
	void SetModel(FBXModel *model) { this->model = model; }

	/// <summary>
	/// グラフィックパイプラインの生成
	/// </summary>
	static void CreateGraphicsPipeline();

	/// <summary>
/// 座標の取得
/// </summary>
/// <returns>座標</returns>
	const XMFLOAT3 &GetPosition() { return position; }

	/// <summary>
	/// 回転の取得
	/// </summary>
	/// <returns>回転</returns>
	const XMFLOAT3 &GetRotation() { return rotation; }

	/// <summary>
	/// ワールド行列の取得
	/// </summary>
	/// <returns>ワールド行列</returns>
	const XMMATRIX &GetMatWorld() { return matWorld; }

	/// <summary>
	/// 座標の設定
	/// </summary>
	/// <param name="position">座標</param>
	void SetPosition(XMFLOAT3 position) { this->position = position; }

	void SetRotation(XMFLOAT3 rotation) { this->rotation = rotation; }

	/// <summary>
	/// ライトの設定
	/// </summary>
	/// <param name="position">ライト</param>
	static void SetLightGroup(LightGroup *lightGroup) { FBXObject3d::lightGroup = lightGroup; }

	/// <summary>
	/// スケールの設定
	/// </summary>
	/// <param name="position">スケール</param>
	void SetScale(XMFLOAT3 scale) { this->scale = scale; }
public://メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ID3D12GraphicsCommandList *cmdList);

	/// <summary>
	/// アニメーション開始
	/// </summary>
	void PlayAnimation(const int& animationNum = 0,const bool& isLoop = true);

protected://メンバ変数
	//定数バッファ
	ComPtr<ID3D12Resource> constBuffTransform;
	//ローカルスケール
	XMFLOAT3 scale = { 1,1,1 };
	//X,Y,Z軸まわりのローカル回転角
	XMFLOAT3 rotation = { 0,0,0 };
	//ローカル座標
	XMFLOAT3 position = { 0,0,0 };
	//ローカルワールド変換行列
	XMMATRIX matWorld;
	//モデル
	FBXModel *model = nullptr;
	//定数バッファ(スキン)
	ComPtr<ID3D12Resource> constBuffSkin;
	//1フレームの時間
	FbxTime frameTime;
	//アニメーション開始時間
	FbxTime startTime;
	//アニメーション終了時間
	FbxTime endTime;
	//現在時間(アニメーション)
	FbxTime currentTime;
	//アニメーション再生中
	bool isPlay = false;
	//アニメーションがループするかいなか
	bool isLoop = false;
private://静的メンバ変数
	//デバイス
	static ID3D12Device *device;
	//カメラ
	static Camera *camera;
	//ルートシグネチャ
	static ComPtr<ID3D12RootSignature> rootsignature;
	//パイプラインステートオブジェクト
	static ComPtr<ID3D12PipelineState> pipelinestate;
	//ライトグループ
	static LightGroup *lightGroup;
};
