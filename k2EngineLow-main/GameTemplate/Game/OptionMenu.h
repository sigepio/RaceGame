#pragma once
#include "sound/SoundSource.h"

class Player;
class Loading;

class OptionMenu:public IGameObject
{
public:
	OptionMenu();
	~OptionMenu();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	void SetWhereComePage(int m_WhereComePage) {
		WhereComePage = m_WhereComePage;
	}

private:
	Vector4 SelectSpriteColor = { 1.0f,1.0f,1.0f,1.0f };
	Vector4 MainSpriteColor = { 1.0f,1.0f,1.0f,0.0f };
	Vector4 TransmissionSpriteColor = { 1.0f,1.0f,1.0f,0.0f };
	Vector4 SoundSpriteColor = { 1.0f,1.0f,1.0f,0.0f };
	Vector4 FadeColor = { 1.0f,1.0f,1.0f,1.0f };

	Vector3 SelectSpritePosition = { -685.75f,260.0f,0.0f };
	Vector3 TransitionsPositionA = { -653.0f,260.0f,0.0f };
	Vector3 TransitionsPositionB = { -653.0f,30.0f,0.0f };
	Vector3 TransitionsPositionC = { -653.0f,-206.0f,0.0f };
	Vector3 BGMGagePosition = { -646.0f,215.0f,0.0f };
	Vector3 SEGagePosition = { -646.0f,-14.808f,0.0f };
	Vector3 EngineSoundGagePosition = { -646.0f,-254.0f,0.0f };

	SpriteRender BaseSprite;
	SpriteRender SelectSprite;
	SpriteRender MainSprite;
	SpriteRender TransmissionSprite;
	SpriteRender SoundSprite;
	SpriteRender TransitionsSpriteA;
	SpriteRender TransitionsSpriteB;
	SpriteRender TransitionsSpriteC;
	SpriteRender BGMGage;
	SpriteRender SEGage;
	SpriteRender EngineSoundGage;
	SpriteRender FadeSprite;

	Player* m_player;
	Loading* m_loading;
	SoundSource* BGM;
	SoundSource* CursorSE;
	SoundSource* DecisionSE;
	SoundSource* CancelSE;

	float BGMVolume;
	float SEVolume;
	float EngineSoundVolume;

	int WhereComePage = 0;//Ç«Ç±Ç©ÇÁóàÇΩÇ©ÇÃäiî[ÅiñﬂÇÈç€Ç…Ç«Ç±Ç÷çsÇ≠Ç©ÇÃéwíË)
	int FadeCount = 0;
	int TransitionsCount = 0;
	int SelectPoint = 0;
	int PageState = 0;//0:Main 1:Transmission 2:Sound
	int SelectMoveCount;
	int Selectdirection = 1;
	int NextPageCount = 0;

	bool SelectMoveUpState = false;
	bool SelectMoveDownState = false;
	bool NextPageState = false;
	bool BackPageState = false;
	bool VolumeChangeStatus = false;
	bool TransMissionChangeStatus = false;
	bool Transmission = false;
};

