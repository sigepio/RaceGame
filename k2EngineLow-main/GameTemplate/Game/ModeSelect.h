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
	Vector4 m_WindowSpriteColor = { 1.0f,1.0f,1.0f,0.0f };

	Vector3 m_WindowSpritePosition = { 0.0f,-50.0f,0.0f };

	SpriteRender BaseSprite;
	SpriteRender TimeAttackSelect;
	SpriteRender TimeTrialSelect;
	SpriteRender WorldChallengeSelect;
	SpriteRender RedBullXChallengeSelect;
	SpriteRender FadeSprite;
	SpriteRender ErrorWindowSprite;				//エラー時のポップアップウィンドウ
	SpriteRender WindowBottonOKSprite;			//ウィンドウのOKボタン

	Loading* m_Loading;
	Player* m_Player;

	SoundSource* BGM;
	SoundSource* CursorSE;
	SoundSource* DecisionSE;
	SoundSource* CancelSE;
	SoundSource* ErrorSE;

	int SelectPointX = 0;
	int SelectPointY = 0;

	int ErrorWindowFlag = 0;//0:非表示 1:表示遷移 2:表示中 3:非表示遷移
	int WindowCount = 0;

	int FadeCount = 0;

	bool FadeState = false;
	bool GoState = false;

	int ModePos[2][2] = { {0,1},
						  {2,3} };


};

