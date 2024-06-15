#pragma once
class FrontWheelBase;

class LeftFrontWheel:public IGameObject, Noncopyable
{
public:
	LeftFrontWheel();
	~LeftFrontWheel();
	bool Start();
	void Update();
	void Move();
	void Rotation();
	void Render(RenderContext& rc);

	void SetForward(Vector3 forward) {
		m_FrontWheelForwardCatch = forward;
	}
	void SetGameEnd(bool m_GameEnd) {
		GameEnd = m_GameEnd;
	}
	//設定系関数

	//車両データの設定
	void SetNowCar(int m_nowcar) {
		m_NowCar = m_nowcar;
	}

	//左フロントタイヤのローカル座標の設定
	void SetLeftFrontWheelLocalPosition(Vector3 m_leftfrontwheellocalposition) {
		m_LocalPosition = m_leftfrontwheellocalposition;
	}

	void SetPauseState(int PauseState) {
		m_PauseState = PauseState;
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
	Quaternion m_FrontWheelLeftRotation;


	ModelRender m_FrontWheelModel;

	FrontWheelBase* m_frontwheelbase;
	
	int m_NowCar = 0;
	int m_PauseState = 0;

	bool GameEnd = false;
};

