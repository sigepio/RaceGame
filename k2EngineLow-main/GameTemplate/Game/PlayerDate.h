#pragma once
class PlayerDate:public IGameObject
{
public:
	PlayerDate();
	~PlayerDate();
	bool Start();
	void Update();

	void SetRideCarNum(int m_RideCarNum) {
		RideCarNum = m_RideCarNum;
	}

	void AddPossessionCar(int m_CarNum) {
		PossessionCar.push_back(m_CarNum);
	}

	int GetCarNum() {
		return RideCarNum;
	}

	bool GetTransmission() {
		return Transmission;
	}

	std::vector<int> GetPossessionCar() {
		return PossessionCar;
	}

private:
	int RideCarNum = 0;
	std::vector<int> PossessionCar = { 0 };

	bool Transmission = true;	//true:AT  false:MT
};

