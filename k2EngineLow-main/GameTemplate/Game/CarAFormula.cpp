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

// 50 RPMごとのトルクカーブ情報を1 RPMごとに線形補完する関数
std::map<int, float> interpolateTorqueCurve(const std::map<int, float>& originalCurve) {
    std::map<int, float> interpolatedCurve;
    int prevRPM = 0;
    float prevTorque = 0.0;

    for (const auto& entry : originalCurve) {
        int currentRPM = entry.first;
        float currentTorque = entry.second;

        // 線形補完して1 RPMごとにデータを追加
        for (int rpm = prevRPM + 1; rpm <= currentRPM; rpm++) {
            float interpolatedTorque = prevTorque + (currentTorque - prevTorque) / (currentRPM - prevRPM);
            interpolatedCurve[rpm] = interpolatedTorque;
        }

        prevRPM = currentRPM;
        prevTorque = currentTorque;
    }

    return interpolatedCurve;
}

//トルクカーブlutファイルを読み込む
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
    return interpolateTorqueCurve(torqueCurveLUT);  // トルクカーブを補完して返す
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

//タイヤの動荷重半径
float TireDynamicLoadRadius(float wheelRadius, float mass, float AirPressure) {
    float TireContactArea = 0.0f;                       //タイヤの接地面積
    TireContactArea = mass / (4 * AirPressure);
    
    return wheelRadius - (mass / TireContactArea);
}

// エンジン回転数計算関数
//float calculate_engine_rpm(float torque, float wheel_speed, float gear_ratio, float final_gear_ratio, float differential_power_split, float differential_coast_split, float clutch_max_torque, VehicleInfo vehicle_info,float RPM ) {
//    float engine_torque = torque * differential_power_split;
//    float wheel_torque = engine_torque / gear_ratio / final_gear_ratio;
//    float wheel_radius = 0.25;
//    float engine_power = wheel_torque * (2 * M_PI * RPM / 60);
//    float engine_speed = engine_power / (clutch_max_torque * vehicle_info.inertia);
//    return engine_speed;
//}
// トルク計算関数
float calculate_torque(float engineTorque, float throttle) {
    // トルクカーブからトルクを取得

    // スロットル開度によるトルク補正
    engineTorque *= throttle/255;

    return engineTorque;
}

// 車速計算関数
float calculate_speed(float torque, float wheel_speed, int gear, float gear_ratio, float final_gear_ratio, float differential_power_split, float differential_coast_split, float clutch_max_torque, float grade, VehicleInfo vehicle_info,float RPM) {
    // トルクから車輪トルクを計算
    float wheel_torque = torque * differential_power_split / gear_ratio / final_gear_ratio;

    // 車両の重量とタイヤの半径から、必要なトルクを計算
    float required_torque = vehicle_info.mass*(0.4f*cos(0)*sin(0))*(0.31/2)*0.1;

    // エンジンのトルクが必要なトルクを超える場合は、車速を計算
    //if (torque >= required_torque) {
    //    float wheel_radius = 0.25;
    //    float engine_power = wheel_torque * (2*M_PI*RPM/60);
    //    float engine_speed = engine_power / (clutch_max_torque * vehicle_info.inertia);
    //    return engine_speed * 60.0 / wheel_radius;
    //}
    //else {
    //    // エンジンのトルクが必要なトルクに満たない場合は、車速を0にする
    //    return 0.0;
    //}
}

