#pragma once
class MyGarage:public IGameObject
{
public:
	MyGarage();
	~MyGarage();
	bool Start();
	void Update();
	void Render(RenderContext&rc);

private:

};

