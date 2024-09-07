#pragma once
class Car_Oreca07;
class Player;
class Car_86GT;

class GameCamera:public IGameObject,Noncopyable
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();
	void TitleSet(int TitleState);

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

	void SetPauseState(int PauseState) {
		m_PauseState = PauseState;
	}

	void SetDi(Vector3 v) {
		DP = v;
	}

	void SetFrontWheelForwardCatch(Vector3 m_FrontWheelForwardCatch) {
		FrontWheelForwardCatch = m_FrontWheelForwardCatch;
	}

	void SetGameEnd(bool m_GameEnd) {
		GameEnd = m_GameEnd;
	}

	void SetPlayFlag(bool m_PlayFlag) {
		PlayFlag = m_PlayFlag;
	}

	void SetMainRaceManagerFlag(bool m_MainRaceManagerFlag) {
		MainRaceManagerFlag = m_MainRaceManagerFlag;
	}

	void SetTurningAngle(float m_TurningAngle) {
		TurningAngle = m_TurningAngle;
	}

	void SetMAIN_TO_CAMERA_POS(Vector3 toCameraPos) {
		MAIN_TO_CAMERA_POS = toCameraPos;
	}
	void SetTargetPoint(Vector3 m_TargetPoint) {
		TargetPoint = m_TargetPoint;
	}
	void SetViewpointDirectionCorrectionByVehicleType(Vector3 m_ViewpointDirectionCorrectionByVehicleType) {
		ViewpointDirectionCorrectionByVehicleType = m_ViewpointDirectionCorrectionByVehicleType;
	}
	void SetViewpointMode(bool m_ViewpointMode) {
		ViewpointMode = m_ViewpointMode;
	}
	void SetViewpointHeight(float m_ViewpointHeight) {
		ViewpointHeight = m_ViewpointHeight;
	}

	void SetTitleMode(bool m_TitleMode) {
		TitleMode = m_TitleMode;
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
	Car_Oreca07* m_ORECA07;
	Player* m_player;
	Car_86GT* m_86GT;

	Vector3 m_position = Vector3::Zero;
	Vector3 m_cameraForward = { 0.0f,0.0f,1.0f };
	Vector3 m_toCameraPos = Vector3::Zero;			//注視点から視点に向かうベクトル
	Vector3 m_target = Vector3::Zero;
	
	Vector3 DP = g_vec3Zero;
	Vector3 FrontWheelForwardCatch = g_vec3Zero;
	Vector3 LastDP = { 0.0f,0.0f,1.0f };
	Vector3 m_cameraPosition= { -150.0f,10.0f,.0f };
	Vector3 MAIN_TO_CAMERA_POS = g_vec3Zero;
	Vector3 TargetPoint = g_vec3Zero;
	Vector3 ViewpointDirectionCorrection = g_vec3Zero;
	Vector3 ViewpointDirectionCorrectionByVehicleType = g_vec3Zero;
	Vector3 titlepos = g_vec3Zero;

	Quaternion CarRotation;
	float RAngle = 0.0f;
	float ThrottleOpening = 0.0f;
	float TurningAngle = 0.0f;
	float CameraEvacuate = 0.0f;
	float TargetEvacuate = 0.0f;
	float UpTarget = 10.0f;
	float ViewpointHeight = 0.0f;

	int m_PauseState = 0;
	int PlayReset = 0;
	int LobbyCount = 0;
	int NowCar = -1;

	int TitleCount = 0;
	int TitleState = 0;

	bool ViewpointMode = false;//true:俯瞰(-) false:ボンネット(+)
	bool MainRaceManagerFlag = false;

	bool PlayFlag = false;
	bool GameEnd = false;

	bool TitleMode = false;
};