Vector4 CarAFormula::CarSpeed(std::vector<std::vector<float>> data, const float SHIFT_UP_RPM_ADJUST,const float SHIFT_DOWN_RPM_ADJUST, float currentRPM, float velocity, float mass, float wheelRadius, float grade, float throttle_input, std::vector<float> GEAR_RATIOS, float currentGear,int MaxGear,float AirPressure,float FinalGearRatio,float Transmission_Efficiency,float acceleration) {
    Vector4 ReturnMember = { 0,0,0,0 };

    // トルクカーブの情報を50 RPMごとから1 RPMごとに線形補完する
	//std::map<int, float> torqueCurveLUT = loadTorqueCurveLUT("power.lut");
    
    //// 次のフレームの状態を更新
    currentRPM =  1500 + velocity * GEAR_RATIOS[currentGear] * FinalGearRatio / (2 * 3.1416 * wheelRadius);
    //float throttle = throttle_input;
   // float engineTorque = getTorqueFromLUT(torqueCurveLUT, static_cast<int>(currentRPM));
    float engineTorque = EngineTorque(currentRPM, data);
    ////float wheelTorque = engineTorque * GEAR_RATIOS[currentGear - 1]*FinalGearRatio* Transmission_Efficiency/** TireDynamicLoadRadius(wheelRadius,mass, AirPressure)*/;

    ////wheelTorque *= (throttle_input / 255.0f);
    //// トルク計算
    //    float torque = calculate_torque(engineTorque, throttle_input);

    //    // 車速計算
    //    float wheel_speed = velocity * 3.6;
    //    velocity = calculate_speed(torque, wheel_speed, currentGear, vehicle_info.gear_ratios[(int)currentGear], vehicle_info.final_gear_ratio, vehicle_info.differential_power_split, vehicle_info.differential_coast_split, vehicle_info.clutch_max_torque, grade, vehicle_info,currentRPM);

    //    // エンジン回転数計算
    //    currentRPM = calculate_engine_rpm(torque, wheel_speed, vehicle_info.gear_ratios[(int)currentGear], vehicle_info.final_gear_ratio, vehicle_info.differential_power_split, vehicle_info.differential_coast_split, vehicle_info.clutch_max_torque, vehicle_info,currentRPM);
    
    

    float wheel_torque = calculate_torque(engineTorque,throttle_input) * GEAR_RATIOS[currentGear - 1] * FinalGearRatio; // ホイールトルクの計算
    float driving_force = wheel_torque / wheelRadius; // 駆動力の計算

    float NeedTorque = mass * 9.81 * sin(grade) / (GEAR_RATIOS[currentGear - 1] * FinalGearRatio);

    //float rolling_resistance = 0.020 * mass * 9.81f;
    //float gradient_resistance = mass * 9.81f * sin((int)grade);
    //float acceleration_resistance = mass * (driving_force / mass);

    //float net_driving_force = driving_force - rolling_resistance - gradient_resistance; // 正味の駆動力の計算

    float NowTorque = driving_force - NeedTorque;

    //使うで！
    float NowAcceleration = NowTorque / mass; // 加速度の計算 (F=ma)
    
    float ActualAcceleration = (NowAcceleration - acceleration)/6.0f;

    velocity += ActualAcceleration; // 速度の更新
    
    if (ActualAcceleration < 0.0f) {
        ActualAcceleration *= -1.0f;
    }
    
    if (velocity <= 0.0f && grade >= 0.0f) {
        velocity = 0.0f;
    }

    // シフトアップ処理
    if (g_pad[0]->IsTrigger(enButtonA) && currentGear < MaxGear) {
        // シフトアップ前の回転数を調整
        currentRPM -= SHIFT_UP_RPM_ADJUST;

        // シフトアップ
        currentGear++;

        // ギア比を更新
        GEAR_RATIOS[currentGear - 1] = GEAR_RATIOS[currentGear - 2];
    }

    // 減速処理
    if (g_pad[0]->IsTrigger(enButtonX) && currentGear > 1) {
        // 減速前の回転数を調整
        currentRPM += SHIFT_DOWN_RPM_ADJUST;

        // シフトダウン
        currentGear--;

        // ギア比を更新
        GEAR_RATIOS[currentGear - 1] = GEAR_RATIOS[currentGear];
    }

    if (currentRPM >= 8000) {
        currentRPM -= 500.0f;
    }

    //// 加速処理
    //float acceleration = (wheelTorque / wheelRadius - mass * 9.81 * grade) / mass;
    //velocity += acceleration;

    

    ReturnMember = { velocity ,currentRPM ,currentGear ,ActualAcceleration };
    
    return ReturnMember;
}

//ベクトルのなす角の計算関数
float AngleBetweenTwoVectors(Vector3 OneVector, Vector3 TwoVector) {
    float Angle = 0.0f;
    Angle = (OneVector.Dot(TwoVector)) / (OneVector.Length() * TwoVector.Length());
    return Angle;
}

