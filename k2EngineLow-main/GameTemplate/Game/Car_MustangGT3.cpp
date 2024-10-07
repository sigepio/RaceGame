#include "stdafx.h"
#include "Car_MustangGT3.h"


#include "PageNum.h"


Car_MustangGT3::Car_MustangGT3() {
    //AE86の初期設定

    // トルク設定
    data = {
    {0, 348},
    {273, 358},
    {547, 368},
    {820, 393},
    {1094, 418},
    {1368, 458},
    {1642, 498},
    {1862, 521},
    {2082, 533},
    {4051, 536},
    {5035, 537.5},
    {6019, 539},
    {6296, 530},
    {6573, 521},
    {6706, 515},
    {6839, 509},
    {6972, 503},
    {7105, 497},
    {7386, 485},
    {7667, 473},
    {7948, 460.5},
    {8000, 458},
    {8100, 200},
    {8350, 100},
    {8500, 0}
    };




    //速度伝達比設定
    GEAR_RATIOS = { 2.500, 1.875, 1.500, 1.258, 1.098, 0.904};
    ShiftDownTiming = { 5800.0f,6100.0f,6300.0f,6700.0f,6000.0f };
    TorqueMultiplier = { 0.5,0.5,0.55,0.6,0.7,0.85,1.2 };

    vehicle_info = {
    1300.0,              //車重[kg]
    2457.0,              //ホイールベース[m]
    0.46,               //重心の高さ[m]
    1.90,              //トレッド幅[m]
    1.285,              //重心から後輪までの長さ [m]
    1.285,              //重心から前輪までの長さ [m]
    0.3,              //タイヤの半径 [m]
    GEAR_RATIOS,        //ギア比
    3.4285,                //デフ比(ファイナルギア)
    data,               //エンジンのトルク[N・m]
    0.1745,//(約10度に設定してあるが変更可)             //タイヤの最大舵角 [rad]
    8000,               //最大制動力[N]
    1.370,              //全高[m]
    3000,               //フロントバネレート[N/m]
    2328,               //リアバネレート[N/m]
    0.1,                //(仮の値)
    6,                  //最大ギア数
    8000,               //最高回転数
    1885,               //アイドリング回転数
    -0.0147f,             //コーナリングパワー
    14.0f,
    ShiftDownTiming,
    200,
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
    m_PlayerCarModel.Init("Assets/modelData/Car/MustangGT3/Body.tkm");
    m_CarWindowModel.Init("Assets/modelData/Car/MustangGT3/BodyAlpha.tkm", true, AlphaBlendMode_Trans);
    WindowState = true;

    //車両データ設定
    m_NowCar = ORECA07;

    //各タイヤのローカル座標設定
    m_LeftFrontWheelLocalPosition = { -0.0f,15.0f,57.0f };		//左フロント
    m_RightFrontWheelLocalPosition = { 0.0f,15.0f,57.0f };		//右フロント
    m_LeftRearWheelLocalPosition = { -0.0f,15.0f,-54.0f };		//左リア
    m_RightRearWheelLocalPosition = { 0.0f,15.0f,-54.0f };		//右リア

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

Car_MustangGT3::~Car_MustangGT3() {

}