#include "stdafx.h"
#include "Car_499P.h"

#include "PageNum.h"


Car_499P::Car_499P() {
    //AE86の初期設定

    // トルク設定
    data = {
    {0, 0},
    {500, 60},
    {1000, 60},
    {1500, 60},
    {2000, 60},
    {2500, 60},
    {3000, 60},
    {3500, 70},
    {4000, 85},
    {4500, 102},
    {5000, 120},
    {5300, 131},
    {5775, 153},
    {6000, 174.1},
    {6300, 192.55},
    {6562, 209.2},
    {7000, 215.82},
    {7500, 237.655},
    {8000, 246.03},
    {8500, 257.1},
    {9000, 261.97},
    {9500, 261.14},
    {10000, 200.57},
    {10500, 143.6},
    {10762, 228.05},
    {11000, 0}
    };









    //速度伝達比設定
    GEAR_RATIOS = { 2.500, 2.000, 1.625, 1.318, 1.133, 1.000, 0.732};
    ShiftDownTiming = { 8000.0f,8000.0f,8100.0f,8500.0f,8700.0f,7100.0f };
    TorqueMultiplier = { 2,2,2,2,2,2,2 };

    vehicle_info = {
    1040.0,              //車重[kg]
    2.9,              //ホイールベース[m]
    0.46,               //重心の高さ[m]
    1.900,              //トレッド幅[m]
    1.285,              //重心から後輪までの長さ [m]
    1.285,              //重心から前輪までの長さ [m]
    0.31,              //タイヤの半径 [m]
    GEAR_RATIOS,        //ギア比
    5.400,                //デフ比(ファイナルギア)
    data,               //エンジンのトルク[N・m]
    0.1745,//(約10度に設定してあるが変更可)             //タイヤの最大舵角 [rad]
    9000,               //最大制動力[N]
    1.050,              //全高[m]
    3000,               //フロントバネレート[N/m]
    2328,               //リアバネレート[N/m]
    0.1,                //(仮の値)
    7,                  //最大ギア数
    10500,               //最高回転数
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
    m_PlayerCarModel.Init("Assets/modelData/Car/499P/Body.tkm");
    WindowState = false;

    //車両データ設定
    m_NowCar = ORECA07;

    //各タイヤのローカル座標設定
    m_LeftFrontWheelLocalPosition = { -32.25f,15.0f,58.5f };		//左フロント
    m_RightFrontWheelLocalPosition = { 31.25f,15.0f,58.5f };		//右フロント
    m_LeftRearWheelLocalPosition = { -31.5f,15.0f,-64.0f };		//左リア
    m_RightRearWheelLocalPosition = { 31.5f,15.0f,-64.0f };		//右リア

    //視点の設定
    BirdsEyeViewCoordinates = { 0.0f, 95.0f, -175.0f };
    BirdsEyeViewViewpointHeight = 65.0f;
    BonnetViewCoordinates = { 0.0f, 0.0f, 10.0f };
    BonnetViewViewpointHeight = 50.0f;

    BirdsEyeViewTargetPoint = { 0.0f, 0.0f, 0.0f };
    BonnetViewTargetPoint = { 0.0f, 40.0f, 200.0f };

    BirdsEyeViewViewpointDirectionCorrectionByVehicleType = { 50,0,25 };
    BonnetViewViewpointDirectionCorrectionByVehicleType = { 75,0,75 };
}

Car_499P::~Car_499P() {

}