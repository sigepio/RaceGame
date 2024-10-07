#pragma once
#include "PageNum.h"

class Player:public IGameObject
{
public:
	Player();
	~Player();
	bool Start();
	void Update();

	void Save();

	void SetRideCarNum(int m_RideCarNum) {
		RideCarNum = m_RideCarNum;
	}

	void SetLicenseClearStatus(int m_LicenseClearStatus[5][5]) {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				LicenseClearStatus[i][j] = m_LicenseClearStatus[i][j];
			}
		}
	}

	void SetLicenseClear(int m_LicenseClear,int LicenseType,int LicenseNum){
		LicenseClearStatus[LicenseType][LicenseNum] = m_LicenseClear;
	}

	void SetLicenseAcquisitionStatus(bool m_LicenseAcquisitionStatus[5]) {
		for (int i = 0; i < 5; i++) {
			LicenseAcquisitionStatus[i] = m_LicenseAcquisitionStatus[i];
		}
	}

	void Setm_LicenseAcquisitionStatus(int m_LicenseType, bool m_LicenseAcquisitionStatus) {
		LicenseAcquisitionStatus[m_LicenseType] = m_LicenseAcquisitionStatus;
	}

	void SetViewpointMode(bool m_ViewpointMode) {
		ViewpointMode = m_ViewpointMode;
	}

	void SetTransmission(bool m_Transmission) {
		Transmission = m_Transmission;
	}

	void SetNowCourse(int m_NowCourse) {
		NowCourse = m_NowCourse;
	}

	bool GetLicenseAcquisitionStatus() {
		return LicenseAcquisitionStatus[5];
	}

	bool GetLicenseAcquisitionStatus(int m_LicenseType) {
		return LicenseAcquisitionStatus[m_LicenseType];
	}

	bool GetViewpointMode() {
		return ViewpointMode;
	}

	int GetLicenseClear(int LicenseType, int LicenseNum) {
		return LicenseClearStatus[LicenseType][LicenseNum];
	}

	int GetLicenseClearStatus() {
		return LicenseClearStatus[5][5];
	}

	void AddPossessionCar(int m_CarNum) {
		PossessionCar.push_back(m_CarNum);
	}

	void SetDomesticClassBLicenseStatus(int m_LicenseNum,int m_DomesticClassBLicenseStatus) {
		DomesticClassBLicenseStatus[m_LicenseNum] = m_DomesticClassBLicenseStatus;
	}

	void SetBGMVolume(float m_BGMVolume) {
		BGMVolume = m_BGMVolume;
	}
	void SetSEVolume(float m_SEVolume) {
		SEVolume = m_SEVolume;
	}
	void SetEngineSoundVolume(float m_EngineSoundVolume) {
		EngineSoundVolume = m_EngineSoundVolume;
	}

	void SetRideCarCache(int m_RideCarCache) {
		RideCarCache = m_RideCarCache;
	}

	int GetCarNum() {
		return RideCarNum;
	}

	int GetNowCourse() {
		return NowCourse;
	}

	int GetDomesticClassBLicenseStatus(int m_LisenseNum) {
		return DomesticClassBLicenseStatus[m_LisenseNum];
	}
	

	bool GetTransmission() {
		return Transmission;
	}

	std::vector<int> GetPossessionCar() {
		return PossessionCar;
	}

	float GetBGMVolume() {
		return BGMVolume;
	}
	float GetSEVolume() {
		return SEVolume;
	}
	float GetEngineSoundVolume() {
		return EngineSoundVolume;
	}

	int GetRideCarCache() {
		return RideCarCache;
	}

private:
	int RideCarNum = 0;
	int RideCarCache = 0;

	std::vector<int> PossessionCar = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21};

	float Money=0.0f;

	float BGMVolume = 1.0f;
	float SEVolume = 1.0f;
	float EngineSoundVolume = 0.7f;

	int NowCourse = -1;

	bool Transmission = true;	//true:AT  false:MT

	int LicenseClearStatus[5][5];

	bool ViewpointMode = false;//true:俯瞰(-) false:ボンネット(+)
	int DomesticClassBLicenseStatus[5] = { 0,0,0,0,0 };
	bool LicenseAcquisitionStatus[5] = { false,false,false,false,false };
};

