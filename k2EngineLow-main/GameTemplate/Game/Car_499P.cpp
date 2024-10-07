#include "stdafx.h"
#include "Car_499P.h"

#include "PageNum.h"


Car_499P::Car_499P() {
    //AE86�̏����ݒ�

    // �g���N�ݒ�
    data = {
    {0, 0},
    {500, 60},
    {1000, 60},
    {1500, 60},
    {2000, 60},
    {2500, 60},
    {3000, 60},
    {3500, 70},
    {4000, 85},
    {4500, 102},
    {5000, 120},
    {5300, 131},
    {5775, 153},
    {6000, 174.1},
    {6300, 192.55},
    {6562, 209.2},
    {7000, 215.82},
    {7500, 237.655},
    {8000, 246.03},
    {8500, 257.1},
    {9000, 261.97},
    {9500, 261.14},
    {10000, 200.57},
    {10500, 143.6},
    {10762, 228.05},
    {11000, 0}
    };









    //���x�`�B��ݒ�
    GEAR_RATIOS = { 2.500, 2.000, 1.625, 1.318, 1.133, 1.000, 0.732};
    ShiftDownTiming = { 8000.0f,8000.0f,8100.0f,8500.0f,8700.0f,7100.0f };
    TorqueMultiplier = { 2,2,2,2,2,2,2 };

    vehicle_info = {
    1040.0,              //�ԏd[kg]
    2.9,              //�z�C�[���x�[�X[m]
    0.46,               //�d�S�̍���[m]
    1.900,              //�g���b�h��[m]
    1.285,              //�d�S�����ւ܂ł̒��� [m]
    1.285,              //�d�S����O�ւ܂ł̒��� [m]
    0.31,              //�^�C���̔��a [m]
    GEAR_RATIOS,        //�M�A��
    5.400,                //�f�t��(�t�@�C�i���M�A)
    data,               //�G���W���̃g���N[N�Em]
    0.1745,//(��10�x�ɐݒ肵�Ă��邪�ύX��)             //�^�C���̍ő�Ǌp [rad]
    9000,               //�ő吧����[N]
    1.050,              //�S��[m]
    3000,               //�t�����g�o�l���[�g[N/m]
    2328,               //���A�o�l���[�g[N/m]
    0.1,                //(���̒l)
    7,                  //�ő�M�A��
    10500,               //�ō���]��
    500.0,               //�A�C�h�����O��]��
    -0.01570f,             //�R�[�i�����O�p���[
    14.0f,
    ShiftDownTiming,
    200,
    100.0f,
    2,
    35.0f,
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
    m_PlayerCarModel.Init("Assets/modelData/Car/499P/Body.tkm");
    WindowState = false;

    //�ԗ��f�[�^�ݒ�
    m_NowCar = ORECA07;

    //�e�^�C���̃��[�J�����W�ݒ�
    m_LeftFrontWheelLocalPosition = { -32.25f,15.0f,58.5f };		//���t�����g
    m_RightFrontWheelLocalPosition = { 31.25f,15.0f,58.5f };		//�E�t�����g
    m_LeftRearWheelLocalPosition = { -31.5f,15.0f,-64.0f };		//�����A
    m_RightRearWheelLocalPosition = { 31.5f,15.0f,-64.0f };		//�E���A

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

Car_499P::~Car_499P() {

}