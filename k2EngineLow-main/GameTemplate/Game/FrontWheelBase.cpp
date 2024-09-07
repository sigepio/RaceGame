#include "stdafx.h"
#include "FrontWheelBase.h"
#include "RightFrontWheel.h"
#include "LeftFrontWheel.h"
#include "BackGround.h"
#include "sound/SoundEngine.h"
#include "CarAFormula.h"
#include "Player.h"
#include "PageNum.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>
#include <functional>
#include <iostream>



FrontWheelBase::FrontWheelBase() {
	
}

FrontWheelBase::~FrontWheelBase() {

}

bool FrontWheelBase::Start() {
	m_BackGround = FindGO<BackGround>("background");
	m_FrontWheelPosition = m_BackGround->GetStartPosition();
	m_FrontWheelForward = m_BackGround->GetStartForward();
	m_FrontWheelRotation.SetRotationY(atan2(m_FrontWheelForward.x, m_FrontWheelForward.z));

	m_characterController.Init(20.0f, 30.0f, m_FrontWheelPosition);
	
	currentRPM = vehicle_info.IdlingRPM;

	m_caraformula = FindGO<CarAFormula>("caraformula");
	m_Player = FindGO<Player>("player");
	
	
	
	//g_soundEngine->ResistWaveFileBank(1001, "Assets/sound/6000RPM.wav");

	UIBace.Init("Assets/sprite/UI/RaceUIBase.DDS", 1600.f, 900.0f);
	LapUI.Init("Assets/sprite/UI/LapUI.DDS", 1600.f, 900.0f);

	RPMGage.Init("Assets/sprite/UI/RPMGage.DDS", 446.0f, 13.0f);
	RPMGage.SetPosition(-222.11538461538453f, -261.0f, 0.0f);
	RPMGage.SetPivot(0.0f, 0.5f);
	RPMGage.Update();

	RPMCover.Init("Assets/sprite/UI/RPMGageCover.DDS", 1600.0f, 900.0f);
	RPMCover.SetPosition(0.0f, -4.8f, 0.0f);
	RPMCover.Update();
	ThrottleGage.Init("Assets/sprite/UI/ThrottleGage.DDS", 20.0f, 131.0f);
	ThrottleGage.SetPosition(574.0f, -392.30769230769226f, 0.0f);
	ThrottleGage.SetPivot(0.5f, 0.0f);
	ThrottleGage.Update();
	
	BrakeGage.Init("Assets/sprite/UI/BrakeGage.DDS", 20.0f, 131.0f);
	BrakeGage.SetPosition(-574.0f, -392.30769230769226f, 0.0f);
	BrakeGage.SetPivot(0.5f, 0.0f);
	BrakeGage.Update();

	//タコメーター
	RPMNeedle.Init("Assets/sprite/UI/Needle.DDS", 5.0f, 356.0f);
	RPMNeedle.SetPosition(354.0f, -380.0f, 0.0f);
	rpmneedlerot.SetRotationDegZ(95);
	RPMNeedle.SetRotation(rpmneedlerot);
	RPMNeedle.Update();

	SpeedNeedle.Init("Assets/sprite/UI/Needle.DDS", 5.0f, 356.0f);
	SpeedNeedle.SetPosition(-356.5f, -380.0f, 0.0f);
	speedneedlerot.SetRotationDegZ(106);
	SpeedNeedle.SetRotation(speedneedlerot);
	SpeedNeedle.Update();

	//タコメーターの種類の決定
	if (vehicle_info.MaxRPM <= 9000.0f) {
		RPMMeter.Init("Assets/sprite/UI/9000RPM.DDS", 1600.f, 900.0f);
		RPMMeterPattern = 0;
	}
	else if (vehicle_info.MaxRPM <= 13000.0f) {
		RPMMeter.Init("Assets/sprite/UI/13000RPM.DDS", 1600.f, 900.0f);
		RPMMeterPattern = 1;
	}
	else if (vehicle_info.MaxRPM <= 15000.0f) {
		RPMMeter.Init("Assets/sprite/UI/15000RPM.DDS", 1600.f, 900.0f);
		RPMMeterPattern = 2;
	}

	MaxSpeed = vehicle_info.MaxRPM / vehicle_info.GEAR_RATIOS[vehicle_info.MaxGear - 1] / vehicle_info.FinalGearRatio * (vehicle_info.TireRadius * 2.0) * M_PI * 60.0f / 1000.0f;
	if (MaxSpeed <= 250.0f) {
		SpeedMeter.Init("Assets/sprite/UI/250km.DDS", 1600.f, 900.0f);
		SpeedMeterPattern = 0;
	}
	else if (MaxSpeed <= 320.0f) {
		SpeedMeter.Init("Assets/sprite/UI/320km.DDS", 1600.f, 900.0f);
		SpeedMeterPattern = 1;
	}
	else if (MaxSpeed <= 410.0f) {
		SpeedMeter.Init("Assets/sprite/UI/410km.DDS", 1600.f, 900.0f);
		SpeedMeterPattern = 2;
	}
	else if (MaxSpeed <= 510.0f) {
		SpeedMeter.Init("Assets/sprite/UI/510km.DDS", 1600.f, 900.0f);
		SpeedMeterPattern = 3;
	}

	//レッドゾーンの設定
	switch (m_Player->GetCarNum())
	{
	case ORECA07:
		RedZone.Init("Assets/sprite/UI/RedZone/ORECA07.DDS", 1600.f, 900.0f);
		break;
	case TOYOTA86GT:
		RedZone.Init("Assets/sprite/UI/RedZone/86GT.DDS", 1600.f, 900.0f);
		break;
	case TOYOTA90Supra:
		RedZone.Init("Assets/sprite/UI/RedZone/A90.DDS", 1600.f, 900.0f);
		break;
	case NissanGTR_17:
		RedZone.Init("Assets/sprite/UI/RedZone/GTRR35.DDS", 1600.f, 900.0f);
		break;
	case MazdaRX_7FD3SSpiritRTypeA:
		RedZone.Init("Assets/sprite/UI/RedZone/RX_7FD3S.DDS", 1600.f, 900.0f);
		break;
	default:
		break;
	}


	engine = NewGO<SoundSource>(0);
	engine_s = NewGO<SoundSource>(0);
	switch (m_Player->GetCarNum())
	{
	case ORECA07:
		engine_s->Init(200);
		break;
	case TOYOTA86GT:
		engine_s->Init(201);
		break;
	case TOYOTA90Supra:
		engine_s->Init(202);
		break;
	case NissanGTR_17:
		engine_s->Init(203);
		break;
	case MazdaRX_7FD3SSpiritRTypeA:
		engine_s->Init(204);
		break;
	default:
		break;
	}
	
	engine_s->Play(true);
	engine_s->SetVolume(m_Player->GetEngineSoundVolume());
	EngineSoundStopCount++;
	return true;
}

