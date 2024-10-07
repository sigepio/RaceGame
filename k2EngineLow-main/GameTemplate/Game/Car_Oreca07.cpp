#include "stdafx.h"
#include "Car_Oreca07.h" 
#include "PageNum.h"


Car_Oreca07::Car_Oreca07() {
	//AE86�̏����ݒ�

	//�g���N�ݒ�
    data = {
     {0, 23.8},
     {250, 49.3},
     {500, 79.9},
     {750, 108.8},
     {1000, 136.0},
     {1250, 149.6},
     {1500, 171.7},
     {1750, 193.8},
     {2000, 214.2},
     {2250, 241.4},
     {2500, 265.2},
     {2750, 289.0},
     {3000, 308.4},
     {3250, 328.1},
     {3500, 340.0},
     {3750, 349.6},
     {4000, 353.6},
     {4250, 351.9},
     {4500, 346.8},
     {4750, 340.0},
     {5000, 333.2},
     {5250, 328.1},
     {5500, 324.7},
     {5750, 319.6},
     {6000, 310.1},
     {6250, 307.7},
     {6500, 304.3},
     {6750, 299.2},
     {7000, 292.4},
     {7250, 289.0},
     {7500, 286.3},
     {7800, 280.5},
     {8050, 267.1},
     {8300, 249.9},
     {8550, 215.9},
     {8800, 184.3},
     {9050, 154.7},
     {9300, 119.0},
     {9550, 83.3},
     {9800, 49.3},
     {10050, 13.6},
     {10250, 0}
    };

    //���x�`�B��ݒ�
    GEAR_RATIOS = { 1.593, 1.231, 0.989, 0.831, 0.704, 0.606 };
    ShiftDownTiming = { 6200.0f,6500.0f,6800.0f,6850.0f,6850.0f };
    TorqueMultiplier = { 1,1,1,1,1,1 };

    vehicle_info = {
    930.0,              //�ԏd[kg]
    2.766,              //�z�C�[���x�[�X[m]
    0.331,              //�d�S�̍���[m]
    1.424,              //�g���b�h��[m]
    0.080,              //�d�S�����ւ܂ł̒��� [m]
    0.085,              //�d�S����O�ւ܂ł̒��� [m]
    0.331,              //�^�C���̔��a [m]
    GEAR_RATIOS,        //�M�A��
    5.1,                //�f�t��(�t�@�C�i���M�A)
    data,               //�G���W���̃g���N[N�Em]
    0.1745,//(��10�x�ɐݒ肵�Ă��邪�ύX��)             //�^�C���̍ő�Ǌp [rad]
    27000,               //�ő吧����[N]
    1.045,              //�S��[m]
    1588,               //�t�����g�o�l���[�g[N/m]
    1456,               //���A�o�l���[�g[N/m]
    0.1,                //(���̒l)
    6,
    8200,
    1500,
    -0.016f,
    18.0f,
    ShiftDownTiming,
    100,
    200.0f,
    0,
    0,
    TorqueMultiplier
    };

	

	//�ő�M�A���ݒ�
	MaxGear = 6;

	//�V�t�g�A�b�v���̉�]�������ʐݒ�
	SHIFT_UP_RPM_ADJUST = 2000.0f;

	//�V�t�g�_�E�����̉�]�����ʐݒ�
	SHIFT_DOWN_RPM_ADJUST = 2000.0f;

	//�`�B�����̐ݒ�
    Transmission_Efficiency = 0.95f;

    //�^�C����C��
    AirPressure = 1.5f;

    //�t�@�C�i���M�A�̐ݒ�
    FinalGearRatio = 5.1f;

	//�ԏd�̐ݒ�
	mass = 735.0f;

	//�^�C���̒��a�ݒ�
	wheelRadius = 0.331f;

	IdolingRPM = 1500.0f;

	//�ԗ����f���ݒ�
	m_PlayerCarModel.Init("Assets/modelData/Car/LMP2.tkm");

	//�ԗ��f�[�^�ݒ�
	m_NowCar = ORECA07;

	//�e�^�C���̃��[�J�����W�ݒ�
	m_LeftFrontWheelLocalPosition = { -30.0f,11.0f,51.0f };		//���t�����g
	m_RightFrontWheelLocalPosition = { 30.0f,11.0f,51.0f };		//�E�t�����g
	m_LeftRearWheelLocalPosition = { -30.0f,11.0f,-58.5f };		//�����A
	m_RightRearWheelLocalPosition = { 30.0f,11.0f,-58.5f };		//�E���A

    //���_�̐ݒ�
    BirdsEyeViewCoordinates = { 0.0f, 95.0f, -175.0f };
    BirdsEyeViewViewpointHeight = 65.0f;
    BonnetViewCoordinates = { 0.0f, 0.0f, 0.0f };
    BonnetViewViewpointHeight = 50.0f;

    BirdsEyeViewTargetPoint = { 0.0f, 0.0f, 0.0f };
    BonnetViewTargetPoint = { 0.0f, 40.0f, 200.0f };

    BirdsEyeViewViewpointDirectionCorrectionByVehicleType = { 50,0,25 };
    BonnetViewViewpointDirectionCorrectionByVehicleType = { 75,0,75 };
}

Car_Oreca07::~Car_Oreca07() {

}