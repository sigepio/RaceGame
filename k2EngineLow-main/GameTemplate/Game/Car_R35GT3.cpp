#include "stdafx.h"
#include "Car_R35GT3.h"

#include "PageNum.h"


Car_R35GT3::Car_R35GT3() {
    //AE86�̏����ݒ�

    // �g���N�ݒ�
    data = {
    {-3000, 100},
    {-250, 100},
    {0, 100},
    {500, 120},
    {1000, 124},
    {1500, 129},
    {2000, 135},
    {2500, 146},
    {3000, 201},
    {3500, 284},
    {4000, 285},
    {4500, 283},
    {5000, 284},
    {5500, 282},
    {6000, 282},
    {6500, 271},
    {6800, 258},
    {7000, 244},
    {7250, 232},
    {7500, 213},
    {8000, 0}
    };




    //���x�`�B��ݒ�
    GEAR_RATIOS = { 2.500, 2.0000, 1.5217, 1.2000, 1.0312, 0.8857 };
    ShiftDownTiming = { 5400.0f,5100.0f,5300.0f,5700.0f,5800.0f };
    TorqueMultiplier = { 0.5,0.6,0.6,0.8,1.2,1.6,1.2 };

    vehicle_info = {
    1300.0,              //�ԏd[kg]
    2457.0,              //�z�C�[���x�[�X[m]
    0.46,               //�d�S�̍���[m]
    1.90,              //�g���b�h��[m]
    1.285,              //�d�S�����ւ܂ł̒��� [m]
    1.285,              //�d�S����O�ւ܂ł̒��� [m]
    0.3,              //�^�C���̔��a [m]
    GEAR_RATIOS,        //�M�A��
    3.055,                //�f�t��(�t�@�C�i���M�A)
    data,               //�G���W���̃g���N[N�Em]
    0.1745,//(��10�x�ɐݒ肵�Ă��邪�ύX��)             //�^�C���̍ő�Ǌp [rad]
    8000,               //�ő吧����[N]
    1.370,              //�S��[m]
    3000,               //�t�����g�o�l���[�g[N/m]
    2328,               //���A�o�l���[�g[N/m]
    0.1,                //(���̒l)
    6,                  //�ő�M�A��
    7000,               //�ō���]��
    2100,               //�A�C�h�����O��]��
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
    m_PlayerCarModel.Init("Assets/modelData/Car/R35GT3/Body.tkm");
    //m_CarWindowModel.Init("Assets/modelData/Car/R35GT3/BodyAlpha.tkm", true, AlphaBlendMode_Trans);
    //WindowState = true;

    //�ԗ��f�[�^�ݒ�
    m_NowCar = ORECA07;

    //�e�^�C���̃��[�J�����W�ݒ�
    m_LeftFrontWheelLocalPosition = { -34.0f,15.0f,57.0f };		//���t�����g
    m_RightFrontWheelLocalPosition = { 34.0f,15.0f,57.0f };		//�E�t�����g
    m_LeftRearWheelLocalPosition = { -34.0f,15.0f,-54.0f };		//�����A
    m_RightRearWheelLocalPosition = { 34.0f,15.0f,-54.0f };		//�E���A

    //���_�̐ݒ�
    BirdsEyeViewCoordinates = { 0.0f, 95.0f, -175.0f };
    BirdsEyeViewViewpointHeight = 65.0f;
    BonnetViewCoordinates = { 0.0f, 0.0f, 20.0f };
    BonnetViewViewpointHeight = 50.0f;

    BirdsEyeViewTargetPoint = { 0.0f, 0.0f, 0.0f };
    BonnetViewTargetPoint = { 0.0f, 40.0f, 200.0f };

    BirdsEyeViewViewpointDirectionCorrectionByVehicleType = { 50,0,25 };
    BonnetViewViewpointDirectionCorrectionByVehicleType = { 75,0,75 };
}

Car_R35GT3::~Car_R35GT3() {

}