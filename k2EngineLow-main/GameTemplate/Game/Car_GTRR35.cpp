#include "stdafx.h"
#include "Car_GTRR35.h"
#include "PageNum.h"


Car_GTRR35::Car_GTRR35() {
    //AE86�̏����ݒ�

    // �g���N�ݒ�
    data = {
    {-3000, 100},
    {-250, 100},
    {0, 120},
    {500, 140},
    {1000, 144},
    {1500, 149},
    {2000, 217},
    {2500, 258},
    {3000, 301},
    {3500, 326},
    {3750, 330},
    {4000, 324},
    {4500, 320},
    {5000, 322},
    {5500, 308},
    {6000, 300},
    {6500, 294},
    {6700, 287},
    {6800, 284},
    {7000, 269},
    {7250, 252},
    {7500, 230},
    {8000, 0}
    };

    //���x�`�B��ݒ�
    GEAR_RATIOS = { 4.056, 	2.301, 1.595, 1.248, 1.001, 0.796 };
    ShiftDownTiming = { 4000.0f,4800.0f,5400.0f,5500.0f,5600.0f};

    vehicle_info = {
    1770.0,              //�ԏd[kg]
    2.780,              //�z�C�[���x�[�X[m]
    0.46,               //�d�S�̍���[m]
    1.590,              //�g���b�h��[m]
    1.285,              //�d�S�����ւ܂ł̒��� [m]
    1.285,              //�d�S����O�ւ܂ł̒��� [m]
    0.3,              //�^�C���̔��a [m]
    GEAR_RATIOS,        //�M�A��
    3.700,                //�f�t��(�t�@�C�i���M�A)
    data,               //�G���W���̃g���N[N�Em]
    0.1745,//(��10�x�ɐݒ肵�Ă��邪�ύX��)             //�^�C���̍ő�Ǌp [rad]
    6000,               //�ő吧����[N]
    1.370,              //�S��[m]
    3000,               //�t�����g�o�l���[�g[N/m]
    2328,               //���A�o�l���[�g[N/m]
    0.1,                //(���̒l)
    6,                  //�ő�M�A��
    7150,               //�ō���]��
    900,               //�A�C�h�����O��]��
    -0.0143f,             //�R�[�i�����O�p���[
    16.0f,
    ShiftDownTiming,
    50,
    200.0f
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
    m_PlayerCarModel.Init("Assets/modelData/Car/R35/Body.tkm");
    m_CarWindowModel.Init("Assets/modelData/Car/R35/Window.tkm");
    WindowState = true;

    //�ԗ��f�[�^�ݒ�
    m_NowCar = ORECA07;

    //�e�^�C���̃��[�J�����W�ݒ�
    m_LeftFrontWheelLocalPosition = { -34.5f,15.0f,54.5f };		//���t�����g
    m_RightFrontWheelLocalPosition = { 30.0f,15.0f,54.5f };		//�E�t�����g
    m_LeftRearWheelLocalPosition = { -34.5f,15.0f,-54.5f };		//�����A
    m_RightRearWheelLocalPosition = { 30.0f,15.0f,-54.5f };		//�E���A

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

Car_GTRR35::~Car_GTRR35() {

}