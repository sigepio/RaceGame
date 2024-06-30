#pragma once
class GameCamera;
class Loading;
class PlayerDate;
class Lighting;

class Garage:public IGameObject
{
public:
	Garage();
	~Garage();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void SetRideCarNum(int m_RideCarNum) {
		RideCarNum = m_RideCarNum;
	}

	void AddPossessionCar(int m_CarNum) {
		PossessionCar.push_back(m_CarNum);
	}

	int GetCarNum() {
		return RideCarNum;
	}

	std::vector<int> GetPossessionCar() {
		return PossessionCar;
	}

private:
	Vector3 BottomDescriptionPosition = { 0.0f,0.0f,0.0f };
	Vector3 CarIcon01Position = { 0.0f,0.0f,0.0f };

	Vector4 BlackOutColor = { 1.0f,1.0f,1.0f,1.0f };

	Quaternion Rotation;

	int FadeCount = 0;
	int RideCarNum = 0;

	float test = 0;

	std::vector<int> PossessionCar;

	GameCamera* m_GameCamera;
	Loading* m_Loading;
	PlayerDate* m_PlayerDate;
	Lighting* m_Lighting;


	ModelRender BaseModel;
	ModelRender NowCarModel;

	SpriteRender BaseSprite;
	SpriteRender CarInformationSprite;
	SpriteRender BottomDescriptionSprite;
	SpriteRender FadeSprite;

};

