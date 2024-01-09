#include "stdafx.h"
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <iostream>
#include <vector>


#include "CarBase.h"
#include "GameCamera.h"
#include "LeftFrontWheel.h"
#include "RightFrontWheel.h"
#include "FrontWheelBase.h"
#include "RightRearWheel.h"
#include "LeftRearWheel.h"
#include "TimeTrialMode.h"
#include "CarData.h"


bool CarBase::Start() {


	m_LapState = 0;
	m_gamecamera = FindGO<GameCamera>("gamecamera");
	m_timetrialmode = FindGO<TimeTrialMode>("timetrialmode");
	m_frontwheelbase = NewGO<FrontWheelBase>(1, "frontwheelbase");
	m_rightfrontwheel = NewGO<RightFrontWheel>(2, "rightfrontwheel");
	m_leftfrontwheel = NewGO<LeftFrontWheel>(2, "leftfrontwheel");

	m_rightrearwheel = NewGO< RightRearWheel>(2,"rightrearwheel");
	m_leftrearwheel = NewGO< LeftRearWheel>(2, "leftrearwheel");

	//左フロントタイヤ設定
	m_leftfrontwheel->SetNowCar(m_NowCar);
	m_leftfrontwheel->SetLeftFrontWheelLocalPosition(m_LeftFrontWheelLocalPosition);
	//右フロントタイヤ設定
	m_rightfrontwheel->SetNowCar(m_NowCar);
	m_rightfrontwheel->SetRightFrontWheelLocalPosition(m_RightFrontWheelLocalPosition);
	//左リアタイヤ設定
	m_leftrearwheel->SetNowCar(m_NowCar);
	m_leftrearwheel->SetLeftRearWheelLocalPosition(m_LeftRearWheelLocalPosition);
	//右リアタイヤ設定
	m_rightrearwheel->SetNowCar(m_NowCar);
	m_rightrearwheel->SetRightRearWheelLocalPosition(m_RightRearWheelLocalPosition);

	m_PlayerPosition.y -= 8.0f;
	

	m_frontwheelbase->SetTorqueData(data);

	//シフトアップ時の回転数調整量の設定
	m_frontwheelbase->SetSHIFT_UP_RPM_ADJUST(SHIFT_UP_RPM_ADJUST);

	//シフトダウン時の回転数調整量の設定
	m_frontwheelbase->SetSHIFT_DOWN_RPM_ADJUST(SHIFT_DOWN_RPM_ADJUST);

	//車重の設定
	m_frontwheelbase->SetMass(mass);

	//タイヤの直径の設定
	m_frontwheelbase->SetWheelRadius(wheelRadius);

	//ギア比の設定
	m_frontwheelbase->SetGearRatios(GEAR_RATIOS);

	//最大ギア数の設定
	m_frontwheelbase->SetMaxGear(MaxGear);

	m_frontwheelbase->SetIdolingRPM(IdolingRPM);

	m_frontwheelbase->SetAirPressure(AirPressure);

	m_frontwheelbase->SetFinalGearRatio(FinalGearRatio);

	m_frontwheelbase->SetTransmission_Efficiency(Transmission_Efficiency);

	m_frontwheelbase->Setvehicle_info(vehicle_info);

	return true;
}

CarBase::CarBase() {

}

CarBase::~CarBase() {

}

// Function to read a LUT file and return a map
std::map<int, double> readLUT(std::string filename) {
	std::map<int, double> lut;
	std::ifstream file(filename);
	std::string line;
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		int key;
		double value;
		if (!(iss >> key >> value)) {
			break;
		}
		lut[key] = value;
	}
	return lut;
}

void CarBase::Update() {
	m_Throttle = m_frontwheelbase->Getm_Speed();
	m_PlayerForward = m_frontwheelbase->GetForward();

	if (m_LapState == 0 && m_frontwheelbase->GetPosition().x <= -5800.0f) {
		m_LapState++;
	}

	Move();
	Set();
}

void CarBase::Set() {
	//カメラ
	m_gamecamera->SetTarget(m_frontwheelbase->GetPosition()+ m_PlayerPosition);
	m_timetrialmode->SetPosition(m_frontwheelbase->GetPosition() + m_PlayerPosition);
}

void CarBase::Move() {
	m_PlayerRotation = m_frontwheelbase->GetRotation();
	m_PlayerCarModel.SetRotation(m_frontwheelbase->GetRotation());
	m_PlayerCarModel.SetPosition(m_frontwheelbase->GetPosition()+ m_PlayerPosition);
	m_PlayerCarModel.Update();
}


void CarBase::Render(RenderContext& rc) {
	m_PlayerCarModel.Draw(rc);
}
