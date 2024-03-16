#include "stdafx.h"
#include "CarAFormula.h"
#define _USE_MATH_DEFINES
#include <iostream>
#include <fstream>
#include <map>
#include <cmath>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;


CarAFormula::CarAFormula() {

}

CarAFormula::~CarAFormula() {

}

bool CarAFormula::Start() {
    return true;
}

void CarAFormula::Update() {

}

// �g���N�J�[�u����1 RPM���Ƃɐ��`�⊮����֐�
float EngineTorque(float rpm, std::vector<std::vector<float>> data) {
    int i = 0;
    while (data[i][0] <= rpm) {
        i++;
        if (i == 40) {
            break;
        }
    }
    /*float t = data[i][1] + ((rpm - data[i - 1][0]) * (data[i - 1][0] - data[i][0])) / (data[i][0] - data[i - 1][1]);*/
    float t = data[i - 1][1] + ((rpm - data[i - 1][0]) * (data[i][1] - data[i - 1][1])) / (data[i][0] - data[i - 1][0]);

    return t;
}




//�x�N�g���̂Ȃ��p�̌v�Z�֐�
float AngleBetweenTwoVectors(Vector3 OneVector, Vector3 TwoVector) {
    float Angle = 0.0f;
    Angle = (OneVector.Dot(TwoVector)) / (OneVector.Length() * TwoVector.Length());
    return Angle;
}

