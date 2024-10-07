#pragma once
class Menu;
class RaceMenu;
class MainRaceManager;
class TimeTrialMode;
class GameCamera;
class Garage;
class LicenseMode;
class LicenseRace;
class OptionMenu;
class BackGround;
class CarChange;
class ModeSelect;

class Loading:public IGameObject
{
public:
	Loading();
	~Loading();
	bool Start();
	void SetTips(int CarState, int CourseState);
	void Update();
	void Render(RenderContext& rc);

	void HandleSceneTransition();
	void HandleTitlePageTransition();
	void HandleWorldMenuPageTransition();
	void HandleRaceMenuPageTransition();
	void HandleLicenseModeTransition();
	void HandleRaceLobbyPageTransition();
	void HandleFadeOutTransition();
	void HandlePlayPageTransition();
	void HandleGaragePageTransition();
	void HandleOptionPageTransition();
	void HandleCarChangePageTransition();
	void HandleModeSelectPageTransition();

	void SetWhereCome(int m_WhereCome) {
		WhereCome = m_WhereCome;
	}

	void SetWhereGo(int m_WhereGo) {
		WhereGo = m_WhereGo;
	}

	void SetCar(int m_CarState) {
		CarState = m_CarState;
	}

	void SetCourse(int m_CourseState) {
		CourseState = m_CourseState;
	}

	void SetPlayMode(int m_PlayMode) {
		PlayMode = m_PlayMode;
	}

	void SetLicenseNum(int m_LicenseNum) {
		LicenseNum = m_LicenseNum;
	}

	void SetModeState(int m_ModeState) {
		ModeState = m_ModeState;
	}


private:

	Vector4 BlackOutColor{ 1.0f, 1.0f, 1.0f, 1.0f };

	SpriteRender BlackOut;
	SpriteRender Base;
	SpriteRender CarLogo;
	SpriteRender CourseLogo;
	SpriteRender TipsSprite;

	Menu* m_menu;
	RaceMenu* m_racemenu;
	MainRaceManager* m_MainRaceManager;
	TimeTrialMode* m_TimeTrialMode;
	GameCamera* m_gamecamera;
	Garage* m_Garage;
	LicenseMode* m_LicenseMode;
	LicenseRace* m_LicenseRace;
	OptionMenu* m_OptionMenu;
	SkyCube* m_skyCube = nullptr;
	BackGround* m_BackGround;
	CarChange* m_CarChange;
	ModeSelect* m_ModeSelect;

	int WhereCome = 0;			//0:タイトル
	int WhereGo = 0;			//0:タイトル
	int CarState = -1;			//0:Oreca07
	int CourseState = -1;		//0:セブリング

	int PlayMode = 0; //0:タイムアタック 1:サーキットエクスペリエンス 2:ライセンス 3:ワールドチャレンジ

	int LicenseNum=0;//1～5:B 6～10:A 11～15:IB 16～20:IA 21～25:S

	int FadeCount;
	int LoadCount = 0;

	int ModeState = 0;

};

