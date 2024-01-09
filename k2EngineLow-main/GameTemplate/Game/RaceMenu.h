#pragma once
class MainRaceManager;


class RaceMenu:public IGameObject
{
public:
	RaceMenu();
	~RaceMenu();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:
	MainRaceManager* m_mainracemanager;
};

