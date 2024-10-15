#include "stdafx.h"
#include "Car_TS050.h"
#include "PageNum.h"


Car_TS050::Car_TS050() {
    //AE86の初期設定

    // トルク設定
    data = {
    {0, 0},
    {1000, 180},
    {1500, 220},
    {2000, 242},
    {2500, 242},
    {3000, 238},
    {3500, 242},
    {4000, 242},
    {4500, 242},
    {5000, 242},
    {5500, 237},
    {6000, 226},
    {6500, 216},
    {7000, 205},
    {7500, 194},
    {8000, 185},
    {8500, 156},
    {8501, 0},
    {8999, 0}
    };



    //速度伝達比設定
    GEAR_RATIOS = { 2.571, 2.062, 1.688, 1.379, 1.194,1.000,0.754 };
    ShiftDownTiming = { 6500.0f,6700.0f,6600.0f,7000.0f,6700.0f,6000.0f };
    TorqueMultiplier = { 2.25,2.25,2.25,2.25,2.25,2.25,2.25 };

    vehicle_info = {
    875.0,              //車重[kg]
    2.425,              //ホイールベース[m]
    0.46,               //重心の高さ[m]
    1.900,              //トレッド幅[m]
    1.285,              //重心から後輪までの長さ [m]
    1.285,              //重心から前輪までの長さ [m]
    0.31,              //タイヤの半径 [m]
    GEAR_RATIOS,        //ギア比
    3.600,                //デフ比(ファイナルギア)
    data,               //エンジンのトルク[N・m]
    0.1745,//(約10度に設定してあるが変更可)             //タイヤの最大舵角 [rad]
    8500,               //最大制動力[N]
    1.050,              //全高[m]
    3000,               //フロントバネレート[N/m]
    2328,               //リアバネレート[N/m]
    0.1,                //(仮の値)
    7,                  //最大ギア数
    8500,               //最高回転数
    500.0,               //アイドリング回転数
    -0.016f,             //コーナリングパワー
    14.0f,
    ShiftDownTiming,
    200,
    100.0f,
    1,
    45.0f,
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
    m_PlayerCarModel.Init("Assets/modelData/Car/TS050/Body.tkm");
    m_CarWindowModel.Init("Assets/modelData/Car/TS050/BodyAlpha.tkm",true,AlphaBlendMode_Trans);
    WindowState = true;

    //車両データ設定
    m_NowCar = ORECA07;

    //各タイヤのローカル座標設定
    m_LeftFrontWheelLocalPosition = { -30.0f,15.0f,58.0f };		//左フロント
    m_RightFrontWheelLocalPosition = { 30.0f,15.0f,58.0f };		//右フロント
    m_LeftRearWheelLocalPosition = { -30.0f,15.0f,-58.0f };		//左リア
    m_RightRearWheelLocalPosition = { 30.0f,15.0f,-58.0f };		//右リア

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

Car_TS050::~Car_TS050() {

}