#pragma once
#include "SceneLight.h"
#include "Bloom.h"
#include "SceneGeometryData.h"

namespace nsK2EngineLow {

	class FontRender;
	class Bloom;
	class ModelRender;
	class SpriteRender;


	class RenderingEngine:public Noncopyable
	{
	public:
		RenderingEngine();
		bool Start();
		void InitShadowMap();
		void Update();
		void CalcViewProjectionMatrixForViewCulling();
		//void InitZPrepassRenderTarget();
		void InitFinalSprite();
		//void InitToonMap();
		void Init2DSprite();
		void Execute(RenderContext& rc);
		//void ZPrepass(RenderContext& rc);
		void ShadowDraw(RenderContext& rc);
		void ModelDraw(RenderContext& rc);
		void SpriteFontDraw(RenderContext& rc);
		void CopyMainRenderTargetToFrameBuffer(RenderContext& rc);
		void Init();

		//�f�B���N�V�������C�g�̐ݒ�
		void SetDirectionLight(Vector3 direction, Vector3 color)
		{
			m_sceneLight.SetDirectionLight(direction, color);
		}

		//�A���r�G���g���C�g�̐ݒ�
		void SetAmbientLight(float x, float y, float z)
		{
			m_sceneLight.SetAmbientLight(x, y, z);
		}

		//�|�C���g���C�g�̐ݒ�
		void SetPointLight(int num, Vector3 position, float range, Vector3 color)
		{
			m_sceneLight.SetPointLight(num, position, range, color);
		}

		//�X�|�b�g���C�g�̐ݒ�
		void SetSpotLight(int num, Vector3 position, float range, Vector3 color, Vector3 direction, float angle)
		{
			m_sceneLight.SetSpotLight(num, position, range, color, direction, angle);
		}

		//�������C�g�̐ݒ�
		void SetHemLight(Vector3 groundColor, Vector3 skyColor, Vector3 groundNormal)
		{
			m_sceneLight.SetHemLight(groundColor, skyColor, groundNormal);
		}

		/// <summary>
		/// �􉽊w�f�[�^��o�^
		/// </summary>
		/// <param name="geomData">�􉽊w�f�[�^</param>
		void RegisterGeometryData(GemometryData* geomData)
		{
			m_sceneGeometryData.RegisterGeometryData(geomData);
		}

		void AddModelRenderObject(ModelRender* modelRender)
		{
			//�R���e�i�̌��ɂ�������
			ModelRenderObject.push_back(modelRender);
		}
		
		void AddSpriteRenderObject(SpriteRender* spriteRender)
		{
			//�R���e�i�̌��ɂ�������
			SpriteRenderObject.push_back(spriteRender);
		}

		void AddFontRenderObject(FontRender* fontRender)
		{
			//�R���e�i�̌��ɂ�������
			FontRenderObject.push_back(fontRender);
		}

		auto GetViewProjectionMatrixForViewCulling() {
			return m_viewProjMatrixForViewCulling;
		}

		//���C�g�r���[�X�N���[���̐ݒ�
		void SetLVP(Matrix mat)
		{
			m_sceneLight.SetLVP(mat);
		}

		//�擾�n�̊֐�
		SceneLight& GetLightingCB()
		{
			return m_sceneLight;
		}

		Light& GetLightCB()
		{
			return m_sceneLight.GetLight();
		}

		RenderTarget& GetMainRenderTarget()
		{
			return m_mainRenderingTarget;
		}

		Sprite& GetFrameBufferSprite()
		{
			return m_copyToframeBufferSprite;
		}

		RenderTarget& GetShadowTarget()
		{
			return shadowMapTarget;
		}

		Camera& GetLightCamera()
		{
			return lightCamera;
		}

		

		static void CreateInstance()
		{
			m_instance = new RenderingEngine;
			m_instance->Init();
		}
		static void DeleteInstance()
		{
			delete m_instance;
		}
		/// <summary>
		/// �C���X�^���X���擾�B
		/// </summary>
		/// <returns></returns>
		static RenderingEngine* GetInstance()
		{
			return m_instance;
		}
	private:
		SceneLight m_sceneLight;
		Bloom m_bloom;
		SceneGeometryData m_sceneGeometryData;

		static RenderingEngine* m_instance;

		RenderTarget m_mainRenderingTarget;
		RenderTarget m_zprepassRenderTarget;
		RenderTarget m_2DRenderTarget;
		Sprite		 m_mainSprite;
		Sprite		 m_2DSprite;
		SpriteInitData m_spiteInitData;
		Sprite m_copyToframeBufferSprite;

		//�V���h�E�p
		RenderTarget shadowMapTarget;
		Camera lightCamera;
		float clearColor[4] = { 1.0f,1.0f,1.0f,1.0f };	//�J���[�o�b�t�@�[�͐^����

		Matrix m_viewProjMatrixForViewCulling;              // �r���[�J�����O�p�̃r���[�v���W�F�N�V�����s��B

		std::vector<ModelRender*>	ModelRenderObject;
		std::vector<SpriteRender*>	SpriteRenderObject;
		std::vector<FontRender*>	FontRenderObject;

		
	};
}

