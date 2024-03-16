
///////////////////////////////////////
// �\���́B
///////////////////////////////////////

// �s�N�Z���V�F�[�_�[�ւ̓���
struct SPSIn
{
	float4 pos : SV_POSITION;       //���W�B
	float3 normal : NORMAL;         //�@���B
	float3 tangent  : TANGENT;      //�ڃx�N�g���B
	float3 biNormal : BINORMAL;     //�]�x�N�g���B
	float2 uv : TEXCOORD0;          //UV���W�B
	float3 worldPos : TEXCOORD1;    // ���[���h���W
};
cbuffer SkyCubeCb : register(b1)
{
    float luminance;	// ���邳�B
};


///////////////////////////////////////
// ���_�V�F�[�_�[�̋��ʏ������C���N���[�h����B
///////////////////////////////////////
#include "ModelVSCommon.h"

///////////////////////////////////////
// �V�F�[�_�[���\�[�X
///////////////////////////////////////
Texture2D<float4> g_albedo : register(t0);      //�A���x�h�}�b�v
Texture2D<float4> g_normal : register(t1);      //�@���}�b�v
Texture2D<float4> g_spacular : register(t2);    //�X�y�L�����}�b�v
TextureCube<float4> g_skyCubeMap : register(t10);

///////////////////////////////////////
// �T���v���[�X�e�[�g
///////////////////////////////////////
sampler g_sampler : register(s0);


////////////////////////////////////////////////
// �֐���`�B
////////////////////////////////////////////////

// �@���}�b�v����@�����擾�B
float3 GetNormalFromNormalMap(float3 normal, float3 tangent, float3 biNormal, float2 uv)
{
	float3 binSpaceNormal = g_normal.SampleLevel(g_sampler, uv, 0.0f).xyz;
	binSpaceNormal = (binSpaceNormal * 2.0f) - 1.0f;

	float3 newNormal = tangent * binSpaceNormal.x + biNormal * binSpaceNormal.y + normal * binSpaceNormal.z;

	return newNormal;
}

// ���f���p�̒��_�V�F�[�_�[�̃G���g���[�|�C���g
SPSIn VSMainCore(SVSIn vsIn, float4x4 mWorldLocal, uniform bool isUsePreComputedVertexBuffer)
{
	SPSIn psIn;
	// ���_���W�����[���h���W�n�ɕϊ�����B
    psIn.pos = CalcVertexPositionInWorldSpace(vsIn.pos, mWorldLocal, isUsePreComputedVertexBuffer);

	// ���_�V�F�[�_�[���烏�[���h���W���o��
	psIn.worldPos = (float3)psIn.pos;
	psIn.pos = mul(mView, psIn.pos); // ���[���h���W�n����J�������W�n�ɕϊ�
	psIn.pos = mul(mProj, psIn.pos); // �J�������W�n����X�N���[�����W�n�ɕϊ�

	// ���[���h��Ԃ̖@���A�ڃx�N�g���A�]�x�N�g�����v�Z����B
	CalcVertexNormalTangentBiNormalInWorldSpace(
		psIn.normal,
		psIn.tangent,
		psIn.biNormal,
		mWorldLocal,
		vsIn.normal,
		vsIn.tangent,
		vsIn.biNormal,
		isUsePreComputedVertexBuffer
	);
	
	psIn.uv = vsIn.uv;
	
	return psIn;
}

/// <summary>
/// �s�N�Z���V�F�[�_�[�̃G���g���[�֐��B
/// </summary>
float4 PSMain(SPSIn psIn) : SV_Target0
{
	float4 albedoColor;
	float3 normal = normalize(psIn.normal);
	//albedoColor = g_skyCubeMap.Sample(g_sampler, psIn.normal);
	albedoColor = g_skyCubeMap.Sample(g_sampler, normal * -1.0f) * luminance;
	return albedoColor;
}
