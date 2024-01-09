#pragma once
class MainRaceManager:public IGameObject
{
public:
	MainRaceManager();
	~MainRaceManager();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
private:

};

