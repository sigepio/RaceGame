#pragma once
class CarAFormula:public IGameObject
{
public:
	CarAFormula();
	~CarAFormula();
	bool Start();
	void Update();


	Vector4 CarSpeed(std::vector<std::vector<float>> data,				//�g���N�J�[�u�̃t�@�C���p�X
					const float SHIFT_UP_RPM_ADJUST,		//�V�t�g�A�b�v���̉�]��������
					const float SHIFT_DOWN_RPM_ADJUST,		//�V�t�g�_�E�����̉�]������
					float currentRPM,						//���̃G���W����]��
					float velocity,						//���̎���
					float mass,							//�ԏd
					float wheelRadius,						//�^�C���̒��a
					float grade,							//���z(10%->0.1)
					float throttle_input,					//�X���b�g���J�x(1.0�t���X���b�g��)
					std::vector<float> GEAR_RATIOS,		//�M�A��
					float currentGear,						//���̃M�A
		            int MaxGear	,							//�ő�M�A��
					float AirPressure, 
					float FinalGearRatio, 
					float Transmission_Efficiency,
		            float acceleration
		);

	SimulationResults CarSimulation(
					VehicleInfo vehicleinfo,				//�ԗ��̏��
					Vector3 Position,						//�ʒu�x�N�g��[m]
					Vector3 VelocityVector,					//���x�x�N�g��[m/s]
					float PitchAngle,						//�s�b�`�p�x[rad]
					float RollAngle,						//���[���p�x[rad]
					Vector3 Acceleration,                   //�����x
					float CurrentRPM,						//�G���W���̉�]�� [rpm]
					float DegreeOfRotationOfTheHandle,		//�n���h���̉�]�x�� [rad]	
					Vector3 Acceleration_DecelerationForce, //��������(�O�̃t���[���̎Ԃɂ����邷�ׂĂ̗�)[N]
					float CurrentGear,						//���݂̃M�A
					float Grade,							//���z[rad]
					float AirDensity,						//��C�̖��x [kg/m3]
					Vector3 WindDirectionVector,			//���̌����x�N�g�� [m/s]
					float Temperature,						//�C�� [��]
					float AtmosphericPressure,				//��C�� [atm]
					float WaterVaporPressure,				//�����C�� [atm]
					float RollingResistanceCoefficient,		//�H�ʂ̓]�����R�W��
					float CoefficientOfFriction,			//�H�ʂƃ^�C���Ƃ̖��C�W��
					float AcceleratorOpening,				//�A�N�Z���̓��ݍ��݋
					float BrakePressure,					//�u���[�L�̓��ݍ��݋
					float SteeringAngle,					//�X�e�A�����O�A���O��
					Vector3 SteeringFrontVector,			//�X�e�A�����O�̐��ʃx�N�g��(���K���ς݂̂�)
					Vector3 FrontWheelOrientationVector		//�O�֌�����\�����Ă���P�ʃx�N�g��
	);	
	void ShiftChange();



	//�擾�n�֐�

	//�G���W���w���o�͂̎擾(�����ɃG���W����]��)
	float GetPi() {
	}


private:


	const float g = 9.8;			// �d�͉����x (m/s^2)
};

