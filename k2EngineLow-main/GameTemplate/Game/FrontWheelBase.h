#pragma once
#include "sound/SoundEngine.h"
class RightFrontWheel;
class LeftFrontWheel;
class CarAFormula;

class FrontWheelBase:public IGameObject,Noncopyable
{
public:
	FrontWheelBase();
	~FrontWheelBase();
	bool Start();
	void Update();
	void Move();
	Vector4 Acceleration();
	void Handling();
	void Render(RenderContext&rc);

	//取得系関数

	//ポジションの取得
	Vector3 GetPosition() {
		return m_FrontWheelPosition;
	}

	//回転数の取得
	Quaternion  GetRotation() {
		return m_FrontWheelRotation;
	}

	Vector3 GetForward() {
		return m_FrontWheelForward;
	}

	float Getm_Speed() {
		return throttle_input;
	}

	Vector3 Get_Velocity() {
		return m_FrontWheelForward;
	}

	Vector3 Get_DVector() {
		return DifferenceVector;
	}

	float GetTireRotation() {
		return VelocityVector * 3600.0f * 2.5f / 1000.0f / 100.0f;
	}

	//設定系関数

	//ポジションの設定
	void SetPosition(Vector3 position) {
		m_FrontWheelPosition = position;
	}

	//プレイヤーの回転力の設定
	void SetPlayerRotation(Quaternion rotation) {
		OriginRotation = rotation;
	}

	void SetForward(Vector3 forward) {
		m_FrontWheelForwardCatch = forward;
	}

	//トルクカーブのファイルパスの設定
	void SetlutFilePath(std::string SetlutFilePath) {
		lutFilePath = SetlutFilePath;
	}

	//シフトアップ時の回転数調整量の設定
	void SetSHIFT_UP_RPM_ADJUST(float SetSHIFT_UP_RPM_ADJUST) {
		SHIFT_UP_RPM_ADJUST = SetSHIFT_UP_RPM_ADJUST;
	}

	//シフトダウン時の回転数調整量の設定
	void SetSHIFT_DOWN_RPM_ADJUST(float SetSHIFT_DOWN_RPM_ADJUST) {
		SHIFT_DOWN_RPM_ADJUST = SetSHIFT_DOWN_RPM_ADJUST;
	}

	//車重の設定
	void SetMass(float Setmass) {
		mass = Setmass;
	}

	//タイヤの直径の設定
	void SetWheelRadius(float SetwheelRadius) {
		wheelRadius = SetwheelRadius;
	}

	//ギア比の設定
	void SetGearRatios(std::vector<float> SetGEAR_RATIOS) {
		GEAR_RATIOS = SetGEAR_RATIOS;
	}
	
	
	void SetMaxGear(int SetMaxGear) {
		MaxGear = SetMaxGear;
	}

	void SetTorqueData(std::vector<std::vector<float>> setdata) {
		data = setdata;
	}

	void SetIdolingRPM(float SetIdolingRPM) {
		IdolingRPM = SetIdolingRPM;
	}

	void SetAirPressure(float SetAirPressure) {
		AirPressure = SetAirPressure;
	}

	void SetFinalGearRatio(float SetFinalGearRatio) {
		FinalGearRatio = SetFinalGearRatio;
	}

	void SetTransmission_Efficiency(float SetTransmission_Efficiency) {
		Transmission_Efficiency = SetTransmission_Efficiency;
	}

	void Setvehicle_info(VehicleInfo Setvehicle_info) {
		vehicle_info = Setvehicle_info;
	}

	void SetPauseState(int PauseState) {
		m_PauseState = PauseState;
	}

	void SetGameEnd(bool m_GameEnd) {
		GameEnd = m_GameEnd;
	}

protected:
	Vector3 m_FrontWheelPosition = Vector3::Zero;
	Vector3 m_LocalPosition;
	Vector3 m_FrontWheelForward = { 0.0f,0.0f,1.0f };
	Vector3 m_FrontWheelForwardCatch = { 0.0f,0.0f,1.0f };
	Vector3 LsatStickL;
	Vector3 m_MoveSpeed;
	Vector3 gearposition;
	Vector3 speedposition;
	Vector3 meterposition;
	