float calculateScaledValue(float currentRPM, float IdolingRPM, float maxRPM, float min_val = 0.1, float max_val = 2.0) {
	// 比率を計算
	float ratio = currentRPM / IdolingRPM;

	// 1:1の比率の時の値を0.1に設定
	// 最大比率の時（MaxRPM / アイドリングの回転数）の値を2.0に設定
	float min_ratio = 1.0;  // 1:1の比率
	float max_ratio = maxRPM / IdolingRPM;

	// 線形補間を使用して値を計算
	float scaled_value = min_val + (ratio - min_ratio) * (max_val - min_val) / (max_ratio - min_ratio);

	// 最小値と最大値の間にクランプする
	scaled_value = (std::max)((std::min)(scaled_value, max_val), min_val);

	return scaled_value;
}

void FrontWheelBase::Update() {
	//計算結果を受け取る構造体の宣言
	SimulationResults ReturnSimulationResults;
	if (m_PauseState == 1 || m_PauseState == 3) {
		engine_s->SetVolume(0.0f);
	}
	if (m_PauseState == -1) {
		/*DifferenceVector = { 0.0f,0.0f,1.0f };*/
		/*m_FrontWheelForward = { 0.0f,0.0f,1.0f };*/
	}
	if (g_pad[0]->IsTrigger(enButtonLB1)) {
		Transmission = true;
	}
	else if (g_pad[0]->IsTrigger(enButtonRB1)) {
		Transmission = false;
	}
	
	if (GameEnd == true) {
		DeleteGO(engine);
		DeleteGO(engine_s);
		DeleteGO(this);
	}
	//いったん凍結
	//Move();
	Vector3 stickL;
	if (m_PauseState == 0|| m_PauseState==-1) {
		engine_s->SetVolume(1.0f);
		//アクセルボタンの入力量の取得
		m_throttle = 0.0f;

		//Rボタン
		throttle_input = 0.0f;
		throttle_input = g_pad[0]->GetRTrigger();
		throttle_input = throttle_input / 255.0f;


		//Lボタン
		brake_input = g_pad[0]->GetLTrigger();
		brake_input = brake_input / 255.0f;

		//ステアリングの切った量の取得

		stickL.x = g_pad[0]->GetLStickXF();

		DegreeOfRotationOfTheHandle = stickL.x * vehicle_info.MaximumSteeringAngleOfTires;

		if (AutoDriveState == true) {
			throttle_input = 1.0f;
			stickL.x = 0.0f;
			Transmission = true;
		}
		else {
			
			if (m_PauseState == -1) {
				m_FrontWheelForward = m_BackGround->GetStartForward();
				throttle_input = 0.0f;
				stickL.x = 0.0f;
			}
			Transmission = m_Player->GetTransmission();
		}

		ReturnSimulationResults = m_caraformula->CarSimulation(
			vehicle_info,
			m_FrontWheelPosition,
			VelocityVector,
			PitchAngle,
			RollAngle,
			AccelerationVector,
			currentRPM,
			DegreeOfRotationOfTheHandle,
			Acceleration_DecelerationForce,
			currentGear,
			grade,
			1.225,//標準大気圧での話
			WindDirectionVector,
			Temperature,
			AtmosphericPressure,
			WaterVaporPressure,
			RollingResistanceCoefficient,
			CoefficientOfFriction,
			throttle_input,
			brake_input,
			DegreeOfRotationOfTheHandle,
			m_FrontWheelForward,
			FrontWheelOrientationVector,
			Transmission,
			ΔRPM
		);

		m_FrontWheelPosition = ReturnSimulationResults.Position;
		VelocityVector = ReturnSimulationResults.VelocityVector;
		PitchAngle = ReturnSimulationResults.PitchAngle;
		RollAngle = ReturnSimulationResults.RollAngle;
		currentRPM = ReturnSimulationResults.CurrentRPM;
		currentGear = ReturnSimulationResults.CurrentGear;
		AccelerationVector = ReturnSimulationResults.Acceleration;
		ΔRPM = ReturnSimulationResults.ΔRPM;

		//float Velocity = sqrt(pow(VelocityVector.x, 2.0) + pow(VelocityVector.y, 2.0) + pow(VelocityVector.z, 2.0));
		RPMGagescale = (currentRPM - (vehicle_info.MaxRPM - 2000.0f)) / (vehicle_info.MaxRPM - (vehicle_info.MaxRPM - 2000.0f));
		//RPMGagescale = (currentRPM - 6000.0f) / 2200.0f;
		if (RPMGagescale <= 0.0f) {
			RPMGagescale = 0.0f;
		}

		//エンジン音のピッチ調整
		engine_s->SetFrequencyRatio(calculateScaledValue(currentRPM, vehicle_info.IdlingRPM, vehicle_info.MaxRPM));

		RPMGageColor.y = -2 * RPMGagescale + 2;
		RPMGageColor.z = -2 * RPMGagescale + 2;
		if (RPMGageColor.y < 0.0f) {
			RPMGageColor.y = 1.0f;
			RPMGageColor.z = 1.0f;
		}

		RPMGage.SetMulColor(RPMGageColor);
		RPMGage.SetScale(RPMGagescale, 1.0f, 0.0f);
		RPMGage.Update();
		ThrottleGage.SetScale(1.0f, throttle_input, 0.0f);
		BrakeGage.SetScale(1.0f, brake_input, 0.0f);
		ThrottleGage.Update();
		BrakeGage.Update();

		//プレイヤーの正面ベクトルを正規化
		m_FrontWheelForward.Normalize();
		m_FrontWheelForwardCatch = m_FrontWheelForward;
		if (VelocityVector != 0.0f) {
			if (stickL.x != 0.0f)
			{

				m_FrontWheelForward.x = m_FrontWheelForward.x * cos(stickL.x * vehicle_info.CorneringPower) - m_FrontWheelForward.z * sin(stickL.x * vehicle_info.CorneringPower);
				m_FrontWheelForward.z = m_FrontWheelForward.x * sin(stickL.x * vehicle_info.CorneringPower) + m_FrontWheelForward.z * cos(stickL.x * vehicle_info.CorneringPower);

				m_FrontWheelRotation.SetRotationY(atan2(m_FrontWheelForward.x, m_FrontWheelForward.z));

			}
		}
		TurningAngle = acos(m_FrontWheelForward.Dot(m_FrontWheelForwardCatch) / (m_FrontWheelForward.Length() * m_FrontWheelForwardCatch.Length()));
		Vector3 m_moveSpeed = g_vec3Zero;
		//上下の移動速度を退避させる
		float y = m_moveSpeed.y;
		m_moveSpeed = m_FrontWheelForward * VelocityVector;
		m_moveSpeed.y = y - 980.0f * g_gameTime->GetFrameDeltaTime(); // 重力
		if (m_characterController.IsOnGround()) {
			//地面についた。
			m_moveSpeed.y = 0.0f;
		}
		m_FrontWheelPosition = m_characterController.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());

		LastDVector = DifferenceVector;

		DifferenceVector = m_FrontWheelPosition - PastVector;
		if (DifferenceVector.x == 0.0f, DifferenceVector.y == 0.0f, DifferenceVector.z == 0.0f) {
			DifferenceVector = LastDVector;
		}
		//スタート時の視点の修正
		if (m_PauseState == -1 && AutoDriveState == false) {
			DifferenceVector = m_BackGround->GetStartForward();
		}
		DifferenceVector.Normalize();
		PastVector = m_FrontWheelPosition;
		//m_characterController.SetPosition({ m_FrontWheelPosition.x ,0.0f,m_FrontWheelPosition.z });

		//if (VelocityVector == 0.0f) {
		//	engine = NewGO<SoundSource>(0);
		//	engine->Init(3);
		//	engine->Play(false);
		//}
		//else {
		//	EngineSound = currentRPM / 6000.0f;
		//	engine_s = NewGO<SoundSource>(0);
		//	engine_s->Init(8);
		//	engine_s->SetFrequencyRatio(EngineSound);
		//	engine->Play(false);
		//}
		wchar_t Velocity[256];
		swprintf_s(Velocity, 256, L"%.0f\n", VelocityVector * 3600.0f * 2.5f / 1000.0f / 100.0f);
		VelocityFont.SetPosition(-130.0f, -330.0f, 0.0f);
		VelocityFont.SetPivot(0.0f, 0.5f);

		wchar_t Gear[256];
		swprintf_s(Gear, 256, L"%.0f\n", currentGear);
		GearFont.SetPosition(50.0f, -325.0f, 0.0f);
		GearFont.SetScale(1.5f);

		wchar_t DebugPos[256];
		swprintf_s(DebugPos, 256, L"%.0f:%.0f:%.0f\n", m_FrontWheelPosition.x, m_FrontWheelPosition.y, m_FrontWheelPosition.z);
		DebugPosFont.SetPosition(0.0f, 0.0f, 0.0f);
		DebugPosFont.SetText(DebugPos);

		wchar_t DebugForward[256];
		swprintf_s(DebugForward, 256, L"%.3f:%.3f:%.3f\n", m_FrontWheelForward.x, m_FrontWheelForward.y, m_FrontWheelForward.z);
		DebugFont.SetPosition(0.0f, -100.0f, 0.0f);
		DebugFont.SetText(DebugForward);
		
		//タコメーターの更新
		ScaleSpeed = VelocityVector * 3600.0f * 2.5f / 1000.0f / 100.0f;
		if (SpeedMeterPattern == 0) {
			speedneedlerot.SetRotationDegZ(106 - (ScaleSpeed * 0.8f));
		}
		else if (SpeedMeterPattern == 1) {
			speedneedlerot.SetRotationDegZ(106 - (ScaleSpeed * 0.625f));
		}
		else if (SpeedMeterPattern == 2) {
			speedneedlerot.SetRotationDegZ(106 - (ScaleSpeed * 0.488f));
		}
		else if (SpeedMeterPattern == 3) {
			speedneedlerot.SetRotationDegZ(106 - (ScaleSpeed * 0.392f));
		}
		SpeedNeedle.SetRotation(speedneedlerot);
		SpeedNeedle.Update();

		if (RPMMeterPattern == 0) {
			rpmneedlerot.SetRotationDegZ(95-(currentRPM*0.0222));
		}
		else if (RPMMeterPattern == 1) {
			rpmneedlerot.SetRotationDegZ(95 - (currentRPM * 0.01538));
		}
		else if (RPMMeterPattern == 2) {
			rpmneedlerot.SetRotationDegZ(95 - (currentRPM * 0.01333));
		}
		RPMNeedle.SetRotation(rpmneedlerot);
		RPMNeedle.Update();

		VelocityFont.SetText(Velocity);
		GearFont.SetText(Gear);
	}

}

