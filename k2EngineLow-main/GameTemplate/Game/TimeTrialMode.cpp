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
#define _USE_MATH_DEFINES


TimeTrialMode::TimeTrialMode() {

}

TimeTrialMode::~TimeTrialMode() {
	DeleteGO(BGM);
}

bool TimeTrialMode::Start() {
	
	PassedTimeBaseSprite.Init("Assets/sprite/CircuitExperience/PassedTimeBase.DDS", 1600.0f, 900.0f);
	PassedTimeSprite.Init("Assets/sprite/CircuitExperience/PassedTimeSebring.DDS", 1600.0f, 900.0f);

	m_background = FindGO<BackGround>("background");
	m_gamecamera = FindGO<GameCamera>("gamecamera");
	m_lighting = FindGO<Lighting>("lighting");
	m_skyCube = FindGO<SkyCube>("skycube");

	m_Oreca07 = NewGO<Car_Oreca07>(2, "car_oreca07");
	
	m_caraformula = NewGO<CarAFormula>(0, "caraformula");

	TimeUIRender.Init("Assets/sprite/TimeUi.DDS", 1920.0f, 1080.0f);
	m_TimeUIPosition.y = -48.0f;
	TimeUIRender.SetPosition(m_TimeUIPosition);
	TimeUIRender.Update();
	CourseMapUISprite.Init("Assets/sprite/UI/CourseMapUI.DDS", 1600.0f, 900.0f);

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

	StartSignalBaseRender.Init("Assets/sprite/StartSignal/Base.DDS", 1600.0f, 900.0f);
	StartSignalBaseRender.SetPosition(StartSignalPosition);
	StartSignalBaseRender.Update();
	StartSignalGreenSignalRender.Init("Assets/sprite/StartSignal/GreenSignal.DDS", 1600.0f, 900.0f);
	StartSignalSignal1Render.Init("Assets/sprite/StartSignal/Signal1.DDS", 1600.0f, 900.0f);
	StartSignalSignal2Render.Init("Assets/sprite/StartSignal/Signal2.DDS", 1600.0f, 900.0f);
	StartSignalSignal3Render.Init("Assets/sprite/StartSignal/Signal3.DDS", 1600.0f, 900.0f);
	StartSignalSignal4Render.Init("Assets/sprite/StartSignal/Signal4.DDS", 1600.0f, 900.0f);
	StartSignalSignal5Render.Init("Assets/sprite/StartSignal/Signal5.DDS", 1600.0f, 900.0f);

	return true;
}

