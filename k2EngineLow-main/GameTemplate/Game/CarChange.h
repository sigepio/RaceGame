#pragma once
#include "sound/SoundSource.h"

class Player;
class Loading;

class CarChange:public IGameObject
{
public:
	CarChange();
	~CarChange();

	bool Start();
	void Update();
	void Render(RenderContext& rc);
	

private:
	Player* m_player;
	Vector3 CarListPos = { 715.0f,-40.0f,0.0f };

	Vector3 ArrowSpritePos = { -450.0f,150.0f,0.0f };

	Vector4 BlackOutColor = { 1.0f,1.0f,1.0f,1.0f };

	SpriteRender CarListSprite;

	SpriteRender BaseSprite;
	SpriteRender ArrowSprite;
	SpriteRender FadeSprite;


	Loading* m_Loading;
	SoundSource* BGM;
	SoundSource* CursorSE;
	SoundSource* DecisionSE;
	SoundSource* CancelSE;

	int LocalSelectPointX = 0;
	int LocalSecectPointY = 0;
	int WorldSelectPointX = 0;
	int WorldSecectPointY = 0;

	int WorldSelectPoint[3][8] = { {0,3,6, 9,12,15,18,21},
								   {1,4,7,10,13,16,19,-1},
								   {2,5,8,11,14,17,20,-1} };

	std::vector<int> PossessionCar = { 0 };
	int NumberOfCarsOwned = 0;
	int Columns=-1;

	int FadeCount = 0;

	int CarListPage = 0;

	bool FadeState = false;
};

