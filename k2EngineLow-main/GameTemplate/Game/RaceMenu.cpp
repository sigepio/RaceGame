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
	CourseSelectBase_Imola.Init("Assets/Sprite/RaceMenu/NonSelect.DDS", 298.0f, 206.0f);
	CourseSelectBase_SilverStone.Init("Assets/Sprite/RaceMenu/NonSelect.DDS", 298.0f, 206.0f);
	
	ModeSelectBase_CE.Init("Assets/Sprite/RaceMenu/NonSelect.DDS", 298.0f, 206.0f);
	ModeSelectBase_TT.Init("Assets/Sprite/RaceMenu/NonSelect.DDS", 298.0f, 206.0f);
	
	CourseSelect.Init("Assets/Sprite/RaceMenu/Select.DDS", 298.0f, 206.0f);

	CourseSelect_Sebring.Init("Assets/Sprite/RaceMenu/SebringSelect.DDS", 298.0f, 206.0f);
	CourseSelect_LeMans.Init("Assets/Sprite/RaceMenu/LeMansSelect.DDS", 298.0f, 206.0f);
	CourseSelect_Monza.Init("Assets/Sprite/RaceMenu/MonzaSelect.DDS", 298.0f, 206.0f);
	CourseSelect_Imola.Init("Assets/Sprite/RaceMenu/ImolaSelect.DDS", 298.0f, 206.0f);
	CourseSelect_SilverStone.Init("Assets/Sprite/RaceMenu/SilverStoneSelect.DDS", 298.0f, 206.0f);
	
	ModeSelect_CE.Init("Assets/Sprite/RaceMenu/CircuitExperience.DDS", 298.0f, 206.0f);
	ModeSelect_TT.Init("Assets/Sprite/RaceMenu/TimeTrial.DDS", 298.0f, 206.0f);

	m_FadeSprite.Init("Assets/Sprite/BlackOut.DDS", 1600.0f, 900.0f);


	m_FadeSprite.SetMulColor(m_FadeColor);

	CourseSelectBase_Sebring.SetPosition(SebringPosition);
	CourseSelectBase_LeMans.SetPosition(LeMansPosition);
	CourseSelectBase_Monza.SetPosition(MonzaPosition);
	CourseSelectBase_Imola.SetPosition(ImolaPosition);
	CourseSelectBase_SilverStone.SetPosition(SilverStonePosition);

	CourseSelect.SetPosition(SelectPosition);
	CourseSelect_Sebring.SetPosition(SebringPosition);
	CourseSelect_LeMans.SetPosition(LeMansPosition);
	CourseSelect_Monza.SetPosition(MonzaPosition);
	CourseSelect_Imola.SetPosition(ImolaPosition);
	CourseSelect_SilverStone.SetPosition(SilverStonePosition);

	CourseInformationinit(CourseSelectPoint);

	
	CourseSelectBase_Sebring.Update();
	CourseSelectBase_LeMans.Update();
	CourseSelectBase_Monza.Update();
	CourseSelectBase_Imola.Update();
	CourseSelectBase_SilverStone.Update();
	CourseSelect.Update();
	CourseSelect_Sebring.Update();
	CourseSelect_LeMans.Update();
	CourseSelect_Monza.Update();
	CourseSelect_Imola.Update();
	CourseSelect_SilverStone.Update();

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

		Main_Imola.Init("Assets/Sprite/RaceMenu/test_Imola.DDS", 1600.0f, 900.0f);
		CourseExclusive_Imola.Init("Assets/Sprite/RaceMenu/Imola.DDS", 1600.0f, 900.0f);
		Main_SilverStone.Init("Assets/Sprite/RaceMenu/test_SilverStone.DDS", 1600.0f, 900.0f);
		CourseExclusive_SilverStone.Init("Assets/Sprite/RaceMenu/SilverStone.DDS", 1600.0f, 900.0f);
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
			case 3:
				m_Loading->SetCourse(ImolaCircuit);
				m_player->SetNowCourse(ImolaCircuit);
				break;
			case 4:
				m_Loading->SetCourse(SilverstoneCircuit);
				m_player->SetNowCourse(SilverstoneCircuit);
				break;
			default:
				break;
			}
			//車種の情報設定
			m_Loading->SetCar(m_player->GetCarNum());
			m_Loading->SetWhereCome(RaceMenuPage);
			m_Loading->SetWhereGo(RaceLobbyPage);
			m_Loading->SetModeState(SelectRaceMode);
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
			m_Loading->SetWhereGo(ModeSelectPage);
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
				CourseSelectBase_Imola.Draw(rc);
				CourseSelectBase_SilverStone.Draw(rc);
			}
			break;
		case 1:
			Main_LeMans.Draw(rc);
			Base.Draw(rc);
			CourseExclusive_LeMans.Draw(rc);
			if (SelectArea == 0) {
				CourseSelectBase_Sebring.Draw(rc);
				CourseSelectBase_Monza.Draw(rc);
				CourseSelectBase_Imola.Draw(rc);
				CourseSelectBase_SilverStone.Draw(rc);
			}
			break;
		case 2:
			Main_Monza.Draw(rc);
			Base.Draw(rc);
			CourseExclusive_Monza.Draw(rc);
			if (SelectArea == 0) {
				CourseSelectBase_Sebring.Draw(rc);
				CourseSelectBase_LeMans.Draw(rc);
				CourseSelectBase_Imola.Draw(rc);
				CourseSelectBase_SilverStone.Draw(rc);
			}
			break;
		case 3:
			Main_Imola.Draw(rc);
			Base.Draw(rc);
			CourseExclusive_Imola.Draw(rc);
			if (SelectArea == 0) {
				CourseSelectBase_Sebring.Draw(rc);
				CourseSelectBase_LeMans.Draw(rc);
				CourseSelectBase_Monza.Draw(rc);
				CourseSelectBase_SilverStone.Draw(rc);
			}
			break;
		case 4:
			Main_SilverStone.Draw(rc);
			Base.Draw(rc);
			CourseExclusive_SilverStone.Draw(rc);
			if (SelectArea == 0) {
				CourseSelectBase_Sebring.Draw(rc);
				CourseSelectBase_LeMans.Draw(rc);
				CourseSelectBase_Monza.Draw(rc);
				CourseSelectBase_Imola.Draw(rc);
			}
			break;
		default:
			break;
		}
	
	CourseSelect.Draw(rc);

	CourseSelect_Sebring.Draw(rc);
	CourseSelect_LeMans.Draw(rc);
	CourseSelect_Monza.Draw(rc);
	CourseSelect_Imola.Draw(rc);
	CourseSelect_SilverStone.Draw(rc);
	m_FadeSprite.Draw(rc);
}