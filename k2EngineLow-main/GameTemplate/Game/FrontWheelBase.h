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

	//�擾�n�֐�

	//�|�W�V�����̎擾
	Vector3 GetPosition() {
		return m_FrontWheelPosition;
	}

	//��]���̎擾
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

	//�ݒ�n�֐�

	//�|�W�V�����̐ݒ�
	void SetPosition(Vector3 position) {
		m_FrontWheelPosition = position;
	}

	//�v���C���[�̉�]�͂̐ݒ�
	void SetPlayerRotation(Quaternion rotation) {
		OriginRotation = rotation;
	}

	void SetForward(Vector3 forward) {
		m_FrontWheelForwardCatch = forward;
	}

	//�g���N�J�[�u�̃t�@�C���p�X�̐ݒ�
	void SetlutFilePath(std::string SetlutFilePath) {
		lutFilePath = SetlutFilePath;
	}

	//�V�t�g�A�b�v���̉�]�������ʂ̐ݒ�
	void SetSHIFT_UP_RPM_ADJUST(float SetSHIFT_UP_RPM_ADJUST) {
		SHIFT_UP_RPM_ADJUST = SetSHIFT_UP_RPM_ADJUST;
	}

	//�V�t�g�_�E�����̉�]�������ʂ̐ݒ�
	void SetSHIFT_DOWN_RPM_ADJUST(float SetSHIFT_DOWN_RPM_ADJUST) {
		SHIFT_DOWN_RPM_ADJUST = SetSHIFT_DOWN_RPM_ADJUST;
	}

	//�ԏd�̐ݒ�
	void SetMass(float Setmass) {
		mass = Setmass;
	}

	//�^�C���̒��a�̐ݒ�
	void SetWheelRadius(float SetwheelRadius) {
		wheelRadius = SetwheelRadius;
	}

	//�M�A��̐ݒ�
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
	
	Vector3 Acceleration_DecelerationForce = Vector3::Zero; //��������(�O�̃t���[���̎Ԃɂ����邷�ׂĂ̗�)[N]
	
	Vector3 FrontWheelOrientationVector = {0.0f,0.0f,1.0f};
	Vector3 PastVector = Vector3::Zero;
	Vector3 DifferenceVector = { 0.0f,0.0f,1.0f };
	Vector3 LastDVector = Vector3::Zero;

	Quaternion OriginRotation;
	Quaternion m_FrontWheelRotation;
	Quaternion m_FrontWheelLocalRotation;
	Quaternion needlerot;
	Quaternion speedneedlerot;

	CharacterController m_characterController;		//�L�����N�^�[�R���g���[���[

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

	float Speed = 0.0f;								//����
	float RSpeed = 0.0f;							//���^�[�����ꂽ���x
	float Rotation_Speed = 0.0f;					//�G���W����]��
	float e_s = 1;

	std::string lutFilePath;
	float SHIFT_UP_RPM_ADJUST;					//�V�t�g�A�b�v���̉�]��������(RPM)
	float SHIFT_DOWN_RPM_ADJUST;				//�V�t�g�_�E�����̉�]������(RPM)
	float currentRPM = 0.0f;					//���̃G���W����]��(RPM)
	float velocity = 0.0f;						//���̎���(km/h)	
	float mass;								//�ԏd(kg)
	float wheelRadius;							//�^�C���̒��a(m)
	float grade = 0.0f;						//���z(10%->0.1)
	float throttle_input = 0.0f;				//�X���b�g���J�x(1.0�t���X���b�g��)
	float brake_input = 0.0f;
	std::vector<float> GEAR_RATIOS;			//�M�A��
	float currentGear = 1;						//���̃M�A
	int MaxGear;								//�ő�M�A��
	float AirPressure;							//�^�C����C��
	float FinalGearRatio;						//�t�@�C�i���M�A
	float Transmission_Efficiency;				//�`�B����

	float PitchAngle = 0.0f;					//�s�b�`�p�x[rad]
	float RollAngle = 0.0f;						//���[���p�x[rad]
	float DegreeOfRotationOfTheHandle = 0.0f;	//�n���h���̉�]�x�� [rad]
	float Temperature = 20.0f;					//�C�� [��]
	float AtmosphericPressure = 1.0f;		    //��C�� [atm]
	float WaterVaporPressure = 0.0231f;			//�����C�� [atm]
	float RollingResistanceCoefficient = 0.02f;	//�H�ʂ̓]�����R�W��
	float CoefficientOfFriction = 1.2f;			//�H�ʂƃ^�C���Ƃ̖��C�W��
	float WindDirectionVector = 0.0f;			//���̌����x�N�g�� [m/s]
	float VelocityVector = 0.0f;
	float AccelerationVector = 0.0f;
	float TurningAngle;

	float acceleration = 0;
	
	float EngineSound = 0.0f;
	float IdolingRPM;

	std::vector<std::vector<float>> data;
	int Gear = 1;									//�M�A

	int m_PauseState = 0;

	VehicleInfo vehicle_info;
};

