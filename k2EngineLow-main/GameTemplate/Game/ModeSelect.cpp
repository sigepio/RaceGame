#include "stdafx.h"
#include "ModeSelect.h"
#include "Loading.h"
#include "PageNum.h"
#include "sound/SoundEngine.h"
#include "Player.h"

ModeSelect::ModeSelect() {

}

ModeSelect::~ModeSelect() {

}

bool ModeSelect::Start() {
	m_Player = FindGO<Player>("player");

	FadeSprite.Init("Assets/Sprite/BlackOut.DDS", 1600.0f, 900.0f);

	BaseSprite.Init("Assets/Sprite/ModeSelect/Base.DDS", 1600.0f, 900.0f);
	TimeAttackSelect.Init("Assets/Sprite/ModeSelect/TimeAttackSelect.DDS", 1600.0f, 900.0f);
	TimeTrialSelect.Init("Assets/Sprite/ModeSelect/TimeTrialSelect.DDS", 1600.0f, 900.0f);
	WorldChallengeSelect.Init("Assets/Sprite/ModeSelect/WorldChallengeSelect.DDS", 1600.0f, 900.0f);
	RedBullXChallengeSelect.Init("Assets/Sprite/ModeSelect/RedBullXChallengeSelect.DDS", 1600.0f, 900.0f);

	ErrorWindowSprite.Init("Assets/Sprite/MyHome/ErrorWindow.DDS", 1632.0f, 918.0f);
	WindowBottonOKSprite.Init("Assets/Sprite/MyHome/WindowBottonOK.DDS", 1632.0f, 918.0f);

	ErrorWindowSprite.SetMulColor(m_WindowSpriteColor);
	WindowBottonOKSprite.SetMulColor(m_WindowSpriteColor);

	ErrorWindowSprite.SetPosition(m_WindowSpritePosition);
	WindowBottonOKSprite.SetPosition(m_WindowSpritePosition);

	ErrorWindowSprite.Update();
	WindowBottonOKSprite.Update();

	BGM = NewGO<SoundSource>(0);
	BGM->Init(14);
	BGM->SetVolume(m_Player->GetBGMVolume());
	BGM->Play(true);

	return true;
}

