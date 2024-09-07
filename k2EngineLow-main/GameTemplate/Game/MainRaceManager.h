#pragma once
#include "sound/SoundSource.h"

class BackGround;
class Loading;
class GameCamera;
class Lighting;
class Player;
class FadeIn;
class Car_86GT;
class Car_Oreca07;
class Car_RX7FD;
class Car_A90Supra;
class Car_GTRR35;

class MainRaceManager:public IGameObject
{
public:
	MainRaceManager();
	~MainRaceManager();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	void SetCourseNum(int m_Course) {
		CourseInformation = m_Course;
	}

	void SetCarInformation(int m_CarInformation) {
		CarInformation = m_CarInformation;
	}

	void SetLicenseNum(int m_LicenseNum) {
		LicenseNum = m_LicenseNum;
	}

	void SetWhereComePage(int m_WhereComePage) {
		WhereComePage = m_WhereComePage;
	}

private:
	Vector4 BlackOutColor = { 1.0f,1.0f,1.0f,1.0f };
	Vector4 LicenseContentsColor = { 1.0f,1.0f,1.0f,0.0f };

	Vector3 ArrowPosition = { -217.0f,-365.0f,0.0f };
	Vector3 LicenseContentsBasePosition = {6.0f,173.76923076923077f,0.0f};

	BackGround* m_background;
	Loading* m_Loading;
	SoundSource* BGM;
	SoundSource* CursorSE;
	SoundSource* DecisionSE;
	SoundSource* CancelSE;
	GameCamera* m_gamecamera;
	Lighting* m_lighting;
	SkyCube* m_skyCube = nullptr;
	Player* m_player;
	FadeIn* m_FadeIn;
	Car_86GT* m_86GT;
	Car_Oreca07* m_Oreca07;
	Car_RX7FD* m_FD3S;
	Car_A90Supra* m_A90Supra;
	Car_GTRR35* m_GTRR35;

	SpriteRender BaseSprite;
	SpriteRender BackSprite;
	SpriteRender ArrowSprite;
	SpriteRender CourseSprite;
	SpriteRender BlackOutSprite;

	//Licenseóp
	SpriteRender LicenseTagSprite;
	SpriteRender LicenseContentsBase;
	SpriteRender LicenseContents;

	ModelRender LicenseFinish;

	int CourseInformation = 0;
	int CarInformation = 0;

	int FadeCount = 0;
	int MoveCount = 0;
	int m_skyCubeType = enSkyCubeType_Day;
	int FadeState = 0;
	int ArrowMove = 0;

	int LicenseNum = 0;//1Å`5:B 6Å`10:A 11Å`15:IB 16Å`20:IA 21Å`25:S

	int LicenseCount = 0;

	int WhereComePage = 0;
	

	int SelectPoint = 0;//0:ÉXÉ^Å[Ég 1:exit

	float LicenseContentsBaseScale = 0.0f;
	float scaleValues[50] = {
	0.0000, 0.0000, 0.0017, 0.0069, 0.0156, 0.0278, 0.0434, 0.0625, 0.0816, 0.0851,
	0.1111, 0.1406, 0.1597, 0.1736, 0.2101, 0.2344, 0.2500, 0.2934, 0.3056, 0.3403,
	0.3733, 0.3906, 0.4375, 0.4444, 0.4983, 0.5017, 0.5556, 0.5625, 0.6094, 0.6267,
	0.6597, 0.6944, 0.7066, 0.7500, 0.7656, 0.7899, 0.8264, 0.8403, 0.8594, 0.8889,
	0.9149, 0.9184, 0.9375, 0.9566, 0.9722, 0.9844, 0.9931, 0.9983, 1.0000, 1.000
	};


};

