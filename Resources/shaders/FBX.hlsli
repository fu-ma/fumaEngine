cbuffer cbuff0 : register(b0)
{
	matrix viewproj;//�r���[�v���W�F�N�V�����s��
	matrix world;//���[���h�s��
	float3 cameraPos;//�J�������W�i���[���h�j
};

//�}�e���A��
cbuffer cbuff1 : register(b1)
{
	//�A���x�h
	float3 baseColor;
	//�����x
	float metalness;
	//���ʔ��ˋ��x
	float specular;
	//�e��
	float roughness;
}

//�o�[�e�b�N�X�o�b�t�@�[�̓���
struct VSInput
{
	float4 pos:POSITION;//�ʒu
	float3 normal:NORMAL;//���_�@��
	float2 uv:TEXCOORD;//�e�N�X�`���[���W
	uint4 boneIndices:BONEINDICES;//�{�[���̔ԍ�
	float4 boneWeights:BONEWEIGHTS;//�{�[���̃X�L���E�F�C�g
};

//���_�V�F�[�_�[����s�N�Z���V�F�[�_�[�ւ̂����Ɏg�p����\����
struct VSOutput
{
	float4 svpos:SV_POSITION;//�V�X�e���p���_���W
	float3 worldpos:POS;//���[���h���W
	float3 normal:NORMAL;//�@��
	float2 uv:TEXCOORD;//uv�l
};

//�{�[���̍ő吔
static const int MAX_BONES = 32;

cbuffer skinning:register(b3)//�{�[���̃X�L�j���O�s�񂪓���
{
	matrix matSkinning[MAX_BONES];
};

//���s�����̐�
static const int DIRLIGHT_NUM = 3;

struct DirLight
{
	float3 lightv;//���C�g�����̒P�ʃx�N�g��
	float3 lightcolor;//���C�g�̐F(RGB)
	uint active;
};

//�_�����̐�
static const int POINTLIGHT_NUM = 3;

struct PointLight
{
	float3 lightpos;//���C�g���W
	float3 lightcolor;//���C�g�̐F(RGB)
	float3 lightatten;//���C�g�̋��������W��
	uint active;
};

//�X�|�b�g���C�g�̐�
static const int SPOTLIGHT_NUM = 3;

struct SpotLight
{
	float3 lightv;//���C�g�̌��������̋t�x�N�g���i�P�ʃx�N�g���j
	float3 lightpos;//���C�g���W
	float3 lightcolor;//���C�g�̐F(RGB)
	float3 lightatten;//���C�g���������W��
	float2 lightfactranglecos;//���C�g�����p�x�̃R�T�C��
	uint active;
};


//�萔�o�b�t�@(���C�g���)
cbuffer cbuff2 : register(b2)
{
	float3 ambientLightColor;
	DirLight dirLights[DIRLIGHT_NUM];
	PointLight pointLights[POINTLIGHT_NUM];
	SpotLight spotLights[SPOTLIGHT_NUM];
}