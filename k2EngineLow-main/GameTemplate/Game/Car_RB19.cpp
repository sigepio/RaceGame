#include "stdafx.h"
#include "Car_RB19.h"

#include "PageNum.h"


Car_RB19::Car_RB19() {
    //AE86の初期設定

    // トルク設定
    data = {
    {0, 34},
    {1000, 127},
    {2000, 178},
    {3000, 230},
    {4000, 238},
    {5000, 231},
    {6000, 240},
    {7000, 234},
    {8000, 230},
    {9000, 256},
    {10000, 269},
    {10500, 267},
    {11000, 261},
    {11500, 221},
    {12000, 186},
    {12500, 168},
    {13000, 149},
    {13500, 136},
    {14000, 131},
    {14500, 118},
    {15000, 113},
    {15500, 105},
    {16000, 0}
    };








    //速度伝達比設定
    GEAR_RATIOS = { 3.4, 2.4, 2.02, 1.72, 1.44, 1.28, 1.12, 1.0};
    ShiftDownTiming = { 10300.0f,12300.0f,12400.0f,12200.0f,12900.0f,12700.0f };
    TorqueMultiplier = { 2.2,2.2,2.2,2.2,2.5,2.5,2.5,2.5 };

    vehicle_info = {
    798.0,              //車重[kg]
    2.9,              //ホイールベース[m]
    0.46,               //重心の高さ[m]
    1.900,              //トレッド幅[m]
    1.285,              //重心から後輪までの長さ [m]
    1.285,              //重心から前輪までの長さ [m]
    0.31,              //タイヤの半径 [m]
    GEAR_RATIOS,        //ギア比
    4.500,                //デフ比(ファイナルギア)
    data,               //エンジンのトルク[N・m]
    0.1745,//(約10度に設定してあるが変更可)             //タイヤの最大舵角 [rad]
    10000,               //最大制動力[N]
    1.050,              //全高[m]
    3000,               //フロントバネレート[N/m]
    2328,               //リアバネレート[N/m]
    0.1,                //(仮の値)
    8,                  //最大ギア数
    15000,               //最高回転数
    500.0,               //アイドリング回転数
    -0.020f,             //コーナリングパワー
    14.0f,
    ShiftDownTiming,
    200,
    100.0f,
    0,
    0.0f,
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
    m_PlayerCarModel.Init("Assets/modelData/Car/RB19/Body.tkm");
    m_CarWindowModel.Init("Assets/modelData/Car/RB19/BodyAlpha.tkm", true, AlphaBlendMode_Trans);
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

Car_RB19::~Car_RB19() {

}