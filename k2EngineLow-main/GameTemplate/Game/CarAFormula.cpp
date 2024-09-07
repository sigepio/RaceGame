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
    float Acceleration,						//加速度
    float CurrentRPM,						//エンジンの回転数 [rpm]
    float DegreeOfRotationOfTheHandle,		//ハンドルの回転度合 [rad]	
    Vector3 Acceleration_DecelerationForce, //加減速力(前のフレームの車にかかるすべての力)[N]
    float CurrentGear,						//現在のギア
    float Grade,							//勾配[rad]
    float AirDensity,						//空気の密度 [kg/m3]
    float WindDirectionVector,				//風の向きベクトル [m/s]
    float Temperature,						//気温 [℃]
    float AtmosphericPressure,				//大気圧 [atm]
    float WaterVaporPressure,				//水蒸気圧 [atm]
    float RollingResistanceCoefficient,		//路面の転がり抵抗係数
    float CoefficientOfFriction,			//路面とタイヤとの摩擦係数
    float AcceleratorOpening,				//アクセルの踏み込み具合
    float BrakePressure,					//ブレーキの踏み込み具合
    float SteeringAngle,					//ステアリングアングル
    Vector3 SteeringFrontVector,			//ステアリングの正面ベクトル(正規化済みのみ)
    Vector3 FrontWheelOrientationVector,	//前輪向きを表現している単位ベクトル
    bool Transmission,						//ATかMTか
    float ΔRPM							    //RPMの変化量
) {
    //ステップ0:準備フェーズ
    //リターン用の構造体の宣言
    SimulationResults simulationresults;

    //エンジントルクを線形補完で計算
    float engineTorque = EngineTorque(CurrentRPM, vehicleinfo.data);
    engineTorque *= AcceleratorOpening;

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


    //エンジンブレーキの計算
    //吸気抵抗
    float Rintake = 0.0f;
    float K1 = 0.25f;       //吸気抵抗係数
    Rintake = K1 * CurrentRPM;

    //内部摩擦抵抗
    float Rfriction = 0.0f;
    float K2 = 0.15f;       //内部摩擦抵抗係数
    Rfriction = K2 * CurrentRPM;

    //慣性抵抗
    float Rinertia = 0.0f;
    float K3 = 0.25f;       //慣性抵抗係数
    Rinertia = K1 * (ΔRPM / g_gameTime->GetFrameDeltaTime());

    //エンジンブレーキ抵抗
    float Rtotal = 0.0f;
    Rtotal = Rintake + Rfriction + Rinertia;

    //ギア比によって変化
    float FEngineBreake = 0.0f;
    FEngineBreake = (Rtotal * vehicleinfo.GEAR_RATIOS[CurrentGear - 1]) / (vehicleinfo.TireRadius * 100.0f);

    //ブレーキ
    float Fbrake = 0.0f;
    Fbrake = (vehicleinfo.MaximumBrakingForce) * BrakePressure * vehicleinfo.TireRadius;
    
    //変速
    if (Transmission == true) {
        // シフトアップ処理
        if (CurrentRPM >= (vehicleinfo.MaxRPM - vehicleinfo.ShiftUpCorrectionValue) && CurrentGear < vehicleinfo.MaxGear) {
            // シフトアップ
            ShiftChangeFlag = true;
            CurrentGear++;
        }

        // シフトダウン処理
        if (CurrentRPM < (vehicleinfo.ShiftDownTiming[CurrentGear-2]) && CurrentGear > 1) {
            // シフトダウン
            ShiftChangeFlag = true;
            CurrentGear--;
        }
    }
    else {
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
    }

    

    //エンジントルクへの抵抗
    if (AcceleratorOpening != 0) {
        Tload = ((Faero + Frr + Fgrade + Fbrake) / (vehicleinfo.GEAR_RATIOS[CurrentGear - 1])) / vehicleinfo.AccelerationFactor;
    }
    else {
        Tload = ((Faero + Frr + Fgrade + Fbrake + FEngineBreake) * vehicleinfo.GEAR_RATIOS[CurrentGear - 1]) / vehicleinfo.AccelerationFactor;
    }
    
    engineTorque -= Tload;
    engineTorque *= vehicleinfo.GEAR_RATIOS[CurrentGear - 1];
    float OriginEngineTorue = engineTorque;

    //エンジントルクからエンジン回転数の計算
    float NewRPM = 0.0f;
    //シフトチェンジ以外のエンジン回転数の計算
    if (ShiftChangeFlag == false) {
        //エンジンの角速度の計算
        float E_Vel = 0.0f;
        E_Vel = ((2.0f * M_PI) / 60.0f) * CurrentRPM;
        

        E_Vel += (engineTorque / 1.0/*慣性モーメント(エンジンの回りにくさ)今回は1.0に設定・調整*/) * (1.0f / 60.0f);
        NewRPM = E_Vel * 30.0f / M_PI;
    }
    else {
        float N_Tire = 0.0f;
        N_Tire = (VelocityVector * 2.5 / 100.0f) / (2 * M_PI * vehicleinfo.TireRadius) * 60.0f;
        NewRPM = N_Tire * vehicleinfo.GEAR_RATIOS[CurrentGear - 1] * vehicleinfo.FinalGearRatio;
    }
    //アイドリング
    if (NewRPM < vehicleinfo.IdlingRPM && VelocityVector * 3600 / 1000 <= 5.0f) {
        NewRPM = vehicleinfo.IdlingRPM;
    }
    //レブリミット
    if (NewRPM >= vehicleinfo.MaxRPM) {
        NewRPM = vehicleinfo.MaxRPM-vehicleinfo.RevLimitGain;
    }
    if (NewRPM <= 0.0f) {
        NewRPM = 0.0f;
    }
    //エンジン回転数からホイール回転数を計算し速度の算出[cm/s(0.4scale)]
    float NewVelocityVector = 0.0f;
    if (Velocity>=5.0f&&Velocity!=0.0f||Velocity==0.0f&&engineTorque>=0.0f) {
        /*NewVelocityVector = NewRPM / (60.0f * vehicleinfo.GEAR_RATIOS[CurrentGear - 1] * vehicleinfo.FinalGearRatio) * (vehicleinfo.TireRadius * 2.0f * M_PI) * 0.4f * 100.0f;*/
        NewVelocityVector = (NewRPM/60.0f)/*RPMは、一分間に何回回転。秒に変換*/ / vehicleinfo.GEAR_RATIOS[CurrentGear - 1] / vehicleinfo.FinalGearRatio * (vehicleinfo.TireRadius * 2.0f) * M_PI * 100.0f * 0.4f;
        
        
    }
    outputfile << "Gear:" << CurrentGear << "_抵抗:" << Tload << "_時速:"<<NewVelocityVector * 3600.0f * 2.5f / 1000.0f / 100.0f <<"_RPM:"<<NewRPM<<"_ΔRPM"<< fabsf(NewRPM - CurrentRPM)<<"_トルク:"<< OriginEngineTorue << "\n";
    //ステップ2:空気抵抗の計算
    //float Faero = 0.0f;

    //進行方向における自動車の空気に対する相対速度を求める
    float RelativeSpeedBetweenWindDirectionAndVehicleSpeed = 0.0f;       //進行方向における自動車の空気に対する相対速度 [m/s]
    
    
    float φ = 0.0f;
    float Θ = 0.0f;


    //ステップ10:加速度を計算
    float NewAcceleration = 0.0f;


    //ステップ11:速度を計算

    //ステップ12:位置を計算
    Vector3 NewPosition = Vector3::Zero;

    

    //ステップ14:リターンする変数たちをまとめる
    simulationresults.Position = NewPosition;
    simulationresults.VelocityVector = NewVelocityVector;
    simulationresults.PitchAngle = φ;
    simulationresults.RollAngle = Θ;
    simulationresults.CurrentRPM = NewRPM;
    simulationresults.ΔRPM = fabsf(NewRPM - CurrentRPM);
    simulationresults.CurrentGear = CurrentGear;
    simulationresults.Acceleration = NewAcceleration;


    return simulationresults;
}



void CarAFormula::ShiftChange() {

}