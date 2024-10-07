#include "stdafx.h"
#include "MainRaceManager.h"
#include "BackGround.h"
#include "PageNum.h"
#include "Loading.h"
#include "GameCamera.h"
#include "Lighting.h"
#include "Player.h"
#include "FadeIn.h"
#include "PageNum.h"

MainRaceManager::MainRaceManager() {

}

MainRaceManager::~MainRaceManager() {

}

bool MainRaceManager::Start(){
	if (WhereComePage != PlayPage) {
		m_background = NewGO<BackGround>(1, "background");
		m_background->SetCourse(CourseInformation);
		m_background->SetLicenseNum(LicenseNum);
		// åªç›ÇÃãÛÇîjä¸ÅB
		m_skyCube = FindGO<SkyCube>("skycube");

		m_skyCube->SetLuminance(1.0f);
		m_skyCube->SetType((EnSkyCubeType)m_skyCubeType);
		m_skyCube->SetScale(50000.0f);
		
	}
	m_gamecamera = NewGO<GameCamera>(4, "gamecamera");
	m_lighting = NewGO<Lighting>(0, "lighting");
	m_gamecamera->SetPlayFlag(false);
	m_gamecamera->SetMainRaceManagerFlag(true);
	m_FadeIn = FindGO<FadeIn>("fadein");

	

	m_player = FindGO<Player>("player");

	
	
	BackSprite.Init("Assets/Sprite/Lobby/Test.DDS", 1600.0f, 900.0f);
	BaseSprite.Init("Assets/Sprite/Lobby/Base.DDS", 1600.0f, 900.0f);
	if (LicenseNum == 0) {
		switch (CourseInformation)
		{
		case sebring:
			CourseSprite.Init("Assets/Sprite/Lobby/Sebring.DDS", 1600.0f, 900.0f);
			break;
		case CircuitDeLaSarthe:
			CourseSprite.Init("Assets/Sprite/Lobby/LeMans.DDS", 1600.0f, 900.0f);
			break;
		case AutodromoNazionaleDiMonza:
			CourseSprite.Init("Assets/Sprite/Lobby/Monza.DDS", 1600.0f, 900.0f);
			break;
		case SilverstoneCircuit:
			CourseSprite.Init("Assets/Sprite/Lobby/Silverstone.DDS", 1600.0f, 900.0f);
			break;
		case ImolaCircuit:
			CourseSprite.Init("Assets/Sprite/Lobby/Imola.DDS", 1600.0f, 900.0f);
			break;
		default:
			break;
		}
	}
	else {
		switch (LicenseNum)
		{
		case 1:
			LicenseTagSprite.Init("Assets/Sprite/Lobby/License/DomesticB/B-1_1.DDS", 1600.0f, 900.0f);
			LicenseContentsBase.Init("Assets/Sprite/Lobby/License/DomesticB/B-1_2.DDS", 1340.0f, 412.0f);
			LicenseContents.Init("Assets/Sprite/Lobby/License/DomesticB/B-1_3.DDS", 1600.0f, 900.0f);

			LicenseContentsBase.SetPosition(LicenseContentsBasePosition);
			LicenseContentsBase.SetPivot( 0.5,1.0 );
			LicenseContentsBase.SetScale(1.0f, LicenseContentsBaseScale, 0.0f);

			LicenseContents.SetMulColor(LicenseContentsColor);

			LicenseContentsBase.Update();
			LicenseContents.Update();

			break;
		case 2:
			LicenseTagSprite.Init("Assets/Sprite/Lobby/License/DomesticB/B-2_1.DDS", 1600.0f, 900.0f);
			LicenseContentsBase.Init("Assets/Sprite/Lobby/License/DomesticB/B-2_2.DDS", 1340.0f, 412.0f);
			LicenseContents.Init("Assets/Sprite/Lobby/License/DomesticB/B-2_3.DDS", 1600.0f, 900.0f);

			LicenseContentsBase.SetPosition(LicenseContentsBasePosition);
			LicenseContentsBase.SetPivot(0.5, 1.0);
			LicenseContentsBase.SetScale(1.0f, LicenseContentsBaseScale, 0.0f);

			LicenseContents.SetMulColor(LicenseContentsColor);

			LicenseContentsBase.Update();
			LicenseContents.Update();

			break;
		case 3:
			LicenseTagSprite.Init("Assets/Sprite/Lobby/License/DomesticB/B-3_1.DDS", 1600.0f, 900.0f);
			LicenseContentsBase.Init("Assets/Sprite/Lobby/License/DomesticB/B-3_2.DDS", 1340.0f, 412.0f);
			LicenseContents.Init("Assets/Sprite/Lobby/License/DomesticB/B-3_3.DDS", 1600.0f, 900.0f);

			LicenseContentsBase.SetPosition(LicenseContentsBasePosition);
			LicenseContentsBase.SetPivot(0.5, 1.0);
			LicenseContentsBase.SetScale(1.0f, LicenseContentsBaseScale, 0.0f);

			LicenseContents.SetMulColor(LicenseContentsColor);

			LicenseContentsBase.Update();
			LicenseContents.Update();

			break;
		case 4:
			LicenseTagSprite.Init("Assets/Sprite/Lobby/License/DomesticB/B-4_1.DDS", 1600.0f, 900.0f);
			LicenseContentsBase.Init("Assets/Sprite/Lobby/License/DomesticB/B-4_2.DDS", 1340.0f, 412.0f);
			LicenseContents.Init("Assets/Sprite/Lobby/License/DomesticB/B-4_3.DDS", 1600.0f, 900.0f);

			LicenseContentsBase.SetPosition(LicenseContentsBasePosition);
			LicenseContentsBase.SetPivot(0.5, 1.0);
			LicenseContentsBase.SetScale(1.0f, LicenseContentsBaseScale, 0.0f);

			LicenseContents.SetMulColor(LicenseContentsColor);

			LicenseContentsBase.Update();
			LicenseContents.Update();

			break;
		case 5:
			LicenseTagSprite.Init("Assets/Sprite/Lobby/License/DomesticB/B-5_1.DDS", 1600.0f, 900.0f);
			LicenseContentsBase.Init("Assets/Sprite/Lobby/License/DomesticB/B-5_2.DDS", 1340.0f, 412.0f);
			LicenseContents.Init("Assets/Sprite/Lobby/License/DomesticB/B-5_3.DDS", 1600.0f, 900.0f);

			LicenseContentsBase.SetPosition(LicenseContentsBasePosition);
			LicenseContentsBase.SetPivot(0.5, 1.0);
			LicenseContentsBase.SetScale(1.0f, LicenseContentsBaseScale, 0.0f);

			LicenseContents.SetMulColor(LicenseContentsColor);

			LicenseContentsBase.Update();
			LicenseContents.Update();

			break;
		default:
			break;
		}
	}
	ArrowSprite.Init("Assets/Sprite/Lobby/Arrow.DDS", 78.0f, 73.0f);
	BlackOutSprite.Init("Assets/Sprite/Lobby/BlackOut.DDS", 1600.0f, 900.0f);

	ArrowSprite.SetPosition(ArrowPosition);
	ArrowSprite.Update();

	BGM = NewGO<SoundSource>(0);
	BGM->Init(2);
	BGM->SetVolume(m_player->GetBGMVolume());
	BGM->Play(true);

	return true;
}

