#include "stdafx.h"
#include "MainRaceManager.h"
#include "BackGround.h"
#include "PageNum.h"
#include "Loading.h"
#include "GameCamera.h"
#include "Lighting.h"

MainRaceManager::MainRaceManager() {

}

MainRaceManager::~MainRaceManager() {

}

bool MainRaceManager::Start(){
	m_background = NewGO<BackGround>(1, "background");
	m_gamecamera = NewGO<GameCamera>(4, "gamecamera");
	m_lighting = NewGO<Lighting>(0, "lighting");
	m_gamecamera->SetPlayFlag(false);
	m_gamecamera->SetMainRaceManagerFlag(true);

	// åªç›ÇÃãÛÇîjä¸ÅB
	DeleteGO(m_skyCube);
	m_skyCube = NewGO<SkyCube>(0, "skycube");

	m_skyCube->SetLuminance(1.0f);
	m_skyCube->SetType((EnSkyCubeType)m_skyCubeType);
	m_skyCube->SetScale(50000.0f);
	
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

	BGM = NewGO<SoundSource>(0);
	BGM->Init(2);
	BGM->Play(true);

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
				DecisionSE = NewGO<SoundSource>(0);
				DecisionSE->Init(101);
				DecisionSE->Play(false);
				FadeState = 1;
				FadeCount = 0;
			}
			if (g_pad[0]->IsTrigger(enButtonRight)) {
				CursorSE = NewGO<SoundSource>(0);
				CursorSE->Init(100);
				CursorSE->Play(false);
				ArrowMove = 1;
				MoveCount = 0;
				
			}
		}
		else if (SelectPoint == 1) {
			if (g_pad[0]->IsTrigger(enButtonA)) {
				CancelSE = NewGO<SoundSource>(0);
				CancelSE->Init(102);
				CancelSE->Play(false);

				FadeState = 2;
				FadeCount = 0;
			}
			if (g_pad[0]->IsTrigger(enButtonLeft)) {
				CursorSE = NewGO<SoundSource>(0);
				CursorSE->Init(100);
				CursorSE->Play(false);
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
			
			DeleteGO(BGM);
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
			DeleteGO(m_gamecamera);
			DeleteGO(m_background);
			DeleteGO(m_lighting);
			DeleteGO(BGM);
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
	//BackSprite.Draw(rc);
	BaseSprite.Draw(rc);
	CourseSprite.Draw(rc);
	ArrowSprite.Draw(rc);

	BlackOutSprite.Draw(rc);
}