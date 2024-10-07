#include "stdafx.h"
#include "Car_LFA.h"

#include "PageNum.h"


Car_LFA::Car_LFA() {
    //AE86�̏����ݒ�

    // �g���N�ݒ�
    data = {
    {0, 0},
    {500, 69},
    {1000, 171},
    {1500, 268},
    {2000, 311},
    {2500, 352},
    {3000, 383},
    {3500, 400},
    {4000, 403},
    {4500, 414},
    {5000, 415},
    {5500, 417},
    {6000, 420},
    {6500, 420},
    {6800, 423},
    {7000, 421},
    {7500, 420},
    {8000, 415},
    {8500, 400},
    {8700, 393},
    {9000, 378},
    {9500, 346},
    {10000, 100}
    };



    //���x�`�B��ݒ�
    GEAR_RATIOS = { 3.231, 	2.188, 1.609, 1.233, 0.970, 0.795};
    ShiftDownTiming = { 6100.0f,6400.0f,6600.0f,7000.0f,7000.0f };
    TorqueMultiplier = { 1.0,1.05,1.1,1.15,1.2,1.2,1.2 };

    vehicle_info = {
    1480.0,              //�ԏd[kg]
    2457.0,              //�z�C�[���x�[�X[m]
    0.46,               //�d�S�̍���[m]
    1.90,              //�g���b�h��[m]
    1.285,              //�d�S�����ւ܂ł̒��� [m]
    1.285,              //�d�S����O�ւ܂ł̒��� [m]
    0.34675,              //�^�C���̔��a [m]
    GEAR_RATIOS,        //�M�A��
    4.217,                //�f�t��(�t�@�C�i���M�A)
    data,               //�G���W���̃g���N[N�Em]
    0.1745,//(��10�x�ɐݒ肵�Ă��邪�ύX��)             //�^�C���̍ő�Ǌp [rad]
    6000,               //�ő吧����[N]
    1.370,              //�S��[m]
    3000,               //�t�����g�o�l���[�g[N/m]
    2328,               //���A�o�l���[�g[N/m]
    0.1,                //(���̒l)
    6,                  //�ő�M�A��
    9500,               //�ō���]��
    850,               //�A�C�h�����O��]��
    -0.0137f,             //�R�[�i�����O�p���[
    14.0f,
    ShiftDownTiming,
    300,
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
    m_PlayerCarModel.Init("Assets/modelData/Car/LFA/Body.tkm");
    WindowState = false;

    //�ԗ��f�[�^�ݒ�
    m_NowCar = ORECA07;

    //�e�^�C���̃��[�J�����W�ݒ�
    m_LeftFrontWheelLocalPosition = { -0.0f,15.0f,63.0f };		//���t�����g
    m_RightFrontWheelLocalPosition = { 0.0f,15.0f,63.0f };		//�E�t�����g
    m_LeftRearWheelLocalPosition = { 1.0f,15.0f,-40.0f };		//�����A
    m_RightRearWheelLocalPosition = { -1.0f,15.0f,-40.0f };		//�E���A

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

Car_LFA::~Car_LFA() {

}