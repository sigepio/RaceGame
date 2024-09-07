#include "stdafx.h"
#include "CarAFormula.h"
#define _USE_MATH_DEFINES
#include <iostream>
#include <fstream>
#include <map>
#include <cmath>
#include <vector>
#include <math.h>

using namespace std;

ofstream outputfile("test.txt");
CarAFormula::CarAFormula() {
    
}

CarAFormula::~CarAFormula() {
    outputfile << "end\n";
    outputfile.close();
}

bool CarAFormula::Start() {
    return true;
}

void CarAFormula::Update() {
    if (GameEnd == true) {
        DeleteGO(this);
    }
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
    float Acceleration,						//�����x
    float CurrentRPM,						//�G���W���̉�]�� [rpm]
    float DegreeOfRotationOfTheHandle,		//�n���h���̉�]�x�� [rad]	
    Vector3 Acceleration_DecelerationForce, //��������(�O�̃t���[���̎Ԃɂ����邷�ׂĂ̗�)[N]
    float CurrentGear,						//���݂̃M�A
    float Grade,							//���z[rad]
    float AirDensity,						//��C�̖��x [kg/m3]
    float WindDirectionVector,				//���̌����x�N�g�� [m/s]
    float Temperature,						//�C�� [��]
    float AtmosphericPressure,				//��C�� [atm]
    float WaterVaporPressure,				//�����C�� [atm]
    float RollingResistanceCoefficient,		//�H�ʂ̓]�����R�W��
    float CoefficientOfFriction,			//�H�ʂƃ^�C���Ƃ̖��C�W��
    float AcceleratorOpening,				//�A�N�Z���̓��ݍ��݋
    float BrakePressure,					//�u���[�L�̓��ݍ��݋
    float SteeringAngle,					//�X�e�A�����O�A���O��
    Vector3 SteeringFrontVector,			//�X�e�A�����O�̐��ʃx�N�g��(���K���ς݂̂�)
    Vector3 FrontWheelOrientationVector,	//�O�֌�����\�����Ă���P�ʃx�N�g��
    bool Transmission,						//AT��MT��
    float ��RPM							    //RPM�̕ω���
) {
    //�X�e�b�v0:�����t�F�[�Y
    //���^�[���p�̍\���̂̐錾
    SimulationResults simulationresults;

    //�G���W���g���N����`�⊮�Ōv�Z
    float engineTorque = EngineTorque(CurrentRPM, vehicleinfo.data);
    engineTorque *= AcceleratorOpening;

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


    //�G���W���u���[�L�̌v�Z
    //�z�C��R
    float Rintake = 0.0f;
    float K1 = 0.25f;       //�z�C��R�W��
    Rintake = K1 * CurrentRPM;

    //�������C��R
    float Rfriction = 0.0f;
    float K2 = 0.15f;       //�������C��R�W��
    Rfriction = K2 * CurrentRPM;

    //������R
    float Rinertia = 0.0f;
    float K3 = 0.25f;       //������R�W��
    Rinertia = K1 * (��RPM / g_gameTime->GetFrameDeltaTime());

    //�G���W���u���[�L��R
    float Rtotal = 0.0f;
    Rtotal = Rintake + Rfriction + Rinertia;

    //�M�A��ɂ���ĕω�
    float FEngineBreake = 0.0f;
    FEngineBreake = (Rtotal * vehicleinfo.GEAR_RATIOS[CurrentGear - 1]) / (vehicleinfo.TireRadius * 100.0f);

    //�u���[�L
    float Fbrake = 0.0f;
    Fbrake = (vehicleinfo.MaximumBrakingForce) * BrakePressure * vehicleinfo.TireRadius;
    
    //�ϑ�
    if (Transmission == true) {
        // �V�t�g�A�b�v����
        if (CurrentRPM >= (vehicleinfo.MaxRPM - vehicleinfo.ShiftUpCorrectionValue) && CurrentGear < vehicleinfo.MaxGear) {
            // �V�t�g�A�b�v
            ShiftChangeFlag = true;
            CurrentGear++;
        }

        // �V�t�g�_�E������
        if (CurrentRPM < (vehicleinfo.ShiftDownTiming[CurrentGear-2]) && CurrentGear > 1) {
            // �V�t�g�_�E��
            ShiftChangeFlag = true;
            CurrentGear--;
        }
    }
    else {
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
    }

    

    //�G���W���g���N�ւ̒�R
    if (AcceleratorOpening != 0) {
        Tload = ((Faero + Frr + Fgrade + Fbrake) / (vehicleinfo.GEAR_RATIOS[CurrentGear - 1])) / vehicleinfo.AccelerationFactor;
    }
    else {
        Tload = ((Faero + Frr + Fgrade + Fbrake + FEngineBreake) * vehicleinfo.GEAR_RATIOS[CurrentGear - 1]) / vehicleinfo.AccelerationFactor;
    }
    
    engineTorque -= Tload;
    engineTorque *= vehicleinfo.GEAR_RATIOS[CurrentGear - 1];
    float OriginEngineTorue = engineTorque;

    //�G���W���g���N����G���W����]���̌v�Z
    float NewRPM = 0.0f;
    //�V�t�g�`�F���W�ȊO�̃G���W����]���̌v�Z
    if (ShiftChangeFlag == false) {
        //�G���W���̊p���x�̌v�Z
        float E_Vel = 0.0f;
        E_Vel = ((2.0f * M_PI) / 60.0f) * CurrentRPM;
        

        E_Vel += (engineTorque / 1.0/*�������[�����g(�G���W���̉��ɂ���)�����1.0�ɐݒ�E����*/) * (1.0f / 60.0f);
        NewRPM = E_Vel * 30.0f / M_PI;
    }
    else {
        float N_Tire = 0.0f;
        N_Tire = (VelocityVector * 2.5 / 100.0f) / (2 * M_PI * vehicleinfo.TireRadius) * 60.0f;
        NewRPM = N_Tire * vehicleinfo.GEAR_RATIOS[CurrentGear - 1] * vehicleinfo.FinalGearRatio;
    }
    //�A�C�h�����O
    if (NewRPM < vehicleinfo.IdlingRPM && VelocityVector * 3600 / 1000 <= 5.0f) {
        NewRPM = vehicleinfo.IdlingRPM;
    }
    //���u���~�b�g
    if (NewRPM >= vehicleinfo.MaxRPM) {
        NewRPM = vehicleinfo.MaxRPM-vehicleinfo.RevLimitGain;
    }
    if (NewRPM <= 0.0f) {
        NewRPM = 0.0f;
    }
    //�G���W����]������z�C�[����]�����v�Z�����x�̎Z�o[cm/s(0.4scale)]
    float NewVelocityVector = 0.0f;
    if (Velocity>=5.0f&&Velocity!=0.0f||Velocity==0.0f&&engineTorque>=0.0f) {
        /*NewVelocityVector = NewRPM / (60.0f * vehicleinfo.GEAR_RATIOS[CurrentGear - 1] * vehicleinfo.FinalGearRatio) * (vehicleinfo.TireRadius * 2.0f * M_PI) * 0.4f * 100.0f;*/
        NewVelocityVector = (NewRPM/60.0f)/*RPM�́A�ꕪ�Ԃɉ����]�B�b�ɕϊ�*/ / vehicleinfo.GEAR_RATIOS[CurrentGear - 1] / vehicleinfo.FinalGearRatio * (vehicleinfo.TireRadius * 2.0f) * M_PI * 100.0f * 0.4f;
        
        
    }
    outputfile << "Gear:" << CurrentGear << "_��R:" << Tload << "_����:"<<NewVelocityVector * 3600.0f * 2.5f / 1000.0f / 100.0f <<"_RPM:"<<NewRPM<<"_��RPM"<< fabsf(NewRPM - CurrentRPM)<<"_�g���N:"<< OriginEngineTorue << "\n";
    //�X�e�b�v2:��C��R�̌v�Z
    //float Faero = 0.0f;

    //�i�s�����ɂ����鎩���Ԃ̋�C�ɑ΂��鑊�Α��x�����߂�
    float RelativeSpeedBetweenWindDirectionAndVehicleSpeed = 0.0f;       //�i�s�����ɂ����鎩���Ԃ̋�C�ɑ΂��鑊�Α��x [m/s]
    
    
    float �� = 0.0f;
    float �� = 0.0f;


    //�X�e�b�v10:�����x���v�Z
    float NewAcceleration = 0.0f;


    //�X�e�b�v11:���x���v�Z

    //�X�e�b�v12:�ʒu���v�Z
    Vector3 NewPosition = Vector3::Zero;

    

    //�X�e�b�v14:���^�[������ϐ��������܂Ƃ߂�
    simulationresults.Position = NewPosition;
    simulationresults.VelocityVector = NewVelocityVector;
    simulationresults.PitchAngle = ��;
    simulationresults.RollAngle = ��;
    simulationresults.CurrentRPM = NewRPM;
    simulationresults.��RPM = fabsf(NewRPM - CurrentRPM);
    simulationresults.CurrentGear = CurrentGear;
    simulationresults.Acceleration = NewAcceleration;


    return simulationresults;
}



void CarAFormula::ShiftChange() {

}