void FrontWheelBase::Handling() {
	//スティックを倒した量の取得
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();

	Vector3 WheelRemit = Calc(m_FrontWheelRotation);

	if (stickL.x != 0.0f)
	{
		//if (WheelRemit.y >= -30.0f && WheelRemit.y <= 30.0f) {
			m_FrontWheelForward.x = m_FrontWheelForward.x * cos(stickL.x * -0.05) - m_FrontWheelForward.z * sin(stickL.x * -0.05);
			m_FrontWheelForward.z = m_FrontWheelForward.x * sin(stickL.x * -0.05) + m_FrontWheelForward.z * cos(stickL.x * -0.05);

			m_FrontWheelRotation.SetRotationY(atan2(m_FrontWheelForward.x, m_FrontWheelForward.z));
		//}
	}
}

void FrontWheelBase::Move() {

	//移動速度の初期化
	m_MoveSpeed = { 0.0f,0.0f,0.0f };

	//プレイヤーの正面ベクトルを正規化
	m_FrontWheelForward.Normalize();


	//xかzの移動速度があったら(スティックの入力があったら)。
	//回転処理
	Vector4 GetMember = { 0,0,0,0 };


	Handling();


	GetMember = Acceleration();

	velocity = RSpeed = GetMember.x;
	currentRPM = GetMember.y;
	currentGear = GetMember.z;
	acceleration = GetMember.w;
	
	
	//m_move = 4.0f * m_accelerator;
	m_MoveSpeed += m_FrontWheelForward  * RSpeed*5.0;


	//座標を教える。
	m_FrontWheelPosition = m_characterController.Execute(m_MoveSpeed, 1.0f / 60.0f);
	m_characterController.SetPosition({ m_FrontWheelPosition.x ,0.0f,m_FrontWheelPosition.z });
	
}

