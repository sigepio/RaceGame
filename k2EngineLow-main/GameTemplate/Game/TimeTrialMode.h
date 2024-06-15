#pragma once


class Lighting;
class GameCamera;
class BackGround;
class Car_RB6;
class Car_Oreca07;
class CarAFormula;
class Loading;


class TimeTrialMode:public IGameObject,Noncopyable
{
public:
	TimeTrialMode();
	~TimeTrialMode();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	void SetPosition(Vector3 position) {
		m_NowPPosition = position;
	}

	

private:
	Vector4 m_Pausecolor = { 1.0f,1.0f,1.0f,0.0f };

	Vector3 m_NowPPosition=Vector3::Zero;
	Vector3 m_TimeUIPosition=Vector3::Zero;
	Vector3 m_FastestLapsPosition = Vector3::Zero;
	Vector3 m_Pauseposition = { 0.0f,-50.0f,0.0f };

	Lighting* m_lighting;
	GameCamera* m_gamecamera;
	BackGround* m_background;
	Car_RB6* m_RB6;
	//Car_AE86* m_AE86;
	Car_Oreca07* m_Oreca07;
	SkyCube* m_skyCube = nullptr;
	CarAFormula* m_caraformula;
	Loading* m_Loading;

	ModelRender StartRender;
	SpriteRender TimeUIRender;
	SpriteRender FastestLapsRender;
	SpriteRender PauseSprite;
	SpriteRender ContinueSpriteNonSelect;
	SpriteRender ContinueSpriteSelect;
	SpriteRender ExitSpriteNonSelect;
	SpriteRender ExitSpriteSelect;


	FontRender TimeFont;
	FontRender FTimeFont;


	
	float m_LapTimeminsec;
	float m_timer;
	float m_timersecont;
	
	float FastestLap=10000.0f;

	float FastestLapTimesec = 60.0f;

	std::vector<float> LapTimeList;


	int m_timerminit;
	int m_LapTimemin;
	int FastestLapTimemin = 10000;
	int m_skyCubeType = enSkyCubeType_Day;
	int LapCount = 0;
	int m_FirstFrame = 0;
	int PauseState = 0;
	int PauseCount = 0;
	int PauseWindowState = 0;

	bool GameEnd = false;

};

