#include "stdafx.h"
#include "RaceMenu.h"
#include "MainRaceManager.h"
#include "Loading.h"
#include "PageNum.h"
#include "Player.h"

#include "sound/SoundEngine.h"

RaceMenu::RaceMenu() {

}

RaceMenu::~RaceMenu() {

}

bool RaceMenu::Start() {
	m_player = FindGO<Player>("player");

	Base.Init("Assets/Sprite/RaceMenu/Base.DDS", 1600.0f, 900.0f);

	CourseSelectBase_Sebring.Init("Assets/Sprite/RaceMenu/NonSelect.DDS", 298.0f, 206.0f);
	CourseSelectBase_LeMans.Init("Assets/Sprite/RaceMenu/NonSelect.DDS", 298.0f, 206.0f);
	CourseSelectBase_Monza.Init("Assets/Sprite/RaceMenu/NonSelect.DDS", 298.0f, 206.0f);
	ModeSelectBase_CE.Init("Assets/Sprite/RaceMenu/NonSelect.DDS", 298.0f, 206.0f);
	ModeSelectBase_TT.Init("Assets/Sprite/RaceMenu/NonSelect.DDS", 298.0f, 206.0f);
	CourseSelect.Init("Assets/Sprite/RaceMenu/Select.DDS", 298.0f, 206.0f);
	CourseSelect_Sebring.Init("Assets/Sprite/RaceMenu/SebringSelect.DDS", 298.0f, 206.0f);
	CourseSelect_LeMans.Init("Assets/Sprite/RaceMenu/LeMansSelect.DDS", 298.0f, 206.0f);
	CourseSelect_Monza.Init("Assets/Sprite/RaceMenu/MonzaSelect.DDS", 298.0f, 206.0f);
	ModeSelect_CE.Init("Assets/Sprite/RaceMenu/CircuitExperience.DDS", 298.0f, 206.0f);
	ModeSelect_TT.Init("Assets/Sprite/RaceMenu/TimeTrial.DDS", 298.0f, 206.0f);

	m_FadeSprite.Init("Assets/Sprite/BlackOut.DDS", 1600.0f, 900.0f);


	m_FadeSprite.SetMulColor(m_FadeColor);

	CourseSelectBase_Sebring.SetPosition(SebringPosition);
	CourseSelectBase_LeMans.SetPosition(LeMansPosition);
	CourseSelectBase_Monza.SetPosition(MonzaPosition);

	CourseSelect.SetPosition(SelectPosition);
	CourseSelect_Sebring.SetPosition(SebringPosition);
	CourseSelect_LeMans.SetPosition(LeMansPosition);
	CourseSelect_Monza.SetPosition(MonzaPosition);

	CourseInformationinit(CourseSelectPoint);

	
	CourseSelectBase_Sebring.Update();
	CourseSelectBase_LeMans.Update();
	CourseSelectBase_Monza.Update();
	CourseSelect.Update();
	CourseSelect_Sebring.Update();
	CourseSelect_LeMans.Update();
	CourseSelect_Monza.Update();

	RaceMenuBGM = NewGO<SoundSource>(0);
	RaceMenuBGM->Init(1);
	RaceMenuBGM->SetVolume(m_player->GetBGMVolume());
	RaceMenuBGM->Play(true);

	return true;
}

void RaceMenu::CourseInformationinit(int CourseSelect) {
		Main_Sebring.Init("Assets/Sprite/RaceMenu/test.DDS", 1600.0f, 900.0f);
		CourseExclusive_Sebring.Init("Assets/Sprite/RaceMenu/Sebring.DDS", 1600.0f, 900.0f);
		Main_LeMans.Init("Assets/Sprite/RaceMenu/test_LeMans.DDS", 1600.0f, 900.0f);
		CourseExclusive_LeMans.Init("Assets/Sprite/RaceMenu/LeMans.DDS", 1600.0f, 900.0f);
		Main_Monza.Init("Assets/Sprite/RaceMenu/test_Monza.DDS", 1600.0f, 900.0f);
		CourseExclusive_Monza.Init("Assets/Sprite/RaceMenu/Monza.DDS", 1600.0f, 900.0f);
}

