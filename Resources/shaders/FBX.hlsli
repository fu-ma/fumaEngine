cbuffer cbuff0 : register(b0)
{
	matrix viewproj;//ビュープロジェクション行列
	matrix world;//ワールド行列
	float3 cameraPos;//カメラ座標（ワールド）
};

//マテリアル
cbuffer cbuff1 : register(b1)
{
	//アルベド
	float3 baseColor;
	//金属度
	float metalness;
	//鏡面反射強度
	float specular;
	//粗さ
	float roughness;
}

//バーテックスバッファーの入力
struct VSInput
{
	float4 pos:POSITION;//位置
	float3 normal:NORMAL;//頂点法線
	float2 uv:TEXCOORD;//テクスチャー座標
	uint4 boneIndices:BONEINDICES;//ボーンの番号
	float4 boneWeights:BONEWEIGHTS;//ボーンのスキンウェイト
};

//頂点シェーダーからピクセルシェーダーへのやり取りに使用する構造体
struct VSOutput
{
	float4 svpos:SV_POSITION;//システム用頂点座標
	float3 worldpos:POS;//ワールド座標
	float3 normal:NORMAL;//法線
	float2 uv:TEXCOORD;//uv値
};

//ボーンの最大数
static const int MAX_BONES = 32;

cbuffer skinning:register(b3)//ボーンのスキニング行列が入る
{
	matrix matSkinning[MAX_BONES];
};

//平行光源の数
static const int DIRLIGHT_NUM = 3;

struct DirLight
{
	float3 lightv;//ライト方向の単位ベクトル
	float3 lightcolor;//ライトの色(RGB)
	uint active;
};

//点光源の数
static const int POINTLIGHT_NUM = 3;

struct PointLight
{
	float3 lightpos;//ライト座標
	float3 lightcolor;//ライトの色(RGB)
	float3 lightatten;//ライトの距離減衰係数
	uint active;
};

//スポットライトの数
static const int SPOTLIGHT_NUM = 3;

struct SpotLight
{
	float3 lightv;//ライトの光線方向の逆ベクトル（単位ベクトル）
	float3 lightpos;//ライト座標
	float3 lightcolor;//ライトの色(RGB)
	float3 lightatten;//ライト距離減衰係数
	float2 lightfactranglecos;//ライト減衰角度のコサイン
	uint active;
};


//定数バッファ(ライト情報)
cbuffer cbuff2 : register(b2)
{
	float3 ambientLightColor;
	DirLight dirLights[DIRLIGHT_NUM];
	PointLight pointLights[POINTLIGHT_NUM];
	SpotLight spotLights[SPOTLIGHT_NUM];
}