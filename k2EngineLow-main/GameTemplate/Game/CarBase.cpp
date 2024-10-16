#include "stdafx.h"
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <iostream>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Player.h"


#include "CarBase.h"
#include "GameCamera.h"
#include "LeftFrontWheel.h"
#include "RightFrontWheel.h"
#include "FrontWheelBase.h"
#include "RightRearWheel.h"
#include "LeftRearWheel.h"
#include "TimeTrialMode.h"
#include "LicenseRace.h"



bool CarBase::Start() {


	m_LapState = 0;
	m_gamecamera = FindGO<GameCamera>("gamecamera");
	if (LicenseNum == 0) {
		m_timetrialmode = FindGO<TimeTrialMode>("timetrialmode");
	}
	else {
		m_LicenseRace = FindGO<LicenseRace>("licenserace");
	}
	

	m_player = FindGO<Player>("player");
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

	Set();
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
	//ゲーム終了
	if (GameEnd == true) {
		m_frontwheelbase->SetGameEnd(GameEnd);
		m_rightfrontwheel->SetGameEnd(GameEnd);
		m_leftfrontwheel->SetGameEnd(GameEnd);

		m_rightrearwheel->SetGameEnd(GameEnd);
		m_leftrearwheel->SetGameEnd(GameEnd);
		DeleteGO(this);
	}
	m_Throttle = m_frontwheelbase->Getm_Speed();
	m_PlayerForward = m_frontwheelbase->GetForward();

	if (m_LapState == 0 && m_frontwheelbase->GetPosition().x >= -10700.0f&& m_frontwheelbase->GetPosition().z <= -4500.0f) {
		m_LapState++;
	}
	if (m_LapState == 1 && m_frontwheelbase->GetPosition().x >= 5300.0f && m_frontwheelbase->GetPosition().z >= 30000.0f) {
		m_LapState++;
	}

	Move();
	Set();
	
	m_frontwheelbase->SetPauseState(m_PauseState);
	m_frontwheelbase->SetAutoDrive(AutoDriveState);
	m_leftfrontwheel->SetPauseState(m_PauseState);
	m_rightrearwheel->SetPauseState(m_PauseState);
	m_leftrearwheel->SetPauseState(m_PauseState);
	m_rightfrontwheel->SetPauseState(m_PauseState);
}

void CarBase::Set() {
	//カメラ
	/*CameraRAngle = m_frontwheelbase->Get_DVector().Dot(ResetVector) / (m_frontwheelbase->Get_DVector().Length() * ResetVector.Length());
	CameraRAngle = acos(CameraRAngle);
	CameraRAngle *= -1.0f;*/
	Vector3 test = Calc(m_frontwheelbase->GetRotation());
	float ANGLE = test.y * -1.0f * M_PI / 180.0f;
	m_gamecamera->SetRAngle(ANGLE);
	
	CameraVector = m_frontwheelbase->Get_DVector();
	CameraVector.y /= 4.0f;
	m_gamecamera->SetDi(CameraVector);
	m_gamecamera->SetCarRotation(m_frontwheelbase->GetRotation());
	m_gamecamera->SetFrontWheelForwardCatch(m_frontwheelbase->GetForward());
	m_gamecamera->SetTarget(m_frontwheelbase->GetPosition());

	if (LicenseNum == 0) {
		m_timetrialmode->SetPosition(m_frontwheelbase->GetPosition());
	}
	else {
		m_LicenseRace->SetPosition(m_frontwheelbase->GetPosition());
		m_LicenseRace->SetVelocity(m_frontwheelbase->GetTireRotation());
	}

	if (m_player->GetViewpointMode() == true) {
		m_gamecamera->SetViewpointMode(m_player->GetViewpointMode());
		m_gamecamera->SetMAIN_TO_CAMERA_POS(BirdsEyeViewCoordinates);
		m_gamecamera->SetViewpointHeight(BirdsEyeViewViewpointHeight);
		m_gamecamera->SetTargetPoint(BirdsEyeViewTargetPoint);
		m_gamecamera->SetViewpointDirectionCorrectionByVehicleType(BirdsEyeViewViewpointDirectionCorrectionByVehicleType);
		if (g_pad[0]->IsTrigger(enButtonRB1) && (m_PauseState == 0 || m_PauseState == -1)) {
			m_player->SetViewpointMode(false);
		}
	}
	else {
		m_gamecamera->SetViewpointMode(m_player->GetViewpointMode());
		m_gamecamera->SetMAIN_TO_CAMERA_POS(BonnetViewCoordinates);
		m_gamecamera->SetViewpointHeight(BonnetViewViewpointHeight);
		m_gamecamera->SetTargetPoint(BonnetViewTargetPoint);
		m_gamecamera->SetViewpointDirectionCorrectionByVehicleType(BonnetViewViewpointDirectionCorrectionByVehicleType);
		if (g_pad[0]->IsTrigger(enButtonRB1) && (m_PauseState == 0 || m_PauseState == -1)) {
			m_player->SetViewpointMode(true);
		}
	}
	

}

void CarBase::Move() {
	m_PlayerRotation = m_frontwheelbase->GetRotation();
	m_PlayerCarModel.SetRotation(m_frontwheelbase->GetRotation());
	m_PlayerPosition = m_frontwheelbase->GetPosition();
	m_PlayerCarModel.SetPosition(m_PlayerPosition);

	m_PlayerCarModel.Update();

	if (WindowState == true) {
		m_CarWindowModel.SetRotation(m_frontwheelbase->GetRotation());
		m_CarWindowModel.SetPosition(m_PlayerPosition);
		m_CarWindowModel.Update();
	}

}


void CarBase::Render(RenderContext& rc) {
	m_PlayerCarModel.SetAlwaysOnDisplay(true);
	m_PlayerCarModel.Draw(rc);
	if (WindowState == true) {
		m_CarWindowModel.SetAlwaysOnDisplay(true);
		m_CarWindowModel.Draw(rc);
	}
}
