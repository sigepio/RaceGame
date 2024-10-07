#include "stdafx.h"
#include "Car_Oreca07.h" 
#include "PageNum.h"


Car_Oreca07::Car_Oreca07() {
	//AE86の初期設定

	//トルク設定
    data = {
     {0, 23.8},
     {250, 49.3},
     {500, 79.9},
     {750, 108.8},
     {1000, 136.0},
     {1250, 149.6},
     {1500, 171.7},
     {1750, 193.8},
     {2000, 214.2},
     {2250, 241.4},
     {2500, 265.2},
     {2750, 289.0},
     {3000, 308.4},
     {3250, 328.1},
     {3500, 340.0},
     {3750, 349.6},
     {4000, 353.6},
     {4250, 351.9},
     {4500, 346.8},
     {4750, 340.0},
     {5000, 333.2},
     {5250, 328.1},
     {5500, 324.7},
     {5750, 319.6},
     {6000, 310.1},
     {6250, 307.7},
     {6500, 304.3},
     {6750, 299.2},
     {7000, 292.4},
     {7250, 289.0},
     {7500, 286.3},
     {7800, 280.5},
     {8050, 267.1},
     {8300, 249.9},
     {8550, 215.9},
     {8800, 184.3},
     {9050, 154.7},
     {9300, 119.0},
     {9550, 83.3},
     {9800, 49.3},
     {10050, 13.6},
     {10250, 0}
    };

    //速度伝達比設定
    GEAR_RATIOS = { 1.593, 1.231, 0.989, 0.831, 0.704, 0.606 };
    ShiftDownTiming = { 6200.0f,6500.0f,6800.0f,6850.0f,6850.0f };
    TorqueMultiplier = { 1,1,1,1,1,1 };

    vehicle_info = {
    930.0,              //車重[kg]
    2.766,              //ホイールベース[m]
    0.331,              //重心の高さ[m]
    1.424,              //トレッド幅[m]
    0.080,              //重心から後輪までの長さ [m]
    0.085,              //重心から前輪までの長さ [m]
    0.331,              //タイヤの半径 [m]
    GEAR_RATIOS,        //ギア比
    5.1,                //デフ比(ファイナルギア)
    data,               //エンジンのトルク[N・m]
    0.1745,//(約10度に設定してあるが変更可)             //タイヤの最大舵角 [rad]
    27000,               //最大制動力[N]
    1.045,              //全高[m]
    1588,               //フロントバネレート[N/m]
    1456,               //リアバネレート[N/m]
    0.1,                //(仮の値)
    6,
    8200,
    1500,
    -0.016f,
    18.0f,
    ShiftDownTiming,
    100,
    200.0f,
    0,
    0,
    TorqueMultiplier
    };

	

	//最大ギア数設定
	MaxGear = 6;

	//シフトアップ時の回転数調整量設定
	SHIFT_UP_RPM_ADJUST = 2000.0f;

	//シフトダウン時の回転調整量設定
	SHIFT_DOWN_RPM_ADJUST = 2000.0f;

	//伝達効率の設定
    Transmission_Efficiency = 0.95f;

    //タイヤ空気圧
    AirPressure = 1.5f;

    //ファイナルギアの設定
    FinalGearRatio = 5.1f;

	//車重の設定
	mass = 735.0f;

	//タイヤの直径設定
	wheelRadius = 0.331f;

	IdolingRPM = 1500.0f;

	//車両モデル設定
	m_PlayerCarModel.Init("Assets/modelData/Car/LMP2.tkm");

	//車両データ設定
	m_NowCar = ORECA07;

	//各タイヤのローカル座標設定
	m_LeftFrontWheelLocalPosition = { -30.0f,11.0f,51.0f };		//左フロント
	m_RightFrontWheelLocalPosition = { 30.0f,11.0f,51.0f };		//右フロント
	m_LeftRearWheelLocalPosition = { -30.0f,11.0f,-58.5f };		//左リア
	m_RightRearWheelLocalPosition = { 30.0f,11.0f,-58.5f };		//右リア

    //視点の設定
    BirdsEyeViewCoordinates = { 0.0f, 95.0f, -175.0f };
    BirdsEyeViewViewpointHeight = 65.0f;
    BonnetViewCoordinates = { 0.0f, 0.0f, 0.0f };
    BonnetViewViewpointHeight = 50.0f;

    BirdsEyeViewTargetPoint = { 0.0f, 0.0f, 0.0f };
    BonnetViewTargetPoint = { 0.0f, 40.0f, 200.0f };

    BirdsEyeViewViewpointDirectionCorrectionByVehicleType = { 50,0,25 };
    BonnetViewViewpointDirectionCorrectionByVehicleType = { 75,0,75 };
}

Car_Oreca07::~Car_Oreca07() {

}