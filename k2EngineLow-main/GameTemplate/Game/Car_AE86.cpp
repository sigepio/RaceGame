#include "stdafx.h"
#include "Car_AE86.h"
#include "CarData.h"

Car_AE86::Car_AE86() {
	//AE86の初期設定

	////トルク設定
	//Ti = 260.0f;

	////速度伝達比設定
	//G[1] = 3.587f;			//1速
	//G[2] = 2.022f;			//2速
	//G[3] = 1.384f;			//3速
	//G[4] = 1.000f;			//4速
	//G[5] = 0.878f;			//5速

	////伝達効率の設定
	//η = 0.9f;

	////車重の設定

	////車両モデル設定
	//m_PlayerCarModel.Init("Assets/modelData/Car/AE86.tkm");

	////車両データ設定
	//m_NowCar = AE86;

	////各タイヤのローカル座標設定
	//m_LeftFrontWheelLocalPosition = { -23.0f,5.0f,55.0f };		//左フロント
	//m_RightFrontWheelLocalPosition = { 23.0f,5.0f,55.0f };		//右フロント
	//m_LeftRearWheelLocalPosition = { -23.0f,5.0f,-73.0f };		//左リア
	//m_RightRearWheelLocalPosition = { 23.0f,5.0f,-73.0f };		//右リア
}

Car_AE86::~Car_AE86() {

}
