#include "stdafx.h"
#include "Car_MustangGT3.h"


#include "PageNum.h"


Car_MustangGT3::Car_MustangGT3() {
    //AE86�̏����ݒ�

    // �g���N�ݒ�
    data = {
    {0, 348},
    {273, 358},
    {547, 368},
    {820, 393},
    {1094, 418},
    {1368, 458},
    {1642, 498},
    {1862, 521},
    {2082, 533},
    {4051, 536},
    {5035, 537.5},
    {6019, 539},
    {6296, 530},
    {6573, 521},
    {6706, 515},
    {6839, 509},
    {6972, 503},
    {7105, 497},
    {7386, 485},
    {7667, 473},
    {7948, 460.5},
    {8000, 458},
    {8100, 200},
    {8350, 100},
    {8500, 0}
    };




    //���x�`�B��ݒ�
    GEAR_RATIOS = { 2.500, 1.875, 1.500, 1.258, 1.098, 0.904};
    ShiftDownTiming = { 5800.0f,6100.0f,6300.0f,6700.0f,6000.0f };
    TorqueMultiplier = { 0.5,0.5,0.55,0.6,0.7,0.85,1.2 };

    vehicle_info = {
    1300.0,              //�ԏd[kg]
    2457.0,              //�z�C�[���x�[�X[m]
    0.46,               //�d�S�̍���[m]
    1.90,              //�g���b�h��[m]
    1.285,              //�d�S�����ւ܂ł̒��� [m]
    1.285,              //�d�S����O�ւ܂ł̒��� [m]
    0.3,              //�^�C���̔��a [m]
    GEAR_RATIOS,        //�M�A��
    3.4285,                //�f�t��(�t�@�C�i���M�A)
    data,               //�G���W���̃g���N[N�Em]
    0.1745,//(��10�x�ɐݒ肵�Ă��邪�ύX��)             //�^�C���̍ő�Ǌp [rad]
    8000,               //�ő吧����[N]
    1.370,              //�S��[m]
    3000,               //�t�����g�o�l���[�g[N/m]
    2328,               //���A�o�l���[�g[N/m]
    0.1,                //(���̒l)
    6,                  //�ő�M�A��
    8000,               //�ō���]��
    1885,               //�A�C�h�����O��]��
    -0.0147f,             //�R�[�i�����O�p���[
    14.0f,
    ShiftDownTiming,
    200,
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
    m_PlayerCarModel.Init("Assets/modelData/Car/MustangGT3/Body.tkm");
    m_CarWindowModel.Init("Assets/modelData/Car/MustangGT3/BodyAlpha.tkm", true, AlphaBlendMode_Trans);
    WindowState = true;

    //�ԗ��f�[�^�ݒ�
    m_NowCar = ORECA07;

    //�e�^�C���̃��[�J�����W�ݒ�
    m_LeftFrontWheelLocalPosition = { -0.0f,15.0f,57.0f };		//���t�����g
    m_RightFrontWheelLocalPosition = { 0.0f,15.0f,57.0f };		//�E�t�����g
    m_LeftRearWheelLocalPosition = { -0.0f,15.0f,-54.0f };		//�����A
    m_RightRearWheelLocalPosition = { 0.0f,15.0f,-54.0f };		//�E���A

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

Car_MustangGT3::~Car_MustangGT3() {

}