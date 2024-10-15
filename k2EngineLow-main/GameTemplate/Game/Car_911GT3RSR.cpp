#include "stdafx.h"
#include "Car_911GT3RSR.h"

#include "PageNum.h"


Car_911GT3RSR::Car_911GT3RSR() {
    //AE86�̏����ݒ�

    // �g���N�ݒ�
    data = {
    {0, 100},
    {500, 200},
    {1000, 206},
    {1500, 239},
    {2000, 274},
    {2500, 285},
    {3000, 284},
    {3500, 287},
    {4000, 294},
    {4500, 328},
    {5000, 368},
    {5500, 390},
    {6000, 402},
    {6250, 413},
    {6500, 412},
    {6750, 418},
    {7000, 412},
    {7500, 404},
    {8000, 403},
    {8250, 397},
    {8500, 377},
    {9000, 352},
    {10000, 0}
    };



    //���x�`�B��ݒ�
    GEAR_RATIOS = { 3.1538, 2.294, 1.850, 1.5263, 1.2926 , 1.0967 };
    ShiftDownTiming = { 6300.0f,6900.0f,7200.0f,7200.0f,7200.0f };
    TorqueMultiplier = { 1.0,1.05,1.1,1.15,1.2,1.2 };

    vehicle_info = {
    1350.0,              //�ԏd[kg]
    2.660,              //�z�C�[���x�[�X[m]
    0.46,               //�d�S�̍���[m]
    2.050,              //�g���b�h��[m]
    1.285,              //�d�S�����ւ܂ł̒��� [m]
    1.285,              //�d�S����O�ւ܂ł̒��� [m]
    0.361,              //�^�C���̔��a [m]
    GEAR_RATIOS,        //�M�A��
    3.7857,                //�f�t��(�t�@�C�i���M�A)
    data,               //�G���W���̃g���N[N�Em]
    0.1745,//(��10�x�ɐݒ肵�Ă��邪�ύX��)             //�^�C���̍ő�Ǌp [rad]
    2900,               //�ő吧����[N]
    1.320,              //�S��[m]
    3000,               //�t�����g�o�l���[�g[N/m]
    2328,               //���A�o�l���[�g[N/m]
    0.1,                //(���̒l)
    6,                  //�ő�M�A��
    9000,               //�ō���]��
    800,               //�A�C�h�����O��]��
    -0.0135f,             //�R�[�i�����O�p���[
    14.0f,
    ShiftDownTiming,
    200,
    150.0f,
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
    m_PlayerCarModel.Init("Assets/modelData/Car/911GT3RSR/Body.tkm");
    m_CarWindowModel.Init("Assets/modelData/Car/911GT3RSR/BodyAlpha.tkm", true, AlphaBlendMode_Trans);
    WindowState = true;

    //�ԗ��f�[�^�ݒ�
    m_NowCar = ORECA07;

    //�e�^�C���̃��[�J�����W�ݒ�
    m_LeftFrontWheelLocalPosition = { -32.0f,15.0f,48.0f };		//���t�����g
    m_RightFrontWheelLocalPosition = { 32.0f,15.0f,48.0f };		//�E�t�����g
    m_LeftRearWheelLocalPosition = { -33.0f,15.0f,-50.0f };		//�����A
    m_RightRearWheelLocalPosition = { 33.0f,15.0f,-50.0f };		//�E���A

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

Car_911GT3RSR::~Car_911GT3RSR() {

}