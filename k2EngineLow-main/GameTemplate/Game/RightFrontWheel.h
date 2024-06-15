#pragma once
class FrontWheelBase;

class RightFrontWheel:public IGameObject,Noncopyable
{
public:
	RightFrontWheel();
	~RightFrontWheel();
	bool Start();
	void Update();
	void Move();
	void Rotation();
	void Render(RenderContext& rc);


	void SetForward(Vector3 forward) {
		m_FrontWheelForwardCatch = forward;
	}
	//車両データの設定
	void SetNowCar(int m_nowcar) {
		m_NowCar = m_nowcar;
	}

	//右フロントタイヤのローカル座標の設定
	void SetRightFrontWheelLocalPosition(Vector3 m_rightfrontwheellocalposition) {
		m_LocalPosition = m_rightfrontwheellocalposition;
	}

	void SetPauseState(int PauseState) {
		m_PauseState = PauseState;
	}
	void SetGameEnd(bool m_GameEnd) {
		GameEnd = m_GameEnd;
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
	Quaternion m_FrontWheelRightRotation;
	

	ModelRender m_FrontWheelModel;

	FrontWheelBase* m_frontwheelbase;

	int m_NowCar = 0;
	int m_PauseState = 0;

	bool GameEnd = false;
};

