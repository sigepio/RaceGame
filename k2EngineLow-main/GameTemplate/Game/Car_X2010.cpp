#include "stdafx.h"
#include "Car_X2010.h"

#include "PageNum.h"


Car_X2010::Car_X2010() {
    //AE86�̏����ݒ�

    // �g���N�ݒ�
    data = {
    {0, 42},
    {250, 42},
    {500, 41},
    {750, 41},
    {1000, 40},
    {1250, 38},
    {1500, 37},
    {1750, 71},
    {2000, 101},
    {2250, 127},
    {2500, 149},
    {2750, 168},
    {3000, 182},
    {3250, 193},
    {3500, 202},
    {3750, 209},
    {4000, 212},
    {4250, 215},
    {4500, 217},
    {4750, 216},
    {5000, 215},
    {5250, 217},
    {5500, 218},
    {5750, 221},
    {6000, 223},
    {6250, 224},
    {6500, 225},
    {6750, 227},
    {7000, 228},
    {7250, 229},
    {7500, 232},
    {7750, 233},
    {8000, 234},
    {8250, 235},
    {8500, 236},
    {8750, 237},
    {9000, 238},
    {9250, 239},
    {9500, 240},
    {9750, 242},
    {10000, 243},
    {10250, 244},
    {10500, 245},
    {10750, 246},
    {11000, 246},
    {11250, 247},
    {11500, 248},
    {11750, 249},
    {12000, 250},
    {12250, 250},
    {12500, 251},
    {12750, 251},
    {13000, 253},
    {13250, 253},
    {13500, 254},
    {13750, 254},
    {14000, 254},
    {14250, 255},
    {14500, 255},
    {14750, 255},
    {15000, 220},
    {15250, 165},
    {15500, 165},
    {15750, 110},
    {16000, 55}
    };





    //���x�`�B��ݒ�
    GEAR_RATIOS = { 3.500, 2.857, 2.312, 1.938, 1.688,1.453,1.245 };
    ShiftDownTiming = { 11900.0f,11800.0f,12200.0f,12700.0f,12600.0f,12400.0f };
    TorqueMultiplier = { 3,3,3,3,3,3,2.75 };

    vehicle_info = {
    615.0,              //�ԏd[kg]
    2.9,              //�z�C�[���x�[�X[m]
    0.46,               //�d�S�̍���[m]
    1.900,              //�g���b�h��[m]
    1.285,              //�d�S�����ւ܂ł̒��� [m]
    1.285,              //�d�S����O�ւ܂ł̒��� [m]
    0.31,              //�^�C���̔��a [m]
    GEAR_RATIOS,        //�M�A��
    2.800,                //�f�t��(�t�@�C�i���M�A)
    data,               //�G���W���̃g���N[N�Em]
    0.1745,//(��10�x�ɐݒ肵�Ă��邪�ύX��)             //�^�C���̍ő�Ǌp [rad]
    10000,               //�ő吧����[N]
    1.050,              //�S��[m]
    3000,               //�t�����g�o�l���[�g[N/m]
    2328,               //���A�o�l���[�g[N/m]
    0.1,                //(���̒l)
    7,                  //�ő�M�A��
    15000,               //�ō���]��
    500.0,               //�A�C�h�����O��]��
    -0.030f,             //�R�[�i�����O�p���[
    14.0f,
    ShiftDownTiming,
    200,
    100.0f,
    0,
    0.0f,
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
    m_PlayerCarModel.Init("Assets/modelData/Car/X2010/Body.tkm");
    m_CarWindowModel.Init("Assets/modelData/Car/X2010/BodyAlpha.tkm", true, AlphaBlendMode_Trans);
    WindowState = true;

    //�ԗ��f�[�^�ݒ�
    m_NowCar = ORECA07;

    //�e�^�C���̃��[�J�����W�ݒ�
    m_LeftFrontWheelLocalPosition = { -32.5f,15.0f,57.0f };		//���t�����g
    m_RightFrontWheelLocalPosition = { 32.5f,15.0f,57.0f };		//�E�t�����g
    m_LeftRearWheelLocalPosition = { -32.0f,15.0f,-68.0f };		//�����A
    m_RightRearWheelLocalPosition = { 32.0f,15.0f,-68.0f };		//�E���A

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

Car_X2010::~Car_X2010() {

}