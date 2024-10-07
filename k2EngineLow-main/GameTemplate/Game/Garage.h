#pragma once
#include "sound/SoundSource.h"

class GameCamera;
class Loading;
class Player;
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

	bool AlphaState = false;
	bool FadeState = false;
	bool CarChangeState = false;

	std::vector<int> PossessionCar;

	GameCamera* m_GameCamera;
	Loading* m_Loading;
	Player* m_Player;
	Lighting* m_Lighting;
	SoundSource* BGM;
	SoundSource* CursorSE;
	SoundSource* DecisionSE;
	SoundSource* CancelSE;


	ModelRender BaseModel;
	ModelRender NowCarModel;
	ModelRender AlphaModel;

	SpriteRender BaseSprite;
	SpriteRender CarInformationSprite;
	SpriteRender BottomDescriptionSprite;
	SpriteRender FadeSprite;

};