	Vector3 Acceleration_DecelerationForce = Vector3::Zero; //加減速力(前のフレームの車にかかるすべての力)[N]
	
	Vector3 FrontWheelOrientationVector = {0.0f,0.0f,1.0f};
	Vector3 PastVector = Vector3::Zero;
	Vector3 DifferenceVector = { 0.0f,0.0f,1.0f };
	Vector3 LastDVector = Vector3::Zero;

	Quaternion OriginRotation;
	Quaternion m_FrontWheelRotation;
	Quaternion m_FrontWheelLocalRotation;
	Quaternion needlerot;
	Quaternion speedneedlerot;

	CharacterController m_characterController;		//キャラクターコントローラー

	ModelRender m_FrontWheelModel;

	SpriteRender meterRender;
	SpriteRender speedRender;
	SpriteRender gearRender;
	SpriteRender needleRender;
	SpriteRender speedneedleRender;

	SpriteRender UIBace;
	SpriteRender RPMGage;
	SpriteRender RPMCover;
	SpriteRender ThrottleGage;
	SpriteRender BrakeGage;


	FontRender RPMFont;
	FontRender VelocityFont;
	FontRender GearFont;

	SoundSource* engine;
	SoundSource* engine_s;

	RightFrontWheel* m_rightfrontwheel;
	LeftFrontWheel* m_leftfrontwheel;

	CarAFormula* m_caraformula;

	bool TurnRightState = false;
	bool GameEnd = false;

	float m_throttle;
	float m_brake;
	float m_accelerator;
	float m_move;
	float RPMGagescale = 0.0f;

	float Speed = 0.0f;								//時速
	float RSpeed = 0.0f;							//リターンされた速度
	float Rotation_Speed = 0.0f;					//エンジン回転数
	float e_s = 1;

	std::string lutFilePath;
	float SHIFT_UP_RPM_ADJUST;					//シフトアップ時の回転数調整量(RPM)
	float SHIFT_DOWN_RPM_ADJUST;				//シフトダウン時の回転調整量(RPM)
	float currentRPM = 0.0f;					//今のエンジン回転数(RPM)
	float velocity = 0.0f;						//今の時速(km/h)	
	float mass;								//車重(kg)
	float wheelRadius;							//タイヤの直径(m)
	float grade = 0.0f;						//勾配(10%->0.1)
	float throttle_input = 0.0f;				//スロットル開度(1.0フルスロットル)
	float brake_input = 0.0f;
	std::vector<float> GEAR_RATIOS;			//ギア比
	float currentGear = 1;						//今のギア
	int MaxGear;								//最大ギア数
	float AirPressure;							//タイヤ空気圧
	float FinalGearRatio;						//ファイナルギア
	float Transmission_Efficiency;				//伝達効率

	float PitchAngle = 0.0f;					//ピッチ角度[rad]
	float RollAngle = 0.0f;						//ロール角度[rad]
	float DegreeOfRotationOfTheHandle = 0.0f;	//ハンドルの回転度合 [rad]
	float Temperature = 20.0f;					//気温 [℃]
	float AtmosphericPressure = 1.0f;		    //大気圧 [atm]
	float WaterVaporPressure = 0.0231f;			//水蒸気圧 [atm]
	float RollingResistanceCoefficient = 0.02f;	//路面の転がり抵抗係数
	float CoefficientOfFriction = 1.2f;			//路面とタイヤとの摩擦係数
	float WindDirectionVector = 0.0f;			//風の向きベクトル [m/s]
	float VelocityVector = 0.0f;
	float AccelerationVector = 0.0f;
	float TurningAngle;

	float acceleration = 0;
	
	float EngineSound = 0.0f;
	float IdolingRPM;

	std::vector<std::vector<float>> data;
	int Gear = 1;									//ギア

	int m_PauseState = 0;

	VehicleInfo vehicle_info;
};

