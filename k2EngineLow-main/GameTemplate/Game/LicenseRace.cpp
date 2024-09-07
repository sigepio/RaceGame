#include "stdafx.h"
#include "LicenseRace.h"
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
#include "Car_86GT.h"
#include "Car_RX7FD.h"
#include "Car_A90Supra.h"
#include "Car_GTRR35.h"
#include "Player.h"
#define _USE_MATH_DEFINES

LicenseRace::LicenseRace() {

}

LicenseRace::~LicenseRace() {

}

bool LicenseRace::Start() {
	//フィニッシュラインの読み込み
	if (LicenseNum > 0) {
		if (LicenseNum == 1 || LicenseNum == 2) {
			FinishLine.Init("Assets/modelData/course/License/B12.tkm");
		}
		else if (LicenseNum == 3 || LicenseNum == 4) {
			FinishLine.Init("Assets/modelData/course/License/B34.tkm");
		}
		else if (LicenseNum == 5) {
			FinishLine.Init("Assets/modelData/course/License/LicenseFinishLine.tkm");
			FinishLine.SetPosition(-13000, 0.0, -13000);
			Quaternion rot;
			rot.AddRotationDegY(180);
			FinishLine.SetRotation(rot);
			FinishLine.Update();
		}
	}
	FinishLine.Update();

	//クリアタイムの設定
	switch (LicenseNum)
	{
	case 1:
		ClearTime = { 20.500,21.500,23.000 };
		break;
	case 2:
		ClearTime = { 16.200,17.500,20.000};
		break;
	case 3:
		ClearTime = { 32.500,34.200,36.000 };
		break;
	case 4:
		ClearTime = { 25.200,26.700,28.000 };
		break;
	case 5:
		ClearTime = { 13.100,14.500,16.000 };
		break;
	default:
		break;
	}

	//画像読み込み
	PassedTimeBaseSprite.Init("Assets/sprite/CircuitExperience/PassedTimeBase.DDS", 1600.0f, 900.0f);

	//目標タイムの読み込み
	switch (LicenseNum)
	{
	case 1:
		PassedTimeSprite.Init("Assets/sprite/LicenseMode/PassedTimeB-1.DDS", 1600.0f, 900.0f);
		break;
	case 2:
		PassedTimeSprite.Init("Assets/sprite/LicenseMode/PassedTimeB-2.DDS", 1600.0f, 900.0f);
		break;
	case 3:
		PassedTimeSprite.Init("Assets/sprite/LicenseMode/PassedTimeB-3.DDS", 1600.0f, 900.0f);
		break;
	case 4:
		PassedTimeSprite.Init("Assets/sprite/LicenseMode/PassedTimeB-4.DDS", 1600.0f, 900.0f);
		break;
	case 5:
		PassedTimeSprite.Init("Assets/sprite/LicenseMode/PassedTimeB-5.DDS", 1600.0f, 900.0f);
		break;
	default:
		break;
	}

	//タイムのUIの設定
	TimeUIRender.Init("Assets/sprite/TimeUi.DDS", 1920.0f, 1080.0f);
	m_TimeUIPosition.y = -48.0f;
	TimeUIRender.SetPosition(m_TimeUIPosition);
	TimeUIRender.Update();

	//ポーズ画面のUI設定
	PauseSprite.Init("Assets/sprite/UI/Pause.DDS", 1600.0f, 900.0f);
	PauseSprite.SetMulColor(m_Pausecolor);
	//再開用
	ContinueSpriteNonSelect.Init("Assets/sprite/UI/Pause_Continue_Non_Select.DDS", 1600.0f, 900.0f);
	ContinueSpriteNonSelect.SetMulColor(m_Pausecolor);
	ContinueSpriteNonSelect.SetPosition(m_Pauseposition);
	ContinueSpriteSelect.Init("Assets/sprite/UI/Pause_Continue_Select.DDS", 1600.0f, 900.0f);
	ContinueSpriteSelect.SetMulColor(m_Pausecolor);
	ContinueSpriteSelect.SetPosition(m_Pauseposition);
	//Exit用
	ExitSpriteNonSelect.Init("Assets/sprite/UI/Pause_Exit_Non_Select.DDS", 1600.0f, 900.0f);
	ExitSpriteNonSelect.SetMulColor(m_Pausecolor);
	ExitSpriteNonSelect.SetPosition(m_Pauseposition);
	ExitSpriteSelect.Init("Assets/sprite/UI/Pause_Exit_Select.DDS", 1600.0f, 900.0f);
	ExitSpriteSelect.SetMulColor(m_Pausecolor);
	ExitSpriteSelect.SetPosition(m_Pauseposition);
	//リトライ用
	RetryNonSelect.Init("Assets/sprite/UI/Pause_Retry_Non_Select.DDS", 1600.0f, 900.0f);
	RetryNonSelect.SetMulColor(m_Pausecolor);
	RetryNonSelect.SetPosition(m_Pauseposition);
	RetrySelect.Init("Assets/sprite/UI/Pause_Retry_Select.DDS", 1600.0f, 900.0f);
	RetrySelect.SetMulColor(m_Pausecolor);
	RetrySelect.SetPosition(m_Pauseposition);
	//更新
	ContinueSpriteNonSelect.Update();
	ContinueSpriteSelect.Update();
	ExitSpriteNonSelect.Update();
	ExitSpriteSelect.Update();
	RetryNonSelect.Update();
	RetrySelect.Update();
	PauseSprite.Update();

	//スタートカウントの設定
	Count3Sprite.Init("Assets/sprite/StartCount/3.DDS", 1600.0f, 900.0f);
	Count2Sprite.Init("Assets/sprite/StartCount/2.DDS", 1600.0f, 900.0f);
	Count1Sprite.Init("Assets/sprite/StartCount/1.DDS", 1600.0f, 900.0f);
	STARTSprite.Init("Assets/sprite/StartCount/START.DDS", 1600.0f, 900.0f);

	//コース図の設定
	switch (CourseNum)
	{
	case sebring:
		CourseMapUISprite.Init("Assets/sprite/UI/CourseMapUI.DDS", 1600.0f, 900.0f);
		break;
	case CircuitDeLaSarthe:
		CourseMapUISprite.Init("Assets/sprite/UI/CourseMapUILeMans.DDS", 1600.0f, 900.0f);
		break;
	case AutodromoNazionaleDiMonza:
		CourseMapUISprite.Init("Assets/sprite/UI/CourseMapUIMonza.DDS", 1600.0f, 900.0f);
		break;
	default:
		break;
	}

	//インスタンスの取得
	m_background = FindGO<BackGround>("background");
	m_gamecamera = FindGO<GameCamera>("gamecamera");
	m_lighting = FindGO<Lighting>("lighting");
	m_skyCube = FindGO<SkyCube>("skycube");
	m_player = FindGO<Player>("player");
	m_caraformula = NewGO<CarAFormula>(0, "caraformula");

	CarNum = m_player->GetCarNum();
	//車種別のインスタンスの取得
	switch (CarNum)
	{
	case ORECA07:
		m_Oreca07 = NewGO<Car_Oreca07>(2, "car_oreca07");
		m_Oreca07->SetLicenseNum(LicenseNum);
		break;
	case TOYOTA86GT:
		m_86GT = NewGO<Car_86GT>(2, "car_86gt");
		m_86GT->SetLicenseNum(LicenseNum);
		break;
	case TOYOTA90Supra:
		m_A90Supra = NewGO<Car_A90Supra>(2, "car_a90supra");
		m_A90Supra->SetLicenseNum(LicenseNum);
		break;
	case NissanGTR_17:
		m_GTRR35 = NewGO<Car_GTRR35>(2, "car_gtrr35");
		m_GTRR35->SetLicenseNum(LicenseNum);
		break;
	case MazdaRX_7FD3SSpiritRTypeA:
		m_FD3S = NewGO<Car_RX7FD>(2, "car_rx7fd");
		m_FD3S->SetLicenseNum(LicenseNum);
		break;
	default:
		break;
	}



	return true;
}

