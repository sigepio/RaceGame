#pragma once
class Car_Oreca07;

class GameCamera:public IGameObject,Noncopyable
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();

	/// <summary>
	/// ターゲットをセットする
	/// </summary>
	/// <param name="target">ターゲット</param>
	void SetTarget(Vector3 target) {
		m_target = target;
	}

	void SetRAngle(float Angle) {
		RAngle = Angle;
	}

	void SetCarRotation(Quaternion Rotation) {
		CarRotation = Rotation;
	}


	void SetDi(Vector3 v) {
		DP = v;
	}

	/// <summary>
	/// カメラのポジションを返す
	/// </summary>
	/// <returns>カメラのポジション</returns>
	Vector3 GetCameraPos() const
	{
		return m_position;
	}

	/// <summary>
	/// カメラの前方向を返す
	/// </summary>
	/// <returns>カメラの前方向</returns>
	Vector3 GetCameraForward() const
	{
		return m_cameraForward;
	}

private:
	/////////////////////////////////////
	//メンバ変数
	/////////////////////////////////////
	Car_Oreca07* m_carbase;

	Vector3 m_position = Vector3::Zero;
	Vector3 m_cameraForward = { 0.0f,0.0f,1.0f };
	Vector3 m_toCameraPos = Vector3::Zero;			//注視点から視点に向かうベクトル
	Vector3 m_target = Vector3::Zero;
	Vector3 DP = g_vec3Zero;

	Quaternion CarRotation;
	float RAngle = 0.0f;

};