void TimeTrialMode::Update() {
		
	if (PauseState == -1) {
		
		if (StartSignalSetCount < 50) {
			StartSignalPosition.y -= 4.0f;
			StartSignalBaseRender.SetPosition(StartSignalPosition);
			StartSignalBaseRender.Update();
		}
		else {
			StartSignalCount++;
			StartSignalTime = 1/g_gameTime->GetFrameDeltaTime();
			if (StartSignalCount % StartSignalTime == 0) {
				StartSignal++;
				if (StartSignal < 4) {
					CountSignalSE = NewGO<SoundSource>(0);
					CountSignalSE->Init(103);
					CountSignalSE->Play(false);
				}
			}
			if (StartSignal == 4) {
				StartSignalSE = NewGO<SoundSource>(0);
				StartSignalSE->Init(104);
				StartSignalSE->Play(false);
				PauseState = 0;
				StartSignalSetCount = 0;
				StartSignalState = 1;

				BGM = NewGO<SoundSource>(0);
				
				BGM->Init(3);
				BGM->Play(false);
				BGM->SetVolume(0.5f);
			}
			
		}
		StartSignalSetCount++;
	}
	if (StartSignalState == 1) {
		if (StartSignalSetCount <= 10) {
			StartSignalPosition.y += 20.0f;
			StartSignalBaseRender.SetPosition(StartSignalPosition);
			StartSignalBaseRender.Update();
		}
		StartSignalSetCount++;
	}


	if (PauseState == 0) {
		if (ResetCount == 1) {
			PauseState = -1;
		}
		else {
			if (ResetCount > 1) {
				if (BGM->IsPlaying() == false) {
					DeleteGO(BGM);
					BGMTrack++;
					BGM = NewGO<SoundSource>(0);
					
					BGM->Init(BGMTrack+2);
					BGM->Play(false);
					BGM->SetVolume(0.5f);
					if (MAXRaceBGM == BGMTrack)
						BGMTrack = 0;
				}
			}
			//時間経過
			m_timer += g_gameTime->GetFrameDeltaTime();
			if (g_pad[0]->IsTrigger(enButtonStart)) {

				BGM->Pause();
				PauseState = 1;
				PauseCount = 0;
			}
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
			BGM->Play(false);
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
			DeleteGO(BGM);
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
	m_timerintsecont = m_timersecont;
	m_timersecont -= m_timerintsecont;
	m_timermsecont = m_timersecont * 1000.0f;
	m_timersecont = m_timer;

	wchar_t Time[256];
	swprintf_s(Time, 256, L"%d:%02d.%03d\n", m_timerminit, m_timerintsecont, m_timermsecont);
	TimeFont.SetPosition(-50.0f, 300.0f, 0.0f);
	

	TimeFont.SetText(Time);


	if (m_Oreca07->Getm_LapState() == 2 && m_NowPPosition.z >= 4000.0f&& m_NowPPosition.x<= 120.0f) {
		if (FastestLap >= m_timerminit*60+m_timersecont) {
			FastestLap = m_timerminit * 60 + m_timersecont;
			FastestLapKeep = FastestLap;
			FastestLapTimemin = m_timerminit;
			FastestLapTimesec = m_timersecont;
			m_Fastesttimerintsecont = FastestLapTimesec;
			FastestLapTimesec -= m_Fastesttimerintsecont;
			m_Fastesttimermsecont = FastestLapTimesec * 100.0f;
			FastestLap = FastestLapTimemin * 60 + m_Fastesttimerintsecont + ((float)m_Fastesttimermsecont/100.0f);
		}
		m_timer = 0.0f;
		m_timerminit = 0.0f;
		m_Oreca07->Setm_LapState(0);
		LapCount++;
		ControlLineSE = NewGO<SoundSource>(0);
		ControlLineSE->Init(106);
		ControlLineSE->Play(false);
		
		wchar_t FTime[256];
		swprintf_s(FTime, 256, L"%d:%02d.%03d\n", FastestLapTimemin, m_Fastesttimerintsecont, m_Fastesttimermsecont);
		FTimeFont.SetPosition(750.0f, -300.0f, 0.0f);

		FTimeFont.SetText(FTime);

	}

	wchar_t m_LapCount[256];
	swprintf_s(m_LapCount, 256, L"%d/3\n", LapCount+1);
	LapCountFont.SetPosition(-870.0f,440.0f, 0.0f);

	LapCountFont.SetText(m_LapCount);


	if (GameMode == CircuitExperience) {
		if (LapCount == 3) {
			PauseState = 3;
			/*DeleteGO(BGM);*/
		}
		if (PauseState == 3) {
			if (ResultCount == 0) {
				ResultBaseSprite.Init("Assets/sprite/CircuitExperience/Base.DDS", 1600.0f, 900.0f);
				ResultSelectSprite.Init("Assets/sprite/CircuitExperience/Select.DDS", 1600.0f, 900.0f);
				ResultSelectArrowSprite.Init("Assets/sprite/CircuitExperience/SelectArrow.DDS", 44.0f, 40.0f);
				FINISHSprite.Init("Assets/sprite/FINISH.DDS", 1600.0f, 900.0f);

				ResultBaseSprite.SetMulColor(ResultBaseColor);
				ResultSelectSprite.SetMulColor(ResultSpriteColor);
				ResultSelectArrowSprite.SetMulColor(ResultSelectArrowColor);
				FINISHSprite.SetMulColor(FINISHColor);

				ResultSelectSprite.SetPosition(ResultSelectSpritePosition);
				ResultSelectArrowSprite.SetPosition(ResultSelectArrowPosition);

				//タイムの設定
				wchar_t ResultTime[256];
				swprintf_s(ResultTime, 256, L"%d:%02d.%03d\n", FastestLapTimemin, m_Fastesttimerintsecont, m_Fastesttimermsecont);
				ResultTimeFont.SetPosition(ResultTimeFontPosition);
				ResultTimeFont.SetColor(ResultTimeColor);
				ResultTimeFont.SetScale(ResultTimeScale);
				ResultTimeFont.SetPivot(0.5f, 0.5f);
				ResultTimeFont.SetText(ResultTime);

				
				if (FastestLapKeep <= 80.500f) {
					ResultSprite.Init("Assets/sprite/CircuitExperience/Gold.DDS", 1600.0f, 900.0f);
					PassedState = true;
					DeleteGO(BGM);
					BGM = NewGO<SoundSource>(0);
					BGM->Init(6);
					BGM->Play(true);
					BGM->SetVolume(0.0f);
				}
				else if (FastestLapKeep <= 83.200f) {
					ResultSprite.Init("Assets/sprite/CircuitExperience/Silver.DDS", 1600.0f, 900.0f);
					PassedState = true;
					DeleteGO(BGM);
					BGM = NewGO<SoundSource>(0);
					BGM->Init(7);
					BGM->Play(true);
					BGM->SetVolume(0.0f);
				}
				else if (FastestLapKeep <= 90.000f) {
					ResultSprite.Init("Assets/sprite/CircuitExperience/Bronze.DDS", 1600.0f, 900.0f);
					PassedState = true;
					DeleteGO(BGM);
					BGM = NewGO<SoundSource>(0);
					BGM->Init(8);
					BGM->Play(true);
					BGM->SetVolume(0.0f);
				}
				else {
					ResultSprite.Init("Assets/sprite/CircuitExperience/Disqualification.DDS", 1600.0f, 900.0f);
					PassedState = false;
					DeleteGO(BGM);
					BGM = NewGO<SoundSource>(0);
					BGM->Init(9);
					BGM->Play(true);
					BGM->SetVolume(0.0f);
				}
				ResultSprite.SetMulColor(ResultColor);
				ResultSprite.SetScale(ResultScale);
			}
			if (ResultCount <= 10) {
				FINISHColor.w = 1.0f;
				FINISHSprite.SetMulColor(FINISHColor);
			}
			else if (ResultCount <= 60) {
				FINISHColor.w = 0.0f;
				FINISHSprite.SetMulColor(FINISHColor);
				BGMVolume += 0.01f;
				BGM->SetVolume(BGMVolume);
				ResultTimeState = true;
				ResultTimeFontPosition.x += 3.0f;
				ResultTimeFont.SetPosition(ResultTimeFontPosition);
				ResultTimeScale -= 0.025f;
				ResultTimeFont.SetScale(ResultTimeScale);
			}
			else if (ResultCount <= 110) {
				ResultBaseColor.w += 0.02f;
				ResultSpriteColor.w += 0.02f;
				ResultBaseSprite.SetMulColor(ResultBaseColor);
				ResultSelectSprite.SetMulColor(ResultSpriteColor);

				ResultSelectSpritePosition.y += 2.0f;
				ResultSelectSprite.SetPosition(ResultSelectSpritePosition);
			}
			if (PassedState==true) {
				if (ResultCount > 110 && ResultCount <= 190) {
					ResultColor.w += 0.0125f;
					ResultSprite.SetMulColor(ResultColor);
					ResultScale.x -= 0.0125f;
					ResultScale.y -= 0.0125f;
					ResultSprite.SetScale(ResultScale);
				}
				else if (ResultCount > 190 && ResultCount <= 200) {
					ResultSelectArrowColor.w += 0.1f;
					ResultSelectArrowSprite.SetMulColor(ResultSelectArrowColor);

					ResultSelectArrowPosition.y -= 42.0f;
					ResultSelectArrowPosition.x -= 5.0f;
					ResultSelectArrowSprite.SetPosition(ResultSelectArrowPosition);
				}
				else {
					ResultSelect();
				}
			}
			else {
				if (ResultCount > 110 && ResultCount <= 130) {
					ResultColor.w += 0.05f;
					ResultSprite.SetMulColor(ResultColor);
					ResultScale.x -= 0.05f;
					ResultScale.y -= 0.05f;
					ResultSprite.SetScale(ResultScale);
				}
				else if (ResultCount <= 140) {
					ResultSelectArrowColor.w += 0.1f;
					ResultSelectArrowSprite.SetMulColor(ResultSelectArrowColor);

					ResultSelectArrowPosition.y -= 3.0f;
					ResultSelectArrowPosition.x -= 0.2f;
					ResultSelectArrowSprite.SetPosition(ResultSelectArrowPosition);
				}
				else {
					ResultSelect();
				}
			}

			ResultSprite.Update();
			ResultBaseSprite.Update();
			ResultSelectSprite.Update();
			ResultSelectArrowSprite.Update();
			FINISHSprite.Update();

			ResultCount++;
		}
	}


	m_FirstFrame++;
	ResetCount++;
	m_gamecamera->SetPauseState(PauseState);
	m_Oreca07->SetPauseState(PauseState);
}

void TimeTrialMode::ResultSelect() {
	
	if (ResultSetectState == 0) {
		if (ResultSetectCount < 5) {
			ResultSelectArrowPosition.x -= 96.0f;
			ResultSelectArrowSprite.SetPosition(ResultSelectArrowPosition);
		}
		else if (g_pad[0]->IsTrigger(enButtonRight)) {
			ResultSetectState = 1;
			ResultSetectCount = 0;
		}
		else if (g_pad[0]->IsTrigger(enButtonA)) {
			m_Loading = NewGO<Loading>(0, "loading");
			m_Loading->SetCar(0);
			m_Loading->SetCourse(0);
			m_Loading->SetWhereCome(PlayPage);
			m_Loading->SetWhereGo(PlayPage);

			GameEnd = true;
			m_Oreca07->SetGameEnd(GameEnd);
			m_caraformula->SetGameEnd(GameEnd);
			DeleteGO(this);
		}
	}
	else if (ResultSetectState == 1) {
		if (ResultSetectCount < 5) {
			ResultSelectArrowPosition.x += 96.0f;
			ResultSelectArrowSprite.SetPosition(ResultSelectArrowPosition);
		}
		else if (g_pad[0]->IsTrigger(enButtonLeft)) {
			ResultSetectState = 0;
			ResultSetectCount = 0;
		}
		else if (g_pad[0]->IsTrigger(enButtonA)) {
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
	}
	ResultSetectCount++;
}

void TimeTrialMode::Render(RenderContext& rc) {
	//StartRender.Draw(rc);
	
	/*FastestLapsRender.Draw(rc);*/
	if (PauseState == 0) {
		FTimeFont.Draw(rc);
	}
	if (StartSignal >= 4) {
		TimeUIRender.Draw(rc);
		TimeFont.Draw(rc);
	}


	PauseSprite.Draw(rc);
	if (PauseWindowState == 0) {
		ContinueSpriteSelect.Draw(rc);
		ExitSpriteNonSelect.Draw(rc);
	}
	else if (PauseWindowState == 1) {
		ContinueSpriteNonSelect.Draw(rc);
		ExitSpriteSelect.Draw(rc);
	}

	StartSignalBaseRender.Draw(rc);
	if (StartSignal > 0 && StartSignal < 4) {
		StartSignalSignal1Render.Draw(rc);
		StartSignalSignal2Render.Draw(rc);
		if (StartSignal > 1) {
			StartSignalSignal3Render.Draw(rc);
			StartSignalSignal4Render.Draw(rc);
			if (StartSignal > 2) {
				StartSignalSignal5Render.Draw(rc);
			}
		}
	}

	
	if (LapCount != 3) {
		LapCountFont.Draw(rc);
		CourseMapUISprite.Draw(rc);
	}

	if (GameMode == CircuitExperience) {
		if (LapCount == 3) {
			ResultBaseSprite.Draw(rc);
			ResultSprite.Draw(rc);
			ResultSelectSprite.Draw(rc);
			ResultSelectArrowSprite.Draw(rc);
			FINISHSprite.Draw(rc);
			if (ResultTimeState == true) {
				ResultTimeFont.Draw(rc);
			}
		}
		if (StartSignal >= 4) {
			PassedTimeBaseSprite.Draw(rc);
			PassedTimeSprite.Draw(rc);
		}
	}
}
