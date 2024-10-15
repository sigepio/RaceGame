#include "stdafx.h"
#include "Car_TS050.h"
#include "PageNum.h"


Car_TS050::Car_TS050() {
    //AE86�̏����ݒ�

    // �g���N�ݒ�
    data = {
    {0, 0},
    {1000, 180},
    {1500, 220},
    {2000, 242},
    {2500, 242},
    {3000, 238},
    {3500, 242},
    {4000, 242},
    {4500, 242},
    {5000, 242},
    {5500, 237},
    {6000, 226},
    {6500, 216},
    {7000, 205},
    {7500, 194},
    {8000, 185},
    {8500, 156},
    {8501, 0},
    {8999, 0}
    };



    //���x�`�B��ݒ�
    GEAR_RATIOS = { 2.571, 2.062, 1.688, 1.379, 1.194,1.000,0.754 };
    ShiftDownTiming = { 6500.0f,6700.0f,6600.0f,7000.0f,6700.0f,6000.0f };
    TorqueMultiplier = { 2.25,2.25,2.25,2.25,2.25,2.25,2.25 };

    vehicle_info = {
    875.0,              //�ԏd[kg]
    2.425,              //�z�C�[���x�[�X[m]
    0.46,               //�d�S�̍���[m]
    1.900,              //�g���b�h��[m]
    1.285,              //�d�S�����ւ܂ł̒��� [m]
    1.285,              //�d�S����O�ւ܂ł̒��� [m]
    0.31,              //�^�C���̔��a [m]
    GEAR_RATIOS,        //�M�A��
    3.600,                //�f�t��(�t�@�C�i���M�A)
    data,               //�G���W���̃g���N[N�Em]
    0.1745,//(��10�x�ɐݒ肵�Ă��邪�ύX��)             //�^�C���̍ő�Ǌp [rad]
    8500,               //�ő吧����[N]
    1.050,              //�S��[m]
    3000,               //�t�����g�o�l���[�g[N/m]
    2328,               //���A�o�l���[�g[N/m]
    0.1,                //(���̒l)
    7,                  //�ő�M�A��
    8500,               //�ō���]��
    500.0,               //�A�C�h�����O��]��
    -0.016f,             //�R�[�i�����O�p���[
    14.0f,
    ShiftDownTiming,
    200,
    100.0f,
    1,
    45.0f,
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
    m_PlayerCarModel.Init("Assets/modelData/Car/TS050/Body.tkm");
    m_CarWindowModel.Init("Assets/modelData/Car/TS050/BodyAlpha.tkm",true,AlphaBlendMode_Trans);
    WindowState = true;

    //�ԗ��f�[�^�ݒ�
    m_NowCar = ORECA07;

    //�e�^�C���̃��[�J�����W�ݒ�
    m_LeftFrontWheelLocalPosition = { -30.0f,15.0f,58.0f };		//���t�����g
    m_RightFrontWheelLocalPosition = { 30.0f,15.0f,58.0f };		//�E�t�����g
    m_LeftRearWheelLocalPosition = { -30.0f,15.0f,-58.0f };		//�����A
    m_RightRearWheelLocalPosition = { 30.0f,15.0f,-58.0f };		//�E���A

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

Car_TS050::~Car_TS050() {

}