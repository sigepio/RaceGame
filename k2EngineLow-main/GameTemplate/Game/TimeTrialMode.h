#pragma once
#include "sound/SoundSource.h"

class Lighting;
class GameCamera;
class BackGround;
class Car_RB6;
class Car_Oreca07;
class CarAFormula;
class Loading;
class Car_86GT;
class Player;
class Car_RX7FD;
class Car_A90Supra;
class Car_GTRR35;



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

	void SetGameMode(int m_GameMode) {
		GameMode = m_GameMode;
	}

	void ResultSelect();

	

private:
	Vector4 m_Pausecolor = { 1.0f,1.0f,1.0f,0.0f };

	
	Vector4 ResultBaseColor = { 1.0f,1.0f,1.0f,0.0f };
	Vector4 ResultSpriteColor = { 1.0f,1.0f,1.0f,0.0f };
	Vector4 ResultSelectArrowColor = { 1.0f,1.0f,1.0f,0.0f };
	Vector4 FINISHColor = { 1.0f,1.0f,1.0f,0.0f };
	Vector4 ResultColor = { 1.0f,1.0f,1.0f,0.0f };
	Vector4 ResultTimeColor = { 1.0f,1.0f,1.0f,0.0f };

	Vector3 m_NowPPosition=Vector3::Zero;
	Vector3 m_TimeUIPosition=Vector3::Zero;
	Vector3 m_FastestLapsPosition = Vector3::Zero;
	Vector3 m_Pauseposition = { 0.0f,-50.0f,0.0f };

	Vector3 ResultScale = { 2.0f,2.0f,1.0f };
	Vector3 ResultSelectSpritePosition = { 0.0f,-100.0f,0.0f };
	Vector3 ResultSelectArrowPosition = { 0.0f,0.0f,0.0f };
	Vector3 ResultTimeFontPosition = { -300.0f,0.0f,0.0f };

	Vector3 ClearTime = Vector3::Zero;		//クリアタイムの設定 x:Gold y:Silver z:Bronze
	Vector3 StartSignalPosition{ 0.0f,200.0f,0.0f };

	Lighting* m_lighting;
	GameCamera* m_gamecamera;
	BackGround* m_background;
	Player* m_player;
	Car_RB6* m_RB6;
	Car_86GT* m_86GT;
	//Car_AE86* m_AE86;
	Car_Oreca07* m_Oreca07;
	Car_RX7FD* m_FD3S;
	Car_A90Supra* m_A90Supra;
	Car_GTRR35* m_GTRR35;
	SkyCube* m_skyCube = nullptr;
	CarAFormula* m_caraformula;
	Loading* m_Loading;

	SoundSource* BGM;
	SoundSource* CountSignalSE;
	SoundSource* StartSignalSE;
	SoundSource* ControlLineSE;

	ModelRender StartRender;
	SpriteRender TimeUIRender;
	SpriteRender FastestLapsRender;
	SpriteRender PauseSprite;
	SpriteRender ContinueSpriteNonSelect;
	SpriteRender ContinueSpriteSelect;
	SpriteRender RetryNonSelect;			//ポーズ時のリトライ用
	SpriteRender RetrySelect;
	SpriteRender ExitSpriteNonSelect;
	SpriteRender ExitSpriteSelect;

	SpriteRender StartSignalBaseRender;
	SpriteRender StartSignalGreenSignalRender;
	SpriteRender StartSignalSignal1Render;
	SpriteRender StartSignalSignal2Render;
	SpriteRender StartSignalSignal3Render;
	SpriteRender StartSignalSignal4Render;
	SpriteRender StartSignalSignal5Render;

	SpriteRender ResultSprite;
	SpriteRender ResultBaseSprite;
	SpriteRender ResultSelectSprite;
	SpriteRender ResultSelectArrowSprite;
	SpriteRender FINISHSprite;
	SpriteRender PassedTimeBaseSprite;
	SpriteRender PassedTimeSprite;
	SpriteRender CourseMapUISprite;

	FontRender ResultTimeFont;
	FontRender TimeFont;
	FontRender FTimeFont;

	FontRender LapCountFont;
	FontRender GAmeModeFont;


	
	float m_LapTimeminsec;
	float m_timer;
	int m_timerintsecont;
	int m_timermsecont;
	float m_timersecont;
	
	float FastestLap=10000.0f;
	float FastestLapKeep = 0.0f;
	int m_Fastesttimerintsecont;
	int m_Fastesttimermsecont;
	float FastestLapTimesec = 60.0f;


	float ResultTimeScale = 3.0f;

	float BGMVolume = 0.0f;

	std::vector<float> LapTimeList;

	CircuitExperienceTime circuit_experience_time;

	int m_timerminit;
	int m_LapTimemin;
	int FastestLapTimemin = 10000;
	int m_skyCubeType = enSkyCubeType_Day;
	int LapCount = 0;
	int m_FirstFrame = 0;
	int PauseState = 0;
	int PauseCount = 0;
	int PauseWindowState = 0;

	int StartSignalCount = 0;
	int StartSignalSetCount = 0;
	int StartSignal = 0;
	int ResetCount = 0;
	int StartSignalState = 0;
	int StartSignalTime = 0;
	int BGMTrack = 1;

	int GameMode = 0;//0:TimeTrial 1:CircuitExperience
	int CarNum = -1;//0:ORECA07 1:86GT 2:

	int NowLap = 0;

	int ResultCount = 0;
	int ResultSetectState = 0;//0:Retry 1:Exit
	int ResultSetectCount = 5;

	bool GameEnd = false;
	bool PassedState = false;
	bool ResultTimeState = false;

};

