#include "k2EngineLowPreCompile.h"
#include "Bloom.h"
namespace nsK2EngineLow {
	Bloom::Bloom()
	{

	}

	Bloom::~Bloom()
	{

	}

	void Bloom::Init(RenderTarget& renderTarget)
	{
		// luminanceRenderTarget(�P�x���o)�Z�b�g
		luminanceRenderTarget.Create(
			1280,    // �e�N�X�`���̕�
			720,   // �e�N�X�`���̍���
			1,											// Mipmap���x��
			1,											// �e�N�X�`���z��̃T�C�Y
			DXGI_FORMAT_R32G32B32A32_FLOAT,				// �J���[�o�b�t�@�̃t�H�[�}�b�g
			DXGI_FORMAT_D32_FLOAT						// �f�v�X�X�e���V���o�b�t�@�̃t�H�[�}�b�g
		);


		// �P�x���o�X�v���C�g�̏�����
		luminanceSpriteInitData.m_fxFilePath = "Assets/shader/PostEffect.fx";
		luminanceSpriteInitData.m_vsEntryPointFunc = "VSMain";
		luminanceSpriteInitData.m_psEntryPoinFunc = "PSSamplingLuminance";
		luminanceSpriteInitData.m_width = g_graphicsEngine->GetFrameBufferWidth();
		luminanceSpriteInitData.m_height = g_graphicsEngine->GetFrameBufferHeight();
		luminanceSpriteInitData.m_textures[0] = &renderTarget.GetRenderTargetTexture();
		luminanceSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;
		m_luminanceSprite.Init(luminanceSpriteInitData);


		// �K�E�V�A���u���[
		gaussianBlur[0].Init(&luminanceRenderTarget.GetRenderTargetTexture());
		gaussianBlur[1].Init(&gaussianBlur[0].GetBokeTexture());
		gaussianBlur[2].Init(&gaussianBlur[1].GetBokeTexture());
		gaussianBlur[3].Init(&gaussianBlur[2].GetBokeTexture());


		// �{�P�摜�p�X�v���C�g�̏�����
		finalSpriteInitData.m_textures[0] = &gaussianBlur[0].GetBokeTexture();
		finalSpriteInitData.m_textures[1] = &gaussianBlur[1].GetBokeTexture();
		finalSpriteInitData.m_textures[2] = &gaussianBlur[2].GetBokeTexture();
		finalSpriteInitData.m_textures[3] = &gaussianBlur[3].GetBokeTexture();

		finalSpriteInitData.m_width = renderTarget.GetWidth();
		finalSpriteInitData.m_height = renderTarget.GetHeight();
		// �{�P�摜����������K�v������̂�2D�p�V�F�[�_�[�ł͂Ȃ���p�V�F�[�_�[�𗘗p����
		finalSpriteInitData.m_fxFilePath = "Assets/shader/PostEffect.fx";
		finalSpriteInitData.m_psEntryPoinFunc = "PSBloomFinal";
		// ���������Z�����ŕ`�悷��̂ŃA���t�@�u�����f�B���O���[�h�����Z�ɂ���
		finalSpriteInitData.m_alphaBlendMode = AlphaBlendMode_Add;
		finalSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;
		m_finalSprite.Init(finalSpriteInitData);
	}

	void Bloom::Update()
	{

	}

	void Bloom::Render(RenderContext& rc, RenderTarget& renderTarget)
	{
		// �P�x���o�p�^�[�Q�b�g�ɕύX���g����悤�ɂȂ�܂ő҂�
		rc.WaitUntilToPossibleSetRenderTarget(luminanceRenderTarget);
		// �^�[�Q�b�g�Z�b�g
		rc.SetRenderTargetAndViewport(luminanceRenderTarget);
		// �^�[�Q�b�g�̃N���A
		rc.ClearRenderTargetView(luminanceRenderTarget);
		//�`�悵�ďI���܂ő҂�
		m_luminanceSprite.Draw(rc);
		rc.WaitUntilFinishDrawingToRenderTarget(luminanceRenderTarget);
		// luminanceRenderTarget�I��



		//�K�E�V�A���u���[�̎��s(�ڂ���)
		gaussianBlur[0].ExecuteOnGPU(rc, 10);
		gaussianBlur[1].ExecuteOnGPU(rc, 10);
		gaussianBlur[2].ExecuteOnGPU(rc, 10);
		gaussianBlur[3].ExecuteOnGPU(rc, 10);



		// MainRenderTarget�Z�b�g
		rc.WaitUntilToPossibleSetRenderTarget(renderTarget);
		rc.SetRenderTargetAndViewport(renderTarget);
		//�{�P�摜�����C�������_�����O�^�[�Q�b�g�ɉ��Z����(mainrenderTarget�ƃu���[��������)
		m_finalSprite.Draw(rc);
		// �I���҂�
		rc.WaitUntilFinishDrawingToRenderTarget(renderTarget);
	}
}
