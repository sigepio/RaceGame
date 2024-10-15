#include "stdafx.h"
#include "Car_BMWMV8LMDh.h"

#include "PageNum.h"


Car_BMWMV8LMDh::Car_BMWMV8LMDh() {
    //AE86�̏����ݒ�

    // �g���N�ݒ�
    data = {
     {0, 25},
     {250, 25},
     {500, 28},
     {750, 65},
     {1000, 84},
     {1250, 91},
     {1500, 102},
     {1750, 117},
     {2000, 134},
     {2250, 154},
     {2500, 177},
     {2750, 205},
     {3000, 234},
     {3250, 258},
     {3500, 287},
     {3750, 310},
     {4000, 331},
     {4250, 350},
     {4500, 368},
     {4750, 386},
     {5000, 399},
     {5250, 413},
     {5500, 422},
     {5750, 430},
     {6000, 432},
     {6250, 433},
     {6500, 433},
     {6750, 428},
     {7000, 423},
     {7250, 414},
     {7500, 402},
     {7750, 380},
     {8000, 356},
     {8250, 329.5},
     {8500, 291},
     {8750, 234},
     {9000, 163},
     {9250, 66},
     {9500, 0}
    };





    //���x�`�B��ݒ�
    GEAR_RATIOS = { 2.375, 1.875, 1.440, 1.194, 1.000,0.818,0.697 };
    ShiftDownTiming = { 6500.0f,6200.0f,6700.0f,6800.0f,6600.0f,6900.0f };
    TorqueMultiplier = { 1.2,1.2,1.2,1.2,1.2,1.2,1.2 };

    vehicle_info = {
    1037.0,              //�ԏd[kg]
    2.425,              //�z�C�[���x�[�X[m]
    0.46,               //�d�S�̍���[m]
    1.900,              //�g���b�h��[m]
    1.285,              //�d�S�����ւ܂ł̒��� [m]
    1.285,              //�d�S����O�ւ܂ł̒��� [m]
    0.340,              //�^�C���̔��a [m]
    GEAR_RATIOS,        //�M�A��
    4.600,                //�f�t��(�t�@�C�i���M�A)
    data,               //�G���W���̃g���N[N�Em]
    0.1745,//(��10�x�ɐݒ肵�Ă��邪�ύX��)             //�^�C���̍ő�Ǌp [rad]
    8300,               //�ő吧����[N]
    1.050,              //�S��[m]
    3000,               //�t�����g�o�l���[�g[N/m]
    2328,               //���A�o�l���[�g[N/m]
    0.1,                //(���̒l)
    7,                  //�ő�M�A��
    8500,               //�ō���]��
    1950.0,               //�A�C�h�����O��]��
    -0.01570f,             //�R�[�i�����O�p���[
    14.0f,
    ShiftDownTiming,
    200,
    100.0f,
    2,
    60.0f,
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
    m_PlayerCarModel.Init("Assets/modelData/Car/BMWMV8LMDh/Body.tkm");
    m_CarWindowModel.Init("Assets/modelData/Car/BMWMV8LMDh/BodyAlpha.tkm", true, AlphaBlendMode_Trans);
    WindowState = true;

    //�ԗ��f�[�^�ݒ�
    m_NowCar = ORECA07;

    //�e�^�C���̃��[�J�����W�ݒ�
    m_LeftFrontWheelLocalPosition = { -32.0f,15.0f,58.5f };		//���t�����g
    m_RightFrontWheelLocalPosition = { 32.0f,15.0f,58.5f };		//�E�t�����g
    m_LeftRearWheelLocalPosition = { -32.0f,15.0f,-65.0f };		//�����A
    m_RightRearWheelLocalPosition = { 32.0f,15.0f,-65.0f };		//�E���A

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

Car_BMWMV8LMDh::~Car_BMWMV8LMDh() {

}