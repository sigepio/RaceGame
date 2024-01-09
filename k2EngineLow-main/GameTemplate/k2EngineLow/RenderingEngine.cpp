#include "k2EngineLowPreCompile.h"
#include "RenderingEngine.h"

namespace nsK2EngineLow {
	RenderingEngine* RenderingEngine::m_instance = nullptr;

	RenderingEngine::RenderingEngine()
	{
		// MainRenderTarget�Z�b�g
		m_mainRenderingTarget.Create(
			g_graphicsEngine->GetFrameBufferWidth(),    // �e�N�X�`���̕�
			g_graphicsEngine->GetFrameBufferHeight(),   // �e�N�X�`���̍���
			1,											// Mipmap���x��
			1,											// �e�N�X�`���z��̃T�C�Y
			DXGI_FORMAT_R32G32B32A32_FLOAT,				// �J���[�o�b�t�@�̃t�H�[�}�b�g
			DXGI_FORMAT_D32_FLOAT						// �f�v�X�X�e���V���o�b�t�@�̃t�H�[�}�b�g
		);



		//2D(�t�H���g��X�v���C�g)�p�̏�����
		Init2DSprite();

		// �u���[���̏�����
		//m_bloom.Init(m_mainRenderingTarget);

		// �V���h�E�ׂ̈̏�����
		InitShadowMap();

		// �ŏI�I�ȃe�N�X�`���𒣂�t���邽�߂̃X�v���C�g��������
		InitFinalSprite();
	}

	void RenderingEngine::Init() {

	}

	bool RenderingEngine::Start()
	{
		return true;
	}

	

	void RenderingEngine::InitShadowMap()
	{
		//���C�g�J�����̏�����̐ݒ�
		//lightCamera.SetUp(0, 1, 0);
		lightCamera.SetUp(1, 0, 0);
		SetLVP(lightCamera.GetViewProjectionMatrix());

		//�V���h�E�}�b�v�p�̃^�[�Q�b�g�̍쐬
		shadowMapTarget.Create(
			13240,	//�𑜓x
			13240,
			1,
			1,
			DXGI_FORMAT_R32_FLOAT,
			DXGI_FORMAT_D32_FLOAT,
			clearColor
		);
	}

	void RenderingEngine::Init2DSprite()
	{
		float clearColor[4] = { 0.0f,0.0f,0.0f,0.0f };

		//2D�p�̃^�[�Q�b�g�̏�����
		m_2DRenderTarget.Create(
			m_mainRenderingTarget.GetWidth(),
			m_mainRenderingTarget.GetHeight(),
			1,
			1,
			DXGI_FORMAT_R8G8B8A8_UNORM,
			DXGI_FORMAT_UNKNOWN,
			clearColor
		);

		// �ŏI�����p�̃X�v���C�g������������
		SpriteInitData spriteInitData;
		//�e�N�X�`����2D�����_�\�^�[�Q�b�g�B
		spriteInitData.m_textures[0] = &m_2DRenderTarget.GetRenderTargetTexture();
		// �𑜓x��mainRenderTarget�̕��ƍ���
		spriteInitData.m_width = m_mainRenderingTarget.GetWidth();
		spriteInitData.m_height = m_mainRenderingTarget.GetHeight();
		// 2D�p�̃V�F�[�_�[���g�p����
		spriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";
		spriteInitData.m_vsEntryPointFunc = "VSMain";
		spriteInitData.m_psEntryPoinFunc = "PSMain";
		//�㏑���B
		spriteInitData.m_alphaBlendMode = AlphaBlendMode_None;
		//�����_�����O�^�[�Q�b�g�̃t�H�[�}�b�g�B
		spriteInitData.m_colorBufferFormat[0] = m_mainRenderingTarget.GetColorBufferFormat();

		m_2DSprite.Init(spriteInitData);

		//�e�N�X�`���̓��C�������_�\�^�[�Q�b�g�B
		spriteInitData.m_textures[0] = &m_mainRenderingTarget.GetRenderTargetTexture();

		//�𑜓x��2D�����_�\�^�[�Q�b�g�̕��ƍ���
		spriteInitData.m_width = m_2DRenderTarget.GetWidth();
		spriteInitData.m_height = m_2DRenderTarget.GetHeight();
		//�����_�����O�^�[�Q�b�g�̃t�H�[�}�b�g�B
		spriteInitData.m_colorBufferFormat[0] = m_2DRenderTarget.GetColorBufferFormat();

		m_mainSprite.Init(spriteInitData);
	}

	void RenderingEngine::InitFinalSprite()
	{
		m_spiteInitData.m_textures[0] = &m_mainRenderingTarget.GetRenderTargetTexture();
		m_spiteInitData.m_width = m_mainRenderingTarget.GetWidth();
		m_spiteInitData.m_height = m_mainRenderingTarget.GetHeight();
		m_spiteInitData.m_fxFilePath = "Assets/shader/sprite.fx";
		m_copyToframeBufferSprite.Init(m_spiteInitData);
	}

