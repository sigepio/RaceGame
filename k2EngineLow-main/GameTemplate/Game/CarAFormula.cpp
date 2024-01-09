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


//float CarAFormula::Engine(float EngineTnrtia, float Limiter, float MinRPM, float FuelConsumption, float Throttle, float Mass, float Angle, float Radius, std::vector<float> GearRatios, float FinalDriveRatio, std::string PowerCurvelut, std::string AOACLlut, std::string GHCLlut, std::string AOACDlut, std::string GHCDlut) {	
//}

// 50 RPM���Ƃ̃g���N�J�[�u����1 RPM���Ƃɐ��`�⊮����֐�
std::map<int, float> interpolateTorqueCurve(const std::map<int, float>& originalCurve) {
    std::map<int, float> interpolatedCurve;
    int prevRPM = 0;
    float prevTorque = 0.0;

    for (const auto& entry : originalCurve) {
        int currentRPM = entry.first;
        float currentTorque = entry.second;

        // ���`�⊮����1 RPM���ƂɃf�[�^��ǉ�
        for (int rpm = prevRPM + 1; rpm <= currentRPM; rpm++) {
            float interpolatedTorque = prevTorque + (currentTorque - prevTorque) / (currentRPM - prevRPM);
            interpolatedCurve[rpm] = interpolatedTorque;
        }

        prevRPM = currentRPM;
        prevTorque = currentTorque;
    }

    return interpolatedCurve;
}

//�g���N�J�[�ulut�t�@�C����ǂݍ���
std::map<int, float> loadTorqueCurveLUT(const std::string& lutFilePath) {
    std::map<int, float> torqueCurveLUT;
    std::ifstream file(lutFilePath);
    if (file.is_open()) {
        int rpm;
        float torque;
        while (file >> rpm >> torque) {
            torqueCurveLUT[rpm] = torque;
        }
        file.close();
    }
    else {
        std::cerr << "Unable to open LUT file: " << lutFilePath << std::endl;
    }
    return interpolateTorqueCurve(torqueCurveLUT);  // �g���N�J�[�u��⊮���ĕԂ�
}

float getTorqueFromLUT(const std::map<int, float>& torqueCurveLUT, int currentRPM) {
    auto it = torqueCurveLUT.upper_bound(currentRPM);
    if (it != torqueCurveLUT.begin()) {
        --it;
    }
    return it->second;
}

float EngineTorque(float rpm, std::vector<std::vector<float>> data) {
    int i = 0;
    while (data[i][0] <= rpm) {
        i++;
    }
    float t = data[i][1] + ((rpm - data[i - 1][0]) * (data[i - 1][0] - data[i][0])) / (data[i][0] - data[i - 1][1]);
    return t;
}

//�^�C���̓��׏d���a
float TireDynamicLoadRadius(float wheelRadius, float mass, float AirPressure) {
    float TireContactArea = 0.0f;                       //�^�C���̐ڒn�ʐ�
    TireContactArea = mass / (4 * AirPressure);
    
    return wheelRadius - (mass / TireContactArea);
}

// �G���W����]���v�Z�֐�
//float calculate_engine_rpm(float torque, float wheel_speed, float gear_ratio, float final_gear_ratio, float differential_power_split, float differential_coast_split, float clutch_max_torque, VehicleInfo vehicle_info,float RPM ) {
//    float engine_torque = torque * differential_power_split;
//    float wheel_torque = engine_torque / gear_ratio / final_gear_ratio;
//    float wheel_radius = 0.25;
//    float engine_power = wheel_torque * (2 * M_PI * RPM / 60);
//    float engine_speed = engine_power / (clutch_max_torque * vehicle_info.inertia);
//    return engine_speed;
//}
// �g���N�v�Z�֐�
float calculate_torque(float engineTorque, float throttle) {
    // �g���N�J�[�u����g���N���擾

    // �X���b�g���J�x�ɂ��g���N�␳
    engineTorque *= throttle/255;

    return engineTorque;
}

