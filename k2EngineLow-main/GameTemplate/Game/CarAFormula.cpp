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

// トルクカーブ情報を1 RPMごとに線形補完する関数
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




//ベクトルのなす角の計算関数
float AngleBetweenTwoVectors(Vector3 OneVector, Vector3 TwoVector) {
    float Angle = 0.0f;
    Angle = (OneVector.Dot(TwoVector)) / (OneVector.Length() * TwoVector.Length());
    return Angle;
}

SimulationResults CarAFormula::CarSimulation(
    VehicleInfo vehicleinfo,				//車両の情報
    Vector3 Position,						//位置ベクトル[m]
    float VelocityVector,					//速度ベクトル[m/s]
    float PitchAngle,						//ピッチ角度[rad]
    float RollAngle,						//ロール角度[rad]
    float Acceleration,                     //加速度
    float CurrentRPM,						//エンジンの回転数 [rpm]
    float DegreeOfRotationOfTheHandle,		//ハンドルの回転度合 [rad]
    Vector3 Acceleration_DecelerationForce, //加減速力(前のフレームの車にかかるすべての力)[N]
    float CurrentGear,						//現在のギア
    float Grade,							//勾配[rad]
    float AirDensity,						//空気の密度 [kg/m3]
    float WindDirectionVector,			    //風の向きベクトル [m/s]
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
    //リターン用の構造体の宣言
    SimulationResults simulationresults;

    //エンジントルクを線形補完で計算
    float engineTorque = EngineTorque(CurrentRPM, vehicleinfo.data);
    engineTorque *= AcceleratorOpening * 2.5f;

    //シフトチェンジフラグ
    bool ShiftChangeFlag = false;

    //抵抗
    float Tload = 0.0f;

 
    //空気抵抗
    float Faero = 0.0f;

    //空気の密度の計算
    float ρ = 0.0f;                  //空気の密度 [kg/m3]

    ρ = ((1.293 * AtmosphericPressure) / (1 + Temperature / 273.15)) * (1 - ((0.378 * WaterVaporPressure) / AtmosphericPressure));


    //自動車の正面投影面積を計算
    float FrontProjectedArea = 0.0f;
    float Velocity = 0.0f;
    Velocity = VelocityVector * 3600.0f / (1000.0f * 100.0f) * 2.5f;

    FrontProjectedArea = vehicleinfo.TreadWidth * vehicleinfo.OverallHeight;

    //ドラッグ係数
    float Cd = 0.3f;

    Faero = 0.5 * Cd * FrontProjectedArea * ρ * pow(Velocity, 1.85f);
    Faero *= vehicleinfo.TireRadius;


    //転がり抵抗
    //総転がり抵抗
    float Frr = 0.0f;

    Frr = 0.015/*転がり抵抗係数(アスファルト)*/ * vehicleinfo.mass * 9.8f;

    Frr *= vehicleinfo.TireRadius;

    //登坂抵抗
    float Fgrade = 0.0f;
    Fgrade = vehicleinfo.mass * 9.8f * sin(0);


    //ブレーキ
    float Fbrake = 0.0f;
    Fbrake = (vehicleinfo.MaximumBrakingForce*(10.0f * ((vehicleinfo.MaxGear / CurrentGear)/ vehicleinfo.MaxGear))) * BrakePressure * vehicleinfo.TireRadius;
    
    //変速
    // シフトアップ処理
    if (g_pad[0]->IsTrigger(enButtonA) && CurrentGear < vehicleinfo.MaxGear) {
        // シフトアップ
        ShiftChangeFlag = true;
        CurrentGear++;
    }

    // シフトダウン処理
    if (g_pad[0]->IsTrigger(enButtonX) && CurrentGear > 1) {
        // シフトダウン
        ShiftChangeFlag = true;
        CurrentGear--;
    }

    //エンジントルクへの抵抗
    Tload = (Faero + Frr + Fgrade + Fbrake) * (vehicleinfo.TireRadius / (vehicleinfo.GEAR_RATIOS[CurrentGear - 1] * vehicleinfo.FinalGearRatio * 0.95));
    engineTorque -= Tload;

    //エンジントルクからエンジン回転数の計算
    float NewRPM = 0.0f;
    //シフトチェンジ以外のエンジン回転数の計算
    if (ShiftChangeFlag == false) {
        //エンジンの角速度の計算
        float E_Vel = 0.0f;
        E_Vel = ((2.0f * M_PI) / 60.0f) * CurrentRPM;


        E_Vel += engineTorque / 1.0/*慣性モーメント(エンジンの回りにくさ)今回は1.0に設定・調整*/ * (1.0f / 60.0f);
        NewRPM = E_Vel * 60.0f / 2.0f / M_PI;
    }
    else {
        float N_Tire = 0.0f;
        N_Tire = (VelocityVector * 2.5 / 100.0f) / (2 * M_PI * vehicleinfo.TireRadius) * 60.0f;
        NewRPM = N_Tire * vehicleinfo.GEAR_RATIOS[CurrentGear - 1] * vehicleinfo.FinalGearRatio;
    }
    //アイドリング
    if (NewRPM < 1500.0f && VelocityVector * 3600 / 1000 <= 5.0f) {
        NewRPM = 1500.0f;
    }
    //レブリミット
    if (NewRPM >= 8200.0f) {
        NewRPM = 8000.0f;
    }
    if (NewRPM <= 0.0f) {
        NewRPM = 0.0f;
    }
    //エンジン回転数からホイール回転数を計算し速度の算出
    float NewVelocityVector = 0.0f;
    if (Velocity>=5.0f&&Velocity!=0.0f||Velocity==0.0f&&engineTorque>=0.0f) {
        NewVelocityVector = NewRPM / (60.0f * vehicleinfo.GEAR_RATIOS[CurrentGear - 1] * vehicleinfo.FinalGearRatio) * (vehicleinfo.TireRadius * 2.0f * M_PI) * 0.4f * 100.0f;
    }

    //ステップ2:空気抵抗の計算
    //float Faero = 0.0f;

    //進行方向における自動車の空気に対する相対速度を求める
    float RelativeSpeedBetweenWindDirectionAndVehicleSpeed = 0.0f;       //進行方向における自動車の空気に対する相対速度 [m/s]
    
    //NewVelocityVector = NewRPM / (60.0f * vehicleinfo.GEAR_RATIOS[CurrentGear - 1] * vehicleinfo.FinalGearRatio) * (vehicleinfo.TireRadius * 2.0f * M_PI) * 0.4f * 1000.0f;
    

    //空気の密度の計算
    //float ρ = 0.0f;                  //空気の密度 [kg/m3]

    ρ = ((1.293 * AtmosphericPressure) / (1 + Temperature / 273.15)) * (1 - ((0.378 * WaterVaporPressure) / AtmosphericPressure));


    //自動車の正面投影面積を計算
   // float FrontProjectedArea = 0.0f;

    FrontProjectedArea = vehicleinfo.TreadWidth * vehicleinfo.OverallHeight;

    Faero = (ρ / 2) * vehicleinfo.AirResistanceCoefficient * FrontProjectedArea * (RelativeSpeedBetweenWindDirectionAndVehicleSpeed * RelativeSpeedBetweenWindDirectionAndVehicleSpeed);



    //ステップ3:転がり抵抗を計算
    //総転がり抵抗
    //float Frr = 0.0f;

    //各タイヤの転がり抵抗
    float Frrfo = 0.0f;      //フロントアウト
    float Frrfi = 0.0f;      //フロントイン
    float Frrro = 0.0f;      //リアアウト
    float Frrri = 0.0f;      //リアイン


    //タイヤにかかる荷重を計算
    //各タイヤの荷重変数
    float Wf = 0.0f;

    //旋回半径を計算
    float TurningRadius = 0.0f;

    TurningRadius = vehicleinfo.WheelBase / sin(SteeringAngle);

   

    /*Wfo = vehicleinfo.mass * ((((vehicleinfo.RearWheelFromCenterOfGravity - (vehicleinfo.CenterOfGravityFromTheGround * PitchAngle)) / vehicleinfo.WheelBase)) - ((1 / 9.81) * (vehicleinfo.CenterOfGravityFromTheGround / vehicleinfo.WheelBase) * (AccelerationInTheDirectionOfTravel / cos(PitchAngle)))) * ((1 / 2) - ((vehicleinfo.CenterOfGravityFromTheGround / vehicleinfo.TreadWidth) * (RollAngle - (1 / 9.81) * (pow(magnitudeOfSpeed,2.0)/ TurningRadius))));
    Wfi = vehicleinfo.mass * ((((vehicleinfo.RearWheelFromCenterOfGravity - (vehicleinfo.CenterOfGravityFromTheGround * PitchAngle)) / vehicleinfo.WheelBase)) - ((1 / 9.81) * (vehicleinfo.CenterOfGravityFromTheGround / vehicleinfo.WheelBase) * (AccelerationInTheDirectionOfTravel / cos(PitchAngle)))) * ((1 / 2) + ((vehicleinfo.CenterOfGravityFromTheGround / vehicleinfo.TreadWidth) * (RollAngle - (1 / 9.81) * (pow(magnitudeOfSpeed, 2.0) / TurningRadius))));
    Wro = vehicleinfo.mass * (1.0 - (((vehicleinfo.RearWheelFromCenterOfGravity - (vehicleinfo.CenterOfGravityFromTheGround * PitchAngle)) / vehicleinfo.WheelBase)) + ((1 / 9.81) * (vehicleinfo.CenterOfGravityFromTheGround / vehicleinfo.WheelBase) * (AccelerationInTheDirectionOfTravel / cos(PitchAngle)))) * ((1 / 2) - ((vehicleinfo.CenterOfGravityFromTheGround / vehicleinfo.TreadWidth) * (RollAngle - (1 / 9.81) * (pow(magnitudeOfSpeed, 2.0) / TurningRadius))));
    Wri = vehicleinfo.mass * (1.0 - (((vehicleinfo.RearWheelFromCenterOfGravity - (vehicleinfo.CenterOfGravityFromTheGround * PitchAngle)) / vehicleinfo.WheelBase)) + ((1 / 9.81) * (vehicleinfo.CenterOfGravityFromTheGround / vehicleinfo.WheelBase) * (AccelerationInTheDirectionOfTravel / cos(PitchAngle)))) * ((1 / 2) -+ ((vehicleinfo.CenterOfGravityFromTheGround / vehicleinfo.TreadWidth) * (RollAngle - (1 / 9.81) * (pow(magnitudeOfSpeed, 2.0) / TurningRadius))));*/

    Wf = (vehicleinfo.mass * 9.8f * vehicleinfo.RearWheelFromCenterOfGravity * vehicleinfo.TreadWidth) / (1.0f * 2.0f);

    Frrfo = 0.015/*転がり抵抗係数(アスファルト)*/ * Wf;
    Frrfi = 0.015/*転がり抵抗係数(アスファルト)*/ * Wf;
    Frrro = 0.015/*転がり抵抗係数(アスファルト)*/ * Wf;
    Frrri = 0.015/*転がり抵抗係数(アスファルト)*/ * Wf;

    Frr = Frrfo + Frrfi + Frrro + Frrri;






    //ステップ8:制動力を計算
    float Fb = 0.0f;

    //トラクションとは逆向きの単位ベクトル(今回はステップ3の時に作成した変数ReverseTractionを使用する)
    Fb = (BrakePressure / 255.0f) * vehicleinfo.MaximumBrakingForce;

    float T2 = 0.0f;

    float Gearlost = 0.0f;

    engineTorque = engineTorque - Frr - Faero - Fb;

    

    


    //ステップ1:トラクションの計算
    float Ftraction = 0.0f;
    float wheel_angular_velocity = 0.0f;
    wheel_angular_velocity = NewRPM * vehicleinfo.GEAR_RATIOS[CurrentGear - 1] * vehicleinfo.FinalGearRatio * 0.95 / 60.0f;

    Ftraction = NewRPM * engineTorque * vehicleinfo.GEAR_RATIOS[CurrentGear - 1] * vehicleinfo.FinalGearRatio * 0.95 / 60.0f;


    //ステップ6:遠心力の計算
    float CentrifugalForce = (vehicleinfo.mass / 9.81) * (pow(VelocityVector, 2.0) / TurningRadius);



    //ステップ7:コーナリングパワーを計算
    Vector3 Fcf = Vector3::Zero;

    ////横滑り角の計算
    float SideslipAngle = 0.0f;

    ////前フレームの速度の単位ベクトルの計算
    Vector3 UnitVectorOfVelocityOfPreviousFrame = { 0.0f,0.0f,1.0f };
    UnitVectorOfVelocityOfPreviousFrame.Normalize();

    SideslipAngle = AngleBetweenTwoVectors(UnitVectorOfVelocityOfPreviousFrame, {0.0f,0.0f,1.0f});

    Vector3 RightAngleVector = { 0.0f,0.0f,1.0f };
    RightAngleVector.Normalize();

    RightAngleVector.Cross(Vector3(0, 1, 0));

    Fcf = RightAngleVector * (40.0f * 9.807f * SteeringAngle)/*(これは一時的なものであり修正必須)*/;


    //ステップ9:クルマにかかる力を計算
    //ロールセンターから重心までの距離[m]を計算
    float CenterOfGravityFromRollCenter = 0.0f;
    CenterOfGravityFromRollCenter = vehicleinfo.CenterOfGravityFromTheGround/*ここは実際はロールセンターだが今は重心を代わりに設定しておく*/;

    //ロール角の計算
    float Θ = 0.0f;
    Θ = (CentrifugalForce * CenterOfGravityFromRollCenter) / ((pow(vehicleinfo.TreadWidth, 2.0) / 2) * (vehicleinfo.FrontSpringRate + vehicleinfo.RearSpringRate) - (vehicleinfo.mass * CenterOfGravityFromRollCenter));

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
    float NewAcceleration = 0.0f;

    //すべての車にかかる力を合算させる
    //遠心力は合算されていないが実際は合算が必要
    //Faeroである空気抵抗は実際はベクトル化されていなければならないが、現在はスカラーのため一時的な解決方法
    /*AllForce.x = AllForce.x - Faero;
    AllForce.y = AllForce.y - Faero;
    AllForce.z = AllForce.z - Faero;*/

    NewAcceleration = Ftraction / vehicleinfo.mass;


    //ステップ11:速度を計算

    //ステップ12:位置を計算
    Vector3 NewPosition = Vector3::Zero;
    //NewPosition = Position + (NewVelocityVector * (1.0f / 60.0f));

    //ステップ14:リターンする変数たちをまとめる
    simulationresults.Position = NewPosition;
    simulationresults.VelocityVector = NewVelocityVector;
    simulationresults.PitchAngle = φ;
    simulationresults.RollAngle = Θ;
    simulationresults.CurrentRPM = NewRPM;
    simulationresults.CurrentGear = CurrentGear;
    simulationresults.Acceleration = NewAcceleration;

    return simulationresults;
}

void CarAFormula::ShiftChange() {

}