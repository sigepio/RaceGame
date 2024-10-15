#include "stdafx.h"
#include "Car_GR010.h"
#include "PageNum.h"


Car_GR010::Car_GR010() {
    //AE86の初期設定

    // トルク設定
    data = {
    {0, 40},
    {250, 40},
    {500, 52},
    {750, 63},
    {1000, 70},
    {1250, 80},
    {1500, 92},
    {1750, 106},
    {2000, 121},
    {2250, 131},
    {2500, 144},
    {2750, 156},
    {3000, 166},
    {3250, 178},
    {3500, 184},
    {3750, 192},
    {4000, 197},
    {4250, 203},
    {4500, 208},
    {4750, 211},
    {5000, 214},
    {5250, 216},
    {5500, 217},
    {5750, 222},
    {6000, 220},
    {6250, 216},
    {6500, 209},
    {6750, 200},
    {7000, 186},
    {7250, 166},
    {7500, 153},
    {7750, 144},
    {8000, 136},
    {8250, 109},
    {8500, 106},
    {8750, 62},
    {9000, 0}
    };




    //速度伝達比設定
    GEAR_RATIOS = { 2.312, 1.812, 1.500, 1.194, 1.000,0.929,0.824 };
    ShiftDownTiming = { 5700.0f,6100.0f,5800.0f,6100.0f,6800.0f,6500.0f };
    TorqueMultiplier = { 1.7,1.75,1.8,1.85,1.9,1.95,2.0 };

    vehicle_info = {
    1040.0,              //車重[kg]
    2.425,              //ホイールベース[m]
    0.46,               //重心の高さ[m]
    1.900,              //トレッド幅[m]
    1.285,              //重心から後輪までの長さ [m]
    1.285,              //重心から前輪までの長さ [m]
    0.31,              //タイヤの半径 [m]
    GEAR_RATIOS,        //ギア比
    3.400,                //デフ比(ファイナルギア)
    data,               //エンジンのトルク[N・m]
    0.1745,//(約10度に設定してあるが変更可)             //タイヤの最大舵角 [rad]
    8300,               //最大制動力[N]
    1.050,              //全高[m]
    3000,               //フロントバネレート[N/m]
    2328,               //リアバネレート[N/m]
    0.1,                //(仮の値)
    7,                  //最大ギア数
    7800,               //最高回転数
    500.0,               //アイドリング回転数
    -0.01570f,             //コーナリングパワー
    14.0f,
    ShiftDownTiming,
    200,
    100.0f,
    2,
    35.0f,
    TorqueMultiplier
    };



    //最大ギア数設定
    MaxGear = 5;

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

    IdolingRPM = 500.0f;

    //車両モデル設定
    m_PlayerCarModel.Init("Assets/modelData/Car/GR010/Body.tkm");
    m_CarWindowModel.Init("Assets/modelData/Car/GR010/BodyAlpha.tkm", true, AlphaBlendMode_Trans);
    WindowState = true;

    //車両データ設定
    m_NowCar = ORECA07;

    //各タイヤのローカル座標設定
    m_LeftFrontWheelLocalPosition = { -32.5f,15.0f,57.0f };		//左フロント
    m_RightFrontWheelLocalPosition = { 32.5f,15.0f,57.0f };		//右フロント
    m_LeftRearWheelLocalPosition = { -32.0f,15.0f,-68.0f };		//左リア
    m_RightRearWheelLocalPosition = { 32.0f,15.0f,-68.0f };		//右リア

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

Car_GR010::~Car_GR010() {

}