#pragma once
class CarAFormula:public IGameObject
{
public:
	CarAFormula();
	~CarAFormula();
	bool Start();
	void Update();
	void SetGameEnd(bool m_GameEnd) {
		GameEnd = m_GameEnd;
	}
	SimulationResults CarSimulation(
					VehicleInfo vehicleinfo,				//�ԗ��̏��
					Vector3 Position,						//�ʒu�x�N�g��[m]
					float VelocityVector,					//���x�x�N�g��[m/s]
					float PitchAngle,						//�s�b�`�p�x[rad]
					float RollAngle,						//���[���p�x[rad]
					float Acceleration,						//�����x
					float CurrentRPM,						//�G���W���̉�]�� [rpm]
					float DegreeOfRotationOfTheHandle,		//�n���h���̉�]�x�� [rad]	
					Vector3 Acceleration_DecelerationForce, //��������(�O�̃t���[���̎Ԃɂ����邷�ׂĂ̗�)[N]
					float CurrentGear,						//���݂̃M�A
					float Grade,							//���z[rad]
					float AirDensity,						//��C�̖��x [kg/m3]
					float WindDirectionVector,				//���̌����x�N�g�� [m/s]
					float Temperature,						//�C�� [��]
					float AtmosphericPressure,				//��C�� [atm]
					float WaterVaporPressure,				//�����C�� [atm]
					float RollingResistanceCoefficient,		//�H�ʂ̓]�����R�W��
					float CoefficientOfFriction,			//�H�ʂƃ^�C���Ƃ̖��C�W��
					float AcceleratorOpening,				//�A�N�Z���̓��ݍ��݋
					float BrakePressure,					//�u���[�L�̓��ݍ��݋
					float SteeringAngle,					//�X�e�A�����O�A���O��
					Vector3 SteeringFrontVector,			//�X�e�A�����O�̐��ʃx�N�g��(���K���ς݂̂�)
					Vector3 FrontWheelOrientationVector,	//�O�֌�����\�����Ă���P�ʃx�N�g��
					bool Transmission,						//AT��MT��
					float ��RPM							//RPM�̕ω���
	);	
	void ShiftChange();



	//�擾�n�֐�

	//�G���W���w���o�͂̎擾(�����ɃG���W����]��)
	float GetPi() {
	}


private:


	const float g = 9.8;			// �d�͉����x (m/s^2)

	bool GameEnd = false;
};