void RaceMenu::Update() {
	if (FadeCount < 5) {

		m_FadeColor.w -= 0.2f;
		m_FadeSprite.SetMulColor(m_FadeColor);
		FadeCount++;
	}
	else
	{
		//コースの選択
		if (SelectArea == 0) {
			if (g_pad[0]->IsTrigger(enButtonA)) {
				DecisionSE = NewGO<SoundSource>(0);
				DecisionSE->Init(101);
				DecisionSE->SetVolume(m_player->GetSEVolume());
				DecisionSE->Play(false);
				/*SelectArea = 1;*/
				FadeState = 1;
				FadeCount = 0;
			}
			else if (g_pad[0]->IsTrigger(enButtonB)) {
				CancelSE = NewGO<SoundSource>(0);
				CancelSE->Init(102);
				CancelSE->SetVolume(m_player->GetSEVolume());
				CancelSE->Play(false);

				FadeState = 2;
				FadeCount = 0;
			}
			else if (g_pad[0]->IsTrigger(enButtonRight) && CourseSelectPoint < (MaxCourseNum - 1)) {
				CursorSE = NewGO<SoundSource>(0);
				CursorSE->Init(100);
				CursorSE->SetVolume(m_player->GetSEVolume());
				CursorSE->Play(false);

				CourseSelectPoint++;
				SelectPosition.x += 310.0f;
				CourseSelect.SetPosition(SelectPosition);
				CourseSelect.Update();
			}
			else if (g_pad[0]->IsTrigger(enButtonLeft) && CourseSelectPoint > 0) {
				CursorSE = NewGO<SoundSource>(0);
				CursorSE->Init(100);
				CursorSE->SetVolume(m_player->GetSEVolume());
				CursorSE->Play(false);

				CourseSelectPoint--;
				SelectPosition.x -= 310.0f;
				CourseSelect.SetPosition(SelectPosition);
				CourseSelect.Update();
			}
		}

		//モードの選択
		else if (SelectArea == 1) {
			if (g_pad[0]->IsTrigger(enButtonA)) {
				DecisionSE = NewGO<SoundSource>(0);
				DecisionSE->Init(101);
				DecisionSE->SetVolume(m_player->GetSEVolume());
				DecisionSE->Play(false);
				FadeState = 1;
				FadeCount = 0;
			}
			else if (g_pad[0]->IsTrigger(enButtonB)) {
				CancelSE = NewGO<SoundSource>(0);
				CancelSE->Init(102);
				CancelSE->SetVolume(m_player->GetSEVolume());
				CancelSE->Play(false);

				SelectArea = 0;
				
			}
			else if (g_pad[0]->IsTrigger(enButtonRight) && CourseSelectPoint < (MaxMode - 1)) {
				CursorSE = NewGO<SoundSource>(0);
				CursorSE->Init(100);
				CursorSE->SetVolume(m_player->GetSEVolume());
				CursorSE->Play(false);

				SelectRaceMode++;
				SelectPosition.x += 310.0f;
				CourseSelect.SetPosition(SelectPosition);
				CourseSelect.Update();
			}
			else if (g_pad[0]->IsTrigger(enButtonLeft) && CourseSelectPoint > 0) {
				CursorSE = NewGO<SoundSource>(0);
				CursorSE->Init(100);
				CursorSE->SetVolume(m_player->GetSEVolume());
				CursorSE->Play(false);

				SelectRaceMode--;
				SelectPosition.x -= 310.0f;
				CourseSelect.SetPosition(SelectPosition);
				CourseSelect.Update();
			}
		}

	}
	if (FadeState == 1) {
		if (FadeCount < 5) {

			m_FadeColor.w += 0.2f;
			m_FadeSprite.SetMulColor(m_FadeColor);
			FadeCount++;
		}
		else {
			m_Loading = NewGO<Loading>(10, "loading");
			//コースの情報設定
			switch (CourseSelectPoint)
			{
			case 0:
				m_Loading->SetCourse(sebring);
				m_player->SetNowCourse(sebring);
				break;
			case 1:
				m_Loading->SetCourse(CircuitDeLaSarthe);
				m_player->SetNowCourse(CircuitDeLaSarthe);
				break;
			case 2:
				m_Loading->SetCourse(AutodromoNazionaleDiMonza);
				m_player->SetNowCourse(AutodromoNazionaleDiMonza);
				break;
			default:
				break;
			}
			//車種の情報設定
			switch (m_player->GetCarNum())
			{
			case 0:
				m_Loading->SetCar(ORECA07);
				break;
			case 1:
				m_Loading->SetCar(TOYOTA86GT);
				break;
			case 2:
				m_Loading->SetCar(TOYOTA90Supra);
				break;
			case 3:
				m_Loading->SetCar(NissanGTR_17);
				break;
			case 4:
				m_Loading->SetCar(MazdaRX_7FD3SSpiritRTypeA);
				break;
			default:
				break;
			}
			m_Loading->SetWhereCome(RaceMenuPage);
			m_Loading->SetWhereGo(RaceLobbyPage);
			DeleteGO(RaceMenuBGM);
			DeleteGO(this);
		}
	}
	if (FadeState == 2) {
		if (FadeCount < 5) {
			m_FadeColor.w += 0.2f;
			m_FadeSprite.SetMulColor(m_FadeColor);
			FadeCount++;
		}
		else {
			m_Loading = NewGO<Loading>(10, "loading");
			m_Loading->SetWhereCome(RaceMenuPage);
			m_Loading->SetWhereGo(WorldMenuPage);
			DeleteGO(RaceMenuBGM);
			DeleteGO(this);
		}
	}
	
}

void RaceMenu::Render(RenderContext& rc) {
	

	
		switch (CourseSelectPoint)
		{
		case 0:
			Main_Sebring.Draw(rc);
			Base.Draw(rc);
			CourseExclusive_Sebring.Draw(rc);
			if (SelectArea == 0) {
				CourseSelectBase_LeMans.Draw(rc);
				CourseSelectBase_Monza.Draw(rc);
			}
			break;
		case 1:
			Main_LeMans.Draw(rc);
			Base.Draw(rc);
			CourseExclusive_LeMans.Draw(rc);
			if (SelectArea == 0) {
				CourseSelectBase_Sebring.Draw(rc);
				CourseSelectBase_Monza.Draw(rc);
			}
			break;
		case 2:
			Main_Monza.Draw(rc);
			Base.Draw(rc);
			CourseExclusive_Monza.Draw(rc);
			if (SelectArea == 0) {
				CourseSelectBase_Sebring.Draw(rc);
				CourseSelectBase_LeMans.Draw(rc);
			}
		default:
			break;
		}
	
	CourseSelect.Draw(rc);

	CourseSelect_Sebring.Draw(rc);
	CourseSelect_LeMans.Draw(rc);
	CourseSelect_Monza.Draw(rc);
	m_FadeSprite.Draw(rc);
}