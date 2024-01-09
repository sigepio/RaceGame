#include "stdafx.h"
#include "FrontWheelBase.h"
#include "RightFrontWheel.h"
#include "LeftFrontWheel.h"
#include "sound/SoundEngine.h"
#include "CarAFormula.h"

FrontWheelBase::FrontWheelBase() {
	m_characterController.Init(70.0f, 150.0f, m_FrontWheelPosition);
}

FrontWheelBase::~FrontWheelBase() {

}

bool FrontWheelBase::Start() {
	
	currentRPM = IdolingRPM;

	m_caraformula = FindGO<CarAFormula>("caraformula");
	
	g_soundEngine->ResistWaveFileBank(3, "Assets/sound/FD3S_idling_v2.wav");
	g_soundEngine->ResistWaveFileBank(8, "Assets/sound/FD3S_3000RPM.wav");
	engine = NewGO<SoundSource>(0);
	engine_s = NewGO<SoundSource>(0);
	engine_s->Init(8);
	engine_s->Play(true);
	engine_s->SetVolume(0);
	return true;
}

void FrontWheelBase::Update() {
	

	//いったん凍結
	//Move();

	//アクセルボタンの入力量の取得
	m_throttle = 0.0f;

	//Rボタン
	throttle_input = g_pad[0]->GetRTrigger();

	//Lボタン
	brake_input = g_pad[0]->GetLTrigger();

	//計算結果を受け取る構造体の宣言
	SimulationResults ReturnSimulationResults;

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
		FrontWheelOrientationVector
		);
	
	m_FrontWheelPosition = ReturnSimulationResults.Position;
	VelocityVector = ReturnSimulationResults.VelocityVector;
	PitchAngle = ReturnSimulationResults.PitchAngle;
	RollAngle = ReturnSimulationResults.RollAngle;
	currentRPM = ReturnSimulationResults.CurrentRPM;
	Acceleration_DecelerationForce = ReturnSimulationResults.AllForce;
	AccelerationVector = ReturnSimulationResults.Acceleration;
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
	GetMember = m_caraformula->CarSpeed(data, SHIFT_UP_RPM_ADJUST, SHIFT_DOWN_RPM_ADJUST, currentRPM, velocity, mass, wheelRadius, grade, throttle_input, GEAR_RATIOS, currentGear, MaxGear,AirPressure,FinalGearRatio,Transmission_Efficiency,acceleration);

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
	
}
