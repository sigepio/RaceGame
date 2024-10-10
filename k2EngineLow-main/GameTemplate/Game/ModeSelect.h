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
	SpriteRender ErrorWindowSprite;				//�G���[���̃|�b�v�A�b�v�E�B���h�E
	SpriteRender WindowBottonOKSprite;			//�E�B���h�E��OK�{�^��

	Loading* m_Loading;
	Player* m_Player;

	SoundSource* BGM;
	SoundSource* CursorSE;
	SoundSource* DecisionSE;
	SoundSource* CancelSE;
	SoundSource* ErrorSE;

	int SelectPointX = 0;
	int SelectPointY = 0;

	int ErrorWindowFlag = 0;//0:��\�� 1:�\���J�� 2:�\���� 3:��\���J��
	int WindowCount = 0;

	int FadeCount = 0;

	bool FadeState = false;
	bool GoState = false;

	int ModePos[2][2] = { {0,1},
						  {2,3} };


};

