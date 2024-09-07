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

	//�擾�n�֐�
	
	//�v���C���[�|�W�V�����̎擾
	Vector3 GetPosition() const {
		return m_PlayerPosition;
	}

	//�v���C���[���[�e�[�V�����̎擾
	Quaternion GetRotation() {
		return m_PlayerRotation;
	}

	Vector3 GetForward() {
		return m_PlayerForward;
	}

	int Getm_LapState() {
		return m_LapState;
	}

	//�ԗ��f�[�^�̎擾
	int GetCarData() {
		return m_NowCar;
	}

	//�^�C���̃��[�J�����W�̎擾
	
	//���t�����g
	Vector3 GetLeftFrontWheelLocalPosition() {
		return m_LeftFrontWheelLocalPosition;
	}

	//�E�t�����g
	Vector3 GetRightFrontWheelLocalPosition() {
		return m_RightFrontWheelLocalPosition;
	}

	//�����A
	Vector3 GetLeftRearWheelLocalPosition() {
		return m_LeftRearWheelLocalPosition;
	}

	//�E���A
	Vector3 GetRightRearWheelLocalPosition() {
		return m_RightRearWheelLocalPosition;
	}

	//�ݒ�n�֐�

	//�v���C���[�|�W�V�����̐ݒ�
	void SetPosition(Vector3 Potion) {
		m_PlayerPosition = Potion;
	}

	//�v���C���[���[�e�[�V�����̐ݒ�
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

	//���̑��̊֐�
	float Returnm_throttle() {
		return m_Throttle;
	}

	bool GetAutoDrive() {
		return AutoDriveState;
	}
	
protected:

	Vector3 m_PlayerPosition=Vector3::Zero;							//�v���C���[�|�W�V����
	Vector3 m_PlayerForward = { 0.0f, 0.0f, 1.0f };					//�v���C���[�̐��ʃx�N�g��
	Vector3 m_PlayerMoveSpeed = Vector3::Zero;						//�v���C���[�̈ړ����x

	Vector3 m_LeftFrontWheelLocalPosition = { 0.0f,0.0f,0.0f };		//���t�����g�^�C���̃��[�J�����W
	Vector3 m_RightFrontWheelLocalPosition = { 0.0f,0.0f,0.0f };	//�E�t�����g�^�C���̃��[�J�����W
	Vector3 m_LeftRearWheelLocalPosition = { 0.0f,0.0f,0.0f };		//�����A�^�C���̃��[�J�����W
	Vector3 m_RightRearWheelLocalPosition = { 0.0f,0.0f,0.0f };		//�E���A�^�C���̃��[�J�����W
	Vector3 ResetVector = { 0.0f,0.0f,1.0f };
	Vector3 CameraVector = Vector3::Zero;

	Vector3 BirdsEyeViewCoordinates;								//���Վ��_�̃J�����̈ʒu
	Vector3 BonnetViewCoordinates;									//�{���l�b�g���_�̃J�����̈ʒu

	Vector3 BirdsEyeViewTargetPoint;								//���Վ��_�̎��_�̈ʒu
	Vector3 BonnetViewTargetPoint;									//�{���l�b�g���_�̎��_�̈ʒu

	Vector3 BirdsEyeViewViewpointDirectionCorrectionByVehicleType;	//���Վ��_�̎��_�����␳�l
	Vector3 BonnetViewViewpointDirectionCorrectionByVehicleType;	//�{���l�b�g���_�̎��_�����␳�l

	Vector4 HoodViewCoordinates;
	

	Quaternion m_PlayerRotation;									//�v���C���[���[�e�[�V����

	

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

	int m_NowCar = 0;													//������Ă���ԗ�
	int m_LapState = 0;												//
	int m_PauseState = 0;
	int LicenseNum = 0;

	float m_Acceleration = 0.0f;
	float m_Throttle = 0.0f;

	
	float SHIFT_UP_RPM_ADJUST;					//�V�t�g�A�b�v���̉�]��������(RPM)
	float SHIFT_DOWN_RPM_ADJUST;				//�V�t�g�_�E�����̉�]������(RPM)
	float currentRPM = 0.0f;					//���̃G���W����]��(RPM)
	float velocity = 0.0f;						//���̎���(km/h)	
	float mass;									//�ԏd(kg)
	float wheelRadius;							//�^�C���̒��a(m)
	float grade = 0.0f;							//���z(10%->0.1)
	float throttle_input = 0.0f;				//�X���b�g���J�x(1.0�t���X���b�g��)
	std::vector<float> GEAR_RATIOS;				//�M�A��
	std::vector<float> ShiftDownTiming;			//�V�t�g�_�E���̉�]��
	int currentGear = 1;						//���̃M�A
	int MaxGear;								//�ő�M�A��
	float AirPressure;							//�^�C����C��
	float FinalGearRatio;						//�t�@�C�i���M�A
	float Transmission_Efficiency;				//�`�B����
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

