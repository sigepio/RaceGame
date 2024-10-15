#include "stdafx.h"
#include "Car_RB19.h"

#include "PageNum.h"


Car_RB19::Car_RB19() {
    //AE86�̏����ݒ�

    // �g���N�ݒ�
    data = {
    {0, 34},
    {1000, 127},
    {2000, 178},
    {3000, 230},
    {4000, 238},
    {5000, 231},
    {6000, 240},
    {7000, 234},
    {8000, 230},
    {9000, 256},
    {10000, 269},
    {10500, 267},
    {11000, 261},
    {11500, 221},
    {12000, 186},
    {12500, 168},
    {13000, 149},
    {13500, 136},
    {14000, 131},
    {14500, 118},
    {15000, 113},
    {15500, 105},
    {16000, 0}
    };








    //���x�`�B��ݒ�
    GEAR_RATIOS = { 3.4, 2.4, 2.02, 1.72, 1.44, 1.28, 1.12, 1.0};
    ShiftDownTiming = { 10300.0f,12300.0f,12400.0f,12200.0f,12900.0f,12700.0f };
    TorqueMultiplier = { 2.2,2.2,2.2,2.2,2.5,2.5,2.5,2.5 };

    vehicle_info = {
    798.0,              //�ԏd[kg]
    2.9,              //�z�C�[���x�[�X[m]
    0.46,               //�d�S�̍���[m]
    1.900,              //�g���b�h��[m]
    1.285,              //�d�S�����ւ܂ł̒��� [m]
    1.285,              //�d�S����O�ւ܂ł̒��� [m]
    0.31,              //�^�C���̔��a [m]
    GEAR_RATIOS,        //�M�A��
    4.500,                //�f�t��(�t�@�C�i���M�A)
    data,               //�G���W���̃g���N[N�Em]
    0.1745,//(��10�x�ɐݒ肵�Ă��邪�ύX��)             //�^�C���̍ő�Ǌp [rad]
    10000,               //�ő吧����[N]
    1.050,              //�S��[m]
    3000,               //�t�����g�o�l���[�g[N/m]
    2328,               //���A�o�l���[�g[N/m]
    0.1,                //(���̒l)
    8,                  //�ő�M�A��
    15000,               //�ō���]��
    500.0,               //�A�C�h�����O��]��
    -0.020f,             //�R�[�i�����O�p���[
    14.0f,
    ShiftDownTiming,
    200,
    100.0f,
    0,
    0.0f,
    TorqueMultiplier
    };



    //�ő�M�A���ݒ�
    MaxGear = 5;

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

    IdolingRPM = 500.0f;

    //�ԗ����f���ݒ�
    m_PlayerCarModel.Init("Assets/modelData/Car/RB19/Body.tkm");
    m_CarWindowModel.Init("Assets/modelData/Car/RB19/BodyAlpha.tkm", true, AlphaBlendMode_Trans);
    WindowState = true;

    //�ԗ��f�[�^�ݒ�
    m_NowCar = ORECA07;

    //�e�^�C���̃��[�J�����W�ݒ�
    m_LeftFrontWheelLocalPosition = { -32.5f,15.0f,57.0f };		//���t�����g
    m_RightFrontWheelLocalPosition = { 32.5f,15.0f,57.0f };		//�E�t�����g
    m_LeftRearWheelLocalPosition = { -32.0f,15.0f,-68.0f };		//�����A
    m_RightRearWheelLocalPosition = { 32.0f,15.0f,-68.0f };		//�E���A

    //���_�̐ݒ�
    BirdsEyeViewCoordinates = { 0.0f, 95.0f, -175.0f };
    BirdsEyeViewViewpointHeight = 65.0f;
    BonnetViewCoordinates = { 0.0f, 0.0f, 10.0f };
    BonnetViewViewpointHeight = 50.0f;

    BirdsEyeViewTargetPoint = { 0.0f, 0.0f, 0.0f };
    BonnetViewTargetPoint = { 0.0f, 40.0f, 200.0f };

    BirdsEyeViewViewpointDirectionCorrectionByVehicleType = { 50,0,25 };
    BonnetViewViewpointDirectionCorrectionByVehicleType = { 75,0,125 };
}

Car_RB19::~Car_RB19() {

}