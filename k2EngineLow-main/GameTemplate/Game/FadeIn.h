#pragma once
class FadeIn:public IGameObject
{
public:
	FadeIn();
	~FadeIn();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	void FedeInStart() {
		FadeInState = true;
		FadeInCount = 0;
		FadeColor = { 1.0f,1.0f,1.0f,0.0f };
		FadeSprite.SetMulColor(FadeColor);
		FadeSprite.Update();
	}

private:
	Vector4 FadeColor = { 1.0f,1.0f,1.0f,0.0f };

	SpriteRender FadeSprite;

	int FadeInCount = 0;
	
	bool FadeInState = false;

};

