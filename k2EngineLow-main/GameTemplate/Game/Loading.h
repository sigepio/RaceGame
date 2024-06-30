#pragma once
class Menu;
class RaceMenu;
class MainRaceManager;
class TimeTrialMode;
class GameCamera;
class Garage;

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
	void HandleRaceLobbyPageTransition();
	void HandleFadeOutTransition();
	void HandlePlayPageTransition();
	void HandleGaragePageTransition();

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

	int WhereCome = 0;			//0:タイトル
	int WhereGo = 0;			//0:タイトル
	int CarState = -1;			//0:Oreca07
	int CourseState = -1;		//0:セブリング

	int FadeCount;
	int LoadCount = 0;

};