SimulationResults CarAFormula::CarSimulation(
                    VehicleInfo vehicleinfo,				//車両の情報
                    Vector3 Position,						//位置ベクトル[m]
                    Vector3 VelocityVector,					//速度ベクトル[m/s]
                    float PitchAngle,						//ピッチ角度[rad]
                    float RollAngle,						//ロール角度[rad]
                    Vector3 Acceleration,                   //加速度
                    float CurrentRPM,						//エンジンの回転数 [rpm]
                    float DegreeOfRotationOfTheHandle,		//ハンドルの回転度合 [rad]
                    Vector3 Acceleration_DecelerationForce, //加減速力(前のフレームの車にかかるすべての力)[N]
                    float CurrentGear,						//現在のギア
                    float Grade,							//勾配[rad]
                    float AirDensity,						//空気の密度 [kg/m3]
                    Vector3 WindDirectionVector,			//風の向きベクトル [m/s]
                    float Temperature,						//気温 [℃]
                    float AtmosphericPressure,				//大気圧 [atm]
                    float WaterVaporPressure,				//水蒸気圧 [atm]
                    float RollingResistanceCoefficient,		//路面の転がり抵抗係数
                    float CoefficientOfFriction,			//路面とタイヤとの摩擦係数
                    float AcceleratorOpening,				//アクセルの踏み込み具合
                    float BrakePressure,					//ブレーキの踏み込み具合
                    float SteeringAngle,					//ステアリングアングル
                    Vector3 SteeringFrontVector,			//ステアリングの正面ベクトル
                    Vector3 FrontWheelOrientationVector	   	//前輪向きを表現している単位ベクトル
) {
    //ステップ0:準備フェーズ
    //エンジントルクを線形補完で計算
    float engineTorque = EngineTorque(CurrentRPM, vehicleinfo.data);

    //リターン用の構造体の宣言
    SimulationResults simulationresults;


    //ステップ1:トラクションの計算
    Vector3 Ftraction = Vector3::Zero;

    Ftraction = FrontWheelOrientationVector * engineTorque * AcceleratorOpening * vehicleinfo.GEAR_RATIOS[CurrentGear - 1] * vehicleinfo.FinalGearRatio * 0.95 / vehicleinfo.TireRadius;



    //ステップ2:空気抵抗の計算
    float Faero = 0.0f;

    //進行方向における自動車の空気に対する相対速度を求める
    Vector3 RelativeSpeedBetweenWindDirectionAndVehicleSpeed = Vector3::Zero;       //進行方向における自動車の空気に対する相対速度 [m/s]

    RelativeSpeedBetweenWindDirectionAndVehicleSpeed = WindDirectionVector + VelocityVector;
    

    //空気の密度の計算
    float ρ = 0.0f;                  //空気の密度 [kg/m3]
    
    ρ = ((1.293 * AtmosphericPressure) / (1 + Temperature / 273.15)) * (1 - ((0.378 * WaterVaporPressure) / AtmosphericPressure));


    //自動車の正面投影面積を計算
    float FrontProjectedArea = 0.0f;

    FrontProjectedArea = vehicleinfo.TreadWidth * vehicleinfo.OverallHeight;

    Faero = (ρ / 2) * vehicleinfo.AirResistanceCoefficient * FrontProjectedArea * (RelativeSpeedBetweenWindDirectionAndVehicleSpeed * RelativeSpeedBetweenWindDirectionAndVehicleSpeed);



    //ステップ3:転がり抵抗を計算
    //総転がり抵抗
    Vector3 Frr = Vector3::Zero;

    //各タイヤの転がり抵抗
    Vector3 Frrfo = Vector3::Zero;      //フロントアウト
    Vector3 Frrfi = Vector3::Zero;      //フロントイン
    Vector3 Frrro = Vector3::Zero;      //リアアウト
    Vector3 Frrri = Vector3::Zero;      //リアイン

    //トラクションとは逆向きの単位ベクトル
    Vector3 ReverseTraction = Vector3::Zero;

    ReverseTraction = Ftraction * -1.0f;
    ReverseTraction.Normalize();

    //タイヤにかかる荷重を計算
    //各タイヤの荷重変数
    float Wfo = 0.0f;
    float Wfi = 0.0f;
    float Wro = 0.0f;
    float Wri = 0.0f;
    
    //旋回半径を計算
    float TurningRadius = 0.0f;

    TurningRadius = vehicleinfo.WheelBase / sin(SteeringAngle);

    //加速度の大きさを計算
    float AccelerationInTheDirectionOfTravel = 0.0f;
    AccelerationInTheDirectionOfTravel = sqrt(pow(Acceleration.x, 2.0) + pow(Acceleration.y, 2.0) + pow(Acceleration.z, 2.0));

    //速度の大きさの計算
    float magnitudeOfSpeed = 0.0f;
    magnitudeOfSpeed = sqrt(pow(VelocityVector.x, 2.0) + pow(VelocityVector.y, 2.0) + pow(VelocityVector.z, 2.0));

    Wfo = vehicleinfo.mass * ((((vehicleinfo.RearWheelFromCenterOfGravity - (vehicleinfo.CenterOfGravityFromTheGround * PitchAngle)) / vehicleinfo.WheelBase)) - ((1 / 9.81) * (vehicleinfo.CenterOfGravityFromTheGround / vehicleinfo.WheelBase) * (AccelerationInTheDirectionOfTravel / cos(PitchAngle)))) * ((1 / 2) - ((vehicleinfo.CenterOfGravityFromTheGround / vehicleinfo.TreadWidth) * (RollAngle - (1 / 9.81) * (pow(magnitudeOfSpeed,2.0)/SteeringAngle))));
    Wfi = vehicleinfo.mass * ((((vehicleinfo.RearWheelFromCenterOfGravity - (vehicleinfo.CenterOfGravityFromTheGround * PitchAngle)) / vehicleinfo.WheelBase)) - ((1 / 9.81) * (vehicleinfo.CenterOfGravityFromTheGround / vehicleinfo.WheelBase) * (AccelerationInTheDirectionOfTravel / cos(PitchAngle)))) * ((1 / 2) + ((vehicleinfo.CenterOfGravityFromTheGround / vehicleinfo.TreadWidth) * (RollAngle - (1 / 9.81) * (pow(magnitudeOfSpeed, 2.0) / SteeringAngle))));
    Wro = vehicleinfo.mass * (1.0 - (((vehicleinfo.RearWheelFromCenterOfGravity - (vehicleinfo.CenterOfGravityFromTheGround * PitchAngle)) / vehicleinfo.WheelBase)) + ((1 / 9.81) * (vehicleinfo.CenterOfGravityFromTheGround / vehicleinfo.WheelBase) * (AccelerationInTheDirectionOfTravel / cos(PitchAngle)))) * ((1 / 2) - ((vehicleinfo.CenterOfGravityFromTheGround / vehicleinfo.TreadWidth) * (RollAngle - (1 / 9.81) * (pow(magnitudeOfSpeed, 2.0) / SteeringAngle))));
    Wri = vehicleinfo.mass * (1.0 - (((vehicleinfo.RearWheelFromCenterOfGravity - (vehicleinfo.CenterOfGravityFromTheGround * PitchAngle)) / vehicleinfo.WheelBase)) + ((1 / 9.81) * (vehicleinfo.CenterOfGravityFromTheGround / vehicleinfo.WheelBase) * (AccelerationInTheDirectionOfTravel / cos(PitchAngle)))) * ((1 / 2) -+ ((vehicleinfo.CenterOfGravityFromTheGround / vehicleinfo.TreadWidth) * (RollAngle - (1 / 9.81) * (pow(magnitudeOfSpeed, 2.0) / SteeringAngle))));

    
    Frrfo = ReverseTraction * 0.015/*転がり抵抗係数(アスファルト)*/ * Wfo;
    Frrfi = ReverseTraction * 0.015/*転がり抵抗係数(アスファルト)*/ * Wfi;
    Frrro = ReverseTraction * 0.015/*転がり抵抗係数(アスファルト)*/ * Wro;
    Frrri = ReverseTraction * 0.015/*転がり抵抗係数(アスファルト)*/ * Wri;

    Frr = Frrfo + Frrfi + Frrro + Frrri;



    //ステップ6:遠心力の計算
    float CentrifugalForce = (vehicleinfo.mass / 9.81) * (pow(magnitudeOfSpeed, 2.0) / SteeringAngle);



    //ステップ7:コーナリングパワーを計算
    Vector3 Fcf = Vector3::Zero;

    //横滑り角の計算
    float SideslipAngle = 0.0f;

    //前フレームの速度の単位ベクトルの計算
    Vector3 UnitVectorOfVelocityOfPreviousFrame = Vector3::Zero;
    UnitVectorOfVelocityOfPreviousFrame = VelocityVector;
    UnitVectorOfVelocityOfPreviousFrame.Normalize();

    SideslipAngle = AngleBetweenTwoVectors(UnitVectorOfVelocityOfPreviousFrame, VelocityVector);

    Vector3 RightAngleVector = Vector3::Zero;
    RightAngleVector = VelocityVector;
    RightAngleVector.Normalize();

    double RightAngle = M_PI / 2; // 90度をラジアンに変換
    RightAngleVector.x = RightAngleVector.x * cos(RightAngle) + RightAngleVector.z * sin(RightAngle);
    RightAngleVector.z = -RightAngleVector.x * sin(RightAngle) + RightAngleVector.z * cos(RightAngle);

    Fcf = RightAngleVector * 0.4/*(これは一時的なものであり修正必須)*/;


    //ステップ8:制動力を計算
    Vector3 Fb = Vector3::Zero;

    //トラクションとは逆向きの単位ベクトル(今回はステップ3の時に作成した変数ReverseTractionを使用する)

    Fb = ReverseTraction * BrakePressure * vehicleinfo.MaximumBrakingForce;


    //ステップ9:クルマにかかる力を計算
    //ロールセンターから重心までの距離[m]を計算
    float CenterOfGravityFromRollCenter = 0.0f;
    CenterOfGravityFromRollCenter = vehicleinfo.CenterOfGravityFromTheGround/*ここは実際はロールセンターだが今は重心を代わりに設定しておく*/;

    //ロール角の計算
    float Θ = 0.0f;
    Θ = (CentrifugalForce * CenterOfGravityFromRollCenter) / ((pow(vehicleinfo.TreadWidth, 2.0) / 2) * (vehicleinfo.FrontSpringRate + vehicleinfo.RearSpringRate)-(vehicleinfo.mass * CenterOfGravityFromRollCenter));

    //ピッチ角の計算
    float φ = 0.0f;

    //前のフレームの加減速力をスカラーに変換
    float ADForce = 0.0f;
    ADForce = sqrt(pow(Acceleration_DecelerationForce.x, 2.0) + pow(Acceleration_DecelerationForce.y, 2.0) + pow(Acceleration_DecelerationForce.z, 2.0));

    //加速時と減速時で計算式が違う
    if (AcceleratorOpening > BrakePressure) {
        φ = (ADForce * CenterOfGravityFromRollCenter) / ((vehicleinfo.RearSpringRate * vehicleinfo.RearWheelFromCenterOfGravity * vehicleinfo.WheelBase) - vehicleinfo.mass * CenterOfGravityFromRollCenter);
    }
    else if (AcceleratorOpening < BrakePressure) {
        φ = (ADForce * CenterOfGravityFromRollCenter) / ((vehicleinfo.FrontSpringRate * vehicleinfo.RearWheelFromCenterOfGravity * vehicleinfo.WheelBase) - vehicleinfo.mass * CenterOfGravityFromRollCenter);
    }



    //ステップ10:加速度を計算
    Vector3 NewAcceleration = Vector3::Zero;

    //すべての車にかかる力を合算させる
    Vector3 AllForce = Ftraction  + Frr  + Fb + Fcf;
    //遠心力は合算されていないが実際は合算が必要
    //Faeroである空気抵抗は実際はベクトル化されていなければならないが、現在はスカラーのため一時的な解決方法
    /*AllForce.x = AllForce.x - Faero;
    AllForce.y = AllForce.y - Faero;
    AllForce.z = AllForce.z - Faero;*/

    NewAcceleration = AllForce / vehicleinfo.mass;


    //ステップ11:速度を計算
    Vector3 NewVelocityVector = Vector3::Zero;

    NewVelocityVector = VelocityVector + (NewAcceleration * (1/60));


    //ステップ12:位置を計算
    Vector3 NewPosition = Vector3::Zero;
    
    NewPosition = Position + (NewVelocityVector * (1 / 60));


    //ステップ13:エンジン回転数を再計算
    //速度の大きさの計算
    float NewmagnitudeOfSpeed = 0.0f;
    NewmagnitudeOfSpeed = sqrt(pow(NewVelocityVector.x, 2.0) + pow(NewVelocityVector.y, 2.0) + pow(NewVelocityVector.z, 2.0));

    float NewRPM = 0.0f;
    NewRPM = NewmagnitudeOfSpeed / (2.0f * M_PI * vehicleinfo.TireRadius) * 60.0f * vehicleinfo.GEAR_RATIOS[CurrentGear] * vehicleinfo.FinalGearRatio;


    //ステップ14:リターンする変数たちをまとめる
    simulationresults.Position = NewPosition;
    simulationresults.VelocityVector = NewVelocityVector; 
    simulationresults.PitchAngle = φ;
    simulationresults.RollAngle = Θ;
    simulationresults.CurrentRPM = NewRPM;
    simulationresults.AllForce = AllForce;
    simulationresults.Acceleration = NewAcceleration;

    return simulationresults;
}

void CarAFormula::ShiftChange() {
	
}