void LicenseRace::Update() {
	//スタートカウント
	if (PauseState == -1) {
		//オートドライブの設定
		switch (CarNum)
		{
		case ORECA07:
			m_Oreca07->SetAutoDrive(true);
			break;
		case TOYOTA86GT:
			m_86GT->SetAutoDrive(true);
			break;
		case TOYOTA90Supra:
			m_A90Supra->SetAutoDrive(true);
			break;
		case NissanGTR_17:
			m_GTRR35->SetAutoDrive(true);
			break;
		case MazdaRX_7FD3SSpiritRTypeA:
			m_FD3S->SetAutoDrive(true);
			break;
		default:
			break;
		}
		StartSignalCount++;
		StartSignalTime = 1 / g_gameTime->GetFrameDeltaTime();
		if (StartSignalCount % StartSignalTime == 0) {
			StartSignal++;
			if (StartSignal < 4) {
				CountSignalSE = NewGO<SoundSource>(0);
				CountSignalSE->Init(103);
				CountSignalSE->SetVolume(m_player->GetSEVolume());
				CountSignalSE->Play(false);
			}
		}
		if (StartSignal == 4) {
			switch (CarNum)
			{
			case ORECA07:
				m_Oreca07->SetAutoDrive(false);
				break;
			case TOYOTA86GT:
				m_86GT->SetAutoDrive(false);
				break;
			case TOYOTA90Supra:
				m_A90Supra->SetAutoDrive(false);
				break;
			case NissanGTR_17:
				m_GTRR35->SetAutoDrive(false);
				break;
			case MazdaRX_7FD3SSpiritRTypeA:
				m_FD3S->SetAutoDrive(false);
				break;
			default:
				break;
			}
			PauseState = 0;
			//スタートのSE
			StartSignalSE = NewGO<SoundSource>(0);
			StartSignalSE->Init(104);
			StartSignalSE->SetVolume(m_player->GetSEVolume());
			StartSignalSE->Play(false);
			//BGMの再生
			BGM = NewGO<SoundSource>(0);

			BGM->Init(3);
			BGM->Play(false);
			BGM->SetVolume(m_player->GetBGMVolume() / 2.0f);
		}

		StartSignalSetCount++;
	}
	
	//ゲーム中
	if (PauseState == 0) {
		//初期化
		if (ResetCount == 1) {
			PauseState = -1;
		}
		else if (ResetCount > 1) {
			//BGMの処理
			if (BGM->IsPlaying() == false) {
				DeleteGO(BGM);
				BGMTrack++;
				BGM = NewGO<SoundSource>(0);

				BGM->Init(BGMTrack + 2);
				BGM->Play(false);
				BGM->SetVolume(m_player->GetBGMVolume() / 2.0f);
				if (MAXRaceBGM == BGMTrack)
					BGMTrack = 0;
			}
			//時間経過
			m_timer += g_gameTime->GetFrameDeltaTime();
			KeepTime += g_gameTime->GetFrameDeltaTime();

			//スタートの削除
			if (m_timer > 1.0f) {
				StartSignal++;
			}
			//ポーズの処理
			if (g_pad[0]->IsTrigger(enButtonStart)) {

				BGM->Pause();
				PauseState = 1;
				PauseCount = 0;
			}
		}

		
	}
	//ポーズ画面
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
			RetryNonSelect.SetMulColor(m_Pausecolor);
			RetryNonSelect.SetPosition(m_Pauseposition);
			RetrySelect.SetMulColor(m_Pausecolor);
			RetrySelect.SetPosition(m_Pauseposition);

			ContinueSpriteNonSelect.Update();
			ContinueSpriteSelect.Update();
			ExitSpriteNonSelect.Update();
			ExitSpriteSelect.Update();
			RetryNonSelect.Update();
			RetrySelect.Update();
			PauseSprite.Update();
		}
		//ゲームに戻る
		else if (g_pad[0]->IsTrigger(enButtonStart) || g_pad[0]->IsTrigger(enButtonA) && PauseWindowState == 0) {
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
		//リトライ
		else if (g_pad[0]->IsTrigger(enButtonA) && PauseWindowState == 1) {
			m_Loading = NewGO<Loading>(0, "loading");
			m_Loading->SetCar(CarNum);
			m_Loading->SetCourse(CourseNum);
			m_Loading->SetWhereCome(PlayPage);
			m_Loading->SetWhereGo(PlayPage);
			m_Loading->SetLicenseNum(LicenseNum);
			DeleteGO(BGM);

			GameEnd = true;
			switch (CarNum)
			{
			case ORECA07:
				m_Oreca07->SetGameEnd(GameEnd);
				break;
			case TOYOTA86GT:
				m_86GT->SetGameEnd(GameEnd);
				break;
			case TOYOTA90Supra:
				m_A90Supra->SetGameEnd(GameEnd);
				break;
			case NissanGTR_17:
				m_GTRR35->SetGameEnd(GameEnd);
				break;
			case MazdaRX_7FD3SSpiritRTypeA:
				m_FD3S->SetGameEnd(GameEnd);
				break;
			default:
				break;
			}
			m_caraformula->SetGameEnd(GameEnd);
			DeleteGO(this);
		}
		//ゲームを終わる
		else if (g_pad[0]->IsTrigger(enButtonA) && PauseWindowState == 2) {
			m_Loading = NewGO<Loading>(0, "loading");
			m_Loading->SetCar(CarNum);
			m_Loading->SetCourse(CourseNum);
			m_Loading->SetWhereCome(PlayPage);
			m_Loading->SetWhereGo(RaceLobbyPage);
			m_Loading->SetLicenseNum(LicenseNum);
			DeleteGO(BGM);

			GameEnd = true;
			m_gamecamera->SetGameEnd(GameEnd);
			switch (CarNum)
			{
			case ORECA07:
				m_Oreca07->SetGameEnd(GameEnd);
				break;
			case TOYOTA86GT:
				m_86GT->SetGameEnd(GameEnd);
				break;
			case TOYOTA90Supra:
				m_A90Supra->SetGameEnd(GameEnd);
				break;
			case NissanGTR_17:
				m_GTRR35->SetGameEnd(GameEnd);
				break;
			case MazdaRX_7FD3SSpiritRTypeA:
				m_FD3S->SetGameEnd(GameEnd);
				break;
			default:
				break;
			}

			m_lighting->SetGameEnd(GameEnd);
			m_caraformula->SetGameEnd(GameEnd);
			m_background->SetGameEnd(GameEnd);
			DeleteGO(BGM);
			DeleteGO(m_skyCube);
			DeleteGO(this);
		}
		else if (g_pad[0]->IsTrigger(enButtonRight) && PauseWindowState >= 0&& PauseWindowState<2) {
			PauseWindowState++;
		}
		else if (g_pad[0]->IsTrigger(enButtonLeft) && PauseWindowState>=1&& PauseWindowState<=2) {
			PauseWindowState--;
		}



		PauseCount++;
	}

	//ポーズを閉じる処理
	if (PauseState == 2) {
		if (PauseCount <= 10) {
			m_Pausecolor.w -= 0.1f;
			m_Pauseposition.y -= 5.0f;
			PauseSprite.SetMulColor(m_Pausecolor);
			ContinueSpriteNonSelect.SetMulColor(m_Pausecolor);
			ContinueSpriteNonSelect.SetPosition(m_Pauseposition);
			ContinueSpriteSelect.SetMulColor(m_Pausecolor);
			ContinueSpriteSelect.SetPosition(m_Pauseposition);
			ExitSpriteNonSelect.SetMulColor(m_Pausecolor);
			ExitSpriteNonSelect.SetPosition(m_Pauseposition);
			ExitSpriteSelect.SetMulColor(m_Pausecolor);
			ExitSpriteSelect.SetPosition(m_Pauseposition);
			RetryNonSelect.SetMulColor(m_Pausecolor);
			RetryNonSelect.SetPosition(m_Pauseposition);
			RetrySelect.SetMulColor(m_Pausecolor);
			RetrySelect.SetPosition(m_Pauseposition);

			ContinueSpriteNonSelect.Update();
			ContinueSpriteSelect.Update();
			ExitSpriteNonSelect.Update();
			ExitSpriteSelect.Update();
			RetryNonSelect.Update();
			RetrySelect.Update();
			PauseSprite.Update();
		}
		else {
			PauseState = 0;
		}
		PauseCount++;
	}

	//タイマーの処理
	if (m_timer >= 60.0f) {
		m_timerminit++;
		m_timer = 0;
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

	wchar_t m_LapCount[256];
	swprintf_s(m_LapCount, 256, L"1/1\n");
	LapCountFont.SetPosition(-870.0f, 440.0f, 0.0f);

	LapCountFont.SetText(m_LapCount);


	//ラップの処理
	switch (CarNum)
	{
	case ORECA07:
		NowLap = m_Oreca07->Getm_LapState();
		break;
	case TOYOTA86GT:
		NowLap = m_86GT->Getm_LapState();
		break;
	case TOYOTA90Supra:
		NowLap = m_A90Supra->Getm_LapState();
		break;
	case NissanGTR_17:
		NowLap = m_GTRR35->Getm_LapState();
		break;
	case MazdaRX_7FD3SSpiritRTypeA:
		NowLap = m_FD3S->Getm_LapState();
		break;
	default:
		break;
	}

	//ゲームの終了するための条件の処理
	if (ResetCount > 1) {
		switch (LicenseNum)
		{
		case 1:
			B_1();
			break;
		case 2:
			B_2();
			break;
		case 3:
			B_3();
			break;
		case 4:
			B_4();
			break;
		case 5:
			B_5();
			break;
		default:
			break;
		}
	}

	//終了処理
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
			swprintf_s(ResultTime, 256, L"%d:%02d.%03d\n", m_timerminit, m_timerintsecont, m_timermsecont);
			ResultTimeFont.SetPosition(ResultTimeFontPosition);
			ResultTimeFont.SetColor(ResultTimeColor);
			ResultTimeFont.SetScale(ResultTimeScale);
			ResultTimeFont.SetPivot(0.5f, 0.5f);
			ResultTimeFont.SetText(ResultTime);

			//トロフィーの表示
			//ゴールド
			if (KeepTime <= ClearTime.x) {
				ResultSprite.Init("Assets/sprite/CircuitExperience/Gold.DDS", 1600.0f, 900.0f);
				PassedState = true;
				DeleteGO(BGM);
				BGM = NewGO<SoundSource>(0);
				BGM->Init(6);
				BGM->Play(true);
				BGM->SetVolume(0.0f);
				ResultState = 3;
			}
			//シルバー
			else if (KeepTime <= ClearTime.y) {
				ResultSprite.Init("Assets/sprite/CircuitExperience/Silver.DDS", 1600.0f, 900.0f);
				PassedState = true;
				DeleteGO(BGM);
				BGM = NewGO<SoundSource>(0);
				BGM->Init(7);
				BGM->Play(true);
				BGM->SetVolume(0.0f);
				ResultState = 2;
			}
			//ブロンズ
			else if (KeepTime <= ClearTime.z) {
				ResultSprite.Init("Assets/sprite/CircuitExperience/Bronze.DDS", 1600.0f, 900.0f);
				PassedState = true;
				DeleteGO(BGM);
				BGM = NewGO<SoundSource>(0);
				BGM->Init(8);
				BGM->Play(true);
				BGM->SetVolume(0.0f);
				ResultState = 1;
			}
			//失格
			else {
				ResultSprite.Init("Assets/sprite/CircuitExperience/Disqualification.DDS", 1600.0f, 900.0f);
				PassedState = true;
				DeleteGO(BGM);
				BGM = NewGO<SoundSource>(0);
				BGM->Init(9);
				BGM->Play(true);
				BGM->SetVolume(0.0f);
				ResultState = 0;
			}

			//プレイヤーデータへの記録
			if (LicenseNum >= 1 && LicenseNum <= 5) {
				if (m_player->GetLicenseClear(0, LicenseNum) < ResultState) {
					m_player->SetLicenseClear(ResultState, 0, LicenseNum-1);
				}
			}

			ResultSprite.SetMulColor(ResultColor);
			ResultSprite.SetScale(ResultScale);
		}
		//Finishの表示
		if (ResultCount <= 10) {
			FINISHColor.w = 1.0f;
			FINISHSprite.SetMulColor(FINISHColor);
		}
		//Finishの非表示
		else if (ResultCount <= 60) {
			FINISHColor.w = 0.0f;
			FINISHSprite.SetMulColor(FINISHColor);
			BGMVolume += 0.01f;
			if (BGMVolume >= m_player->GetBGMVolume()) {
				BGMVolume = m_player->GetBGMVolume();
			}
			BGM->SetVolume(BGMVolume);
			ResultTimeState = true;
			ResultTimeFontPosition.x += 3.0f;
			ResultTimeFont.SetPosition(ResultTimeFontPosition);
			ResultTimeScale -= 0.025f;
			ResultTimeFont.SetScale(ResultTimeScale);
		}
		//リザルト画面の準備
		else if (ResultCount <= 110) {
			ResultBaseColor.w += 0.02f;
			ResultSpriteColor.w += 0.02f;
			ResultBaseSprite.SetMulColor(ResultBaseColor);
			ResultSelectSprite.SetMulColor(ResultSpriteColor);

			ResultSelectSpritePosition.y += 2.0f;
			ResultSelectSprite.SetPosition(ResultSelectSpritePosition);
		}
		if (PassedState == true) {
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

	//ポーズの情報共有
	m_gamecamera->SetPauseState(PauseState);

	switch (CarNum)
	{
	case ORECA07:
		m_Oreca07->SetPauseState(PauseState);
		break;
	case TOYOTA86GT:
		m_86GT->SetPauseState(PauseState);
		break;
	case TOYOTA90Supra:
		m_A90Supra->SetPauseState(PauseState);
		break;
	case NissanGTR_17:
		m_GTRR35->SetPauseState(PauseState);
		break;
	case MazdaRX_7FD3SSpiritRTypeA:
		m_FD3S->SetPauseState(PauseState);
		break;
	default:
		break;
	}

	ResetCount++;

}

