#include"FBX.hlsli"
//0�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
Texture2D<float4> baseTex : register(t0);
//1�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
Texture2D<float4> metalnessTex : register(t1);
//2�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
Texture2D<float4> normalTex : register(t2);
//3�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
Texture2D<float4> roughnessTex : register(t3);

//0�ԃX���b�g�ɐݒ肳�ꂽ�T���v���[
SamplerState smp : register(s0);

//�A���x�h
static float3 s_baseColor;
//�����x
static float s_metalness;
//�e��
static float s_roughness;

//��
static const float PI = 3.141592654f;

//���˓_�̖@���x�N�g��
static float3 N;

struct PSOutput
{
	float4 target0 : SV_TARGET0;
	float4 target1 : SV_TARGET1;
};

//UE4��GGX���z
//alpha : roughness��2��
//NdotH : �@���ƃn�[�t�x�N�g���̓���
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

//UE4��Smith���f��
float GeometricSmith(float cosine)
{
	float k = (roughness + 1.0f);

	k = k * k / 8.0f;

	return cosine / (cosine * (1.0f - k) + k);
}

//�f�B�Y�j�[�̃t���l���v�Z
float3 DisneyFresnel(float LdotH)
{
	//F��(�t���l��:Fresnel)
	//�P�x
	float luminance = 0.3f * s_baseColor.r + 0.6f * s_baseColor.g + 0.1f * s_baseColor.b;
	//�F����
	float3 tintColor = s_baseColor / luminance;
	//������̋��ʔ��ːF���v�Z
	float3 nonMetalColor = specular * 0.08f * tintColor;
	//metalness�ɂ��F��� �����̏ꍇ�̓x�[�X�J���[
	float3 specularColor = lerp(nonMetalColor, baseColor, metalness);
	//NdotH�̊�����SchlickFresnel���
	return SchlickFresnel3(specularColor, float3(1, 1, 1), LdotH);
}

//���ʔ��˂̌v�Z
float3 CookTorranceSpecular(float NdotL, float NdotV, float NdotH, float LdotH)
{
	//D��(���z:Distribution)
	float Ds = DistributionGGX(roughness * roughness, NdotH);

	//F��(�t���l��:Fresnel)
	float3 Fs = DisneyFresnel(LdotH);

	//G��(�􉽌���:Geometry attenuation)
	float Gs = GeometricSmith(NdotL) * GeometricSmith(NdotV);

	//m��(����)
	float m = 4.0f * NdotL * NdotV;

	//�������ċ��ʔ��˂̐F�𓾂�
	return Ds * Fs * Gs / m;
}

//Schlick�ɂ��ߎ�
//f0��f90�̒l��(1-cosine)��5���lerp����
//f0 : ���������ɓ��Ђ����Ƃ��̔��˗�
//f90 : �������s�ɓ��Ђ����Ƃ��̔��˗�
//cosine : 2�x�N�g���̂Ȃ��p�̃R�T�C��(���ϒl)
float SchlickFresnel(float f0, float f90, float cosine)
{
	float m = saturate(1 - cosine);
	float m2 = m * m;
	float m5 = m2 * m2 * m;
	return lerp(f0, f90, m5);
}

//�o�������˕��z�֐�
float3 BRDF(float3 L, float3 V)
{
	//�@���ƃ��C�g�����̓���
	float NdotL = dot(N, L);
	//�@���ƃJ���������̓���
	float NdotV = dot(N, V);
	//�ǂ��炩��90�x�ȏ�ł���ΐ^������Ԃ�
	if (NdotL < 0 || NdotV < 0)
	{
		return float3(0, 0, 0);
	}

	//���C�g�����ƃJ���������̒���(�n�[�t�x�N�g��)
	float3 H = normalize(L + V);
	//�@���ƃn�[�t�x�N�g���̓���
	float NdotH = dot(N, H);
	//���C�g�ƃn�[�t�x�N�g���̓���
	float LdotH = dot(L, H);
	//�g�U���˗�
	float diffuseReflectance = 1.0f / PI;

	float energyBias = 0.5f * roughness;
	//���ˊp��90�x�̏ꍇ�̊g�U���˗�
	float Fd90 = energyBias + 2.0f * LdotH * LdotH * roughness;
	//�����Ă����Ƃ��̊g�U���˗�
	float FL = SchlickFresnel(1.0f, Fd90, NdotL);
	//�o�Ă����Ƃ��̊g�U���˗�
	float FV = SchlickFresnel(1.0f, Fd90, NdotV);
	float energyFactor = lerp(1.0f, 1.0f / 1.51f, roughness);
	//�����ďo�Ă����܂ł̊g�U���˗�
	float Fd = FL * FV * energyFactor;

	//�g�U���ˌ�
	float3 diffuseColor = diffuseReflectance * Fd * baseColor * (1 - metalness);

	//���ʔ��ˌ�
	float3 specularColor = CookTorranceSpecular(NdotL, NdotV, NdotH, LdotH);

	return diffuseColor + specularColor;
}

////�G���g���[�|�C���g
//PSOutput main(VSOutput input)
//{
//	PSOutput output;
//	//�e�N�X�`���}�b�s���O
//	float4 texcolor = tex.Sample(smp,input.uv);
//	//Lambert����
//	float3 light = normalize(float3(1, -1, 1));//�E���������̃��C�g
//	float diffuse = saturate(dot(-light, input.normal));
//	float brightness = diffuse + 0.3f;
//	float4 shadecolor = float4(brightness, brightness, brightness, 1.0f);
//	//�A�e�ƃe�N�X�`���̐F������
//	output.target0 = shadecolor * texcolor;
//	output.target1 = float4(1 - (shadecolor * texcolor).rgb, 1);
//	return output;
//}

float4 main(VSOutput input) : SV_TARGET
{
	//�ʂ̏���static�ϐ��ɑ�����A�֐�����Q�Ƃł���悤�ɂ���
	N = input.normal;
	//�p�����[�^���e�N�X�`����RGB����擾
	s_baseColor = baseColor + baseTex.Sample(smp, input.uv).rgb;
	s_metalness = metalness + metalnessTex.Sample(smp, input.uv).r;
	s_roughness = roughness + roughnessTex.Sample(smp, input.uv).r;
	//�ŏI�I��RGB
	float3 finalRGB = float3(0, 0, 0);
	//���_���王�_�ւ̕����x�N�g��
	float3 eyedir = normalize(cameraPos - input.worldpos.xyz);

	//���s����
	for (int i = 0; i < DIRLIGHT_NUM; i++)
	{
		if (!dirLights[i].active)
		{
			continue;
		}
		//BRDF�̌��ʂƃ��C�g�F������
		finalRGB += BRDF(dirLights[i].lightv, eyedir) * dirLights[i].lightcolor;
	}

	return float4(finalRGB, 1);
}