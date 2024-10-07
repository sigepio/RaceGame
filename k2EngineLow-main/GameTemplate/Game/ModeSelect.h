#pragma once
#include "sound/SoundSource.h"

class Player;
class Loading;

class ModeSelect: public IGameObject
{
public:
	ModeSelect();
	~ModeSelect();

	bool Start();
	void Update();
	void Render(RenderContext& rc);
private:
	Vector4 BlackOutColor = { 1.0f,1.0f,1.0f,1.0f };


	SpriteRender BaseSprite;
	SpriteRender TimeAttackSelect;
	SpriteRender TimeTrialSelect;
	SpriteRender WorldChallengeSelect;
	SpriteRender RedBullXChallengeSelect;
	SpriteRender FadeSprite;

	Loading* m_Loading;
	Player* m_Player;

	SoundSource* BGM;
	SoundSource* CursorSE;
	SoundSource* DecisionSE;
	SoundSource* CancelSE;

	int SelectPointX = 0;
	int SelectPointY = 0;

	int FadeCount = 0;

	bool FadeState = false;
	bool GoState = false;

	int ModePos[2][2] = { {0,1},
						  {2,3} };


};

