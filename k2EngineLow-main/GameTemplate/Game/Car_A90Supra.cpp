#include "stdafx.h"
#include "Car_A90Supra.h"
#include "PageNum.h"


Car_A90Supra::Car_A90Supra() {
    //AE86�̏����ݒ�

    // �g���N�ݒ�
    data = {
    {0, 100},
    {250, 100},
    {500, 119},
    {750, 139},
    {1000, 146},
    {1250, 158},
    {1500, 208},
    {1750, 242},
    {2000, 241},
    {2250, 240},
    {2500, 242},
    {2750, 242},
    {3000, 242},
    {3250, 240},
    {3500, 241},
    {3750, 242},
    {4000, 240},
    {4250, 242},
    {4500, 243},
    {4750, 235},
    {5000, 224},
    {5250, 217},
    {5500, 209.6},
    {5750, 204.6},
    {6000, 195},
    {6250, 188.2},
    {6500, 180},
    {6750, 160},
    {7000, 149},
    {7250, 136},
    {7500, 115}
    };

    //���x�`�B��ݒ�
    GEAR_RATIOS = { 5.25, 3.360, 2.172, 1.720, 1.316, 1.000,0.822,0.640 };
    ShiftDownTiming = { 4400.0f,4500.0f,5500.0f,5300.0f,5300.0f,5300.0f,5300.0f };
    TorqueMultiplier = { 1,1,1,1,1,1,1,1 };

    vehicle_info = {
    1630.0,              //�ԏd[kg]
    2.470,              //�z�C�[���x�[�X[m]
    0.46,               //�d�S�̍���[m]
    1.590,              //�g���b�h��[m]
    1.285,              //�d�S�����ւ܂ł̒��� [m]
    1.285,              //�d�S����O�ւ܂ł̒��� [m]
    0.3,              //�^�C���̔��a [m]
    GEAR_RATIOS,        //�M�A��
    3.154,                //�f�t��(�t�@�C�i���M�A)
    data,               //�G���W���̃g���N[N�Em]
    0.1745,//(��10�x�ɐݒ肵�Ă��邪�ύX��)             //�^�C���̍ő�Ǌp [rad]
    5500,               //�ő吧����[N]
    1.295,              //�S��[m]
    3000,               //�t�����g�o�l���[�g[N/m]
    2328,               //���A�o�l���[�g[N/m]
    0.1,                //(���̒l)
    8,                  //�ő�M�A��
    7200,               //�ō���]��
    1000,               //�A�C�h�����O��]��
    -0.014f,             //�R�[�i�����O�p���[
    14.5f,
    ShiftDownTiming,
    100,
    200.0f,
    0,
    0,
    TorqueMultiplier
    };



    //�ő�M�A���ݒ�
    MaxGear = 8;

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
    m_PlayerCarModel.Init("Assets/modelData/Car/A90Supra/Body.tkm");
    WindowState = false;

    //�ԗ��f�[�^�ݒ�
    m_NowCar = ORECA07;

    //�e�^�C���̃��[�J�����W�ݒ�
    m_LeftFrontWheelLocalPosition = { -30.0f,15.0f,50.0f };		//���t�����g
    m_RightFrontWheelLocalPosition = { 30.0f,15.0f,50.0f };		//�E�t�����g
    m_LeftRearWheelLocalPosition = { -31.0f,15.0f,-50.0f };		//�����A
    m_RightRearWheelLocalPosition = { 31.0f,15.0f,-50.0f };		//�E���A

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

Car_A90Supra::~Car_A90Supra() {

}