#include "stdafx.h"
#include "Car_86GT.h"
#include "PageNum.h"


Car_86GT::Car_86GT() {
    //AE86の初期設定

    // トルク設定
    data = {
        {0, 5},
        {200, 10.5},
        {400, 22.4},
        {650, 70.6},
        {800, 82},
        {1000, 95.25},
        {1200, 111.6},
        {1400, 130.3},
        {1600, 145.5},
        {1800, 161.1},
        {2000, 169},
        {2200, 173.9},
        {2400, 177.2},
        {2500, 177.9},
        {2600, 178.7},
        {2700, 179.9},
        {3000, 180.2},
        {3100, 179.8},
        {3200, 179.6},
        {3300, 178.8},
        {3400, 177.4},
        {3600, 174.5},
        {3800, 165.1},
        {4000, 163},
        {4100, 166},
        {4200, 168.7},
        {4300, 174.8},
        {4400, 177.8},
        {4500, 181.1},
        {4700, 184.9},
        {4800, 184.5},
        {4900, 182.5},
        {5000, 180.1},
        {5100, 178.4},
        {5200, 178.1},
        {5300, 177.7},
        {5400, 177.6},
        {5600, 177.9},
        {5700, 177.4},
        {6000, 179.2},
        {6200, 182.9},
        {6300, 183.6},
        {6400, 183.1},
        {6600, 179.1},
        {6800, 173.8},
        {7000, 164.4},
        {7200, 153.7},
        {7400, 142.7},
        {7600, 131},
        {7800, 167.1},
        {8000, 158.7},
        {8200, 147},
        {8400, 135.5},
        {8600, 121},
        {8800, 100},
        {9000, 0}
    };
    //速度伝達比設定
    GEAR_RATIOS = { 3.626, 2.188, 1.541, 1.213, 1.000, 0.767 };
    ShiftDownTiming = {4400.0f,5200.0f,5700.0f,6100.0f,5600.0f};
    

    vehicle_info = {
    1470.0,              //車重[kg]
    2.570,              //ホイールベース[m]
    0.46,               //重心の高さ[m]
    1.530,              //トレッド幅[m]
    1.285,              //重心から後輪までの長さ [m]
    1.285,              //重心から前輪までの長さ [m]
    0.3,              //タイヤの半径 [m]
    GEAR_RATIOS,        //ギア比
    4.3,                //デフ比(ファイナルギア)
    data,               //エンジンのトルク[N・m]
    0.1745,//(約10度に設定してあるが変更可)             //タイヤの最大舵角 [rad]
    3500,               //最大制動力[N]
    1.320,              //全高[m]
    3000,               //フロントバネレート[N/m]
    2328,               //リアバネレート[N/m]
    0.1,                //(仮の値)
    6,                  //最大ギア数
    7500,               //最高回転数
    800,               //アイドリング回転数
    -0.014f,             //コーナリングパワー
    14.0f,
    ShiftDownTiming,
    100,
    350.0f
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
    m_PlayerCarModel.Init("Assets/modelData/Car/86GT/Body.tkm");
    m_CarWindowModel.Init("Assets/modelData/Car/86GT/Window.tkm");
    WindowState = true;

    //車両データ設定
    m_NowCar = ORECA07;

    //各タイヤのローカル座標設定
    m_LeftFrontWheelLocalPosition = { -30.0f,15.0f,50.0f };		//左フロント
    m_RightFrontWheelLocalPosition = { 30.0f,15.0f,50.0f };		//右フロント
    m_LeftRearWheelLocalPosition = { -31.0f,15.0f,-50.0f };		//左リア
    m_RightRearWheelLocalPosition = { 31.0f,15.0f,-50.0f };		//右リア

    //視点の設定
    BirdsEyeViewCoordinates = { 0.0f, 95.0f, -175.0f};
    BirdsEyeViewViewpointHeight = 65.0f;
    BonnetViewCoordinates = { 0.0f, 0.0f, 10.0f };
    BonnetViewViewpointHeight = 50.0f;

    BirdsEyeViewTargetPoint = { 0.0f, 0.0f, 0.0f };
    BonnetViewTargetPoint = { 0.0f, 40.0f, 200.0f };

    BirdsEyeViewViewpointDirectionCorrectionByVehicleType = { 50,0,25 };
    BonnetViewViewpointDirectionCorrectionByVehicleType = { 75,0,75 };
}

Car_86GT::~Car_86GT() {

}