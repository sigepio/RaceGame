#pragma once
class BackGround;

class Test:public IGameObject
{
public:
	Test();
	
	void Render(RenderContext& rc);

	ModelRender Test_Model;
	SpriteRender Test_Sprite;
	BackGround* bg;
private:
	Vector3 Light_Direction = { 0.0f,-1.0f,0.0f };
	Vector3 Light_Color = { 0.5f,0.5f,0.5f };

	Vector3 spLightDirection = { 0.0f,0.0f,1.0f };
	Vector3 spLightColor = { 0.5f,0.5f,0.5f };
};

