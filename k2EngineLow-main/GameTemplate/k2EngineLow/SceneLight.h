#pragma once

namespace nsK2EngineLow {
	//�f�B���N�V�������C�g�\����
	struct DirectionLight
	{
		Vector3 ligDirection;
		float pad0;
		Vector3 ligColor;
	};
	//�|�C���g���C�g�\����
	struct PointLight
	{
		Vector3 ligPosition;
		float pad0;
		Vector3 ligColor;
		float ligRange;
	};
	//�X�|�b�g���C�g�\����
	struct SpotLight
	{
		Vector3 ligPosition;
		float pad0;
		Vector3 ligColor;
		float ligRange;
		Vector3 ligDirection;
		float ligAngle;
	};
	//�����C�g�\����
	struct HemLight
	{
		Vector3 groundColor;
		float pad0;
		Vector3 skyColor;
		float pad1;
		Vector3 groundNormal;
	};

	//���C�g�\����
	struct Light
	{
		DirectionLight directionLight;	//�f�B���N�V�������C�g�̔z��
		float pad0;
		Vector3 eyePos;					//���_�̈ʒu
		float pad1;
		Vector3 ambientLight;			//����
		float pad2;
		//
		PointLight pointLight[10];		//�|�C���g���C�g�̔z��
		SpotLight spotLight[10];		//�X�|�b�g���C�g�̔z��
		HemLight hemLight;				//�������C�g�̔z��
		float pad3;
		//
		Matrix m_LVP;					//���C�g�r���[�X�N���[���z��
	};
	class SceneLight
	{
	public:
		//������
		void Init()
		{
			m_light.eyePos = g_camera3D->GetPosition();
		}

		void SetDirectionLight(Vector3 direction, Vector3 color)
		{
			m_light.directionLight.ligDirection = direction;
			m_light.directionLight.ligColor = color;
		}
		void SetAmbientLight(float x, float y, float z)
		{
			m_light.ambientLight.x = x;
			m_light.ambientLight.y = y;
			m_light.ambientLight.z = z;
		}
		void SetPointLight(int num, Vector3 position, float range, Vector3 color)
		{
			m_light.pointLight[num].ligPosition = position;
			m_light.pointLight[num].ligRange = range;
			m_light.pointLight[num].ligColor = color;
		}
		void SetSpotLight(int num, Vector3 position, float range, Vector3 color, Vector3 direction, float angle)
		{
			m_light.spotLight[num].ligPosition = position;
			m_light.spotLight[num].ligRange = range;
			m_light.spotLight[num].ligColor = color;
			m_light.spotLight[num].ligDirection = direction;
			m_light.spotLight[num].ligAngle = angle;
		}
		void SetHemLight(Vector3 groundColor, Vector3 skyColor, Vector3 groundNormal)
		{
			m_light.hemLight.groundColor = groundColor;
			m_light.hemLight.skyColor = skyColor;
			m_light.hemLight.groundNormal = groundNormal;
		}
		void SetLVP(Matrix mat)
		{
			m_light.m_LVP = mat;
		}
		Light& GetLight()
		{
			return m_light;
		}
	private:
		Light m_light;	//�V�[�����C�g
	};
}


