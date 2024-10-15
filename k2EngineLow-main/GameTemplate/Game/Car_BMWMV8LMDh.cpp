#include "stdafx.h"
#include "Car_BMWMV8LMDh.h"

#include "PageNum.h"


Car_BMWMV8LMDh::Car_BMWMV8LMDh() {
    //AE86の初期設定

    // トルク設定
    data = {
     {0, 25},
     {250, 25},
     {500, 28},
     {750, 65},
     {1000, 84},
     {1250, 91},
     {1500, 102},
     {1750, 117},
     {2000, 134},
     {2250, 154},
     {2500, 177},
     {2750, 205},
     {3000, 234},
     {3250, 258},
     {3500, 287},
     {3750, 310},
     {4000, 331},
     {4250, 350},
     {4500, 368},
     {4750, 386},
     {5000, 399},
     {5250, 413},
     {5500, 422},
     {5750, 430},
     {6000, 432},
     {6250, 433},
     {6500, 433},
     {6750, 428},
     {7000, 423},
     {7250, 414},
     {7500, 402},
     {7750, 380},
     {8000, 356},
     {8250, 329.5},
     {8500, 291},
     {8750, 234},
     {9000, 163},
     {9250, 66},
     {9500, 0}
    };





    //速度伝達比設定
    GEAR_RATIOS = { 2.375, 1.875, 1.440, 1.194, 1.000,0.818,0.697 };
    ShiftDownTiming = { 6500.0f,6200.0f,6700.0f,6800.0f,6600.0f,6900.0f };
    TorqueMultiplier = { 1.2,1.2,1.2,1.2,1.2,1.2,1.2 };

    vehicle_info = {
    1037.0,              //車重[kg]
    2.425,              //ホイールベース[m]
    0.46,               //重心の高さ[m]
    1.900,              //トレッド幅[m]
    1.285,              //重心から後輪までの長さ [m]
    1.285,              //重心から前輪までの長さ [m]
    0.340,              //タイヤの半径 [m]
    GEAR_RATIOS,        //ギア比
    4.600,                //デフ比(ファイナルギア)
    data,               //エンジンのトルク[N・m]
    0.1745,//(約10度に設定してあるが変更可)             //タイヤの最大舵角 [rad]
    8300,               //最大制動力[N]
    1.050,              //全高[m]
    3000,               //フロントバネレート[N/m]
    2328,               //リアバネレート[N/m]
    0.1,                //(仮の値)
    7,                  //最大ギア数
    8500,               //最高回転数
    1950.0,               //アイドリング回転数
    -0.01570f,             //コーナリングパワー
    14.0f,
    ShiftDownTiming,
    200,
    100.0f,
    2,
    60.0f,
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
    m_PlayerCarModel.Init("Assets/modelData/Car/BMWMV8LMDh/Body.tkm");
    m_CarWindowModel.Init("Assets/modelData/Car/BMWMV8LMDh/BodyAlpha.tkm", true, AlphaBlendMode_Trans);
    WindowState = true;

    //車両データ設定
    m_NowCar = ORECA07;

    //各タイヤのローカル座標設定
    m_LeftFrontWheelLocalPosition = { -32.0f,15.0f,58.5f };		//左フロント
    m_RightFrontWheelLocalPosition = { 32.0f,15.0f,58.5f };		//右フロント
    m_LeftRearWheelLocalPosition = { -32.0f,15.0f,-65.0f };		//左リア
    m_RightRearWheelLocalPosition = { 32.0f,15.0f,-65.0f };		//右リア

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

Car_BMWMV8LMDh::~Car_BMWMV8LMDh() {

}