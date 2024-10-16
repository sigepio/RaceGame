#include "stdafx.h"
#include "WorldMode.h"
#include "PageNum.h"
#include "Loading.h"
#include "Sound.h"
#include "Player.h"


#include "sound/SoundEngine.h"

WorldMode::WorldMode() {
	SelectState = 0;
}

WorldMode::~WorldMode() {

}

bool WorldMode::Start() {
	m_player = FindGO<Player>("player");
	
	m_player->Save();
	m_player->SetRideCarCache(m_player->GetCarNum());
	

	Sound* mSound = FindGO<Sound>("sound");

	BaseSprite.Init("Assets/Sprite/MyHome/Base.DDS", 1632.0f, 918.0f);
	MyGarageSprite.Init("Assets/Sprite/MyHome/Garage.DDS", 1632.0f, 918.0f);
	MyGarageSelectSprite.Init("Assets/Sprite/MyHome/Garage_Frame.DDS", 1632.0f, 918.0f);
	CarDealerSprite.Init("Assets/Sprite/MyHome/Dealer.DDS", 1632.0f, 918.0f);
	CarDealerSelectSprite.Init("Assets/Sprite/MyHome/Dealer_Frame.DDS", 1632.0f, 918.0f);
	TuningSprite.Init("Assets/Sprite/MyHome/Tuning.DDS", 1632.0f, 918.0f);
	TuningSelectSprite.Init("Assets/Sprite/MyHome/Tuning_Frame.DDS", 1632.0f, 918.0f);
	MaintenanceSprite.Init("Assets/Sprite/MyHome/Maintenance.DDS", 1632.0f, 918.0f);
	MaintenanceSelectSprite.Init("Assets/Sprite/MyHome/Maintenance_Frame.DDS", 1632.0f, 918.0f);
	LicenseSprite.Init("Assets/Sprite/MyHome/License.DDS", 1632.0f, 918.0f);
	LicenseSelectSprite.Init("Assets/Sprite/MyHome/License_Frame.DDS", 1632.0f, 918.0f);
	WorldRaceSprite.Init("Assets/Sprite/MyHome/Race.DDS", 1632.0f, 918.0f);
	WorldRaceSelectSprite.Init("Assets/Sprite/MyHome/Race_Frame.DDS", 1632.0f, 918.0f);
	ErrorWindowSprite.Init("Assets/Sprite/MyHome/ErrorWindow.DDS", 1632.0f, 918.0f);
	WindowBottonOKSprite.Init("Assets/Sprite/MyHome/WindowBottonOK.DDS", 1632.0f, 918.0f);
	BlackOut.Init("Assets/Sprite/BlackOut.DDS", 1600.0f, 900.0f);

	ErrorWindowSprite.SetMulColor(m_WindowSpriteColor);
	WindowBottonOKSprite.SetMulColor(m_WindowSpriteColor); 

	ErrorWindowSprite.SetPosition(m_WindowSpritePosition);
	WindowBottonOKSprite.SetPosition(m_WindowSpritePosition);

	BlackOut.SetMulColor(m_FadeColor);


	BGM = NewGO<SoundSource>(0);
	BGM->Init(0);
	BGM->SetVolume(m_player->GetBGMVolume());
	BGM->Play(true);

	return true;
}

