#pragma once
class Sound;
class Menu;
class TimeTrialMode;
class Loading;
class Player;
class GameCamera;
class Lighting;
class FadeIn;

class Title:public IGameObject,Noncopyable
{
public:
	Title();
	~Title();
	void Update();
	bool Start();
	void Render(RenderContext&rc);
	
private:
	Loading* m_loading;
	Sound* m_Sound;
	GameCamera* m_GameCamera;
	Lighting* m_Lighting;
	FadeIn* m_FadeIn;
	SkyCube* m_skyCube;

	ModelRender CarModel;

	SpriteRender m_TitleSprite;
	SpriteRender m_PressStartSprite;
	SpriteRender m_FadeSprite;

	Vector4 m_PressStartSpriteColor = { 1.0f,1.0f,1.0f,1.0f };
	Vector4 m_FadeColor = { 1.0f,1.0f,1.0f,0.0f };

	int m_skyCubeType = enSkyCubeType_Day;
	int m_PressColorTime=0;
	int m_PressDirection=1;
	int FadeState = 0;
	int FadeCount;

};

