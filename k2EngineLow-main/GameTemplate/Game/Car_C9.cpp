#include "stdafx.h"
#include "Car_C9.h"


#include "PageNum.h"


Car_C9::Car_C9() {
    //AE86の初期設定

    // トルク設定
    data = {
     {-3000, 100},
     {-250, 100},
     {0, 200},
     {500, 363},
     {1000, 371},
     {1500, 383},
     {2000, 384},
     {2500, 396},
     {3000, 402},
     {3500, 407},
     {4000, 411},
     {4500, 415},
     {5000, 415},
     {5500, 420},
     {6000, 411},
     {6500, 402},
     {7000, 379},
     {7500, 341},
     {8000, 0}
    };




    //速度伝達比設定
    GEAR_RATIOS = { 2.2857, 1.9333, 1.5882, 1.2632, 0.952 };
    ShiftDownTiming = { 5600.0f,5400.0f,5200.0f,5000.0f };
    TorqueMultiplier = { 0.5,0.6,0.7,0.8,1.1 };

    vehicle_info = {
    830.0,              //車重[kg]
    2.660,              //ホイールベース[m]
    0.46,               //重心の高さ[m]
    2.050,              //トレッド幅[m]
    1.285,              //重心から後輪までの長さ [m]
    1.285,              //重心から前輪までの長さ [m]
    0.32,              //タイヤの半径 [m]
    GEAR_RATIOS,        //ギア比
    2.818,                //デフ比(ファイナルギア)
    data,               //エンジンのトルク[N・m]
    0.1745,//(約10度に設定してあるが変更可)             //タイヤの最大舵角 [rad]
    8000,               //最大制動力[N]
    1.320,              //全高[m]
    3000,               //フロントバネレート[N/m]
    2328,               //リアバネレート[N/m]
    0.1,                //(仮の値)
    5,                  //最大ギア数
    7000,               //最高回転数
    1800,               //アイドリング回転数
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
    m_PlayerCarModel.Init("Assets/modelData/Car/C9/Body.tkm");
    m_CarWindowModel.Init("Assets/modelData/Car/C9/BodyAlpha.tkm", true, AlphaBlendMode_Trans);
    WindowState = true;

    //車両データ設定
    m_NowCar = ORECA07;

    //各タイヤのローカル座標設定
    m_LeftFrontWheelLocalPosition = { -31.0f,13.0f,50.0f };		//左フロント
    m_RightFrontWheelLocalPosition = { 31.0f,13.0f,50.0f };		//右フロント
    m_LeftRearWheelLocalPosition = { -30.0f,15.0f,-57.0f };		//左リア
    m_RightRearWheelLocalPosition = { 30.0f,15.0f,-57.0f };		//右リア

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

Car_C9::~Car_C9() {

}