#pragma once
class GameCamera;
class RightFrontWheel;
class FrontWheelBase;
class RightRearWheel;
class LeftRearWheel;
class TimeTrialMode;
class LeftFrontWheel;
class Player;
class LicenseRace;

class CarBase:public IGameObject,Noncopyable
{
public:

	CarBase();
	~CarBase();
	bool Start();
	void Update();
	
	void Move();
	void Set();
	void Render(RenderContext& rc);

	void SetGameEnd(bool m_GameEnd) {
		GameEnd = m_GameEnd;
	}

	

	std::map<int, float> readLUT(std::string filename);

	//取得系関数
	
	//プレイヤーポジションの取得
	Vector3 GetPosition() const {
		return m_PlayerPosition;
	}

	//プレイヤーローテーションの取得
	Quaternion GetRotation() {
		return m_PlayerRotation;
	}

	Vector3 GetForward() {
		return m_PlayerForward;
	}

	int Getm_LapState() {
		return m_LapState;
	}

	//車両データの取得
	int GetCarData() {
		return m_NowCar;
	}

	//タイヤのローカル座標の取得
	
	//左フロント
	Vector3 GetLeftFrontWheelLocalPosition() {
		return m_LeftFrontWheelLocalPosition;
	}

	//右フロント
	Vector3 GetRightFrontWheelLocalPosition() {
		return m_RightFrontWheelLocalPosition;
	}

	//左リア
	Vector3 GetLeftRearWheelLocalPosition() {
		return m_LeftRearWheelLocalPosition;
	}

	//右リア
	Vector3 GetRightRearWheelLocalPosition() {
		return m_RightRearWheelLocalPosition;
	}

	//設定系関数

	//プレイヤーポジションの設定
	void SetPosition(Vector3 Potion) {
		m_PlayerPosition = Potion;
	}

	//プレイヤーローテーションの設定
	void SetRotation(Quaternion Rotation) {
		m_PlayerRotation = Rotation;
	}

	void Setm_LapState(int LapState) {
		m_LapState = LapState;
	}

	void SetPauseState(int PauseState) {
		m_PauseState = PauseState;
	}

	void SetLicenseNum(int m_LicenseNum) {
		LicenseNum = m_LicenseNum;
	}

	void SetAutoDrive(bool m_AutoDrive) {
		AutoDriveState = m_AutoDrive;
	}

	//その他の関数
	float Returnm_throttle() {
		return m_Throttle;
	}

	bool GetAutoDrive() {
		return AutoDriveState;
	}
	
protected:

	Vector3 m_PlayerPosition=Vector3::Zero;							//プレイヤーポジション
	Vector3 m_PlayerForward = { 0.0f, 0.0f, 1.0f };					//プレイヤーの正面ベクトル
	Vector3 m_PlayerMoveSpeed = Vector3::Zero;						//プレイヤーの移動速度

	Vector3 m_LeftFrontWheelLocalPosition = { 0.0f,0.0f,0.0f };		//左フロントタイヤのローカル座標
	Vector3 m_RightFrontWheelLocalPosition = { 0.0f,0.0f,0.0f };	//右フロントタイヤのローカル座標
	Vector3 m_LeftRearWheelLocalPosition = { 0.0f,0.0f,0.0f };		//左リアタイヤのローカル座標
	Vector3 m_RightRearWheelLocalPosition = { 0.0f,0.0f,0.0f };		//右リアタイヤのローカル座標
	Vector3 ResetVector = { 0.0f,0.0f,1.0f };
	Vector3 CameraVector = Vector3::Zero;

	Vector3 BirdsEyeViewCoordinates;								//俯瞰視点のカメラの位置
	Vector3 BonnetViewCoordinates;									//ボンネット視点のカメラの位置

	Vector3 BirdsEyeViewTargetPoint;								//俯瞰視点の視点の位置
	Vector3 BonnetViewTargetPoint;									//ボンネット視点の視点の位置

	Vector3 BirdsEyeViewViewpointDirectionCorrectionByVehicleType;	//俯瞰視点の視点方向補正値
	Vector3 BonnetViewViewpointDirectionCorrectionByVehicleType;	//ボンネット視点の視点方向補正値

	Vector4 HoodViewCoordinates;
	

	Quaternion m_PlayerRotation;									//プレイヤーローテーション

	

	ModelRender m_PlayerCarModel;
	ModelRender m_CarWindowModel;

	TimeTrialMode* m_timetrialmode;
	GameCamera*m_gamecamera=nullptr;
	RightFrontWheel* m_rightfrontwheel=nullptr;
	LeftFrontWheel* m_leftfrontwheel = nullptr;
	FrontWheelBase* m_frontwheelbase = nullptr;
	RightRearWheel* m_rightrearwheel = nullptr;
	LeftRearWheel* m_leftrearwheel = nullptr;
	Player* m_player;
	LicenseRace* m_LicenseRace;

	int m_NowCar = 0;													//今乗っている車両
	int m_LapState = 0;												//
	int m_PauseState = 0;
	int LicenseNum = 0;

	float m_Acceleration = 0.0f;
	float m_Throttle = 0.0f;

	
	float SHIFT_UP_RPM_ADJUST;					//シフトアップ時の回転数調整量(RPM)
	float SHIFT_DOWN_RPM_ADJUST;				//シフトダウン時の回転調整量(RPM)
	float currentRPM = 0.0f;					//今のエンジン回転数(RPM)
	float velocity = 0.0f;						//今の時速(km/h)	
	float mass;									//車重(kg)
	float wheelRadius;							//タイヤの直径(m)
	float grade = 0.0f;							//勾配(10%->0.1)
	float throttle_input = 0.0f;				//スロットル開度(1.0フルスロットル)
	std::vector<float> GEAR_RATIOS;				//ギア比
	std::vector<float> ShiftDownTiming;			//シフトダウンの回転数
	int currentGear = 1;						//今のギア
	int MaxGear;								//最大ギア数
	float AirPressure;							//タイヤ空気圧
	float FinalGearRatio;						//ファイナルギア
	float Transmission_Efficiency;				//伝達効率
	float CameraRAngle = 0.0f;

	float BirdsEyeViewViewpointHeight;
	float BonnetViewViewpointHeight;

	std::vector<std::vector<float>> data;

	float IdolingRPM;

	VehicleInfo vehicle_info;

	std::map<int, float> PowerCurve;

	bool GameEnd = false;
	
	bool AutoDriveState = false;

	bool WindowState = false;
};

