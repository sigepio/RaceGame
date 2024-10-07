#include "stdafx.h"
#include "Car_FordGTLM.h"


#include "PageNum.h"


Car_FordGTLM::Car_FordGTLM() {
    //AE86�̏����ݒ�

    // �g���N�ݒ�
    data = {
    {0, 265},
    {500, 270},
    {1000, 275},
    {1500, 280},
    {2000, 285},
    {2500, 290},
    {3000, 295},
    {3500, 300},
    {3750, 305},
    {4000, 315},
    {4500, 325},
    {5000, 335},
    {5500, 340},
    {6000, 335},
    {6500, 325},
    {7000, 315}
    };



    //���x�`�B��ݒ�
    GEAR_RATIOS = { 2.611, 1.708, 1.233, 0.940, 0.767, 0.630 };
    ShiftDownTiming = { 4200.0f,4700.0f,5000.0f,5400.0f,5500.0f};
    TorqueMultiplier = { 0.8,0.9,1.0,1.1,1.2,1.5,1.2,1.5 };

    vehicle_info = {
    1558.0,              //�ԏd[kg]
    2.470,              //�z�C�[���x�[�X[m]
    0.46,               //�d�S�̍���[m]
    1.590,              //�g���b�h��[m]
    1.285,              //�d�S�����ւ܂ł̒��� [m]
    1.285,              //�d�S����O�ւ܂ł̒��� [m]
    0.34,              //�^�C���̔��a [m]
    GEAR_RATIOS,        //�M�A��
    4.5,                //�f�t��(�t�@�C�i���M�A)
    data,               //�G���W���̃g���N[N�Em]
    0.1745,//(��10�x�ɐݒ肵�Ă��邪�ύX��)             //�^�C���̍ő�Ǌp [rad]
    7500,               //�ő吧����[N]
    1.295,              //�S��[m]
    3000,               //�t�����g�o�l���[�g[N/m]
    2328,               //���A�o�l���[�g[N/m]
    0.1,                //(���̒l)
    6,                  //�ő�M�A��
    7000,               //�ō���]��
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
    m_PlayerCarModel.Init("Assets/modelData/Car/FordGTLM/Body.tkm");

    //�ԗ��f�[�^�ݒ�
    m_NowCar = ORECA07;

    //�e�^�C���̃��[�J�����W�ݒ�
    m_LeftFrontWheelLocalPosition = { -30.0f,15.0f,50.0f };		//���t�����g
    m_RightFrontWheelLocalPosition = { 30.0f,15.0f,50.0f };		//�E�t�����g
    m_LeftRearWheelLocalPosition = { -31.0f,17.0f,-61.0f };		//�����A
    m_RightRearWheelLocalPosition = { 31.0f,17.0f,-61.0f };		//�E���A

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

Car_FordGTLM::~Car_FordGTLM() {

}