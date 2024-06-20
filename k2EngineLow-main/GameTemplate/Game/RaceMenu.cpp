#include "stdafx.h"
#include "RaceMenu.h"
#include "MainRaceManager.h"
#include "Loading.h"
#include "PageNum.h"

#include "sound/SoundEngine.h"

RaceMenu::RaceMenu() {

}

RaceMenu::~RaceMenu() {

}

bool RaceMenu::Start() {
	Base.Init("Assets/Sprite/RaceMenu/Base.DDS", 1600.0f, 900.0f);

	CourseSelectBase_Sebring.Init("Assets/Sprite/RaceMenu/NonSelect.DDS", 298.0f, 206.0f);
	CourseSelect.Init("Assets/Sprite/RaceMenu/Select.DDS", 298.0f, 206.0f);
	CourseSelect_Sebring.Init("Assets/Sprite/RaceMenu/SebringSelect.DDS", 298.0f, 206.0f);
	m_FadeSprite.Init("Assets/Sprite/BlackOut.DDS", 1600.0f, 900.0f);


	m_FadeSprite.SetMulColor(m_FadeColor);

	CourseSelectBase_Sebring.SetPosition(SebringPosition);
	CourseSelect.SetPosition(SelectPosition);
	CourseSelect_Sebring.SetPosition(SebringPosition);

	CourseInformationinit(CourseSelectPoint);

	
	CourseSelectBase_Sebring.Update();
	CourseSelect.Update();
	CourseSelect_Sebring.Update();

	RaceMenuBGM = NewGO<SoundSource>(0);
	RaceMenuBGM->Init(1);
	RaceMenuBGM->Play(true);

	return true;
}

void RaceMenu::CourseInformationinit(int CourseSelect) {
	Main.Init("Assets/Sprite/RaceMenu/test.DDS", 1600.0f, 900.0f);
	CourseExclusive.Init("Assets/Sprite/RaceMenu/Sebring.DDS", 1600.0f, 900.0f);
	
}

void RaceMenu::Update() {
	if (FadeCount < 5) {

		m_FadeColor.w -= 0.2f;
		m_FadeSprite.SetMulColor(m_FadeColor);
		FadeCount++;
	}
	else
	{
		if (g_pad[0]->IsTrigger(enButtonA)) {
			DecisionSE = NewGO<SoundSource>(0);
			DecisionSE->Init(101);
			DecisionSE->Play(false);
			FadeState = 1;
			FadeCount = 0;
		}
		else if (g_pad[0]->IsTrigger(enButtonB)) {
			CancelSE = NewGO<SoundSource>(0);
			CancelSE->Init(102);
			CancelSE->Play(false);

			FadeState = 2;
			FadeCount = 0;
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
			m_Loading->SetCar(ORECA07);
			m_Loading->SetCourse(Sebring);
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
			m_Loading->SetCar(ORECA07);
			m_Loading->SetCourse(Sebring);
			m_Loading->SetWhereCome(RaceMenuPage);
			m_Loading->SetWhereGo(WorldMenuPage);
			DeleteGO(RaceMenuBGM);
			DeleteGO(this);
		}
	}
	
}

void RaceMenu::Render(RenderContext& rc) {
	Main.Draw(rc);
	Base.Draw(rc);
	CourseExclusive.Draw(rc);

	
	switch (CourseSelectPoint)
	{
	case 0:
		break;
	case 1:
		CourseSelectBase_Sebring.Draw(rc);
		break;
	default:
		break;
	}
	CourseSelect.Draw(rc);

	CourseSelect_Sebring.Draw(rc);
	m_FadeSprite.Draw(rc);
}