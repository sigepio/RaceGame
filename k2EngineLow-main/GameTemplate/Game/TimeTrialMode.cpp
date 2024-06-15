#include "stdafx.h"
#include "TimeTrialMode.h"
#include "Lighting.h"
#include "GameCamera.h"
#include "Car_RB6.h"
#include "Car_AE86.h"
#include "Car_Oreca07.h"
#include "BackGround.h"
#include "FrontWheelBase.h"
#include <vector>
#include "CarAFormula.h"
#include "Loading.h"
#include "PageNum.h"


TimeTrialMode::TimeTrialMode() {

}

TimeTrialMode::~TimeTrialMode() {
	
}

bool TimeTrialMode::Start() {
	
	// 現在の空を破棄。
	DeleteGO(m_skyCube);
	m_skyCube = NewGO<SkyCube>(0, "skycube");

	m_skyCube->SetLuminance(1.0f);
	m_skyCube->SetType((EnSkyCubeType)m_skyCubeType);
	m_skyCube->SetScale(5000.0f);

	m_background = FindGO<BackGround>("background");
	
	m_gamecamera = NewGO<GameCamera>(4, "gamecamera");

	m_Oreca07 = NewGO<Car_Oreca07>(2, "car_oreca07");
	m_lighting = NewGO<Lighting>(0, "lighting");
	m_caraformula = NewGO<CarAFormula>(0, "caraformula");

	TimeUIRender.Init("Assets/sprite/TimeUi.DDS", 1920.0f, 1080.0f);
	m_TimeUIPosition.y = -48.0f;
	TimeUIRender.SetPosition(m_TimeUIPosition);
	TimeUIRender.Update();

	/*FastestLapsRender.Init("Assets/sprite/FastestLap.DDS", 1632.0f, 918.0f);
	m_FastestLapsPosition = { Vector3(700.0f, 360.0f, 0.0f) };
	FastestLapsRender.SetPosition(m_FastestLapsPosition);
	FastestLapsRender.Update();*/

	//StartRender.Init("Assets/modelData/course/track1.tkm", false);
	
	PauseSprite.Init("Assets/sprite/UI/Pause.DDS", 1600.0f, 900.0f);
	PauseSprite.SetMulColor(m_Pausecolor);

	ContinueSpriteNonSelect.Init("Assets/sprite/UI/Pause_Continue_Non_Select.DDS", 1600.0f, 900.0f);
	ContinueSpriteNonSelect.SetMulColor(m_Pausecolor);
	ContinueSpriteNonSelect.SetPosition(m_Pauseposition);
	ContinueSpriteSelect.Init("Assets/sprite/UI/Pause_Continue_Select.DDS", 1600.0f, 900.0f);
	ContinueSpriteSelect.SetMulColor(m_Pausecolor);
	ContinueSpriteSelect.SetPosition(m_Pauseposition);

	ExitSpriteNonSelect.Init("Assets/sprite/UI/Pause_Exit_Non_Select.DDS", 1600.0f, 900.0f);
	ExitSpriteNonSelect.SetMulColor(m_Pausecolor);
	ExitSpriteNonSelect.SetPosition(m_Pauseposition);
	ExitSpriteSelect.Init("Assets/sprite/UI/Pause_Exit_Select.DDS", 1600.0f, 900.0f);
	ExitSpriteSelect.SetMulColor(m_Pausecolor);
	ExitSpriteSelect.SetPosition(m_Pauseposition);

	//PauseSprite.Update();

	return true;
}

