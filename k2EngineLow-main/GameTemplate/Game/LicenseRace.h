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
class LicenseRace:public IGameObject
{
public:
	LicenseRace();
	~LicenseRace();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	void B_1();
	void B_2();
	void B_3();
	void B_4();
	void B_5();

	void SetPosition(Vector3 position) {
		m_NowPPosition = position;
	}

	void SetGameMode(int m_GameMode) {
		GameMode = m_GameMode;
	}

	void SetFinishPosition(Vector3 m_FinishPosition) {
		FinishPosition = m_FinishPosition;
	}

	void SetLicenseNum(int m_LicenseNum) {
		LicenseNum = m_LicenseNum;
	}

	void SetCourseNum(int m_CourseNum) {
		CourseNum = m_CourseNum;
	}

	void SetVelocity(float m_Velocity) {
		Velocity = m_Velocity;
	}

	void ResultSelect();


private:
	Vector3 m_NowPPosition = Vector3::Zero;
	Vector3 FinishPosition = Vector3::Zero;				//フィニッシュラインの位置

	Vector3 m_TimeUIPosition = Vector3::Zero;			//タイムのUIの位置
	Vector3 m_Pauseposition = { 0.0f,-50.0f,0.0f };		//ポーズの位置

	//リザルト関連のポジション
	Vector3 ResultScale = { 2.0f,2.0f,1.0f };
	Vector3 ResultSelectSpritePosition = { 0.0f,-100.0f,0.0f };
	Vector3 ResultSelectArrowPosition = { 0.0f,0.0f,0.0f };
	Vector3 ResultTimeFontPosition = { -300.0f,0.0f,0.0f };

	Vector3 ClearTime = Vector3::Zero;		//クリアタイムの設定 x:Gold y:Silver z:Bronze

	Vector4 m_Pausecolor = { 1.0f,1.0f,1.0f,0.0f };		//ポーズ画面のカラー

	//リザルト関連のcolor
	Vector4 ResultBaseColor = { 1.0f,1.0f,1.0f,0.0f };
	Vector4 ResultSpriteColor = { 1.0f,1.0f,1.0f,0.0f };
	Vector4 ResultSelectArrowColor = { 1.0f,1.0f,1.0f,0.0f };
	Vector4 FINISHColor = { 1.0f,1.0f,1.0f,0.0f };
	Vector4 ResultColor = { 1.0f,1.0f,1.0f,0.0f };
	Vector4 ResultTimeColor = { 1.0f,1.0f,1.0f,0.0f };


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

	SpriteRender PassedTimeBaseSprite;		//目標タイムのベース
	SpriteRender PassedTimeSprite;			//目標タイム
	SpriteRender TimeUIRender;				//現在のタイムのUI
	SpriteRender CourseMapUISprite;			//コース図
	SpriteRender PauseSprite;				//ポーズのUI
	SpriteRender ContinueSpriteNonSelect;	//ポーズ時の再開用
	SpriteRender ContinueSpriteSelect;			
	SpriteRender ExitSpriteNonSelect;		//ポーズ時のExit用
	SpriteRender ExitSpriteSelect;
	SpriteRender RetryNonSelect;			//ポーズ時のリトライ用
	SpriteRender RetrySelect;
	SpriteRender Count3Sprite;					//スタートカウント用
	SpriteRender Count2Sprite;
	SpriteRender Count1Sprite;
	SpriteRender STARTSprite;
	SpriteRender ResultSprite;				//リザルト関連のスプライト
	SpriteRender ResultBaseSprite;
	SpriteRender ResultSelectSprite;
	SpriteRender ResultSelectArrowSprite;
	SpriteRender FINISHSprite;

	FontRender TimeFont;
	FontRender ResultTimeFont;
	FontRender LapCountFont;

	ModelRender FinishLine;

	float m_timer;
	float KeepTime = 0.0f;
	float m_timersecont; 
	float BGMVolume = 0.0f;
	float Velocity = 0.0f;

	float ResultTimeScale = 3.0f;//リザルト画面のタイムのスケール

	int GameMode = 0;//0:TimeTrial 1:CircuitExperience
	int CarNum = -1;//0:ORECA07 1:86GT 2:
	int LicenseNum = 0;//1～5:B 6～10:A 11～15:IB 16～20:IA 21～25:S
	int CourseNum = 0;
	int PauseState = 0;	//ゲームの状態
	int PauseCount = 0;	//ポーズのカウント
	int PauseWindowState = 0;//ポーズのウィンドウの状態
	int StartSignalCount = 0;
	int StartSignalSetCount = 0;
	int StartSignal = 0;
	int ResetCount = 0;
	int StartSignalState = 0;
	int StartSignalTime = 0;
	int BGMTrack = 1;
	int m_timerminit;//タイマー
	int m_timerintsecont;
	int m_timermsecont;
	int NowLap = 0;//ラップ数
	int ResultCount = 0;//リザルト用のカウント
	int ResultSetectState = 0;//0:Retry 1:Exit
	int ResultSetectCount = 5;

	int ResultState = 0;

	int AutoDriveCount = 0;

	bool GameEnd = false;
	bool PassedState = false;
	bool ResultTimeState = false;
};