Vector4 FrontWheelBase::Acceleration() {
	//加減速計算処理

	

	//ブレーキ
	m_brake = 0.0f;

	m_brake = g_pad[0]->GetLTrigger();

	Vector4 GetMember = { 0,0,0,0 };
	//GetMember = m_caraformula->CarSpeed(data, SHIFT_UP_RPM_ADJUST, SHIFT_DOWN_RPM_ADJUST, currentRPM, velocity, mass, wheelRadius, grade, throttle_input, GEAR_RATIOS, currentGear, MaxGear,AirPressure,FinalGearRatio,Transmission_Efficiency,acceleration);

	//if (Speed > 320.0f) {
	//	Speed = 320;
	//	Rotation_Speed = 110;
	//	Gear = 7;
	//}
	//if (m_throttle!=0.0f)
	//{
	//	engine_s->SetVolume(1);
	//	engine_s->SetFrequencyRatio(e_s);
	//	
	//	//needlerot.SetRotationDegZ(Rotation_Speed * -2.0);
	//	//speedneedlerot.SetRotationDegZ(Speed * -0.65);
	//	
	//	if (Gear == 1 && Rotation_Speed <= 110) {
	//		Rotation_Speed += 3;
	//		Speed += 3;
	//		e_s += 0.025;

	//	}
	//	else if (Rotation_Speed < 105) {
	//		Rotation_Speed += (1.5f / Gear / 1.7) * 2.5;
	//		Speed += ((1.5f / Gear / 1.7) * 5.0);
	//		e_s += 0.01;
	//	}

	//}

	//else {
	//	engine_s->SetVolume(1);
	//	engine_s->SetFrequencyRatio(e_s);
	//	//speedneedlerot.SetRotationDegZ(Speed * -0.65);
	//	//needlerot.SetRotationDegZ(Rotation_Speed * -2.0);
	//	if (Gear > 1) {
	//		if (Speed > 0) {
	//			Speed -= 0.5;
	//			e_s -= 0.01;
	//		}
	//		if (Rotation_Speed > 0) {
	//			Rotation_Speed -= 0.5;
	//		}
	//	}
	//	else if (Gear == 1) {
	//		if (Speed > 0) {
	//			Speed -= 0.5;
	//			e_s -= 0.01;
	//		}
	//		if (Rotation_Speed > 0) {
	//			Rotation_Speed -= 0.5;
	//		}
	//	}

	//	if (Gear > 2 && Rotation_Speed < 70 && m_throttle == 0.0f) {
	//		Gear -= 1;
	//		Rotation_Speed = 100;
	//		e_s = 2;

	//	}
	//	else if (Gear == 2 && Rotation_Speed < 70 && m_throttle == 0.0f) {
	//		Gear -= 1;
	//		Speed = 100;
	//		Rotation_Speed = 100;
	//		e_s = 2;

	//	}
	//	if (Speed < 0) {
	//		Speed = 0;
	//	}
	//	if (Rotation_Speed < 18) {
	//		Rotation_Speed = 18;
	//		e_s = 1;

	//	}

	//}
	//if (Rotation_Speed > 105 && Gear < 7 ) {
	//	//speedneedlerot.SetRotationDegZ(Speed * -0.65);
	//	//needlerot.SetRotationDegZ(Rotation_Speed * -2.0);
	//	Gear += 1.0f;
	//	
	//	Rotation_Speed = 90;
	//	e_s = 1.81;

	//}
	////ブレーキ
	//if (m_brake!=0.0f && Speed > 0) {
	//	//speedneedlerot.SetRotationDegZ(Speed * -0.65);
	//	//needlerot.SetRotationDegZ(Rotation_Speed * -2.0);
	//	Rotation_Speed -= 2.5;
	//	Speed -= 2.5;

	//}

	//if (Rotation_Speed >= 17.5 && Rotation_Speed < 18.1) {
	//	engine->Init(3);
	//	engine->Play(true);
	//	engine->SetVolume(0.2);
	//}

	return GetMember;
}

void FrontWheelBase::Render(RenderContext& rc) {
	if (m_PauseState != 3) {
		DebugPosFont.Draw(rc);
		DebugFont.Draw(rc);
		VelocityFont.Draw(rc);
		GearFont.Draw(rc);
		UIBace.Draw(rc);
		RedZone.Draw(rc);
		RPMMeter.Draw(rc);
		SpeedMeter.Draw(rc);
		RPMNeedle.Draw(rc);
		SpeedNeedle.Draw(rc);
		RPMGage.Draw(rc);
		RPMCover.Draw(rc);
		ThrottleGage.Draw(rc);
		BrakeGage.Draw(rc);
		LapUI.Draw(rc);
	}
}