	void RenderingEngine::Execute(RenderContext& rc)
	{

		// �V���h�E�̕`��
		ShadowDraw(rc);

		// ���f���̕`��
		ModelDraw(rc);

		//�����ŃG�t�F�N�g�h���[�B
		EffectEngine::GetInstance()->Draw();

		// �摜�ƕ����̕`��
		SpriteFontDraw(rc);

		//�u���[����K�p(ON.OFF�ύX��)
		//m_bloom.Render(rc, m_mainRenderingTarget);

		// ���C�������_�����O�^�[�Q�b�g�̊G���t���[���o�b�t�@�ɃR�s�[
		CopyMainRenderTargetToFrameBuffer(rc);


		// �N���A
		ModelRenderObject.clear();
		SpriteRenderObject.clear();
		FontRenderObject.clear();
	}

	void RenderingEngine::ShadowDraw(RenderContext& rc)
	{
		//�^�[�Q�b�g���V���h�E�}�b�v�ɕύX
		rc.WaitUntilFinishDrawingToRenderTarget(shadowMapTarget);
		rc.SetRenderTargetAndViewport(shadowMapTarget);
		rc.ClearRenderTargetView(shadowMapTarget);

		// �܂Ƃ߂ĉe���f�������_�[��`��
		for (auto MobjData : ModelRenderObject)
		{
			//��l���Ȃ烉�C�g�J�������X�V
			//if (MobjData->GetSyuzinkou() == true) {
				//���C�g�J�����̍X�V
				//lightCamera.SetPosition(MobjData->GetPositionX() + 600.0f, MobjData->GetPositionY() + 800.0f, MobjData->GetPositionZ());
				lightCamera.SetPosition(MobjData->GetPositionX(), MobjData->GetPositionY() + 5000.0f, MobjData->GetPositionZ());
				lightCamera.SetTarget(MobjData->GetPositionX(), MobjData->GetPositionY(), MobjData->GetPositionZ());
				lightCamera.Update();
			//}
			//���C�g�r���[�Z�b�g
			SetLVP(lightCamera.GetViewProjectionMatrix());
			//�e���f���̕`��
			MobjData->OnShadowDraw(rc);
			rc.WaitUntilFinishDrawingToRenderTarget(shadowMapTarget);
		}
	}

	void RenderingEngine::ModelDraw(RenderContext& rc)
	{
		// ���C���̃^�[�Q�b�g���g����悤�ɂȂ�܂ő҂�
		rc.WaitUntilToPossibleSetRenderTarget(m_mainRenderingTarget);
		// �^�[�Q�b�g�Z�b�g
		rc.SetRenderTargetAndViewport(m_mainRenderingTarget);
		// �^�[�Q�b�g�̃N���A
		rc.ClearRenderTargetView(m_mainRenderingTarget);

		// �܂Ƃ߂ă��f�������_�[��`��
		for (auto MobjData : ModelRenderObject) {
			MobjData->OnDraw(rc);
		}

		// �`�悳���܂ő҂�
		rc.WaitUntilFinishDrawingToRenderTarget(m_mainRenderingTarget);
	}

	void RenderingEngine::SpriteFontDraw(RenderContext& rc)
	{
		// 2D�p�̃^�[�Q�b�g���g����悤�ɂȂ�܂ő҂�
		rc.WaitUntilToPossibleSetRenderTarget(m_2DRenderTarget);
		// �^�[�Q�b�g�Z�b�g
		rc.SetRenderTargetAndViewport(m_2DRenderTarget);
		// �^�[�Q�b�g�̃N���A
		rc.ClearRenderTargetView(m_2DRenderTarget);

		m_mainSprite.Draw(rc);

		// �X�v���C�g�ƕ�����`��
		for (auto SobjData : SpriteRenderObject) {
			SobjData->OnDraw(rc);
		}
		for (auto FobjData : FontRenderObject) {
			FobjData->OnDraw(rc);
		}

		// �`�悳���܂ő҂�
		rc.WaitUntilFinishDrawingToRenderTarget(m_2DRenderTarget);
		//�^�[�Q�b�g�����C���ɖ߂�
		rc.WaitUntilToPossibleSetRenderTarget(m_mainRenderingTarget);
		rc.SetRenderTargetAndViewport(m_mainRenderingTarget);
		m_2DSprite.Draw(rc);
		rc.WaitUntilFinishDrawingToRenderTarget(m_mainRenderingTarget);
	}

	void RenderingEngine::CopyMainRenderTargetToFrameBuffer(RenderContext& rc)
	{
		// �t���[���o�b�t�@�ɃZ�b�g
		rc.SetRenderTarget(
			g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
			g_graphicsEngine->GetCurrentFrameBuffuerDSV()
		);


		m_copyToframeBufferSprite.Draw(rc);
	}
}