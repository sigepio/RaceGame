#include "stdafx.h"
#include "Car_911GT3RSR.h"

#include "PageNum.h"


Car_911GT3RSR::Car_911GT3RSR() {
    //AE86の初期設定

    // トルク設定
    data = {
    {0, 100},
    {500, 200},
    {1000, 206},
    {1500, 239},
    {2000, 274},
    {2500, 285},
    {3000, 284},
    {3500, 287},
    {4000, 294},
    {4500, 328},
    {5000, 368},
    {5500, 390},
    {6000, 402},
    {6250, 413},
    {6500, 412},
    {6750, 418},
    {7000, 412},
    {7500, 404},
    {8000, 403},
    {8250, 397},
    {8500, 377},
    {9000, 352},
    {10000, 0}
    };



    //速度伝達比設定
    GEAR_RATIOS = { 3.1538, 2.294, 1.850, 1.5263, 1.2926 , 1.0967 };
    ShiftDownTiming = { 6300.0f,6900.0f,7200.0f,7200.0f,7200.0f };
    TorqueMultiplier = { 1.0,1.05,1.1,1.15,1.2,1.2 };

    vehicle_info = {
    1350.0,              //車重[kg]
    2.660,              //ホイールベース[m]
    0.46,               //重心の高さ[m]
    2.050,              //トレッド幅[m]
    1.285,              //重心から後輪までの長さ [m]
    1.285,              //重心から前輪までの長さ [m]
    0.361,              //タイヤの半径 [m]
    GEAR_RATIOS,        //ギア比
    3.7857,                //デフ比(ファイナルギア)
    data,               //エンジンのトルク[N・m]
    0.1745,//(約10度に設定してあるが変更可)             //タイヤの最大舵角 [rad]
    2900,               //最大制動力[N]
    1.320,              //全高[m]
    3000,               //フロントバネレート[N/m]
    2328,               //リアバネレート[N/m]
    0.1,                //(仮の値)
    6,                  //最大ギア数
    9000,               //最高回転数
    800,               //アイドリング回転数
    -0.0135f,             //コーナリングパワー
    14.0f,
    ShiftDownTiming,
    200,
    150.0f,
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
    m_PlayerCarModel.Init("Assets/modelData/Car/911GT3RSR/Body.tkm");
    m_CarWindowModel.Init("Assets/modelData/Car/911GT3RSR/BodyAlpha.tkm", true, AlphaBlendMode_Trans);
    WindowState = true;

    //車両データ設定
    m_NowCar = ORECA07;

    //各タイヤのローカル座標設定
    m_LeftFrontWheelLocalPosition = { -32.0f,15.0f,48.0f };		//左フロント
    m_RightFrontWheelLocalPosition = { 32.0f,15.0f,48.0f };		//右フロント
    m_LeftRearWheelLocalPosition = { -33.0f,15.0f,-50.0f };		//左リア
    m_RightRearWheelLocalPosition = { 33.0f,15.0f,-50.0f };		//右リア

    //視点の設定
    BirdsEyeViewCoordinates = { 0.0f, 95.0f, -175.0f };
    BirdsEyeViewViewpointHeight = 65.0f;
    BonnetViewCoordinates = { 0.0f, 0.0f, 10.0f };
    BonnetViewViewpointHeight = 50.0f;

    BirdsEyeViewTargetPoint = { 0.0f, 0.0f, 0.0f };
    BonnetViewTargetPoint = { 0.0f, 40.0f, 200.0f };

    BirdsEyeViewViewpointDirectionCorrectionByVehicleType = { 50,0,25 };
    BonnetViewViewpointDirectionCorrectionByVehicleType = { 75,0,125 };
}

Car_911GT3RSR::~Car_911GT3RSR() {

}