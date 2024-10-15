#include "stdafx.h"
#include "Car_911GT3RS.h"

#include "PageNum.h"


Car_911GT3RS::Car_911GT3RS() {
    //AE86の初期設定

    // トルク設定
    data = {
    {0, 100},
    {500, 200},
    {1000, 209},
    {1500, 242},
    {2000, 278},
    {2500, 288},
    {3000, 296},
    {3500, 299},
    {4000, 306},
    {4500, 349},
    {5000, 364},
    {5500, 385},
    {6000, 398},
    {6250, 400},
    {6500, 399},
    {6750, 397},
    {7000, 399},
    {7500, 392},
    {8000, 382},
    {8250, 376},
    {8500, 355},
    {9000, 330},
    {10000, 0}
    };


    //速度伝達比設定
    GEAR_RATIOS = { 3.75, 	2.38, 1.72, 1.34, 1.11, 0.96, 0.84 };
    ShiftDownTiming = { 5400.0f,6200.0f,6700.0f,7100.0f,7500.0f,7500.0f };
    TorqueMultiplier = { 1.0,1.05,1.1,1.15,1.2,1.2,1.2 };

    vehicle_info = {
    1525.0,              //車重[kg]
    2457.0,              //ホイールベース[m]
    0.46,               //重心の高さ[m]
    1.90,              //トレッド幅[m]
    1.285,              //重心から後輪までの長さ [m]
    1.285,              //重心から前輪までの長さ [m]
    0.3,              //タイヤの半径 [m]
    GEAR_RATIOS,        //ギア比
    3.700,                //デフ比(ファイナルギア)
    data,               //エンジンのトルク[N・m]
    0.1745,//(約10度に設定してあるが変更可)             //タイヤの最大舵角 [rad]
    7000,               //最大制動力[N]
    1.370,              //全高[m]
    3000,               //フロントバネレート[N/m]
    2328,               //リアバネレート[N/m]
    0.1,                //(仮の値)
    7,                  //最大ギア数
    9000,               //最高回転数
    900,               //アイドリング回転数
    -0.0147f,             //コーナリングパワー
    14.0f,
    ShiftDownTiming,
    100,
    350.0f,
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
    m_PlayerCarModel.Init("Assets/modelData/Car/911GT3RS/Body.tkm");
    WindowState = false;

    //車両データ設定
    m_NowCar = ORECA07;

    //各タイヤのローカル座標設定
    m_LeftFrontWheelLocalPosition = { -30.0f,15.0f,49.0f };		//左フロント
    m_RightFrontWheelLocalPosition = { 30.0f,15.0f,49.0f };		//右フロント
    m_LeftRearWheelLocalPosition = { -30.0f,15.0f,-49.0f };		//左リア
    m_RightRearWheelLocalPosition = { 30.0f,15.0f,-49.0f };		//右リア

    //視点の設定
    BirdsEyeViewCoordinates = { 0.0f, 95.0f, -175.0f };
    BirdsEyeViewViewpointHeight = 65.0f;
    BonnetViewCoordinates = { 0.0f, 0.0f, 20.0f };
    BonnetViewViewpointHeight = 50.0f;

    BirdsEyeViewTargetPoint = { 0.0f, 0.0f, 0.0f };
    BonnetViewTargetPoint = { 0.0f, 40.0f, 200.0f };

    BirdsEyeViewViewpointDirectionCorrectionByVehicleType = { 50,0,25 };
    BonnetViewViewpointDirectionCorrectionByVehicleType = { 75,0,125 };
}

Car_911GT3RS::~Car_911GT3RS() {

}