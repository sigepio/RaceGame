#include "stdafx.h"
#include "Car_FordGTGT3.h"

#include "PageNum.h"


Car_FordGTGT3::Car_FordGTGT3() {
    //AE86�̏����ݒ�

    // �g���N�ݒ�
    data = {
    {0, 100},
    {500, 206},
    {1000, 210},
    {1500, 197},
    {2000, 208},
    {2500, 219},
    {3000, 229},
    {3500, 270},
    {4000, 275},
    {4500, 279},
    {5000, 285},
    {5500, 286},
    {6000, 285},
    {6500, 286},
    {7000, 286},
    {7500, 276},
    {8000, 271},
    {8500, 265},
    {9000, 251}
    };



    //���x�`�B��ݒ�
    GEAR_RATIOS = { 2.6428, 2.0000, 1.5600, 1.34, 1.2000, 1.0312, 0.8857 };
    ShiftDownTiming = { 6200.0f,6800.0f,7200.0f,7800.0f,7200.0f,7500.0f };
    TorqueMultiplier = { 1.0,1.05,1.1,1.15,1.2,1.2,1.5 };

    vehicle_info = {
    1200.0,              //�ԏd[kg]
    2457.0,              //�z�C�[���x�[�X[m]
    0.46,               //�d�S�̍���[m]
    1.90,              //�g���b�h��[m]
    1.285,              //�d�S�����ւ܂ł̒��� [m]
    1.285,              //�d�S����O�ւ܂ł̒��� [m]
    0.3,              //�^�C���̔��a [m]
    GEAR_RATIOS,        //�M�A��
    3.700,                //�f�t��(�t�@�C�i���M�A)
    data,               //�G���W���̃g���N[N�Em]
    0.1745,//(��10�x�ɐݒ肵�Ă��邪�ύX��)             //�^�C���̍ő�Ǌp [rad]
    8000,               //�ő吧����[N]
    1.370,              //�S��[m]
    3000,               //�t�����g�o�l���[�g[N/m]
    2328,               //���A�o�l���[�g[N/m]
    0.1,                //(���̒l)
    7,                  //�ő�M�A��
    9000,               //�ō���]��
    900,               //�A�C�h�����O��]��
    -0.0147f,             //�R�[�i�����O�p���[
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
    m_PlayerCarModel.Init("Assets/modelData/Car/FordGTGT3/Body.tkm");
    m_CarWindowModel.Init("Assets/modelData/Car/FordGTGT3/BodyAlpha.tkm", true, AlphaBlendMode_Trans);
    WindowState = true;

    //�ԗ��f�[�^�ݒ�
    m_NowCar = ORECA07;

    //�e�^�C���̃��[�J�����W�ݒ�
    m_LeftFrontWheelLocalPosition = { -30.0f,15.0f,54.0f };		//���t�����g
    m_RightFrontWheelLocalPosition = { 30.0f,15.0f,54.0f };		//�E�t�����g
    m_LeftRearWheelLocalPosition = { -30.0f,15.0f,-55.0f };		//�����A
    m_RightRearWheelLocalPosition = { 30.0f,15.0f,-55.0f };		//�E���A

    //���_�̐ݒ�
    BirdsEyeViewCoordinates = { 0.0f, 95.0f, -175.0f };
    BirdsEyeViewViewpointHeight = 65.0f;
    BonnetViewCoordinates = { 0.0f, 0.0f, 20.0f };
    BonnetViewViewpointHeight = 50.0f;

    BirdsEyeViewTargetPoint = { 0.0f, 0.0f, 0.0f };
    BonnetViewTargetPoint = { 0.0f, 40.0f, 200.0f };

    BirdsEyeViewViewpointDirectionCorrectionByVehicleType = { 50,0,25 };
    BonnetViewViewpointDirectionCorrectionByVehicleType = { 75,0,125 };
}

Car_FordGTGT3::~Car_FordGTGT3() {

}