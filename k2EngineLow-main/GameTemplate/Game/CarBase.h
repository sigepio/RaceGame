#pragma once
class GameCamera;
class RightFrontWheel;
class FrontWheelBase;
class RightRearWheel;
class LeftRearWheel;
class TimeTrialMode;
class LeftFrontWheel;

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

	//���̑��̊֐�
	float Returnm_throttle() {
		return m_Throttle;
	}

	
protected:

	Vector3 m_PlayerPosition=Vector3::Zero;							//�v���C���[�|�W�V����
	Vector3 m_PlayerForward = { 0.0f, 0.0f, 1.0f };					//�v���C���[�̐��ʃx�N�g��
	Vector3 m_PlayerMoveSpeed = Vector3::Zero;						//�v���C���[�̈ړ����x

	Vector3 m_LeftFrontWheelLocalPosition = { 0.0f,0.0f,0.0f };		//���t�����g�^�C���̃��[�J�����W
	Vector3 m_RightFrontWheelLocalPosition = { 0.0f,0.0f,0.0f };	//�E�t�����g�^�C���̃��[�J�����W
	Vector3 m_LeftRearWheelLocalPosition = { 0.0f,0.0f,0.0f };		//�����A�^�C���̃��[�J�����W
	Vector3 m_RightRearWheelLocalPosition = { 0.0f,0.0f,0.0f };		//�E���A�^�C���̃��[�J�����W

	Quaternion m_PlayerRotation;									//�v���C���[���[�e�[�V����

	

	ModelRender m_PlayerCarModel;

	TimeTrialMode* m_timetrialmode;
	GameCamera*m_gamecamera=nullptr;
	RightFrontWheel* m_rightfrontwheel=nullptr;
	LeftFrontWheel* m_leftfrontwheel = nullptr;
	FrontWheelBase* m_frontwheelbase = nullptr;
	RightRearWheel* m_rightrearwheel = nullptr;
	LeftRearWheel* m_leftrearwheel = nullptr;

	int m_NowCar = 0;													//������Ă���ԗ�
	int m_LapState = 0;												//

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
	int currentGear = 1;						//���̃M�A
	int MaxGear;								//�ő�M�A��
	float AirPressure;							//�^�C����C��
	float FinalGearRatio;						//�t�@�C�i���M�A
	float Transmission_Efficiency;				//�`�B����

	std::vector<std::vector<float>> data;

	float IdolingRPM;

	VehicleInfo vehicle_info;

	std::map<int, float> PowerCurve;
};

