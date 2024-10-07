#include "stdafx.h"
#include "Car_A90Supra.h"
#include "PageNum.h"


Car_A90Supra::Car_A90Supra() {
    //AE86の初期設定

    // トルク設定
    data = {
    {0, 100},
    {250, 100},
    {500, 119},
    {750, 139},
    {1000, 146},
    {1250, 158},
    {1500, 208},
    {1750, 242},
    {2000, 241},
    {2250, 240},
    {2500, 242},
    {2750, 242},
    {3000, 242},
    {3250, 240},
    {3500, 241},
    {3750, 242},
    {4000, 240},
    {4250, 242},
    {4500, 243},
    {4750, 235},
    {5000, 224},
    {5250, 217},
    {5500, 209.6},
    {5750, 204.6},
    {6000, 195},
    {6250, 188.2},
    {6500, 180},
    {6750, 160},
    {7000, 149},
    {7250, 136},
    {7500, 115}
    };

    //速度伝達比設定
    GEAR_RATIOS = { 5.25, 3.360, 2.172, 1.720, 1.316, 1.000,0.822,0.640 };
    ShiftDownTiming = { 4400.0f,4500.0f,5500.0f,5300.0f,5300.0f,5300.0f,5300.0f };
    TorqueMultiplier = { 1,1,1,1,1,1,1,1 };

    vehicle_info = {
    1630.0,              //車重[kg]
    2.470,              //ホイールベース[m]
    0.46,               //重心の高さ[m]
    1.590,              //トレッド幅[m]
    1.285,              //重心から後輪までの長さ [m]
    1.285,              //重心から前輪までの長さ [m]
    0.3,              //タイヤの半径 [m]
    GEAR_RATIOS,        //ギア比
    3.154,                //デフ比(ファイナルギア)
    data,               //エンジンのトルク[N・m]
    0.1745,//(約10度に設定してあるが変更可)             //タイヤの最大舵角 [rad]
    5500,               //最大制動力[N]
    1.295,              //全高[m]
    3000,               //フロントバネレート[N/m]
    2328,               //リアバネレート[N/m]
    0.1,                //(仮の値)
    8,                  //最大ギア数
    7200,               //最高回転数
    1000,               //アイドリング回転数
    -0.014f,             //コーナリングパワー
    14.5f,
    ShiftDownTiming,
    100,
    200.0f,
    0,
    0,
    TorqueMultiplier
    };



    //最大ギア数設定
    MaxGear = 8;

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
    m_PlayerCarModel.Init("Assets/modelData/Car/A90Supra/Body.tkm");
    WindowState = false;

    //車両データ設定
    m_NowCar = ORECA07;

    //各タイヤのローカル座標設定
    m_LeftFrontWheelLocalPosition = { -30.0f,15.0f,50.0f };		//左フロント
    m_RightFrontWheelLocalPosition = { 30.0f,15.0f,50.0f };		//右フロント
    m_LeftRearWheelLocalPosition = { -31.0f,15.0f,-50.0f };		//左リア
    m_RightRearWheelLocalPosition = { 31.0f,15.0f,-50.0f };		//右リア

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

Car_A90Supra::~Car_A90Supra() {

}