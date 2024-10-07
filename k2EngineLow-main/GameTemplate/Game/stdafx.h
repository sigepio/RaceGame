#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "k2EngineLowPreCompile.h"
using namespace nsK2EngineLow;
// K2EngineLow�̃O���[�o���A�N�Z�X�|�C���g
extern K2EngineLow* g_k2EngineLow;

// �f�[�^���i�[���邽�߂̍\����
struct Data {
    int x;
    double y;
};

// �ԗ����
struct VehicleInfo {
    double mass;							//�ԏd
	float WheelBase;						//�z�C�[���x�[�X [m]
	float CenterOfGravityFromTheGround;		//�n�ʂ���d�S�܂ł̍��� [m]
	float TreadWidth;						//�g���b�h�� [m]
	float RearWheelFromCenterOfGravity;		//�d�S�����ւ܂ł̒��� [m]
	float FrontWheelFromCenterOfGravity;	//�d�S����O�ւ܂ł̒��� [m]
	float TireRadius;						//�^�C���̔��a [m]
	std::vector<float> GEAR_RATIOS;			//�M�A��
	float FinalGearRatio;					//�f�t��(�t�@�C�i���M�A)
	std::vector<std::vector<float>> data;	//�G���W���̃g���N[N�Em]
	float MaximumSteeringAngleOfTires;		//�^�C���̍ő�Ǌp [rad]
	float MaximumBrakingForce;				//�ő吧����[N]
	float OverallHeight;					//�S��[m]
	float FrontSpringRate;					//�t�����g�o�l���[�g[N/m]
	float RearSpringRate;					//���A�o�l���[�g[N/m]
	float AirResistanceCoefficient;			//��C��R�W��
	float MaxGear;							//�ő�M�A��
	float MaxRPM;							//�ő��]��
	float IdlingRPM;						//�A�C�h�����O���̉�]��
	float CorneringPower;
	float AccelerationFactor;	
	std::vector<float> ShiftDownTiming;
	float ShiftUpCorrectionValue;
	float RevLimitGain;
	int HybridType;							//�n�C�u���b�h�̎�� 0:Non 1:LMP1 2:LMH/LMDH
	float HybridTorque;						//�n�C�u���b�h�V�X�e���̃g���N
	std::vector<float> TorqueMultiplier;

};

//�V�~�����[�g����
struct SimulationResults {
    Vector3 Position;						//�ʒu�x�N�g��[m]
    float VelocityVector;					//���x�x�N�g��[m/s]
    float PitchAngle;						//�s�b�`�p�x[rad]
    float RollAngle;						//���[���p�x[rad]
    float CurrentRPM;						//�G���W���̉�]�� [rpm]
	float ��RPM;							//RPM �̕ω���[rpm]
	float CurrentGear;						//�M�A
	float Acceleration;						//�����x
	float TurningAngle;						//����p�x[rad]
};


const int MAXRaceBGM = 3;

struct CircuitExperienceTime {
	float GoldTime;
	float SilverTime;
	float BronzeTime;
};

