#pragma once
class FrontWheelBase;

class RightRearWheel :public IGameObject, Noncopyable
{
public:
	RightRearWheel();
	~RightRearWheel();
	bool Start();
	void Update();
	void Rotation();
	void Render(RenderContext& rc);


	void SetForward(Vector3 forward) {
		m_FrontWheelForwardCatch = forward;
	}
	//�ԗ��f�[�^�̐ݒ�
	void SetNowCar(int m_nowcar) {
		m_NowCar = m_nowcar;
	}

	//�E�t�����g�^�C���̃��[�J�����W�̐ݒ�
	void SetRightRearWheelLocalPosition(Vector3 m_rightrearwheellocalposition) {
		m_LocalPosition = m_rightrearwheellocalposition;
	}

private:
	Vector3 m_FrontWheelPosition = Vector3::Zero;
	Vector3 m_LocalPosition;
	Vector3 m_FrontWheelForward = { 0.0f,0.0f,1.0f };
	Vector3 m_FrontWheelForwardCatch = { 0.0f,0.0f,1.0f };
	Vector3 LsatStickL;

	Quaternion OriginRotation;
	Quaternion m_FrontWheelRotation;
	Quaternion m_FrontWheelLocalRotation;
	Quaternion m_FrontWheelRotationRotation;

	FrontWheelBase* m_frontwheelbase;

	ModelRender m_FrontWheelModel;

	int m_NowCar = 0;
};

