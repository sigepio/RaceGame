#include "stdafx.h"
#include "Car_787B.h"


#include "PageNum.h"


Car_787B::Car_787B() {
    //AE86の初期設定

    // トルク設定
    data = {
    {0, 90},
    {250, 117},
    {500, 144},
    {750, 162},
    {1000, 198},
    {1250, 234},
    {1500, 270},
    {1750, 297},
    {2000, 315},
    {2250, 328.5},
    {2500, 333},
    {2750, 342},
    {3000, 351},
    {3250, 360},
    {3500, 369},
    {3750, 376.2},
    {4000, 387},
    {4250, 403.2},
    {4500, 421.2},
    {4750, 432},
    {5000, 437.4},
    {5250, 442.8},
    {5500, 454.5},
    {5750, 489.6},
    {6000, 524.7},
    {6250, 543.6},
    {6500, 547.2},
    {6750, 546.3},
    {7000, 544.5},
    {7250, 541.8},
    {7500, 538.2},
    {7750, 533.7},
    {8000, 528.3},
    {8250, 523.8},
    {8500, 515.7},
    {8750, 504},
    {9000, 491.4},
    {9250, 477},
    {9500, 462.6},
    {9750, 447.3},
    {10000, 427.5},
    {10250, 405.9},
    {10500, 378.9}
    };



    //速度伝達比設定
    GEAR_RATIOS = { 1.833, 1.471, 1.160, 1.000, 0.764 };
    ShiftDownTiming = { 6900.0f,6800.0f,7400.0f,6600.0f };
    TorqueMultiplier = { 1.1,1.1,1.1,1.2,1.2 };

    vehicle_info = {
    830.0,              //車重[kg]
    2.660,              //ホイールベース[m]
    0.46,               //重心の高さ[m]
    2.050,              //トレッド幅[m]
    1.285,              //重心から後輪までの長さ [m]
    1.285,              //重心から前輪までの長さ [m]
    0.32,              //タイヤの半径 [m]
    GEAR_RATIOS,        //ギア比
    4.429,                //デフ比(ファイナルギア)
    data,               //エンジンのトルク[N・m]
    0.1745,//(約10度に設定してあるが変更可)             //タイヤの最大舵角 [rad]
    8000,               //最大制動力[N]
    1.320,              //全高[m]
    3000,               //フロントバネレート[N/m]
    2328,               //リアバネレート[N/m]
    0.1,                //(仮の値)
    5,                  //最大ギア数
    9000,               //最高回転数
    800,               //アイドリング回転数
    -0.0145f,             //コーナリングパワー
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
    m_PlayerCarModel.Init("Assets/modelData/Car/787B/Body.tkm");
    m_CarWindowModel.Init("Assets/modelData/Car/787B/BodyAlpha.tkm", true, AlphaBlendMode_Trans);
    WindowState = true;

    //車両データ設定
    m_NowCar = ORECA07;

    //各タイヤのローカル座標設定
    m_LeftFrontWheelLocalPosition = { -0.0f,13.0f,59.5f };		//左フロント
    m_RightFrontWheelLocalPosition = { 31.0f,13.0f,59.5f };		//右フロント
    m_LeftRearWheelLocalPosition = { -0.0f,15.0f,-45.0f };		//左リア
    m_RightRearWheelLocalPosition = { 0.0f,15.0f,-45.0f };		//右リア

    //視点の設定
    BirdsEyeViewCoordinates = { 0.0f, 95.0f, -175.0f };
    BirdsEyeViewViewpointHeight = 65.0f;
    BonnetViewCoordinates = { 0.0f, -10.0f, -20.0f };
    BonnetViewViewpointHeight = 50.0f;

    BirdsEyeViewTargetPoint = { 0.0f, 0.0f, 0.0f };
    BonnetViewTargetPoint = { 0.0f, 40.0f, 200.0f };

    BirdsEyeViewViewpointDirectionCorrectionByVehicleType = { 50,0,25 };
    BonnetViewViewpointDirectionCorrectionByVehicleType = { 75,0,125 };
}

Car_787B::~Car_787B() {

}