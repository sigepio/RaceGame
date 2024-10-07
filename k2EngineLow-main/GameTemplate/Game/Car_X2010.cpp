#include "stdafx.h"
#include "Car_X2010.h"

#include "PageNum.h"


Car_X2010::Car_X2010() {
    //AE86の初期設定

    // トルク設定
    data = {
    {0, 42},
    {250, 42},
    {500, 41},
    {750, 41},
    {1000, 40},
    {1250, 38},
    {1500, 37},
    {1750, 71},
    {2000, 101},
    {2250, 127},
    {2500, 149},
    {2750, 168},
    {3000, 182},
    {3250, 193},
    {3500, 202},
    {3750, 209},
    {4000, 212},
    {4250, 215},
    {4500, 217},
    {4750, 216},
    {5000, 215},
    {5250, 217},
    {5500, 218},
    {5750, 221},
    {6000, 223},
    {6250, 224},
    {6500, 225},
    {6750, 227},
    {7000, 228},
    {7250, 229},
    {7500, 232},
    {7750, 233},
    {8000, 234},
    {8250, 235},
    {8500, 236},
    {8750, 237},
    {9000, 238},
    {9250, 239},
    {9500, 240},
    {9750, 242},
    {10000, 243},
    {10250, 244},
    {10500, 245},
    {10750, 246},
    {11000, 246},
    {11250, 247},
    {11500, 248},
    {11750, 249},
    {12000, 250},
    {12250, 250},
    {12500, 251},
    {12750, 251},
    {13000, 253},
    {13250, 253},
    {13500, 254},
    {13750, 254},
    {14000, 254},
    {14250, 255},
    {14500, 255},
    {14750, 255},
    {15000, 220},
    {15250, 165},
    {15500, 165},
    {15750, 110},
    {16000, 55}
    };





    //速度伝達比設定
    GEAR_RATIOS = { 3.500, 2.857, 2.312, 1.938, 1.688,1.453,1.245 };
    ShiftDownTiming = { 11900.0f,11800.0f,12200.0f,12700.0f,12600.0f,12400.0f };
    TorqueMultiplier = { 3,3,3,3,3,3,2.75 };

    vehicle_info = {
    615.0,              //車重[kg]
    2.9,              //ホイールベース[m]
    0.46,               //重心の高さ[m]
    1.900,              //トレッド幅[m]
    1.285,              //重心から後輪までの長さ [m]
    1.285,              //重心から前輪までの長さ [m]
    0.31,              //タイヤの半径 [m]
    GEAR_RATIOS,        //ギア比
    2.800,                //デフ比(ファイナルギア)
    data,               //エンジンのトルク[N・m]
    0.1745,//(約10度に設定してあるが変更可)             //タイヤの最大舵角 [rad]
    10000,               //最大制動力[N]
    1.050,              //全高[m]
    3000,               //フロントバネレート[N/m]
    2328,               //リアバネレート[N/m]
    0.1,                //(仮の値)
    7,                  //最大ギア数
    15000,               //最高回転数
    500.0,               //アイドリング回転数
    -0.030f,             //コーナリングパワー
    14.0f,
    ShiftDownTiming,
    200,
    100.0f,
    0,
    0.0f,
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
    m_PlayerCarModel.Init("Assets/modelData/Car/X2010/Body.tkm");
    m_CarWindowModel.Init("Assets/modelData/Car/X2010/BodyAlpha.tkm", true, AlphaBlendMode_Trans);
    WindowState = true;

    //車両データ設定
    m_NowCar = ORECA07;

    //各タイヤのローカル座標設定
    m_LeftFrontWheelLocalPosition = { -32.5f,15.0f,57.0f };		//左フロント
    m_RightFrontWheelLocalPosition = { 32.5f,15.0f,57.0f };		//右フロント
    m_LeftRearWheelLocalPosition = { -32.0f,15.0f,-68.0f };		//左リア
    m_RightRearWheelLocalPosition = { 32.0f,15.0f,-68.0f };		//右リア

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

Car_X2010::~Car_X2010() {

}