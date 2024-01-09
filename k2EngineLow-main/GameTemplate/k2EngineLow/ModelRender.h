#pragma once
namespace nsK2EngineLow {
	struct ModelInitDataFR :public ModelInitData
	{
		ModelInitDataFR()
		{
			m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;
		}
	};

	class ModelRender
	{
	public:
		ModelRender();
		~ModelRender();
		void InitCommon(const char* tkmFiliPath, AnimationClip* animationClips);
		void InitSkyCubeModel(ModelInitData& initData);
		
		//������
		void Init(const char* filePath,
			bool m_shadowDrop = true,//�e(true���e����)
			AnimationClip* animationClips = nullptr,
			int numAnimationClips = 0,
			EnModelUpAxis enModelUpAxis = enModelUpAxisZ);
		//�A�b�v�f�[�g
		void Update(bool m_syuzinkou = false);
		//�`�揈��
		void Draw(RenderContext& rc);

		//���W�ݒ�
		void SetPosition(const Vector3& pos) {
			m_position = pos;//�����ɐݒ肵�����W�f�[�^����
		}
		//������float�^�̕ϐ�3����͂�����Vector3�^�ɕϊ�����SetPosition(Vector3)�֐����Ăяo��
		void SetPosition(float x, float y, float z) {
			SetPosition({ x,y,z });
		}
		//������float�^�̓����ϐ�����͂�����Vector3�^�ɕϊ�����SetPosition(Vector3)�֐����Ăяo��
		void SetPosition(float xyz) {
			SetPosition({ xyz,xyz,xyz });
		}

		//��]����
		void SetRotation(const Quaternion& rotation) {
			m_rotation = rotation;//�����ɐݒ肵��Quaternion�f�[�^����
		}
		
		//�g��ݒ�
		void SetScale(const Vector3& scale) {
			m_scale = scale;//�����ɐݒ肵��Vector3�f�[�^����
		}
		void SetScale(float x, float y, float z) {
			SetScale({ x,y,z });
		}
		void SetScale(float xyz) {
			SetScale({ xyz,xyz,xyz });
		}

		//���W�g���]���ׂĂ�ݒ�
		void SetTRS(const Vector3& pos, const Quaternion& rotation, const Vector3 scale) {
			SetPosition(pos);
			SetRotation(rotation);
			SetScale(scale);
		}

		//���f�����擾
		Model& GetModel() {
			return m_model;
		}

		//���f���̍��W���擾
		Vector3& GetPosition() {
			return m_position;
		}

		//���f����X���W���擾
		float& GetPositionX() {
			return m_position.x;
		}
		//���f����Y���W���擾
		float& GetPositionY() {
			return m_position.y;
		}
		//���f����Z���W���擾
		float& GetPositionZ() {
			return m_position.z;
		}

		bool& GetSyuzinkou() {
			return syuok;
		}

		//�A�j���[�V�����̍Đ�
		void PlayAnimation(int animNo, float interpolateTime = 0.0f) {//�A�j���[�V�����N���b�v�̔ԍ��A�A�j���[�V�����̐؂�ւ������炩�ɂ��鎞��
			Now_Animation_Number = animNo;//�����̃A�j���[�V�����i���o�[����
			m_animation.Play(animNo, interpolateTime);
		}

		//�A�j���[�V�����N���b�v�̃i���o�[���擾
		int GetAnimNum() {
			return Now_Animation_Number;
		}

		void OnDraw(RenderContext& rc) {
			m_model.Draw(rc,1);
		}

		void OnShadowDraw(RenderContext& rc)
		{
			m_shadowModel.Draw(rc, RenderingEngine::GetInstance()->GetLightCamera());
		}

		void PlayFlash() {
			m_flashFlag = true;
		}
		private:
			//�A�j���[�V�����̏�����
			void InitAnimation(AnimationClip* animationClips,	//�A�j���[�V�����N���b�v
				int numAnimationClips,							//�A�j���[�V�����N���b�v�̐�
				EnModelUpAxis enModelUpAxis);					//���f���̏����

			//�X�P���g���̏�����
			void InitSkeleton(const char* filePath);
		public:

		private:
			//���f��
			Model m_model;
			Model m_shadowModel;
			Model m_zprepassModel;		//ZPrepass�ŕ`�悳��郂�f��

			//�A�j���[�V����
			Animation m_animation;
			AnimationClip* m_animationClips;
			int m_numAnimationClips = 0;
			Skeleton m_skeleton;
			float m_animationSpeed = 1.0f;

			//���W�E��]�E�傫��
			Vector3 m_position = Vector3::Zero;
			Quaternion m_rotation = { 0.0f,0.0f,0.0f,1.0f };
			Vector3 m_scale = Vector3::One;

			bool syuok = false;
			bool m_flashFlag = false;

			int Now_Animation_Number = -1;
	};

}