SimulationResults CarAFormula::CarSimulation(
    VehicleInfo vehicleinfo,				//�ԗ��̏��
    Vector3 Position,						//�ʒu�x�N�g��[m]
    float VelocityVector,					//���x�x�N�g��[m/s]
    float PitchAngle,						//�s�b�`�p�x[rad]
    float RollAngle,						//���[���p�x[rad]
    float Acceleration,                     //�����x
    float CurrentRPM,						//�G���W���̉�]�� [rpm]
    float DegreeOfRotationOfTheHandle,		//�n���h���̉�]�x�� [rad]
    Vector3 Acceleration_DecelerationForce, //��������(�O�̃t���[���̎Ԃɂ����邷�ׂĂ̗�)[N]
    float CurrentGear,						//���݂̃M�A
    float Grade,							//���z[rad]
    float AirDensity,						//��C�̖��x [kg/m3]
    float WindDirectionVector,			    //���̌����x�N�g�� [m/s]
    float Temperature,						//�C�� [��]
    float AtmosphericPressure,				//��C�� [atm]
    float WaterVaporPressure,				//�����C�� [atm]
    float RollingResistanceCoefficient,		//�H�ʂ̓]�����R�W��
    float CoefficientOfFriction,			//�H�ʂƃ^�C���Ƃ̖��C�W��
    float AcceleratorOpening,				//�A�N�Z���̓��ݍ��݋
    float BrakePressure,					//�u���[�L�̓��ݍ��݋
    float SteeringAngle,					//�X�e�A�����O�A���O��
    Vector3 SteeringFrontVector,			//�X�e�A�����O�̐��ʃx�N�g��
    Vector3 FrontWheelOrientationVector	   	//�O�֌�����\�����Ă���P�ʃx�N�g��
) {
    //�X�e�b�v0:�����t�F�[�Y
    //���^�[���p�̍\���̂̐錾
    SimulationResults simulationresults;

    //�G���W���g���N����`�⊮�Ōv�Z
    float engineTorque = EngineTorque(CurrentRPM, vehicleinfo.data);
    engineTorque *= AcceleratorOpening * 2.5f;

    //�V�t�g�`�F���W�t���O
    bool ShiftChangeFlag = false;

    //��R
    float Tload = 0.0f;

 
    //��C��R
    float Faero = 0.0f;

    //��C�̖��x�̌v�Z
    float �� = 0.0f;                  //��C�̖��x [kg/m3]

    �� = ((1.293 * AtmosphericPressure) / (1 + Temperature / 273.15)) * (1 - ((0.378 * WaterVaporPressure) / AtmosphericPressure));


    //�����Ԃ̐��ʓ��e�ʐς��v�Z
    float FrontProjectedArea = 0.0f;
    float Velocity = 0.0f;
    Velocity = VelocityVector * 3600.0f / (1000.0f * 100.0f) * 2.5f;

    FrontProjectedArea = vehicleinfo.TreadWidth * vehicleinfo.OverallHeight;

    //�h���b�O�W��
    float Cd = 0.3f;

    Faero = 0.5 * Cd * FrontProjectedArea * �� * pow(Velocity, 1.85f);
    Faero *= vehicleinfo.TireRadius;


    //�]�����R
    //���]�����R
    float Frr = 0.0f;

    Frr = 0.015/*�]�����R�W��(�A�X�t�@���g)*/ * vehicleinfo.mass * 9.8f;

    Frr *= vehicleinfo.TireRadius;

    //�o���R
    float Fgrade = 0.0f;
    Fgrade = vehicleinfo.mass * 9.8f * sin(0);


    //�u���[�L
    float Fbrake = 0.0f;
    Fbrake = (vehicleinfo.MaximumBrakingForce*(10.0f * ((vehicleinfo.MaxGear / CurrentGear)/ vehicleinfo.MaxGear))) * BrakePressure * vehicleinfo.TireRadius;
    
    //�ϑ�
    // �V�t�g�A�b�v����
    if (g_pad[0]->IsTrigger(enButtonA) && CurrentGear < vehicleinfo.MaxGear) {
        // �V�t�g�A�b�v
        ShiftChangeFlag = true;
        CurrentGear++;
    }

    // �V�t�g�_�E������
    if (g_pad[0]->IsTrigger(enButtonX) && CurrentGear > 1) {
        // �V�t�g�_�E��
        ShiftChangeFlag = true;
        CurrentGear--;
    }

    //�G���W���g���N�ւ̒�R
    Tload = (Faero + Frr + Fgrade + Fbrake) * (vehicleinfo.TireRadius / (vehicleinfo.GEAR_RATIOS[CurrentGear - 1] * vehicleinfo.FinalGearRatio * 0.95));
    engineTorque -= Tload;

    //�G���W���g���N����G���W����]���̌v�Z
    float NewRPM = 0.0f;
    //�V�t�g�`�F���W�ȊO�̃G���W����]���̌v�Z
    if (ShiftChangeFlag == false) {
        //�G���W���̊p���x�̌v�Z
        float E_Vel = 0.0f;
        E_Vel = ((2.0f * M_PI) / 60.0f) * CurrentRPM;


        E_Vel += engineTorque / 1.0/*�������[�����g(�G���W���̉��ɂ���)�����1.0�ɐݒ�E����*/ * (1.0f / 60.0f);
        NewRPM = E_Vel * 60.0f / 2.0f / M_PI;
    }
    else {
        float N_Tire = 0.0f;
        N_Tire = (VelocityVector * 2.5 / 100.0f) / (2 * M_PI * vehicleinfo.TireRadius) * 60.0f;
        NewRPM = N_Tire * vehicleinfo.GEAR_RATIOS[CurrentGear - 1] * vehicleinfo.FinalGearRatio;
    }
    //�A�C�h�����O
    if (NewRPM < 1500.0f && VelocityVector * 3600 / 1000 <= 5.0f) {
        NewRPM = 1500.0f;
    }
    //���u���~�b�g
    if (NewRPM >= 8200.0f) {
        NewRPM = 8000.0f;
    }
    if (NewRPM <= 0.0f) {
        NewRPM = 0.0f;
    }
    //�G���W����]������z�C�[����]�����v�Z�����x�̎Z�o
    float NewVelocityVector = 0.0f;
    if (Velocity>=5.0f&&Velocity!=0.0f||Velocity==0.0f&&engineTorque>=0.0f) {
        NewVelocityVector = NewRPM / (60.0f * vehicleinfo.GEAR_RATIOS[CurrentGear - 1] * vehicleinfo.FinalGearRatio) * (vehicleinfo.TireRadius * 2.0f * M_PI) * 0.4f * 100.0f;
    }

    //�X�e�b�v2:��C��R�̌v�Z
    //float Faero = 0.0f;

    //�i�s�����ɂ����鎩���Ԃ̋�C�ɑ΂��鑊�Α��x�����߂�
    float RelativeSpeedBetweenWindDirectionAndVehicleSpeed = 0.0f;       //�i�s�����ɂ����鎩���Ԃ̋�C�ɑ΂��鑊�Α��x [m/s]
    
    //NewVelocityVector = NewRPM / (60.0f * vehicleinfo.GEAR_RATIOS[CurrentGear - 1] * vehicleinfo.FinalGearRatio) * (vehicleinfo.TireRadius * 2.0f * M_PI) * 0.4f * 1000.0f;
    

    //��C�̖��x�̌v�Z
    //float �� = 0.0f;                  //��C�̖��x [kg/m3]

    �� = ((1.293 * AtmosphericPressure) / (1 + Temperature / 273.15)) * (1 - ((0.378 * WaterVaporPressure) / AtmosphericPressure));


    //�����Ԃ̐��ʓ��e�ʐς��v�Z
   // float FrontProjectedArea = 0.0f;

    FrontProjectedArea = vehicleinfo.TreadWidth * vehicleinfo.OverallHeight;

    Faero = (�� / 2) * vehicleinfo.AirResistanceCoefficient * FrontProjectedArea * (RelativeSpeedBetweenWindDirectionAndVehicleSpeed * RelativeSpeedBetweenWindDirectionAndVehicleSpeed);



    //�X�e�b�v3:�]�����R���v�Z
    //���]�����R
    //float Frr = 0.0f;

    //�e�^�C���̓]�����R
    float Frrfo = 0.0f;      //�t�����g�A�E�g
    float Frrfi = 0.0f;      //�t�����g�C��
    float Frrro = 0.0f;      //���A�A�E�g
    float Frrri = 0.0f;      //���A�C��


    //�^�C���ɂ�����׏d���v�Z
    //�e�^�C���̉׏d�ϐ�
    float Wf = 0.0f;

    //���񔼌a���v�Z
    float TurningRadius = 0.0f;

    TurningRadius = vehicleinfo.WheelBase / sin(SteeringAngle);

   

    /*Wfo = vehicleinfo.mass * ((((vehicleinfo.RearWheelFromCenterOfGravity - (vehicleinfo.CenterOfGravityFromTheGround * PitchAngle)) / vehicleinfo.WheelBase)) - ((1 / 9.81) * (vehicleinfo.CenterOfGravityFromTheGround / vehicleinfo.WheelBase) * (AccelerationInTheDirectionOfTravel / cos(PitchAngle)))) * ((1 / 2) - ((vehicleinfo.CenterOfGravityFromTheGround / vehicleinfo.TreadWidth) * (RollAngle - (1 / 9.81) * (pow(magnitudeOfSpeed,2.0)/ TurningRadius))));
    Wfi = vehicleinfo.mass * ((((vehicleinfo.RearWheelFromCenterOfGravity - (vehicleinfo.CenterOfGravityFromTheGround * PitchAngle)) / vehicleinfo.WheelBase)) - ((1 / 9.81) * (vehicleinfo.CenterOfGravityFromTheGround / vehicleinfo.WheelBase) * (AccelerationInTheDirectionOfTravel / cos(PitchAngle)))) * ((1 / 2) + ((vehicleinfo.CenterOfGravityFromTheGround / vehicleinfo.TreadWidth) * (RollAngle - (1 / 9.81) * (pow(magnitudeOfSpeed, 2.0) / TurningRadius))));
    Wro = vehicleinfo.mass * (1.0 - (((vehicleinfo.RearWheelFromCenterOfGravity - (vehicleinfo.CenterOfGravityFromTheGround * PitchAngle)) / vehicleinfo.WheelBase)) + ((1 / 9.81) * (vehicleinfo.CenterOfGravityFromTheGround / vehicleinfo.WheelBase) * (AccelerationInTheDirectionOfTravel / cos(PitchAngle)))) * ((1 / 2) - ((vehicleinfo.CenterOfGravityFromTheGround / vehicleinfo.TreadWidth) * (RollAngle - (1 / 9.81) * (pow(magnitudeOfSpeed, 2.0) / TurningRadius))));
    Wri = vehicleinfo.mass * (1.0 - (((vehicleinfo.RearWheelFromCenterOfGravity - (vehicleinfo.CenterOfGravityFromTheGround * PitchAngle)) / vehicleinfo.WheelBase)) + ((1 / 9.81) * (vehicleinfo.CenterOfGravityFromTheGround / vehicleinfo.WheelBase) * (AccelerationInTheDirectionOfTravel / cos(PitchAngle)))) * ((1 / 2) -+ ((vehicleinfo.CenterOfGravityFromTheGround / vehicleinfo.TreadWidth) * (RollAngle - (1 / 9.81) * (pow(magnitudeOfSpeed, 2.0) / TurningRadius))));*/

    Wf = (vehicleinfo.mass * 9.8f * vehicleinfo.RearWheelFromCenterOfGravity * vehicleinfo.TreadWidth) / (1.0f * 2.0f);

    Frrfo = 0.015/*�]�����R�W��(�A�X�t�@���g)*/ * Wf;
    Frrfi = 0.015/*�]�����R�W��(�A�X�t�@���g)*/ * Wf;
    Frrro = 0.015/*�]�����R�W��(�A�X�t�@���g)*/ * Wf;
    Frrri = 0.015/*�]�����R�W��(�A�X�t�@���g)*/ * Wf;

    Frr = Frrfo + Frrfi + Frrro + Frrri;






    //�X�e�b�v8:�����͂��v�Z
    float Fb = 0.0f;

    //�g���N�V�����Ƃ͋t�����̒P�ʃx�N�g��(����̓X�e�b�v3�̎��ɍ쐬�����ϐ�ReverseTraction���g�p����)
    Fb = (BrakePressure / 255.0f) * vehicleinfo.MaximumBrakingForce;

    float T2 = 0.0f;

    float Gearlost = 0.0f;

    engineTorque = engineTorque - Frr - Faero - Fb;

    

    


    //�X�e�b�v1:�g���N�V�����̌v�Z
    float Ftraction = 0.0f;
    float wheel_angular_velocity = 0.0f;
    wheel_angular_velocity = NewRPM * vehicleinfo.GEAR_RATIOS[CurrentGear - 1] * vehicleinfo.FinalGearRatio * 0.95 / 60.0f;

    Ftraction = NewRPM * engineTorque * vehicleinfo.GEAR_RATIOS[CurrentGear - 1] * vehicleinfo.FinalGearRatio * 0.95 / 60.0f;


    //�X�e�b�v6:���S�͂̌v�Z
    float CentrifugalForce = (vehicleinfo.mass / 9.81) * (pow(VelocityVector, 2.0) / TurningRadius);



    //�X�e�b�v7:�R�[�i�����O�p���[���v�Z
    Vector3 Fcf = Vector3::Zero;

    ////������p�̌v�Z
    float SideslipAngle = 0.0f;

    ////�O�t���[���̑��x�̒P�ʃx�N�g���̌v�Z
    Vector3 UnitVectorOfVelocityOfPreviousFrame = { 0.0f,0.0f,1.0f };
    UnitVectorOfVelocityOfPreviousFrame.Normalize();

    SideslipAngle = AngleBetweenTwoVectors(UnitVectorOfVelocityOfPreviousFrame, {0.0f,0.0f,1.0f});

    Vector3 RightAngleVector = { 0.0f,0.0f,1.0f };
    RightAngleVector.Normalize();

    RightAngleVector.Cross(Vector3(0, 1, 0));

    Fcf = RightAngleVector * (40.0f * 9.807f * SteeringAngle)/*(����͈ꎞ�I�Ȃ��̂ł���C���K�{)*/;


    //�X�e�b�v9:�N���}�ɂ�����͂��v�Z
    //���[���Z���^�[����d�S�܂ł̋���[m]���v�Z
    float CenterOfGravityFromRollCenter = 0.0f;
    CenterOfGravityFromRollCenter = vehicleinfo.CenterOfGravityFromTheGround/*�����͎��ۂ̓��[���Z���^�[�������͏d�S�����ɐݒ肵�Ă���*/;

    //���[���p�̌v�Z
    float �� = 0.0f;
    �� = (CentrifugalForce * CenterOfGravityFromRollCenter) / ((pow(vehicleinfo.TreadWidth, 2.0) / 2) * (vehicleinfo.FrontSpringRate + vehicleinfo.RearSpringRate) - (vehicleinfo.mass * CenterOfGravityFromRollCenter));

    //�s�b�`�p�̌v�Z
    float �� = 0.0f;

    //�O�̃t���[���̉������͂��X�J���[�ɕϊ�
    float ADForce = 0.0f;
    ADForce = sqrt(pow(Acceleration_DecelerationForce.x, 2.0) + pow(Acceleration_DecelerationForce.y, 2.0) + pow(Acceleration_DecelerationForce.z, 2.0));

    //�������ƌ������Ōv�Z�����Ⴄ
    if (AcceleratorOpening > BrakePressure) {
        �� = (ADForce * CenterOfGravityFromRollCenter) / ((vehicleinfo.RearSpringRate * vehicleinfo.RearWheelFromCenterOfGravity * vehicleinfo.WheelBase) - vehicleinfo.mass * CenterOfGravityFromRollCenter);
    }
    else if (AcceleratorOpening < BrakePressure) {
        �� = (ADForce * CenterOfGravityFromRollCenter) / ((vehicleinfo.FrontSpringRate * vehicleinfo.RearWheelFromCenterOfGravity * vehicleinfo.WheelBase) - vehicleinfo.mass * CenterOfGravityFromRollCenter);
    }



    //�X�e�b�v10:�����x���v�Z
    float NewAcceleration = 0.0f;

    //���ׂĂ̎Ԃɂ�����͂����Z������
    //���S�͍͂��Z����Ă��Ȃ������ۂ͍��Z���K�v
    //Faero�ł����C��R�͎��ۂ̓x�N�g��������Ă��Ȃ���΂Ȃ�Ȃ����A���݂̓X�J���[�̂��߈ꎞ�I�ȉ������@
    /*AllForce.x = AllForce.x - Faero;
    AllForce.y = AllForce.y - Faero;
    AllForce.z = AllForce.z - Faero;*/

    NewAcceleration = Ftraction / vehicleinfo.mass;


    //�X�e�b�v11:���x���v�Z

    //�X�e�b�v12:�ʒu���v�Z
    Vector3 NewPosition = Vector3::Zero;
    //NewPosition = Position + (NewVelocityVector * (1.0f / 60.0f));

    //�X�e�b�v14:���^�[������ϐ��������܂Ƃ߂�
    simulationresults.Position = NewPosition;
    simulationresults.VelocityVector = NewVelocityVector;
    simulationresults.PitchAngle = ��;
    simulationresults.RollAngle = ��;
    simulationresults.CurrentRPM = NewRPM;
    simulationresults.CurrentGear = CurrentGear;
    simulationresults.Acceleration = NewAcceleration;

    return simulationresults;
}

void CarAFormula::ShiftChange() {

}