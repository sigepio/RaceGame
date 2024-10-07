#include "stdafx.h"
#include "Car_C9.h"


#include "PageNum.h"


Car_C9::Car_C9() {
    //AE86�̏����ݒ�

    // �g���N�ݒ�
    data = {
     {-3000, 100},
     {-250, 100},
     {0, 200},
     {500, 363},
     {1000, 371},
     {1500, 383},
     {2000, 384},
     {2500, 396},
     {3000, 402},
     {3500, 407},
     {4000, 411},
     {4500, 415},
     {5000, 415},
     {5500, 420},
     {6000, 411},
     {6500, 402},
     {7000, 379},
     {7500, 341},
     {8000, 0}
    };




    //���x�`�B��ݒ�
    GEAR_RATIOS = { 2.2857, 1.9333, 1.5882, 1.2632, 0.952 };
    ShiftDownTiming = { 5600.0f,5400.0f,5200.0f,5000.0f };
    TorqueMultiplier = { 0.5,0.6,0.7,0.8,1.1 };

    vehicle_info = {
    830.0,              //�ԏd[kg]
    2.660,              //�z�C�[���x�[�X[m]
    0.46,               //�d�S�̍���[m]
    2.050,              //�g���b�h��[m]
    1.285,              //�d�S�����ւ܂ł̒��� [m]
    1.285,              //�d�S����O�ւ܂ł̒��� [m]
    0.32,              //�^�C���̔��a [m]
    GEAR_RATIOS,        //�M�A��
    2.818,                //�f�t��(�t�@�C�i���M�A)
    data,               //�G���W���̃g���N[N�Em]
    0.1745,//(��10�x�ɐݒ肵�Ă��邪�ύX��)             //�^�C���̍ő�Ǌp [rad]
    8000,               //�ő吧����[N]
    1.320,              //�S��[m]
    3000,               //�t�����g�o�l���[�g[N/m]
    2328,               //���A�o�l���[�g[N/m]
    0.1,                //(���̒l)
    5,                  //�ő�M�A��
    7000,               //�ō���]��
    1800,               //�A�C�h�����O��]��
    -0.0145f,             //�R�[�i�����O�p���[
    14.0f,
    ShiftDownTiming,
    100,
    350.0f,
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
    m_PlayerCarModel.Init("Assets/modelData/Car/C9/Body.tkm");
    m_CarWindowModel.Init("Assets/modelData/Car/C9/BodyAlpha.tkm", true, AlphaBlendMode_Trans);
    WindowState = true;

    //�ԗ��f�[�^�ݒ�
    m_NowCar = ORECA07;

    //�e�^�C���̃��[�J�����W�ݒ�
    m_LeftFrontWheelLocalPosition = { -31.0f,13.0f,50.0f };		//���t�����g
    m_RightFrontWheelLocalPosition = { 31.0f,13.0f,50.0f };		//�E�t�����g
    m_LeftRearWheelLocalPosition = { -30.0f,15.0f,-57.0f };		//�����A
    m_RightRearWheelLocalPosition = { 30.0f,15.0f,-57.0f };		//�E���A

    //���_�̐ݒ�
    BirdsEyeViewCoordinates = { 0.0f, 95.0f, -175.0f };
    BirdsEyeViewViewpointHeight = 65.0f;
    BonnetViewCoordinates = { 0.0f, 0.0f, 10.0f };
    BonnetViewViewpointHeight = 50.0f;

    BirdsEyeViewTargetPoint = { 0.0f, 0.0f, 0.0f };
    BonnetViewTargetPoint = { 0.0f, 40.0f, 200.0f };

    BirdsEyeViewViewpointDirectionCorrectionByVehicleType = { 50,0,25 };
    BonnetViewViewpointDirectionCorrectionByVehicleType = { 75,0,75 };
}

Car_C9::~Car_C9() {

}