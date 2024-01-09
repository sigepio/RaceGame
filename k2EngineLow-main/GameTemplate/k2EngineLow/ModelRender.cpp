#include "k2EngineLowPreCompile.h"
#include "ModelRender.h"

namespace nsK2EngineLow {

	ModelRender::ModelRender()
	{

	}

	ModelRender::~ModelRender()
	{

	}

	void ModelRender::Init(const char* filePath,
		bool m_shadowDrop,
		AnimationClip* animationClips,
		int numAnimationClips,
		EnModelUpAxis enModelUpAxis)
	{
		// �X�P���g�����������B
		InitSkeleton(filePath);
		// �A�j���[�V�������������B
		InitAnimation(animationClips, numAnimationClips, enModelUpAxis);


		//���f���̏�����
		ModelInitDataFR modelInitData;
		//�e���𗎂Ƃ��������Ƃ��������ŃV�F�[�_�[��ς���
		if (m_shadowDrop == true) {
			// ���f���̏�����
			modelInitData.m_tkmFilePath = filePath;
			modelInitData.m_fxFilePath = "Assets/shader/model.fx";
			modelInitData.m_expandConstantBuffer = &RenderingEngine::GetInstance()->GetLightCB();
			modelInitData.m_expandConstantBufferSize = sizeof(RenderingEngine::GetInstance()->GetLightCB());
			modelInitData.m_modelUpAxis = enModelUpAxis;

		//	//�֊s���̏���
		//	//�g��SRV��ZPrepass�ō쐬���ꂽ�[�x�e�N�X�`�����w�肷��
		//	modelInitData.m_expandShaderResoruceView[0] = RenderingEngine::GetInstance()->GetZPrepassDepthTexture();
		//	//ZPrepass�̏�����
		//	InitCommon(filePath, animationClips);


			// �V���h�E�}�b�v�ɕ`�悷�郂�f����������
			ModelInitData shadowModelInitData;
			shadowModelInitData.m_tkmFilePath = filePath;
			shadowModelInitData.m_fxFilePath = "Assets/shader/sampleDrawShadowMap.fx";
			//shadowModelInitData.m_psEntryPointFunc = "PSShadowMain";
			shadowModelInitData.m_modelUpAxis = enModelUpAxis;
			// �J���[�o�b�t�@�[�̃t�H�[�}�b�g�ɕύX���������̂ŁA��������ύX����
			shadowModelInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32_FLOAT;

			//�A�j���[�V�����L���ŃG���g���[�|�C���g��ς���
			if (animationClips != nullptr) {
				shadowModelInitData.m_skeleton = &m_skeleton;
				shadowModelInitData.m_vsSkinEntryPointFunc = "VSSkinMain";
			}
			else {
				shadowModelInitData.m_vsEntryPointFunc = "VSMain";
			}

			m_shadowModel.Init(shadowModelInitData);
		}
		else {
			// �e���󂯂�w�i���f����������
			modelInitData.m_tkmFilePath = filePath;
			// �V���h�E���V�[�o�[(�e�����Ƃ���郂�f��)�p�̃V�F�[�_�[���w�肷��
			modelInitData.m_fxFilePath = "Assets/shader/shadowReciever.fx";
			// �V���h�E�}�b�v���g��SRV�ɐݒ肷��
			modelInitData.m_expandShaderResoruceView[1] = &RenderingEngine::GetInstance()->GetShadowTarget().GetRenderTargetTexture();
			// ���C�g�r���[�v���W�F�N�V�����s����g���萔�o�b�t�@�[�ɐݒ肷��
			modelInitData.m_expandConstantBuffer = &RenderingEngine::GetInstance()->GetLightCB();
			modelInitData.m_expandConstantBufferSize = sizeof(RenderingEngine::GetInstance()->GetLightCB());
		}

		//�A�j���[�V�����L���ŃG���g���[�|�C���g��ς���
		if (animationClips != nullptr) {
			modelInitData.m_skeleton = &m_skeleton;
			modelInitData.m_vsSkinEntryPointFunc = "VSSkinMain";
		}
		else {
			modelInitData.m_vsEntryPointFunc = "VSMain";
		}

		m_model.Init(modelInitData);
	}

	void ModelRender::InitCommon(const char* tkmFilePath, AnimationClip* animationClips)
	{
		// ZPrepass�`��p�̃��f����������
		ModelInitData modelInitData;
		modelInitData.m_tkmFilePath = tkmFilePath;
		modelInitData.m_fxFilePath = "Assets/shader/ZPrepass.fx";
		modelInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32_FLOAT;

		//�A�j���[�V�����L���ŃG���g���[�|�C���g��ς���
		if (animationClips != nullptr) {
			modelInitData.m_skeleton = &m_skeleton;
			modelInitData.m_vsSkinEntryPointFunc = "VSSkinMain";
		}
		else {
			modelInitData.m_vsEntryPointFunc = "VSMain";
		}

		m_zprepassModel.Init(modelInitData);
	}

	void ModelRender::Update(bool m_syuzinkou)
	{
		//���f�����Ɉړ���]�g���n��
		m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
		//�e�̃��f���Ɉړ���]�g���n��
		m_shadowModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
		//�֊s���Ɉړ���]�g���n��
		m_zprepassModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);

		if (m_skeleton.IsInited()) {
			m_skeleton.Update(m_model.GetWorldMatrix());
		}
		//�A�j���[�V������i�߂�B
		m_animation.Progress(g_gameTime->GetFrameDeltaTime() * m_animationSpeed);

		//��l���Ȃ烉�C�g�J������ǔ�������
		if (m_syuzinkou == true) {
			syuok = true;
		}
		else {
			syuok = false;
		}
	}

	void ModelRender::InitAnimation(AnimationClip* animationClips, int numAnimationClips, EnModelUpAxis enModelUpAxis)
	{
		m_animationClips = animationClips;
		m_numAnimationClips = numAnimationClips;
		if (m_animationClips != nullptr) {
			m_animation.Init(m_skeleton,
				m_animationClips,
				numAnimationClips);
		}
	}

	void ModelRender::InitSkeleton(const char* filePath)
	{
		//�X�P���g���̃f�[�^��ǂݍ��݁B
		std::string skeletonFilePath = filePath;
		int pos = (int)skeletonFilePath.find(".tkm");
		skeletonFilePath.replace(pos, 4, ".tks");
		m_skeleton.Init(skeletonFilePath.c_str());
	}

	void ModelRender::InitSkyCubeModel(ModelInitData& initData)
	{
		m_model.Init(initData);
	}

	void ModelRender::Draw(RenderContext& rc)
	{
		
		RenderingEngine::GetInstance()->AddModelRenderObject(this);
		/*RenderingEngine::GetInstance()Add3DModelToZPrepass(m_zprepassModel);*/
	}
}
