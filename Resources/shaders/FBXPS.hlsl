#include"FBX.hlsli"
//0番スロットに設定されたテクスチャ
Texture2D<float4> baseTex : register(t0);
//1番スロットに設定されたテクスチャ
Texture2D<float4> metalnessTex : register(t1);
//2番スロットに設定されたテクスチャ
Texture2D<float4> normalTex : register(t2);
//3番スロットに設定されたテクスチャ
Texture2D<float4> roughnessTex : register(t3);

//0番スロットに設定されたサンプラー
SamplerState smp : register(s0);

//アルベド
static float3 s_baseColor;
//金属度
static float s_metalness;
//粗さ
static float s_roughness;

//π
static const float PI = 3.141592654f;

//反射点の法線ベクトル
static float3 N;

struct PSOutput
{
	float4 target0 : SV_TARGET0;
	float4 target1 : SV_TARGET1;
};

//UE4のGGX分布
//alpha : roughnessの2乗
//NdotH : 法線とハーフベクトルの内積
float DistributionGGX(float alpha, float NdotH)
{
	float alpha2 = alpha * alpha;
	float t = NdotH * NdotH * (alpha2 - 1.0f) + 1.0f;
	return alpha2 / (PI * t * t);
}

float3 SchlickFresnel3(float3 f0, float3 f90, float cosine)
{
	float m = saturate(1 - cosine);
	float m2 = m * m;
	float m5 = m2 * m2 * m;
	return lerp(f0, f90, m5);
}

//UE4のSmithモデル
float GeometricSmith(float cosine)
{
	float k = (roughness + 1.0f);

	k = k * k / 8.0f;

	return cosine / (cosine * (1.0f - k) + k);
}

//ディズニーのフレネル計算
float3 DisneyFresnel(float LdotH)
{
	//F項(フレネル:Fresnel)
	//輝度
	float luminance = 0.3f * s_baseColor.r + 0.6f * s_baseColor.g + 0.1f * s_baseColor.b;
	//色合い
	float3 tintColor = s_baseColor / luminance;
	//非金属の鏡面反射色を計算
	float3 nonMetalColor = specular * 0.08f * tintColor;
	//metalnessによる色補間 金属の場合はベースカラー
	float3 specularColor = lerp(nonMetalColor, baseColor, metalness);
	//NdotHの割合でSchlickFresnel補間
	return SchlickFresnel3(specularColor, float3(1, 1, 1), LdotH);
}

//鏡面反射の計算
float3 CookTorranceSpecular(float NdotL, float NdotV, float NdotH, float LdotH)
{
	//D項(分布:Distribution)
	float Ds = DistributionGGX(roughness * roughness, NdotH);

	//F項(フレネル:Fresnel)
	float3 Fs = DisneyFresnel(LdotH);

	//G項(幾何減衰:Geometry attenuation)
	float Gs = GeometricSmith(NdotL) * GeometricSmith(NdotV);

	//m項(分母)
	float m = 4.0f * NdotL * NdotV;

	//合成して鏡面反射の色を得る
	return Ds * Fs * Gs / m;
}

//Schlickによる近似
//f0とf90の値を(1-cosine)の5乗でlerpする
//f0 : 光が垂直に入社したときの反射率
//f90 : 光が平行に入社したときの反射率
//cosine : 2ベクトルのなす角のコサイン(内積値)
float SchlickFresnel(float f0, float f90, float cosine)
{
	float m = saturate(1 - cosine);
	float m2 = m * m;
	float m5 = m2 * m2 * m;
	return lerp(f0, f90, m5);
}

//双方向反射分布関数
float3 BRDF(float3 L, float3 V)
{
	//法線とライト方向の内積
	float NdotL = dot(N, L);
	//法線とカメラ方向の内積
	float NdotV = dot(N, V);
	//どちらかが90度以上であれば真っ黒を返す
	if (NdotL < 0 || NdotV < 0)
	{
		return float3(0, 0, 0);
	}

	//ライト方向とカメラ方向の中間(ハーフベクトル)
	float3 H = normalize(L + V);
	//法線とハーフベクトルの内積
	float NdotH = dot(N, H);
	//ライトとハーフベクトルの内積
	float LdotH = dot(L, H);
	//拡散反射率
	float diffuseReflectance = 1.0f / PI;

	float energyBias = 0.5f * roughness;
	//入射角が90度の場合の拡散反射率
	float Fd90 = energyBias + 2.0f * LdotH * LdotH * roughness;
	//入っていくときの拡散反射率
	float FL = SchlickFresnel(1.0f, Fd90, NdotL);
	//出ていくときの拡散反射率
	float FV = SchlickFresnel(1.0f, Fd90, NdotV);
	float energyFactor = lerp(1.0f, 1.0f / 1.51f, roughness);
	//入って出ていくまでの拡散反射率
	float Fd = FL * FV * energyFactor;

	//拡散反射光
	float3 diffuseColor = diffuseReflectance * Fd * baseColor * (1 - metalness);

	//鏡面反射光
	float3 specularColor = CookTorranceSpecular(NdotL, NdotV, NdotH, LdotH);

	return diffuseColor + specularColor;
}

////エントリーポイント
//PSOutput main(VSOutput input)
//{
//	PSOutput output;
//	//テクスチャマッピング
//	float4 texcolor = tex.Sample(smp,input.uv);
//	//Lambert反射
//	float3 light = normalize(float3(1, -1, 1));//右下奥向きのライト
//	float diffuse = saturate(dot(-light, input.normal));
//	float brightness = diffuse + 0.3f;
//	float4 shadecolor = float4(brightness, brightness, brightness, 1.0f);
//	//陰影とテクスチャの色を合成
//	output.target0 = shadecolor * texcolor;
//	output.target1 = float4(1 - (shadecolor * texcolor).rgb, 1);
//	return output;
//}

float4 main(VSOutput input) : SV_TARGET
{
	//面の情報をstatic変数に代入し、関数から参照できるようにする
	N = input.normal;
	//パラメータをテクスチャのRGBから取得
	s_baseColor = baseColor + baseTex.Sample(smp, input.uv).rgb;
	s_metalness = metalness + metalnessTex.Sample(smp, input.uv).r;
	s_roughness = roughness + roughnessTex.Sample(smp, input.uv).r;
	//最終的なRGB
	float3 finalRGB = float3(0, 0, 0);
	//頂点から視点への方向ベクトル
	float3 eyedir = normalize(cameraPos - input.worldpos.xyz);

	//平行光源
	for (int i = 0; i < DIRLIGHT_NUM; i++)
	{
		if (!dirLights[i].active)
		{
			continue;
		}
		//BRDFの結果とライト色を合成
		finalRGB += BRDF(dirLights[i].lightv, eyedir) * dirLights[i].lightcolor;
	}

	return float4(finalRGB, 1);
}