// �ԑ��v�Z�֐�
float calculate_speed(float torque, float wheel_speed, int gear, float gear_ratio, float final_gear_ratio, float differential_power_split, float differential_coast_split, float clutch_max_torque, float grade, VehicleInfo vehicle_info,float RPM) {
    // �g���N����ԗփg���N���v�Z
    float wheel_torque = torque * differential_power_split / gear_ratio / final_gear_ratio;

    // �ԗ��̏d�ʂƃ^�C���̔��a����A�K�v�ȃg���N���v�Z
    float required_torque = vehicle_info.mass*(0.4f*cos(0)*sin(0))*(0.31/2)*0.1;

    // �G���W���̃g���N���K�v�ȃg���N�𒴂���ꍇ�́A�ԑ����v�Z
    //if (torque >= required_torque) {
    //    float wheel_radius = 0.25;
    //    float engine_power = wheel_torque * (2*M_PI*RPM/60);
    //    float engine_speed = engine_power / (clutch_max_torque * vehicle_info.inertia);
    //    return engine_speed * 60.0 / wheel_radius;
    //}
    //else {
    //    // �G���W���̃g���N���K�v�ȃg���N�ɖ����Ȃ��ꍇ�́A�ԑ���0�ɂ���
    //    return 0.0;
    //}
}

