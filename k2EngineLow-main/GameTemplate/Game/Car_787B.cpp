#include "stdafx.h"
#include "Car_787B.h"


#include "PageNum.h"


Car_787B::Car_787B() {
    //AE86�̏����ݒ�

    // �g���N�ݒ�
    data = {
    {0, 90},
    {250, 117},
    {500, 144},
    {750, 162},
    {1000, 198},
    {1250, 234},
    {1500, 270},
    {1750, 297},
    {2000, 315},
    {2250, 328.5},
    {2500, 333},
    {2750, 342},
    {3000, 351},
    {3250, 360},
    {3500, 369},
    {3750, 376.2},
    {4000, 387},
    {4250, 403.2},
    {4500, 421.2},
    {4750, 432},
    {5000, 437.4},
    {5250, 442.8},
    {5500, 454.5},
    {5750, 489.6},
    {6000, 524.7},
    {6250, 543.6},
    {6500, 547.2},
    {6750, 546.3},
    {7000, 544.5},
    {7250, 541.8},
    {7500, 538.2},
    {7750, 533.7},
    {8000, 528.3},
    {8250, 523.8},
    {8500, 515.7},
    {8750, 504},
    {9000, 491.4},
    {9250, 477},
    {9500, 462.6},
    {9750, 447.3},
    {10000, 427.5},
    {10250, 405.9},
    {10500, 378.9}
    };



    //���x�`�B��ݒ�
    GEAR_RATIOS = { 1.833, 1.471, 1.160, 1.000, 0.764 };
    ShiftDownTiming = { 6900.0f,6800.0f,7400.0f,6600.0f };
    TorqueMultiplier = { 1.1,1.1,1.1,1.2,1.2 };

    vehicle_info = {
    830.0,              //�ԏd[kg]
    2.660,              //�z�C�[���x�[�X[m]
    0.46,               //�d�S�̍���[m]
    2.050,              //�g���b�h��[m]
    1.285,              //�d�S�����ւ܂ł̒��� [m]
    1.285,              //�d�S����O�ւ܂ł̒��� [m]
    0.32,              //�^�C���̔��a [m]
    GEAR_RATIOS,        //�M�A��
    4.429,                //�f�t��(�t�@�C�i���M�A)
    data,               //�G���W���̃g���N[N�Em]
    0.1745,//(��10�x�ɐݒ肵�Ă��邪�ύX��)             //�^�C���̍ő�Ǌp [rad]
    8000,               //�ő吧����[N]
    1.320,              //�S��[m]
    3000,               //�t�����g�o�l���[�g[N/m]
    2328,               //���A�o�l���[�g[N/m]
    0.1,                //(���̒l)
    5,                  //�ő�M�A��
    9000,               //�ō���]��
    800,               //�A�C�h�����O��]��
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
    m_PlayerCarModel.Init("Assets/modelData/Car/787B/Body.tkm");
    m_CarWindowModel.Init("Assets/modelData/Car/787B/BodyAlpha.tkm", true, AlphaBlendMode_Trans);
    WindowState = true;

    //�ԗ��f�[�^�ݒ�
    m_NowCar = ORECA07;

    //�e�^�C���̃��[�J�����W�ݒ�
    m_LeftFrontWheelLocalPosition = { -0.0f,13.0f,59.5f };		//���t�����g
    m_RightFrontWheelLocalPosition = { 31.0f,13.0f,59.5f };		//�E�t�����g
    m_LeftRearWheelLocalPosition = { -0.0f,15.0f,-45.0f };		//�����A
    m_RightRearWheelLocalPosition = { 0.0f,15.0f,-45.0f };		//�E���A

    //���_�̐ݒ�
    BirdsEyeViewCoordinates = { 0.0f, 95.0f, -175.0f };
    BirdsEyeViewViewpointHeight = 65.0f;
    BonnetViewCoordinates = { 0.0f, -10.0f, -20.0f };
    BonnetViewViewpointHeight = 50.0f;

    BirdsEyeViewTargetPoint = { 0.0f, 0.0f, 0.0f };
    BonnetViewTargetPoint = { 0.0f, 40.0f, 200.0f };

    BirdsEyeViewViewpointDirectionCorrectionByVehicleType = { 50,0,25 };
    BonnetViewViewpointDirectionCorrectionByVehicleType = { 75,0,125 };
}

Car_787B::~Car_787B() {

}