void ModeSelect::Update() {
	if (FadeCount < 5) {

		BlackOutColor.w -= 0.2f;
		FadeSprite.SetMulColor(BlackOutColor);
		FadeSprite.Update();
		FadeCount++;
	}
	else {
		if (ErrorWindowFlag == 0) {
			if (g_pad[0]->IsTrigger(enButtonRight) && SelectPointX == 0) {
				CursorSE = NewGO<SoundSource>(0);
				CursorSE->Init(100);
				CursorSE->SetVolume(m_Player->GetSEVolume());
				CursorSE->Play(false);
				SelectPointX++;
			}
			else if (g_pad[0]->IsTrigger(enButtonLeft) && SelectPointX == 1) {
				CursorSE = NewGO<SoundSource>(0);
				CursorSE->Init(100);
				CursorSE->SetVolume(m_Player->GetSEVolume());
				CursorSE->Play(false);
				SelectPointX--;
			}
			else if (g_pad[0]->IsTrigger(enButtonUp) && SelectPointY == 1) {
				CursorSE = NewGO<SoundSource>(0);
				CursorSE->Init(100);
				CursorSE->SetVolume(m_Player->GetSEVolume());
				CursorSE->Play(false);
				SelectPointY--;
			}
			else if (g_pad[0]->IsTrigger(enButtonDown) && SelectPointY == 0) {
				CursorSE = NewGO<SoundSource>(0);
				CursorSE->Init(100);
				CursorSE->SetVolume(m_Player->GetSEVolume());
				CursorSE->Play(false);
				SelectPointY++;
			}
			else if (g_pad[0]->IsTrigger(enButtonA)) {
				if (SelectPointY == 0) {
					DecisionSE = NewGO<SoundSource>(0);
					DecisionSE->Init(101);
					DecisionSE->SetVolume(m_Player->GetSEVolume());
					DecisionSE->Play(false);
					FadeCount = 0;
					GoState = true;
					FadeState = true;
				}
				else if (SelectPointY == 1) {
					ErrorSE = NewGO<SoundSource>(0);
					ErrorSE->Init(105);
					ErrorSE->SetVolume(m_Player->GetSEVolume());
					ErrorSE->Play(false);
					WindowCount = 0;
					ErrorWindowFlag = 1;
				}
			}
			else  if (g_pad[0]->IsTrigger(enButtonB)) {
				CancelSE = NewGO<SoundSource>(0);
				CancelSE->Init(102);
				CancelSE->SetVolume(m_Player->GetSEVolume());
				CancelSE->Play(false);
				FadeCount = 0;
				FadeState = true;

			}
		}

		if (FadeState == true) {
			if (FadeCount < 5) {
				BlackOutColor.w += 0.2f;
				FadeSprite.SetMulColor(BlackOutColor);
				FadeSprite.Update();
				FadeCount++;
			}
			else {
				if (GoState == true) {
					m_Loading = NewGO<Loading>(10, "loading");
					m_Loading->SetWhereCome(ModeSelectPage);
					m_Loading->SetWhereGo(RaceMenuPage);
					m_Loading->SetModeState(ModePos[SelectPointY][SelectPointX]);
					DeleteGO(BGM);
					DeleteGO(this);
				}
				else {
					m_Loading = NewGO<Loading>(10, "loading");
					m_Loading->SetWhereCome(ModeSelectPage);
					m_Loading->SetWhereGo(WorldMenuPage);
					DeleteGO(BGM);
					DeleteGO(this);
				}
			}
		}
	}

	if (ErrorWindowFlag == 1) {
		m_WindowSpriteColor.w += 0.1f;
		m_WindowSpritePosition.y += 5.0f;

		ErrorWindowSprite.SetMulColor(m_WindowSpriteColor);
		WindowBottonOKSprite.SetMulColor(m_WindowSpriteColor);

		ErrorWindowSprite.SetPosition(m_WindowSpritePosition);
		WindowBottonOKSprite.SetPosition(m_WindowSpritePosition);
		WindowCount++;
		if (WindowCount == 10) {
			ErrorWindowFlag = 2;
		}
	}
	else if (ErrorWindowFlag == 2) {
		if (g_pad[0]->IsTrigger(enButtonA)) {
			DecisionSE = NewGO<SoundSource>(0);
			DecisionSE->Init(101);
			DecisionSE->SetVolume(m_Player->GetSEVolume());
			DecisionSE->Play(false);
			ErrorWindowFlag = 3;
			WindowCount = 0;
		}
	}
	else if (ErrorWindowFlag == 3) {
		m_WindowSpriteColor.w -= 0.2f;
		m_WindowSpritePosition.y -= 10.0f;

		ErrorWindowSprite.SetMulColor(m_WindowSpriteColor);
		WindowBottonOKSprite.SetMulColor(m_WindowSpriteColor);

		ErrorWindowSprite.SetPosition(m_WindowSpritePosition);
		WindowBottonOKSprite.SetPosition(m_WindowSpritePosition);
		WindowCount++;
		if (WindowCount == 5) {
			ErrorWindowFlag = 0;
			WindowCount = 0;
		}
	}
	ErrorWindowSprite.Update();
	WindowBottonOKSprite.Update();
}

void ModeSelect::Render(RenderContext& rc) {
	BaseSprite.Draw(rc);
	if (SelectPointY == 0) {
		if (SelectPointX == 0) {
			TimeAttackSelect.Draw(rc);
		}
		else if (SelectPointX == 1) {
			TimeTrialSelect.Draw(rc);
		}
	}
	else if (SelectPointY == 1) {
		if (SelectPointX == 0) {
			WorldChallengeSelect.Draw(rc);
		}
		else if (SelectPointX == 1) {
			RedBullXChallengeSelect.Draw(rc);
		}
	}
	ErrorWindowSprite.Draw(rc);
	WindowBottonOKSprite.Draw(rc);
	FadeSprite.Draw(rc);
}