Vector4 CarAFormula::CarSpeed(std::vector<std::vector<float>> data, const float SHIFT_UP_RPM_ADJUST,const float SHIFT_DOWN_RPM_ADJUST, float currentRPM, float velocity, float mass, float wheelRadius, float grade, float throttle_input, std::vector<float> GEAR_RATIOS, float currentGear,int MaxGear,float AirPressure,float FinalGearRatio,float Transmission_Efficiency,float acceleration) {
    Vector4 ReturnMember = { 0,0,0,0 };

    // �g���N�J�[�u�̏���50 RPM���Ƃ���1 RPM���Ƃɐ��`�⊮����
	//std::map<int, float> torqueCurveLUT = loadTorqueCurveLUT("power.lut");
    
    //// ���̃t���[���̏�Ԃ��X�V
    currentRPM =  1500 + velocity * GEAR_RATIOS[currentGear] * FinalGearRatio / (2 * 3.1416 * wheelRadius);
    //float throttle = throttle_input;
   // float engineTorque = getTorqueFromLUT(torqueCurveLUT, static_cast<int>(currentRPM));
    float engineTorque = EngineTorque(currentRPM, data);
    ////float wheelTorque = engineTorque * GEAR_RATIOS[currentGear - 1]*FinalGearRatio* Transmission_Efficiency/** TireDynamicLoadRadius(wheelRadius,mass, AirPressure)*/;

    ////wheelTorque *= (throttle_input / 255.0f);
    //// �g���N�v�Z
    //    float torque = calculate_torque(engineTorque, throttle_input);

    //    // �ԑ��v�Z
    //    float wheel_speed = velocity * 3.6;
    //    velocity = calculate_speed(torque, wheel_speed, currentGear, vehicle_info.gear_ratios[(int)currentGear], vehicle_info.final_gear_ratio, vehicle_info.differential_power_split, vehicle_info.differential_coast_split, vehicle_info.clutch_max_torque, grade, vehicle_info,currentRPM);

    //    // �G���W����]���v�Z
    //    currentRPM = calculate_engine_rpm(torque, wheel_speed, vehicle_info.gear_ratios[(int)currentGear], vehicle_info.final_gear_ratio, vehicle_info.differential_power_split, vehicle_info.differential_coast_split, vehicle_info.clutch_max_torque, vehicle_info,currentRPM);
    
    

    float wheel_torque = calculate_torque(engineTorque,throttle_input) * GEAR_RATIOS[currentGear - 1] * FinalGearRatio; // �z�C�[���g���N�̌v�Z
    float driving_force = wheel_torque / wheelRadius; // �쓮�͂̌v�Z

    float NeedTorque = mass * 9.81 * sin(grade) / (GEAR_RATIOS[currentGear - 1] * FinalGearRatio);

    //float rolling_resistance = 0.020 * mass * 9.81f;
    //float gradient_resistance = mass * 9.81f * sin((int)grade);
    //float acceleration_resistance = mass * (driving_force / mass);

    //float net_driving_force = driving_force - rolling_resistance - gradient_resistance; // �����̋쓮�͂̌v�Z

    float NowTorque = driving_force - NeedTorque;

    //�g���ŁI
    float NowAcceleration = NowTorque / mass; // �����x�̌v�Z (F=ma)
    
    float ActualAcceleration = (NowAcceleration - acceleration)/6.0f;

    velocity += ActualAcceleration; // ���x�̍X�V
    
    if (ActualAcceleration < 0.0f) {
        ActualAcceleration *= -1.0f;
    }
    
    if (velocity <= 0.0f && grade >= 0.0f) {
        velocity = 0.0f;
    }

    // �V�t�g�A�b�v����
    if (g_pad[0]->IsTrigger(enButtonA) && currentGear < MaxGear) {
        // �V�t�g�A�b�v�O�̉�]���𒲐�
        currentRPM -= SHIFT_UP_RPM_ADJUST;

        // �V�t�g�A�b�v
        currentGear++;

        // �M�A����X�V
        GEAR_RATIOS[currentGear - 1] = GEAR_RATIOS[currentGear - 2];
    }

    // ��������
    if (g_pad[0]->IsTrigger(enButtonX) && currentGear > 1) {
        // �����O�̉�]���𒲐�
        currentRPM += SHIFT_DOWN_RPM_ADJUST;

        // �V�t�g�_�E��
        currentGear--;

        // �M�A����X�V
        GEAR_RATIOS[currentGear - 1] = GEAR_RATIOS[currentGear];
    }

    if (currentRPM >= 8000) {
        currentRPM -= 500.0f;
    }

    //// ��������
    //float acceleration = (wheelTorque / wheelRadius - mass * 9.81 * grade) / mass;
    //velocity += acceleration;

    

    ReturnMember = { velocity ,currentRPM ,currentGear ,ActualAcceleration };
    
    return ReturnMember;
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
                    Vector3 VelocityVector,					//���x�x�N�g��[m/s]
                    float PitchAngle,						//�s�b�`�p�x[rad]
                    float RollAngle,						//���[���p�x[rad]
                    Vector3 Acceleration,                   //�����x
                    float CurrentRPM,						//�G���W���̉�]�� [rpm]
                    float DegreeOfRotationOfTheHandle,		//�n���h���̉�]�x�� [rad]
                    Vector3 Acceleration_DecelerationForce, //��������(�O�̃t���[���̎Ԃɂ����邷�ׂĂ̗�)[N]
                    float CurrentGear,						//���݂̃M�A
                    float Grade,							//���z[rad]
                    float AirDensity,						//��C�̖��x [kg/m3]
                    Vector3 WindDirectionVector,			//���̌����x�N�g�� [m/s]
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
    //�G���W���g���N����`�⊮�Ōv�Z
    float engineTorque = EngineTorque(CurrentRPM, vehicleinfo.data);

    //���^�[���p�̍\���̂̐錾
    SimulationResults simulationresults;


    //�X�e�b�v1:�g���N�V�����̌v�Z
    Vector3 Ftraction = Vector3::Zero;

    Ftraction = FrontWheelOrientationVector * engineTorque * AcceleratorOpening * vehicleinfo.GEAR_RATIOS[CurrentGear - 1] * vehicleinfo.FinalGearRatio * 0.95 / vehicleinfo.TireRadius;



    //�X�e�b�v2:��C��R�̌v�Z
    float Faero = 0.0f;

    //�i�s�����ɂ����鎩���Ԃ̋�C�ɑ΂��鑊�Α��x�����߂�
    Vector3 RelativeSpeedBetweenWindDirectionAndVehicleSpeed = Vector3::Zero;       //�i�s�����ɂ����鎩���Ԃ̋�C�ɑ΂��鑊�Α��x [m/s]

    RelativeSpeedBetweenWindDirectionAndVehicleSpeed = WindDirectionVector + VelocityVector;
    

    //��C�̖��x�̌v�Z
    float �� = 0.0f;                  //��C�̖��x [kg/m3]
    
    �� = ((1.293 * AtmosphericPressure) / (1 + Temperature / 273.15)) * (1 - ((0.378 * WaterVaporPressure) / AtmosphericPressure));


    //�����Ԃ̐��ʓ��e�ʐς��v�Z
    float FrontProjectedArea = 0.0f;

    FrontProjectedArea = vehicleinfo.TreadWidth * vehicleinfo.OverallHeight;

    Faero = (�� / 2) * vehicleinfo.AirResistanceCoefficient * FrontProjectedArea * (RelativeSpeedBetweenWindDirectionAndVehicleSpeed * RelativeSpeedBetweenWindDirectionAndVehicleSpeed);



    //�X�e�b�v3:�]�����R���v�Z
    //���]�����R
    Vector3 Frr = Vector3::Zero;

    //�e�^�C���̓]�����R
    Vector3 Frrfo = Vector3::Zero;      //�t�����g�A�E�g
    Vector3 Frrfi = Vector3::Zero;      //�t�����g�C��
    Vector3 Frrro = Vector3::Zero;      //���A�A�E�g
    Vector3 Frrri = Vector3::Zero;      //���A�C��

    //�g���N�V�����Ƃ͋t�����̒P�ʃx�N�g��
    Vector3 ReverseTraction = Vector3::Zero;

    ReverseTraction = Ftraction * -1.0f;
    ReverseTraction.Normalize();

    //�^�C���ɂ�����׏d���v�Z
    //�e�^�C���̉׏d�ϐ�
    float Wfo = 0.0f;
    float Wfi = 0.0f;
    float Wro = 0.0f;
    float Wri = 0.0f;
    
    //���񔼌a���v�Z
    float TurningRadius = 0.0f;

    TurningRadius = vehicleinfo.WheelBase / sin(SteeringAngle);

    //�����x�̑傫�����v�Z
    float AccelerationInTheDirectionOfTravel = 0.0f;
    AccelerationInTheDirectionOfTravel = sqrt(pow(Acceleration.x, 2.0) + pow(Acceleration.y, 2.0) + pow(Acceleration.z, 2.0));

    //���x�̑傫���̌v�Z
    float magnitudeOfSpeed = 0.0f;
    magnitudeOfSpeed = sqrt(pow(VelocityVector.x, 2.0) + pow(VelocityVector.y, 2.0) + pow(VelocityVector.z, 2.0));

    Wfo = vehicleinfo.mass * ((((vehicleinfo.RearWheelFromCenterOfGravity - (vehicleinfo.CenterOfGravityFromTheGround * PitchAngle)) / vehicleinfo.WheelBase)) - ((1 / 9.81) * (vehicleinfo.CenterOfGravityFromTheGround / vehicleinfo.WheelBase) * (AccelerationInTheDirectionOfTravel / cos(PitchAngle)))) * ((1 / 2) - ((vehicleinfo.CenterOfGravityFromTheGround / vehicleinfo.TreadWidth) * (RollAngle - (1 / 9.81) * (pow(magnitudeOfSpeed,2.0)/SteeringAngle))));
    Wfi = vehicleinfo.mass * ((((vehicleinfo.RearWheelFromCenterOfGravity - (vehicleinfo.CenterOfGravityFromTheGround * PitchAngle)) / vehicleinfo.WheelBase)) - ((1 / 9.81) * (vehicleinfo.CenterOfGravityFromTheGround / vehicleinfo.WheelBase) * (AccelerationInTheDirectionOfTravel / cos(PitchAngle)))) * ((1 / 2) + ((vehicleinfo.CenterOfGravityFromTheGround / vehicleinfo.TreadWidth) * (RollAngle - (1 / 9.81) * (pow(magnitudeOfSpeed, 2.0) / SteeringAngle))));
    Wro = vehicleinfo.mass * (1.0 - (((vehicleinfo.RearWheelFromCenterOfGravity - (vehicleinfo.CenterOfGravityFromTheGround * PitchAngle)) / vehicleinfo.WheelBase)) + ((1 / 9.81) * (vehicleinfo.CenterOfGravityFromTheGround / vehicleinfo.WheelBase) * (AccelerationInTheDirectionOfTravel / cos(PitchAngle)))) * ((1 / 2) - ((vehicleinfo.CenterOfGravityFromTheGround / vehicleinfo.TreadWidth) * (RollAngle - (1 / 9.81) * (pow(magnitudeOfSpeed, 2.0) / SteeringAngle))));
    Wri = vehicleinfo.mass * (1.0 - (((vehicleinfo.RearWheelFromCenterOfGravity - (vehicleinfo.CenterOfGravityFromTheGround * PitchAngle)) / vehicleinfo.WheelBase)) + ((1 / 9.81) * (vehicleinfo.CenterOfGravityFromTheGround / vehicleinfo.WheelBase) * (AccelerationInTheDirectionOfTravel / cos(PitchAngle)))) * ((1 / 2) -+ ((vehicleinfo.CenterOfGravityFromTheGround / vehicleinfo.TreadWidth) * (RollAngle - (1 / 9.81) * (pow(magnitudeOfSpeed, 2.0) / SteeringAngle))));

    
    Frrfo = ReverseTraction * 0.015/*�]�����R�W��(�A�X�t�@���g)*/ * Wfo;
    Frrfi = ReverseTraction * 0.015/*�]�����R�W��(�A�X�t�@���g)*/ * Wfi;
    Frrro = ReverseTraction * 0.015/*�]�����R�W��(�A�X�t�@���g)*/ * Wro;
    Frrri = ReverseTraction * 0.015/*�]�����R�W��(�A�X�t�@���g)*/ * Wri;

    Frr = Frrfo + Frrfi + Frrro + Frrri;



    //�X�e�b�v6:���S�͂̌v�Z
    float CentrifugalForce = (vehicleinfo.mass / 9.81) * (pow(magnitudeOfSpeed, 2.0) / SteeringAngle);



    //�X�e�b�v7:�R�[�i�����O�p���[���v�Z
    Vector3 Fcf = Vector3::Zero;

    //������p�̌v�Z
    float SideslipAngle = 0.0f;

    //�O�t���[���̑��x�̒P�ʃx�N�g���̌v�Z
    Vector3 UnitVectorOfVelocityOfPreviousFrame = Vector3::Zero;
    UnitVectorOfVelocityOfPreviousFrame = VelocityVector;
    UnitVectorOfVelocityOfPreviousFrame.Normalize();

    SideslipAngle = AngleBetweenTwoVectors(UnitVectorOfVelocityOfPreviousFrame, VelocityVector);

    Vector3 RightAngleVector = Vector3::Zero;
    RightAngleVector = VelocityVector;
    RightAngleVector.Normalize();

    double RightAngle = M_PI / 2; // 90�x�����W�A���ɕϊ�
    RightAngleVector.x = RightAngleVector.x * cos(RightAngle) + RightAngleVector.z * sin(RightAngle);
    RightAngleVector.z = -RightAngleVector.x * sin(RightAngle) + RightAngleVector.z * cos(RightAngle);

    Fcf = RightAngleVector * 0.4/*(����͈ꎞ�I�Ȃ��̂ł���C���K�{)*/;


    //�X�e�b�v8:�����͂��v�Z
    Vector3 Fb = Vector3::Zero;

    //�g���N�V�����Ƃ͋t�����̒P�ʃx�N�g��(����̓X�e�b�v3�̎��ɍ쐬�����ϐ�ReverseTraction���g�p����)

    Fb = ReverseTraction * BrakePressure * vehicleinfo.MaximumBrakingForce;


    //�X�e�b�v9:�N���}�ɂ�����͂��v�Z
    //���[���Z���^�[����d�S�܂ł̋���[m]���v�Z
    float CenterOfGravityFromRollCenter = 0.0f;
    CenterOfGravityFromRollCenter = vehicleinfo.CenterOfGravityFromTheGround/*�����͎��ۂ̓��[���Z���^�[�������͏d�S�����ɐݒ肵�Ă���*/;

    //���[���p�̌v�Z
    float �� = 0.0f;
    �� = (CentrifugalForce * CenterOfGravityFromRollCenter) / ((pow(vehicleinfo.TreadWidth, 2.0) / 2) * (vehicleinfo.FrontSpringRate + vehicleinfo.RearSpringRate)-(vehicleinfo.mass * CenterOfGravityFromRollCenter));

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
    Vector3 NewAcceleration = Vector3::Zero;

    //���ׂĂ̎Ԃɂ�����͂����Z������
    Vector3 AllForce = Ftraction  + Frr  + Fb + Fcf;
    //���S�͍͂��Z����Ă��Ȃ������ۂ͍��Z���K�v
    //Faero�ł����C��R�͎��ۂ̓x�N�g��������Ă��Ȃ���΂Ȃ�Ȃ����A���݂̓X�J���[�̂��߈ꎞ�I�ȉ������@
    /*AllForce.x = AllForce.x - Faero;
    AllForce.y = AllForce.y - Faero;
    AllForce.z = AllForce.z - Faero;*/

    NewAcceleration = AllForce / vehicleinfo.mass;


    //�X�e�b�v11:���x���v�Z
    Vector3 NewVelocityVector = Vector3::Zero;

    NewVelocityVector = VelocityVector + (NewAcceleration * (1/60));


    //�X�e�b�v12:�ʒu���v�Z
    Vector3 NewPosition = Vector3::Zero;
    
    NewPosition = Position + (NewVelocityVector * (1 / 60));


    //�X�e�b�v13:�G���W����]�����Čv�Z
    //���x�̑傫���̌v�Z
    float NewmagnitudeOfSpeed = 0.0f;
    NewmagnitudeOfSpeed = sqrt(pow(NewVelocityVector.x, 2.0) + pow(NewVelocityVector.y, 2.0) + pow(NewVelocityVector.z, 2.0));

    float NewRPM = 0.0f;
    NewRPM = NewmagnitudeOfSpeed / (2.0f * M_PI * vehicleinfo.TireRadius) * 60.0f * vehicleinfo.GEAR_RATIOS[CurrentGear] * vehicleinfo.FinalGearRatio;


    //�X�e�b�v14:���^�[������ϐ��������܂Ƃ߂�
    simulationresults.Position = NewPosition;
    simulationresults.VelocityVector = NewVelocityVector; 
    simulationresults.PitchAngle = ��;
    simulationresults.RollAngle = ��;
    simulationresults.CurrentRPM = NewRPM;
    simulationresults.AllForce = AllForce;
    simulationresults.Acceleration = NewAcceleration;

    return simulationresults;
}

void CarAFormula::ShiftChange() {
	
}