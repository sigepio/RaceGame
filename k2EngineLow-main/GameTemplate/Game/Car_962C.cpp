#include "stdafx.h"
#include "Car_962C.h"


#include "PageNum.h"


Car_962C::Car_962C() {
    //AE86�̏����ݒ�

    // �g���N�ݒ�
    data = {
    {0, 100},
    {500, 100},
    {1000, 125},
    {1500, 119},
    {2000, 134},
    {2500, 162},
    {3000, 189},
    {3500, 252},
    {4000, 250},
    {4500, 224},
    {5000, 227},
    {5500, 234},
    {6000, 232},
    {6500, 223},
    {7000, 214},
    {7500, 211},
    {8000, 205},
    {8200, 207},
    {8500, 207},
    {9000, 0}
    };






    //���x�`�B��ݒ�
    GEAR_RATIOS = { 2.250, 1.444, 1.038, 0.827, 0.709 };
    ShiftDownTiming = { 4900.0f,5500.0f,6100.0f,6500.0f};
    TorqueMultiplier = { 2,2.3,2.6,2.9,3.5 };


    vehicle_info = {
    830.0,              //�ԏd[kg]
    2.660,              //�z�C�[���x�[�X[m]
    0.46,               //�d�S�̍���[m]
    2.050,              //�g���b�h��[m]
    1.285,              //�d�S�����ւ܂ł̒��� [m]
    1.285,              //�d�S����O�ւ܂ł̒��� [m]
    0.355,              //�^�C���̔��a [m]
    GEAR_RATIOS,        //�M�A��
    4.6250,                //�f�t��(�t�@�C�i���M�A)
    data,               //�G���W���̃g���N[N�Em]
    0.1745,//(��10�x�ɐݒ肵�Ă��邪�ύX��)             //�^�C���̍ő�Ǌp [rad]
    8000,               //�ő吧����[N]
    1.320,              //�S��[m]
    3000,               //�t�����g�o�l���[�g[N/m]
    2328,               //���A�o�l���[�g[N/m]
    0.1,                //(���̒l)
    5,                  //�ő�M�A��
    8000,               //�ō���]��
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
    m_PlayerCarModel.Init("Assets/modelData/Car/962C/Body.tkm");
    m_CarWindowModel.Init("Assets/modelData/Car/962C/BodyAlpha.tkm", true, AlphaBlendMode_Trans);
    WindowState = true;

    //�ԗ��f�[�^�ݒ�
    m_NowCar = ORECA07;

    //�e�^�C���̃��[�J�����W�ݒ�
    m_LeftFrontWheelLocalPosition = { -31.0f,13.0f,59.5f };		//���t�����g
    m_RightFrontWheelLocalPosition = { 31.0f,13.0f,59.5f };		//�E�t�����g
    m_LeftRearWheelLocalPosition = { -31.0f,15.0f,-46.0f };		//�����A
    m_RightRearWheelLocalPosition = { 31.0f,15.0f,-46.0f };		//�E���A

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

Car_962C::~Car_962C() {

}