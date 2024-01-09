#pragma once
namespace nsK2EngineLow {
	class FontRender
	{
	public:
		static const int MAX_TEXT_SIZE = 256;
		~FontRender() {

		}

		//�\�����镶���G��ݒ�
		void SetText(const wchar_t* text)
		{
			swprintf_s(m_text, text);
		}

		//�\�����镶�����擾
		const wchar_t* GetText()const {
			return m_text;
		}

		//���W�ݒ�Az��0.0f��
		void SetPosition(float x, float y, float z)
		{
			SetPosition({ x,y,z });
		}
		//���W�ݒ�
		void SetPosition(const Vector3& position) {
			m_position = position;
		}
		//���W���擾
		const Vector3& GetPosition()const
		{
			return m_position;
		}

		//�傫����ݒ�
		void SetScale(const float scale)
		{
			m_scale = scale;
		}
		//�傫�����擾
		const float GetScale() const
		{
			return m_scale;
		}

		//�F��ݒ�
		void SetColor(float r, float g, float b, float a)
		{
			SetColor({ r, g, b, a });
		}
		void SetColor(const Vector4& color)
		{
			m_color = color;
		}
		//�F���擾
		const Vector4& GetColor()const
		{
			return m_color;
		}

		//��]��ݒ�
		const float GetRotation()const
		{
			return m_rotation;
		}

		//�s�{�b�g�ݒ�
		// x = 0.5, y = 0.5�ŉ摜�̒��S����_
		// x = 0.0, y = 0.0�ŉ摜�̍���
		// x = 1.0, y = 1.0�ŉ摜�̉E��
		void SetPivot(float x, float y)
		{
			SetPivot({ x,y });
		}
		void SetPivot(const Vector2& pivot)
		{
			m_pivot = pivot;
		}
		//�s�{�b�g�̎擾
		const Vector2& GetPivot()const
		{
			return m_pivot;
		}

		//�`�揈��
		void Draw(RenderContext& rc);

		void OnDraw(RenderContext& rc)
		{
			if (m_text == nullptr)
			{
				return;
			}

			OnRender2D(rc);
		}

	private:
		void OnRender2D(RenderContext& rc)
		{
			m_font.Begin(rc);
			m_font.Draw(m_text, Vector2(m_position.x, m_position.y), m_color, m_rotation, m_scale, m_pivot);
			m_font.End(rc);
		}

	private:
		Vector3		m_position = Vector3::Zero;			//���W�B	
		float		m_scale = 1.0f;						//�����̑傫���B
		Vector4		m_color = g_vec4White;				//�����̐F�A�f�t�H���g�Ŕ��B
		float		m_rotation = 0.0f;					//��]�B
		Vector2		m_pivot = Sprite::DEFAULT_PIVOT;	//�s�{�b�g�B
		wchar_t		m_text[MAX_TEXT_SIZE];				//�����B
		Font		m_font;								//�t�H���g�B
	};
	
}

