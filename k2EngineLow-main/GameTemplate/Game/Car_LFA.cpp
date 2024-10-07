#include "stdafx.h"
#include "Car_LFA.h"

#include "PageNum.h"


Car_LFA::Car_LFA() {
    //AE86の初期設定

    // トルク設定
    data = {
    {0, 0},
    {500, 69},
    {1000, 171},
    {1500, 268},
    {2000, 311},
    {2500, 352},
    {3000, 383},
    {3500, 400},
    {4000, 403},
    {4500, 414},
    {5000, 415},
    {5500, 417},
    {6000, 420},
    {6500, 420},
    {6800, 423},
    {7000, 421},
    {7500, 420},
    {8000, 415},
    {8500, 400},
    {8700, 393},
    {9000, 378},
    {9500, 346},
    {10000, 100}
    };



    //速度伝達比設定
    GEAR_RATIOS = { 3.231, 	2.188, 1.609, 1.233, 0.970, 0.795};
    ShiftDownTiming = { 6100.0f,6400.0f,6600.0f,7000.0f,7000.0f };
    TorqueMultiplier = { 1.0,1.05,1.1,1.15,1.2,1.2,1.2 };

    vehicle_info = {
    1480.0,              //車重[kg]
    2457.0,              //ホイールベース[m]
    0.46,               //重心の高さ[m]
    1.90,              //トレッド幅[m]
    1.285,              //重心から後輪までの長さ [m]
    1.285,              //重心から前輪までの長さ [m]
    0.34675,              //タイヤの半径 [m]
    GEAR_RATIOS,        //ギア比
    4.217,                //デフ比(ファイナルギア)
    data,               //エンジンのトルク[N・m]
    0.1745,//(約10度に設定してあるが変更可)             //タイヤの最大舵角 [rad]
    6000,               //最大制動力[N]
    1.370,              //全高[m]
    3000,               //フロントバネレート[N/m]
    2328,               //リアバネレート[N/m]
    0.1,                //(仮の値)
    6,                  //最大ギア数
    9500,               //最高回転数
    850,               //アイドリング回転数
    -0.0137f,             //コーナリングパワー
    14.0f,
    ShiftDownTiming,
    300,
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
    m_PlayerCarModel.Init("Assets/modelData/Car/LFA/Body.tkm");
    WindowState = false;

    //車両データ設定
    m_NowCar = ORECA07;

    //各タイヤのローカル座標設定
    m_LeftFrontWheelLocalPosition = { -0.0f,15.0f,63.0f };		//左フロント
    m_RightFrontWheelLocalPosition = { 0.0f,15.0f,63.0f };		//右フロント
    m_LeftRearWheelLocalPosition = { 1.0f,15.0f,-40.0f };		//左リア
    m_RightRearWheelLocalPosition = { -1.0f,15.0f,-40.0f };		//右リア

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

Car_LFA::~Car_LFA() {

}