void MainRaceManager::Update() {
	
	if (LicenseNum != 0) {
		if (LicenseCount < 50) {
			LicenseContentsBase.SetScale(1.0f, scaleValues[LicenseCount], 0.0f);
		}
		else if (LicenseCount < 100) {
			LicenseContentsColor.w += 0.02f;
			LicenseContents.SetMulColor(LicenseContentsColor);
		}
		LicenseContents.Update();
		LicenseContentsBase.Update();
		LicenseCount++;
	}
	if (FadeCount < 5) {
		BlackOutColor.w -= 0.2;
		BlackOutSprite.SetMulColor(BlackOutColor);
	}
	else if (FadeCount > 6) {
		if (SelectPoint == 0) {
			if (g_pad[0]->IsTrigger(enButtonA)) {
				DecisionSE = NewGO<SoundSource>(0);
				DecisionSE->Init(101);
				DecisionSE->SetVolume(m_player->GetSEVolume());
				DecisionSE->Play(false);
				FadeCount = 0;
				FadeState = 1;
				
			}
			if (g_pad[0]->IsTrigger(enButtonRight)) {
				CursorSE = NewGO<SoundSource>(0);
				CursorSE->Init(100);
				CursorSE->SetVolume(m_player->GetSEVolume());
				CursorSE->Play(false);
				ArrowMove = 1;
				MoveCount = 0;
				
			}
		}
		else if (SelectPoint == 1) {
			if (g_pad[0]->IsTrigger(enButtonA)) {
				CancelSE = NewGO<SoundSource>(0);
				CancelSE->Init(102);
				CancelSE->SetVolume(m_player->GetSEVolume());
				CancelSE->Play(false);
				FadeCount = 0;
				FadeState = 2;
				
			}
			if (g_pad[0]->IsTrigger(enButtonLeft)) {
				CursorSE = NewGO<SoundSource>(0);
				CursorSE->Init(100);
				CursorSE->SetVolume(m_player->GetSEVolume());
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
			
		}
		else {
			m_Loading = NewGO<Loading>(10, "loading");
			m_Loading->SetCar(m_player->GetCarNum());
			m_Loading->SetCourse(CourseInformation);
			m_Loading->SetWhereCome(RaceLobbyPage);
			m_Loading->SetWhereGo(PlayPage);
			m_Loading->SetLicenseNum(LicenseNum);
			m_Loading->SetModeState(ModeState);
			
			DeleteGO(BGM);
			DeleteGO(this);
		}
	}
	if (FadeState == 2) {
		m_FadeIn->FedeInStart();
		BlackOutColor.w = 1.0f;
		BlackOutSprite.SetMulColor(BlackOutColor);
		if (FadeCount < 5) {
			BlackOutColor.w += 0.2f;
			BlackOutSprite.SetMulColor(BlackOutColor);
			
		}
		else {
			m_Loading = NewGO<Loading>(10, "loading");
			m_Loading->SetCar(m_player->GetCarNum());
			m_Loading->SetCourse(CourseInformation);
			m_Loading->SetWhereCome(RaceLobbyPage);
			if (LicenseNum == 0) {
				m_Loading->SetWhereGo(RaceMenuPage);
			}
			else {
				m_Loading->SetWhereGo(LicenseModePage);
			}
			
			DeleteGO(m_gamecamera);
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
	BlackOutSprite.Update();
	FadeCount++;
}

void MainRaceManager::Render(RenderContext& rc) {
	//BackSprite.Draw(rc);
	BaseSprite.Draw(rc);
	if (LicenseNum == 0) {
		CourseSprite.Draw(rc);
	}
	else {
		LicenseTagSprite.Draw(rc);
		LicenseContentsBase.Draw(rc);
		LicenseContents.Draw(rc);
	}
	ArrowSprite.Draw(rc);

	BlackOutSprite.Draw(rc);


}