void TimeTrialMode::Update() {
		
	if (PauseState == 0) {
		//時間経過
		m_timer += g_gameTime->GetFrameDeltaTime();
		if (g_pad[0]->IsTrigger(enButtonStart)) {
			PauseState = 1;
			PauseCount = 0;
		}
	}
	
	if (PauseState == 1) {
		//ポーズ画面への遷移
		if (PauseCount <= 10) {
			m_Pausecolor.w += 0.1f;
			m_Pauseposition.y += 5.0f;
			PauseSprite.SetMulColor(m_Pausecolor);
			ContinueSpriteNonSelect.SetMulColor(m_Pausecolor);
			ContinueSpriteNonSelect.SetPosition(m_Pauseposition);
			ContinueSpriteSelect.SetMulColor(m_Pausecolor);
			ContinueSpriteSelect.SetPosition(m_Pauseposition);
			ExitSpriteNonSelect.SetMulColor(m_Pausecolor);
			ExitSpriteNonSelect.SetPosition(m_Pauseposition);
			ExitSpriteSelect.SetMulColor(m_Pausecolor);
			ExitSpriteSelect.SetPosition(m_Pauseposition);

			ContinueSpriteNonSelect.Update();
			ContinueSpriteSelect.Update();
			ExitSpriteNonSelect.Update();
			ExitSpriteSelect.Update();
			PauseSprite.Update();
		}
		//ゲームに戻る
		else if (g_pad[0]->IsTrigger(enButtonStart)|| g_pad[0]->IsTrigger(enButtonA)&&PauseWindowState==0){
			PauseState = 2;
			PauseCount = 0;
			return;
		}
		else if (g_pad[0]->IsTrigger(enButtonB)) {
			if (PauseWindowState = 0) {
				PauseState = 2;
				PauseCount = 0;
				return;
			}
			else {
				PauseWindowState = 0;
			}
		}
		//ゲームを終わる
		else if (g_pad[0]->IsTrigger(enButtonA) && PauseWindowState == 1) {
			m_Loading = NewGO<Loading>(0, "loading");
			m_Loading->SetCar(0);
			m_Loading->SetCourse(0);
			m_Loading->SetWhereCome(PlayPage);
			m_Loading->SetWhereGo(RaceLobbyPage);

			GameEnd = true;
			m_gamecamera->SetGameEnd(GameEnd);
			m_Oreca07->SetGameEnd(GameEnd);
			m_lighting->SetGameEnd(GameEnd);
			m_caraformula->SetGameEnd(GameEnd);
			m_background->SetGameEnd(GameEnd);
			DeleteGO(m_skyCube);
			DeleteGO(this);
		}
		else if (g_pad[0]->IsTrigger(enButtonRight) && PauseWindowState == 0) {
			PauseWindowState = 1;
		}
		else if (g_pad[0]->IsTrigger(enButtonLeft) && PauseWindowState == 1) {
			PauseWindowState = 0;
		}

		

		PauseCount++;
	}
	if (PauseState == 2) {
		if (PauseCount <= 10) {
			m_Pausecolor.w -= 0.1f;
			m_Pauseposition.y -= 5.0f;
			ContinueSpriteNonSelect.SetMulColor(m_Pausecolor);
			ContinueSpriteNonSelect.SetPosition(m_Pauseposition);
			ContinueSpriteSelect.SetMulColor(m_Pausecolor);
			ContinueSpriteSelect.SetPosition(m_Pauseposition);
			ExitSpriteNonSelect.SetMulColor(m_Pausecolor);
			ExitSpriteNonSelect.SetPosition(m_Pauseposition);
			ExitSpriteSelect.SetMulColor(m_Pausecolor);
			ExitSpriteSelect.SetPosition(m_Pauseposition);

			ContinueSpriteNonSelect.Update();
			ContinueSpriteSelect.Update();
			ExitSpriteNonSelect.Update();
			ExitSpriteSelect.Update();
			PauseSprite.SetMulColor(m_Pausecolor);
			PauseSprite.Update();
		}
		else {
			PauseState = 0;
		}
		PauseCount++;
	}
	
	if (m_timer >= 60.0f) {
		m_timerminit ++;
		m_timer =0;
	}
	m_timersecont = m_timer;
	

	wchar_t Time[256];
	swprintf_s(Time, 256, L"%d:%.3f\n", m_timerminit,m_timersecont);
	TimeFont.SetPosition(-50.0f, 300.0f, 0.0f);
	

	TimeFont.SetText(Time);

	if (m_Oreca07->Getm_LapState() == 1 && m_NowPPosition.z >= 0.0f&& m_NowPPosition.x>-100.0f) {
		if (FastestLap >= m_timerminit*60+m_timersecont) {
			FastestLap = m_timerminit * 60 + m_timersecont;
			FastestLapTimemin = m_timerminit;
			FastestLapTimesec = m_timersecont;
		}
		m_timer = 0.0f;
		m_timerminit = 0.0f;
		m_Oreca07->Setm_LapState(0);
		LapCount++;
		
		wchar_t FTime[256];
		swprintf_s(FTime, 256, L"%d:%.3f\n", FastestLapTimemin, FastestLapTimesec);
		FTimeFont.SetPosition(750.0f, -300.0f, 0.0f);


		FTimeFont.SetText(FTime);

	}

	

	m_FirstFrame++;

	m_gamecamera->SetPauseState(PauseState);
	m_Oreca07->SetPauseState(PauseState);
}

void TimeTrialMode::Render(RenderContext& rc) {
	//StartRender.Draw(rc);
	TimeUIRender.Draw(rc);
	/*FastestLapsRender.Draw(rc);*/
	FTimeFont.Draw(rc);
	TimeFont.Draw(rc);
	PauseSprite.Draw(rc);
	if (PauseWindowState == 0) {
		ContinueSpriteSelect.Draw(rc);
		ExitSpriteNonSelect.Draw(rc);
	}
	else if (PauseWindowState == 1) {
		ContinueSpriteNonSelect.Draw(rc);
		ExitSpriteSelect.Draw(rc);
	}
	
}