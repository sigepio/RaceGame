#include "stdafx.h"
#include "MainRaceManager.h"
#include "BackGround.h"
#include "PageNum.h"
#include "Loading.h"

MainRaceManager::MainRaceManager() {

}

MainRaceManager::~MainRaceManager() {

}

bool MainRaceManager::Start(){
	m_background = NewGO<BackGround>(1, "background");
	
	BackSprite.Init("Assets/Sprite/Lobby/Test.DDS", 1600.0f, 900.0f);
	BaseSprite.Init("Assets/Sprite/Lobby/Base.DDS", 1600.0f, 900.0f);
	switch (CourseInformation)
	{
	case Sebring:
		CourseSprite.Init("Assets/Sprite/Lobby/Sebring.DDS", 1600.0f, 900.0f);
		break;
	default:
		break;
	}
	ArrowSprite.Init("Assets/Sprite/Lobby/Arrow.DDS", 78.0f, 73.0f);
	BlackOutSprite.Init("Assets/Sprite/Lobby/BlackOut.DDS", 1600.0f, 900.0f);

	ArrowSprite.SetPosition(ArrowPosition);
	ArrowSprite.Update();
	return true;
}

void MainRaceManager::Update() {
	if (FadeCount < 5) {
		BlackOutColor.w -= 0.2;
		BlackOutSprite.SetMulColor(BlackOutColor);
	}
	else if (FadeCount > 6) {
		if (SelectPoint == 0) {
			if (g_pad[0]->IsTrigger(enButtonA)) {
				FadeState = 1;
				FadeCount = 0;
			}
			if (g_pad[0]->IsTrigger(enButtonRight)) {
				ArrowMove = 1;
				MoveCount = 0;
				
			}
		}
		else if (SelectPoint == 1) {
			if (g_pad[0]->IsTrigger(enButtonA)) {
				FadeState = 2;
				FadeCount = 0;
			}
			if (g_pad[0]->IsTrigger(enButtonLeft)) {
				ArrowMove = 2;
				MoveCount = 0;
			}
		}
		if (g_pad[0]->IsTrigger(enButtonB)) {
			MoveCount = 0;
			ArrowMove = 1;
		}
		
	}
	if (FadeState == 1) {
		if (FadeCount < 5) {
			BlackOutColor.w += 0.2f;
			BlackOutSprite.SetMulColor(BlackOutColor);
			FadeCount++;
		}
		else {
			m_Loading = NewGO<Loading>(10, "loading");
			m_Loading->SetCar(CarInformation);
			m_Loading->SetCourse(CourseInformation);
			m_Loading->SetWhereCome(RaceLobbyPage);
			m_Loading->SetWhereGo(PlayPage);
			DeleteGO(this);
		}
	}
	if (FadeState == 2) {
		if (FadeCount < 5) {
			BlackOutColor.w += 0.2f;
			BlackOutSprite.SetMulColor(BlackOutColor);
			FadeCount++;
		}
		else {
			m_Loading = NewGO<Loading>(10, "loading");
			m_Loading->SetCar(CarInformation);
			m_Loading->SetCourse(CourseInformation);
			m_Loading->SetWhereCome(RaceLobbyPage);
			m_Loading->SetWhereGo(RaceMenuPage);
			DeleteGO(this);
		}
	}

	if (ArrowMove == 1) {
		if (SelectPoint == 0) {
			if (MoveCount < 5) {
				ArrowPosition.x += 94.0f;
				ArrowSprite.SetPosition(ArrowPosition);
				ArrowSprite.Update();
			}
			else {
				SelectPoint = 1;
				ArrowMove = 0;
			}
			MoveCount++;
		}
		else {
			SelectPoint = 1;
			ArrowMove = 0;
		}
	}
	else if (ArrowMove == 2) {
		if (MoveCount < 5) {
			ArrowPosition.x -= 94.0f;
			ArrowSprite.SetPosition(ArrowPosition);
			ArrowSprite.Update();
		}
		else {
			SelectPoint = 0;
			ArrowMove = 0;
		}
		MoveCount++;
	}
	FadeCount++;
}

void MainRaceManager::Render(RenderContext& rc) {
	BackSprite.Draw(rc);
	BaseSprite.Draw(rc);
	CourseSprite.Draw(rc);
	ArrowSprite.Draw(rc);

	BlackOutSprite.Draw(rc);
}