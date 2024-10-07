#include "stdafx.h"
#include "Car_FordGTLM.h"


#include "PageNum.h"


Car_FordGTLM::Car_FordGTLM() {
    //AE86の初期設定

    // トルク設定
    data = {
    {0, 265},
    {500, 270},
    {1000, 275},
    {1500, 280},
    {2000, 285},
    {2500, 290},
    {3000, 295},
    {3500, 300},
    {3750, 305},
    {4000, 315},
    {4500, 325},
    {5000, 335},
    {5500, 340},
    {6000, 335},
    {6500, 325},
    {7000, 315}
    };



    //速度伝達比設定
    GEAR_RATIOS = { 2.611, 1.708, 1.233, 0.940, 0.767, 0.630 };
    ShiftDownTiming = { 4200.0f,4700.0f,5000.0f,5400.0f,5500.0f};
    TorqueMultiplier = { 0.8,0.9,1.0,1.1,1.2,1.5,1.2,1.5 };

    vehicle_info = {
    1558.0,              //車重[kg]
    2.470,              //ホイールベース[m]
    0.46,               //重心の高さ[m]
    1.590,              //トレッド幅[m]
    1.285,              //重心から後輪までの長さ [m]
    1.285,              //重心から前輪までの長さ [m]
    0.34,              //タイヤの半径 [m]
    GEAR_RATIOS,        //ギア比
    4.5,                //デフ比(ファイナルギア)
    data,               //エンジンのトルク[N・m]
    0.1745,//(約10度に設定してあるが変更可)             //タイヤの最大舵角 [rad]
    7500,               //最大制動力[N]
    1.295,              //全高[m]
    3000,               //フロントバネレート[N/m]
    2328,               //リアバネレート[N/m]
    0.1,                //(仮の値)
    6,                  //最大ギア数
    7000,               //最高回転数
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
    m_PlayerCarModel.Init("Assets/modelData/Car/FordGTLM/Body.tkm");

    //車両データ設定
    m_NowCar = ORECA07;

    //各タイヤのローカル座標設定
    m_LeftFrontWheelLocalPosition = { -30.0f,15.0f,50.0f };		//左フロント
    m_RightFrontWheelLocalPosition = { 30.0f,15.0f,50.0f };		//右フロント
    m_LeftRearWheelLocalPosition = { -31.0f,17.0f,-61.0f };		//左リア
    m_RightRearWheelLocalPosition = { 31.0f,17.0f,-61.0f };		//右リア

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

Car_FordGTLM::~Car_FordGTLM() {

}