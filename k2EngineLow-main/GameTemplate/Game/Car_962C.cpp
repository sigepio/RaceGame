#include "stdafx.h"
#include "Car_962C.h"


#include "PageNum.h"


Car_962C::Car_962C() {
    //AE86の初期設定

    // トルク設定
    data = {
    {0, 100},
    {500, 100},
    {1000, 125},
    {1500, 119},
    {2000, 134},
    {2500, 162},
    {3000, 189},
    {3500, 252},
    {4000, 250},
    {4500, 224},
    {5000, 227},
    {5500, 234},
    {6000, 232},
    {6500, 223},
    {7000, 214},
    {7500, 211},
    {8000, 205},
    {8200, 207},
    {8500, 207},
    {9000, 0}
    };






    //速度伝達比設定
    GEAR_RATIOS = { 2.250, 1.444, 1.038, 0.827, 0.709 };
    ShiftDownTiming = { 4900.0f,5500.0f,6100.0f,6500.0f};
    TorqueMultiplier = { 2,2.3,2.6,2.9,3.5 };


    vehicle_info = {
    830.0,              //車重[kg]
    2.660,              //ホイールベース[m]
    0.46,               //重心の高さ[m]
    2.050,              //トレッド幅[m]
    1.285,              //重心から後輪までの長さ [m]
    1.285,              //重心から前輪までの長さ [m]
    0.355,              //タイヤの半径 [m]
    GEAR_RATIOS,        //ギア比
    4.6250,                //デフ比(ファイナルギア)
    data,               //エンジンのトルク[N・m]
    0.1745,//(約10度に設定してあるが変更可)             //タイヤの最大舵角 [rad]
    8000,               //最大制動力[N]
    1.320,              //全高[m]
    3000,               //フロントバネレート[N/m]
    2328,               //リアバネレート[N/m]
    0.1,                //(仮の値)
    5,                  //最大ギア数
    8000,               //最高回転数
    800,               //アイドリング回転数
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
    m_PlayerCarModel.Init("Assets/modelData/Car/962C/Body.tkm");
    m_CarWindowModel.Init("Assets/modelData/Car/962C/BodyAlpha.tkm", true, AlphaBlendMode_Trans);
    WindowState = true;

    //車両データ設定
    m_NowCar = ORECA07;

    //各タイヤのローカル座標設定
    m_LeftFrontWheelLocalPosition = { -31.0f,13.0f,59.5f };		//左フロント
    m_RightFrontWheelLocalPosition = { 31.0f,13.0f,59.5f };		//右フロント
    m_LeftRearWheelLocalPosition = { -31.0f,15.0f,-46.0f };		//左リア
    m_RightRearWheelLocalPosition = { 31.0f,15.0f,-46.0f };		//右リア

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

Car_962C::~Car_962C() {

}