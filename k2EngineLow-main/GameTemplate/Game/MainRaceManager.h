#pragma once
class BackGround;
class Loading;

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

private:
	Vector4 BlackOutColor = { 1.0f,1.0f,1.0f,1.0f };
	Vector3 ArrowPosition = { -217.0f,-365.0f,0.0f };

	BackGround* m_background;
	Loading* m_Loading;

	SpriteRender BaseSprite;
	SpriteRender BackSprite;
	SpriteRender ArrowSprite;
	SpriteRender CourseSprite;
	SpriteRender BlackOutSprite;

	int CourseInformation = 0;
	int CarInformation = 0;

	int FadeCount = 0;
	int MoveCount = 0;

	int FadeState = 0;
	int ArrowMove = 0;
	

	int SelectPoint = 0;//0:スタート 1:exit
};

