#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "k2EngineLowPreCompile.h"
using namespace nsK2EngineLow;
// K2EngineLowのグローバルアクセスポイント
extern K2EngineLow* g_k2EngineLow;

// データを格納するための構造体
struct Data {
    int x;
    double y;
};

// 車両情報
struct VehicleInfo {
    double mass;							//車重
	float WheelBase;						//ホイールベース [m]
	float CenterOfGravityFromTheGround;		//地面から重心までの高さ [m]
	float TreadWidth;						//トレッド幅 [m]
	float RearWheelFromCenterOfGravity;		//重心から後輪までの長さ [m]
	float FrontWheelFromCenterOfGravity;	//重心から前輪までの長さ [m]
	float TireRadius;						//タイヤの半径 [m]
	std::vector<float> GEAR_RATIOS;			//ギア比
	float FinalGearRatio;					//デフ比(ファイナルギア)
	std::vector<std::vector<float>> data;	//エンジンのトルク[N・m]
	float MaximumSteeringAngleOfTires;		//タイヤの最大舵角 [rad]
	float MaximumBrakingForce;				//最大制動力[N]
	float OverallHeight;					//全高[m]
	float FrontSpringRate;					//フロントバネレート[N/m]
	float RearSpringRate;					//リアバネレート[N/m]
	float AirResistanceCoefficient;			//空気抵抗係数
	float MaxGear;							//最大ギア数
};

//シミュレート結果
struct SimulationResults {
    Vector3 Position;						//位置ベクトル[m]
    float VelocityVector;					//速度ベクトル[m/s]
    float PitchAngle;						//ピッチ角度[rad]
    float RollAngle;						//ロール角度[rad]
    float CurrentRPM;						//エンジンの回転数 [rpm]
	float CurrentGear;						//ギア
	float Acceleration;						//加速度
};

