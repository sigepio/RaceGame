#pragma once
class FrontWheelBase;
class Player;

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
	//車両データの設定
	void SetNowCar(int m_nowcar) {
		m_NowCar = m_nowcar;
	}

	//右フロントタイヤのローカル座標の設定
	void SetRightRearWheelLocalPosition(Vector3 m_rightrearwheellocalposition) {
		m_LocalPosition = m_rightrearwheellocalposition;
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
	Quaternion m_FrontWheelRotationRotation;

	FrontWheelBase* m_frontwheelbase;
	Player* m_player;

	ModelRender m_FrontWheelModel;

	int m_NowCar = 0;
	int m_PauseState = 0;

	bool GameEnd = false;
};