void LicenseRace::ResultSelect() {

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
			m_Loading->SetCar(CarNum);
			m_Loading->SetCourse(CourseNum);
			m_Loading->SetWhereCome(PlayPage);
			m_Loading->SetWhereGo(PlayPage);
			m_Loading->SetLicenseNum(LicenseNum);
			DeleteGO(BGM);

			GameEnd = true;
			switch (CarNum)
			{
			case ORECA07:
				m_Oreca07->SetGameEnd(GameEnd);
				break;
			case TOYOTA86GT:
				m_86GT->SetGameEnd(GameEnd);
				break;
			case TOYOTA90Supra:
				m_A90Supra->SetGameEnd(GameEnd);
				break;
			case NissanGTR_17:
				m_GTRR35->SetGameEnd(GameEnd);
				break;
			case MazdaRX_7FD3SSpiritRTypeA:
				m_FD3S->SetGameEnd(GameEnd);
				break;
			default:
				break;
			}
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
			m_Loading->SetCar(CarNum);
			m_Loading->SetCourse(CourseNum);
			m_Loading->SetWhereCome(PlayPage);
			m_Loading->SetWhereGo(RaceLobbyPage);
			m_Loading->SetLicenseNum(LicenseNum);
			DeleteGO(BGM);

			GameEnd = true;
			m_gamecamera->SetGameEnd(GameEnd);

			switch (CarNum)
			{
			case ORECA07:
				m_Oreca07->SetGameEnd(GameEnd);
				break;
			case TOYOTA86GT:
				m_86GT->SetGameEnd(GameEnd);
				break;
			case TOYOTA90Supra:
				m_A90Supra->SetGameEnd(GameEnd);
				break;
			case NissanGTR_17:
				m_GTRR35->SetGameEnd(GameEnd);
				break;
			case MazdaRX_7FD3SSpiritRTypeA:
				m_FD3S->SetGameEnd(GameEnd);
				break;
			default:
				break;
			}
			m_lighting->SetGameEnd(GameEnd);
			m_caraformula->SetGameEnd(GameEnd);
			m_background->SetGameEnd(GameEnd);
			DeleteGO(m_skyCube);
			DeleteGO(this);
		}
	}
	ResultSetectCount++;
}

