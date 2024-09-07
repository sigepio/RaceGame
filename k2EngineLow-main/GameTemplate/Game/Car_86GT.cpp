#include "stdafx.h"
#include "Car_86GT.h"
#include "PageNum.h"


Car_86GT::Car_86GT() {
    //AE86�̏����ݒ�

    // �g���N�ݒ�
    data = {
        {0, 5},
        {200, 10.5},
        {400, 22.4},
        {650, 70.6},
        {800, 82},
        {1000, 95.25},
        {1200, 111.6},
        {1400, 130.3},
        {1600, 145.5},
        {1800, 161.1},
        {2000, 169},
        {2200, 173.9},
        {2400, 177.2},
        {2500, 177.9},
        {2600, 178.7},
        {2700, 179.9},
        {3000, 180.2},
        {3100, 179.8},
        {3200, 179.6},
        {3300, 178.8},
        {3400, 177.4},
        {3600, 174.5},
        {3800, 165.1},
        {4000, 163},
        {4100, 166},
        {4200, 168.7},
        {4300, 174.8},
        {4400, 177.8},
        {4500, 181.1},
        {4700, 184.9},
        {4800, 184.5},
        {4900, 182.5},
        {5000, 180.1},
        {5100, 178.4},
        {5200, 178.1},
        {5300, 177.7},
        {5400, 177.6},
        {5600, 177.9},
        {5700, 177.4},
        {6000, 179.2},
        {6200, 182.9},
        {6300, 183.6},
        {6400, 183.1},
        {6600, 179.1},
        {6800, 173.8},
        {7000, 164.4},
        {7200, 153.7},
        {7400, 142.7},
        {7600, 131},
        {7800, 167.1},
        {8000, 158.7},
        {8200, 147},
        {8400, 135.5},
        {8600, 121},
        {8800, 100},
        {9000, 0}
    };
    //���x�`�B��ݒ�
    GEAR_RATIOS = { 3.626, 2.188, 1.541, 1.213, 1.000, 0.767 };
    ShiftDownTiming = {4400.0f,5200.0f,5700.0f,6100.0f,5600.0f};
    

    vehicle_info = {
    1470.0,              //�ԏd[kg]
    2.570,              //�z�C�[���x�[�X[m]
    0.46,               //�d�S�̍���[m]
    1.530,              //�g���b�h��[m]
    1.285,              //�d�S�����ւ܂ł̒��� [m]
    1.285,              //�d�S����O�ւ܂ł̒��� [m]
    0.3,              //�^�C���̔��a [m]
    GEAR_RATIOS,        //�M�A��
    4.3,                //�f�t��(�t�@�C�i���M�A)
    data,               //�G���W���̃g���N[N�Em]
    0.1745,//(��10�x�ɐݒ肵�Ă��邪�ύX��)             //�^�C���̍ő�Ǌp [rad]
    3500,               //�ő吧����[N]
    1.320,              //�S��[m]
    3000,               //�t�����g�o�l���[�g[N/m]
    2328,               //���A�o�l���[�g[N/m]
    0.1,                //(���̒l)
    6,                  //�ő�M�A��
    7500,               //�ō���]��
    800,               //�A�C�h�����O��]��
    -0.014f,             //�R�[�i�����O�p���[
    14.0f,
    ShiftDownTiming,
    100,
    350.0f
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
    m_PlayerCarModel.Init("Assets/modelData/Car/86GT/Body.tkm");
    m_CarWindowModel.Init("Assets/modelData/Car/86GT/Window.tkm");
    WindowState = true;

    //�ԗ��f�[�^�ݒ�
    m_NowCar = ORECA07;

    //�e�^�C���̃��[�J�����W�ݒ�
    m_LeftFrontWheelLocalPosition = { -30.0f,15.0f,50.0f };		//���t�����g
    m_RightFrontWheelLocalPosition = { 30.0f,15.0f,50.0f };		//�E�t�����g
    m_LeftRearWheelLocalPosition = { -31.0f,15.0f,-50.0f };		//�����A
    m_RightRearWheelLocalPosition = { 31.0f,15.0f,-50.0f };		//�E���A

    //���_�̐ݒ�
    BirdsEyeViewCoordinates = { 0.0f, 95.0f, -175.0f};
    BirdsEyeViewViewpointHeight = 65.0f;
    BonnetViewCoordinates = { 0.0f, 0.0f, 10.0f };
    BonnetViewViewpointHeight = 50.0f;

    BirdsEyeViewTargetPoint = { 0.0f, 0.0f, 0.0f };
    BonnetViewTargetPoint = { 0.0f, 40.0f, 200.0f };

    BirdsEyeViewViewpointDirectionCorrectionByVehicleType = { 50,0,25 };
    BonnetViewViewpointDirectionCorrectionByVehicleType = { 75,0,75 };
}

Car_86GT::~Car_86GT() {

}