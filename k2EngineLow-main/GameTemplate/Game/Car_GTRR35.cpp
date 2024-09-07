#include "stdafx.h"
#include "Car_GTRR35.h"
#include "PageNum.h"


Car_GTRR35::Car_GTRR35() {
    //AE86の初期設定

    // トルク設定
    data = {
    {-3000, 100},
    {-250, 100},
    {0, 120},
    {500, 140},
    {1000, 144},
    {1500, 149},
    {2000, 217},
    {2500, 258},
    {3000, 301},
    {3500, 326},
    {3750, 330},
    {4000, 324},
    {4500, 320},
    {5000, 322},
    {5500, 308},
    {6000, 300},
    {6500, 294},
    {6700, 287},
    {6800, 284},
    {7000, 269},
    {7250, 252},
    {7500, 230},
    {8000, 0}
    };

    //速度伝達比設定
    GEAR_RATIOS = { 4.056, 	2.301, 1.595, 1.248, 1.001, 0.796 };
    ShiftDownTiming = { 4000.0f,4800.0f,5400.0f,5500.0f,5600.0f};

    vehicle_info = {
    1770.0,              //車重[kg]
    2.780,              //ホイールベース[m]
    0.46,               //重心の高さ[m]
    1.590,              //トレッド幅[m]
    1.285,              //重心から後輪までの長さ [m]
    1.285,              //重心から前輪までの長さ [m]
    0.3,              //タイヤの半径 [m]
    GEAR_RATIOS,        //ギア比
    3.700,                //デフ比(ファイナルギア)
    data,               //エンジンのトルク[N・m]
    0.1745,//(約10度に設定してあるが変更可)             //タイヤの最大舵角 [rad]
    6000,               //最大制動力[N]
    1.370,              //全高[m]
    3000,               //フロントバネレート[N/m]
    2328,               //リアバネレート[N/m]
    0.1,                //(仮の値)
    6,                  //最大ギア数
    7150,               //最高回転数
    900,               //アイドリング回転数
    -0.0143f,             //コーナリングパワー
    16.0f,
    ShiftDownTiming,
    50,
    200.0f
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
    m_PlayerCarModel.Init("Assets/modelData/Car/R35/Body.tkm");
    m_CarWindowModel.Init("Assets/modelData/Car/R35/Window.tkm");
    WindowState = true;

    //車両データ設定
    m_NowCar = ORECA07;

    //各タイヤのローカル座標設定
    m_LeftFrontWheelLocalPosition = { -34.5f,15.0f,54.5f };		//左フロント
    m_RightFrontWheelLocalPosition = { 30.0f,15.0f,54.5f };		//右フロント
    m_LeftRearWheelLocalPosition = { -34.5f,15.0f,-54.5f };		//左リア
    m_RightRearWheelLocalPosition = { 30.0f,15.0f,-54.5f };		//右リア

    //視点の設定
    BirdsEyeViewCoordinates = { 0.0f, 95.0f, -175.0f };
    BirdsEyeViewViewpointHeight = 65.0f;
    BonnetViewCoordinates = { 0.0f, 0.0f, 20.0f };
    BonnetViewViewpointHeight = 50.0f;

    BirdsEyeViewTargetPoint = { 0.0f, 0.0f, 0.0f };
    BonnetViewTargetPoint = { 0.0f, 40.0f, 200.0f };

    BirdsEyeViewViewpointDirectionCorrectionByVehicleType = { 50,0,25 };
    BonnetViewViewpointDirectionCorrectionByVehicleType = { 75,0,75 };
}

Car_GTRR35::~Car_GTRR35() {

}