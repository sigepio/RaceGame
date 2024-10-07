#include "stdafx.h"
#include "Car_FordGT.h"

#include "PageNum.h"


Car_FordGT::Car_FordGT() {
    //AE86の初期設定

    // トルク設定
    data = {
    {0, 279},
    {500, 279},
    {1000, 308},
    {1500, 442},
    {2000, 500},
    {2500, 564},
    {3000, 587},
    {3500, 650},
    {4000, 750},
    {4500, 760},
    {5000, 780},
    {5500, 800},
    {6000, 770},
    {6400, 714},
    {6500, 690},
    {7000, 583},
    {7500, 550}
    };


    //速度伝達比設定
    GEAR_RATIOS = { 2.611, 1.708, 1.233, 0.940, 0.767, 0.630 };
    ShiftDownTiming = { 4400.0f,4900.0f,5300.0f,5700.0f,5700.0f,5300.0f,5300.0f };
    TorqueMultiplier = { 0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5 };

    vehicle_info = {
    1658.0,              //車重[kg]
    2.470,              //ホイールベース[m]
    0.46,               //重心の高さ[m]
    1.590,              //トレッド幅[m]
    1.285,              //重心から後輪までの長さ [m]
    1.285,              //重心から前輪までの長さ [m]
    0.355,              //タイヤの半径 [m]
    GEAR_RATIOS,        //ギア比
    3.360,                //デフ比(ファイナルギア)
    data,               //エンジンのトルク[N・m]
    0.1745,//(約10度に設定してあるが変更可)             //タイヤの最大舵角 [rad]
    3500,               //最大制動力[N]
    1.295,              //全高[m]
    3000,               //フロントバネレート[N/m]
    2328,               //リアバネレート[N/m]
    0.1,                //(仮の値)
    6,                  //最大ギア数
    7200,               //最高回転数
    1000,               //アイドリング回転数
    -0.0125f,             //コーナリングパワー
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
    m_PlayerCarModel.Init("Assets/modelData/Car/FordGT/Body.tkm");
    m_CarWindowModel.Init("Assets/modelData/Car/FordGT/BodyAlpha.tkm");
    WindowState = true;

    //車両データ設定
    m_NowCar = ORECA07;

    //各タイヤのローカル座標設定
    m_LeftFrontWheelLocalPosition = { -30.0f,15.0f,50.0f };		//左フロント
    m_RightFrontWheelLocalPosition = { 30.0f,15.0f,50.0f };		//右フロント
    m_LeftRearWheelLocalPosition = { -31.0f,17.0f,-57.0f };		//左リア
    m_RightRearWheelLocalPosition = { 31.0f,17.0f,-57.0f };		//右リア

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

Car_FordGT::~Car_FordGT() {

}