void WorldMode::Update() {
	if (Count % 60 == 0) {
		SelectDirection *= -1;
	}

	m_SelectSpriteColor.w -= 0.016 * SelectDirection;
	if (g_pad[0]->IsTrigger(enButtonStart)) {
		FadeSate = 1;
		FadeCount = 0;
		OptionState = true;
	}
	switch (SelectState)
	{
	case 0:
		MyGarageSelectSprite.SetMulColor(m_SelectSpriteColor);
		WorldRaceSelectSprite.SetMulColor(m_NonSelectSpriteColor);
		LicenseSelectSprite.SetMulColor(m_NonSelectSpriteColor);
		CarDealerSelectSprite.SetMulColor(m_NonSelectSpriteColor);
		TuningSelectSprite.SetMulColor(m_NonSelectSpriteColor);
		MaintenanceSelectSprite.SetMulColor(m_NonSelectSpriteColor);
		if (ErrorWindowFlag == 0) {
			if (g_pad[0]->IsTrigger(enButtonA)) {

				DecisionSE = NewGO<SoundSource>(0);
				DecisionSE->Init(101);
				DecisionSE->SetVolume(m_player->GetSEVolume());
				DecisionSE->Play(false);
				FadeSate = 1;
				FadeCount = 0;
			}
			if (g_pad[0]->IsTrigger(enButtonRight)) {
				CursorSE = NewGO<SoundSource>(0);
				CursorSE->Init(100);
				CursorSE->SetVolume(m_player->GetSEVolume());
				CursorSE->Play(false);

				m_SelectSpriteColor.w = 1.0f;
				SelectDirection = 1;
				Count = 0;
				SelectState = 1;
			}
		}
		break;
	case 1:
		WorldRaceSelectSprite.SetMulColor(m_SelectSpriteColor);

		MyGarageSelectSprite.SetMulColor(m_NonSelectSpriteColor);
		LicenseSelectSprite.SetMulColor(m_NonSelectSpriteColor);
		CarDealerSelectSprite.SetMulColor(m_NonSelectSpriteColor);
		TuningSelectSprite.SetMulColor(m_NonSelectSpriteColor);
		MaintenanceSelectSprite.SetMulColor(m_NonSelectSpriteColor);

		if (g_pad[0]->IsTrigger(enButtonA)) {
			/*if (SelectFlag[SelectState] == 0 && ErrorWindowFlag == 0) {
				ErrorWindowFlag = 1;
			}
			else {
				
			}*/
			DecisionSE = NewGO<SoundSource>(0);
			DecisionSE->Init(101);
			DecisionSE->SetVolume(m_player->GetSEVolume());
			DecisionSE->Play(false);
			FadeSate = 1;
			FadeCount = 0;
		}
		if (g_pad[0]->IsTrigger(enButtonRight)) {
			CursorSE = NewGO<SoundSource>(0);
			CursorSE->Init(100);
			CursorSE->SetVolume(m_player->GetSEVolume());
			CursorSE->Play(false);

			m_SelectSpriteColor.w = 1.0f;
			SelectDirection = 1;
			Count = 0;
			SelectState = 2;
		}
		if (g_pad[0]->IsTrigger(enButtonLeft)) {
			CursorSE = NewGO<SoundSource>(0);
			CursorSE->Init(100);
			CursorSE->SetVolume(m_player->GetSEVolume());
			CursorSE->Play(false);

			m_SelectSpriteColor.w = 1.0f;
			SelectDirection = 1;
			Count = 0;
			SelectState = 0;
		}
		if (g_pad[0]->IsTrigger(enButtonDown)) {
			CursorSE = NewGO<SoundSource>(0);
			CursorSE->Init(100);
			CursorSE->SetVolume(m_player->GetSEVolume());
			CursorSE->Play(false);

			m_SelectSpriteColor.w = 1.0f;
			SelectDirection = 1;
			Count = 0;
			SelectState = 3;
		}
		break;
	case 2:
		LicenseSelectSprite.SetMulColor(m_SelectSpriteColor);
		MyGarageSelectSprite.SetMulColor(m_NonSelectSpriteColor);
		WorldRaceSelectSprite.SetMulColor(m_NonSelectSpriteColor);
		CarDealerSelectSprite.SetMulColor(m_NonSelectSpriteColor);
		TuningSelectSprite.SetMulColor(m_NonSelectSpriteColor);
		MaintenanceSelectSprite.SetMulColor(m_NonSelectSpriteColor);
			if (g_pad[0]->IsTrigger(enButtonA)) {
				DecisionSE = NewGO<SoundSource>(0);
				DecisionSE->Init(101);
				DecisionSE->SetVolume(m_player->GetSEVolume());
				DecisionSE->Play(false);
				FadeSate = 1;
				FadeCount = 0;
			}
			if (g_pad[0]->IsTrigger(enButtonLeft)) {
				CursorSE = NewGO<SoundSource>(0);
				CursorSE->Init(100);
				CursorSE->SetVolume(m_player->GetSEVolume());
				CursorSE->Play(false);

				m_SelectSpriteColor.w = 1.0f;
				SelectDirection = 1;
				Count = 0;
				SelectState = 1;
			}
			if (g_pad[0]->IsTrigger(enButtonDown)) {
				CursorSE = NewGO<SoundSource>(0);
				CursorSE->Init(100);
				CursorSE->SetVolume(m_player->GetSEVolume());
				CursorSE->Play(false);

				m_SelectSpriteColor.w = 1.0f;
				SelectDirection = 1;
				Count = 0;
				SelectState = 5;
			}
		break;
	case 3:
		LicenseSelectSprite.SetMulColor(m_NonSelectSpriteColor);
		MyGarageSelectSprite.SetMulColor(m_NonSelectSpriteColor);
		WorldRaceSelectSprite.SetMulColor(m_NonSelectSpriteColor);
		CarDealerSelectSprite.SetMulColor(m_SelectSpriteColor);
		TuningSelectSprite.SetMulColor(m_NonSelectSpriteColor);
		MaintenanceSelectSprite.SetMulColor(m_NonSelectSpriteColor);
		if (ErrorWindowFlag == 0) {
			if (g_pad[0]->IsTrigger(enButtonA)) {
				if (ErrorWindowFlag == 0) {
					ErrorSE = NewGO<SoundSource>(0);
					ErrorSE->Init(105);
					ErrorSE->SetVolume(m_player->GetSEVolume());
					ErrorSE->Play(false);
					WindowCount = 0;
					ErrorWindowFlag = 1;
				}
			}

			if (g_pad[0]->IsTrigger(enButtonRight)) {
				CursorSE = NewGO<SoundSource>(0);
				CursorSE->Init(100);
				CursorSE->SetVolume(m_player->GetSEVolume());
				CursorSE->Play(false);

				m_SelectSpriteColor.w = 1.0f;
				SelectDirection = 1;
				Count = 0;
				SelectState = 4;
			}
			if (g_pad[0]->IsTrigger(enButtonLeft)) {
				CursorSE = NewGO<SoundSource>(0);
				CursorSE->Init(100);
				CursorSE->SetVolume(m_player->GetSEVolume());
				CursorSE->Play(false);

				m_SelectSpriteColor.w = 1.0f;
				SelectDirection = 1;
				Count = 0;
				SelectState = 0;
			}
			if (g_pad[0]->IsTrigger(enButtonDown)) {
				CursorSE = NewGO<SoundSource>(0);
				CursorSE->Init(100);
				CursorSE->SetVolume(m_player->GetSEVolume());
				CursorSE->Play(false);

				m_SelectSpriteColor.w = 1.0f;
				SelectDirection = 1;
				Count = 0;
				SelectState = 1;
			}
		}

		break;
	case 4:
		LicenseSelectSprite.SetMulColor(m_NonSelectSpriteColor);
		MyGarageSelectSprite.SetMulColor(m_NonSelectSpriteColor);
		WorldRaceSelectSprite.SetMulColor(m_NonSelectSpriteColor);
		CarDealerSelectSprite.SetMulColor(m_NonSelectSpriteColor);
		TuningSelectSprite.SetMulColor(m_SelectSpriteColor);
		MaintenanceSelectSprite.SetMulColor(m_NonSelectSpriteColor);

		if (ErrorWindowFlag == 0) {
			if (g_pad[0]->IsTrigger(enButtonA)) {
				if (ErrorWindowFlag == 0) {
					ErrorSE = NewGO<SoundSource>(0);
					ErrorSE->Init(105);
					ErrorSE->SetVolume(m_player->GetSEVolume());
					ErrorSE->Play(false);
					WindowCount = 0;
					ErrorWindowFlag = 1;
				}
			}

			if (g_pad[0]->IsTrigger(enButtonRight)) {
				CursorSE = NewGO<SoundSource>(0);
				CursorSE->Init(100);
				CursorSE->SetVolume(m_player->GetSEVolume());
				CursorSE->Play(false);

				m_SelectSpriteColor.w = 1.0f;
				SelectDirection = 1;
				Count = 0;
				SelectState = 5;
			}
			if (g_pad[0]->IsTrigger(enButtonLeft)) {
				CursorSE = NewGO<SoundSource>(0);
				CursorSE->Init(100);
				CursorSE->SetVolume(m_player->GetSEVolume());
				CursorSE->Play(false);

				m_SelectSpriteColor.w = 1.0f;
				SelectDirection = 1;
				Count = 0;
				SelectState = 3;
			}
			if (g_pad[0]->IsTrigger(enButtonDown)) {
				CursorSE = NewGO<SoundSource>(0);
				CursorSE->Init(100);
				CursorSE->SetVolume(m_player->GetSEVolume());
				CursorSE->Play(false);

				m_SelectSpriteColor.w = 1.0f;
				SelectDirection = 1;
				Count = 0;
				SelectState = 1;
			}
		}
		break;
	case 5:
		LicenseSelectSprite.SetMulColor(m_NonSelectSpriteColor);
		MyGarageSelectSprite.SetMulColor(m_NonSelectSpriteColor);
		WorldRaceSelectSprite.SetMulColor(m_NonSelectSpriteColor);
		CarDealerSelectSprite.SetMulColor(m_NonSelectSpriteColor);
		TuningSelectSprite.SetMulColor(m_NonSelectSpriteColor);
		MaintenanceSelectSprite.SetMulColor(m_SelectSpriteColor);
		if (ErrorWindowFlag == 0) {
			if (g_pad[0]->IsTrigger(enButtonA)) {
				if (ErrorWindowFlag == 0) {
					ErrorSE = NewGO<SoundSource>(0);
					ErrorSE->Init(105);
					ErrorSE->SetVolume(m_player->GetSEVolume());
					ErrorSE->Play(false);
					WindowCount = 0;
					ErrorWindowFlag = 1;
				}
			}

			if (g_pad[0]->IsTrigger(enButtonLeft)) {
				CursorSE = NewGO<SoundSource>(0);
				CursorSE->Init(100);
				CursorSE->SetVolume(m_player->GetSEVolume());
				CursorSE->Play(false);

				m_SelectSpriteColor.w = 1.0f;
				SelectDirection = 1;
				Count = 0;
				SelectState = 4;
			}
			if (g_pad[0]->IsTrigger(enButtonUp)) {
				CursorSE = NewGO<SoundSource>(0);
				CursorSE->Init(100);
				CursorSE->SetVolume(m_player->GetSEVolume());
				CursorSE->Play(false);

				m_SelectSpriteColor.w = 1.0f;
				SelectDirection = 1;
				Count = 0;
				SelectState = 2;
			}
		}
		break;
	default:
		break;
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
			DecisionSE->SetVolume(m_player->GetSEVolume());
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
	
	
	if (Count % 10 == 0) {
	}
	if (FadeSate == -1) {
		if (FadeCount > 5) {
			FadeSate = 0;
		}
		else {


			m_FadeColor.w -= 0.2;
			BlackOut.SetMulColor(m_FadeColor);
			FadeCount++;
		}
	}
	else if (FadeSate == 1) {
		
		if (FadeCount > 5) {
			if (OptionState == true) {
				m_loading = NewGO<Loading>(10, "loading");
				m_loading->SetWhereCome(WorldMenuPage);
				m_loading->SetWhereGo(OptionPage);
				DeleteGO(BGM);
				DeleteGO(this);
			}
			else {
				switch (SelectState)
				{
				case 0:
					m_loading = NewGO<Loading>(10, "loading");
					m_loading->SetWhereCome(WorldMenuPage);
					m_loading->SetWhereGo(GaragePage);
					DeleteGO(BGM);
					DeleteGO(this);
					break;
				case 1:
					m_loading = NewGO<Loading>(10, "loading");
					m_loading->SetWhereCome(WorldMenuPage);
					m_loading->SetWhereGo(ModeSelectPage);
					DeleteGO(BGM);
					DeleteGO(this);
					break;
				case 2:
					m_loading = NewGO<Loading>(10, "loading");
					m_loading->SetWhereCome(WorldMenuPage);
					m_loading->SetWhereGo(LicenseModePage);
					DeleteGO(BGM);
					DeleteGO(this);
					break;
				case 3:
					CarDealerSelectSprite.SetMulColor(m_SelectSpriteColor);
					break;
				case 4:
					TuningSelectSprite.SetMulColor(m_SelectSpriteColor);
					break;
				case 5:
					MaintenanceSelectSprite.SetMulColor(m_SelectSpriteColor);
					break;
				default:
					break;
				}
			}
		}
		else {

			m_FadeColor.w += 0.2;
			BlackOut.SetMulColor(m_FadeColor);
			FadeCount++;
		}
	}

	ErrorWindowSprite.Update();
	WindowBottonOKSprite.Update();

	Count++;
}


void WorldMode::Render(RenderContext& rc) {
	BaseSprite.Draw(rc);
	MyGarageSprite.Draw(rc);
	CarDealerSprite.Draw(rc);
	TuningSprite.Draw(rc);
	MaintenanceSprite.Draw(rc);
	LicenseSprite.Draw(rc);
	WorldRaceSprite.Draw(rc);
	

		MyGarageSelectSprite.Draw(rc);

		WorldRaceSelectSprite.Draw(rc);

		LicenseSelectSprite.Draw(rc);

		CarDealerSelectSprite.Draw(rc);

		TuningSelectSprite.Draw(rc);

		MaintenanceSelectSprite.Draw(rc);

	ErrorWindowSprite.Draw(rc);
	WindowBottonOKSprite.Draw(rc);

	BlackOut.Draw(rc);
}