//国内B級ライセンス1のコード
void LicenseRace::B_1() {
	if (m_NowPPosition.x >= -14684.854f && m_NowPPosition.z >= -5250 && Velocity == 0.0f) {
		PauseState = 3;
	}
}

//国内B級ライセンス2のコード
void LicenseRace::B_2() {
	if (m_NowPPosition.x >= -14684.854f && m_NowPPosition.z >= -5250 && Velocity == 0.0f) {
		PauseState = 3;
	}
}

//国内B級ライセンス3のコード
void LicenseRace::B_3() {
	if (m_NowPPosition.x <= -14000.0f && m_NowPPosition.z >= -37464.0f) {
		PauseState = 3;
	}
}

//国内B級ライセンス4のコード
void LicenseRace::B_4() {
	if (m_NowPPosition.x <= -14000.0f && m_NowPPosition.z >= -37464.0f) {
		PauseState = 3;
	}
}

void LicenseRace::B_5() {
	if (m_NowPPosition.x <= -13000.0f && m_NowPPosition.z <= 0.0f) {
		PauseState = 3;
	}
}

void LicenseRace::Render(RenderContext& rc) {
	if (LicenseNum != 0) {
		FinishLine.SetAlwaysOnDisplay(true);
		FinishLine.Draw(rc);
	}

	//StartRender.Draw(rc);

	/*FastestLapsRender.Draw(rc);*/
	if (StartSignal >= 4) {
		TimeUIRender.Draw(rc);
		TimeFont.Draw(rc);
	}


	
	if (StartSignal == 1) {
		Count3Sprite.Draw(rc);
	}
	else if (StartSignal == 2) {
		Count2Sprite.Draw(rc);
	}
	else if (StartSignal == 3) {
		Count1Sprite.Draw(rc);
	}
	else if (StartSignal == 4) {
		if(PauseWindowState != 1)
		STARTSprite.Draw(rc);
	}


	if (PauseState != 3) {
		LapCountFont.Draw(rc);
		CourseMapUISprite.Draw(rc);
	}

		if (PauseState == 3) {
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

		PauseSprite.Draw(rc);
		if (PauseWindowState == 0) {
			ContinueSpriteSelect.Draw(rc);
			ExitSpriteNonSelect.Draw(rc);
			RetryNonSelect.Draw(rc);
		}
		else if (PauseWindowState == 1) {
			ContinueSpriteNonSelect.Draw(rc);
			RetrySelect.Draw(rc);
			ExitSpriteNonSelect.Draw(rc);
		}
		else if (PauseWindowState == 2) {
			ContinueSpriteNonSelect.Draw(rc);
			ExitSpriteSelect.Draw(rc);
			RetryNonSelect.Draw(rc);
		}
}
