#include "stdafx.h"
#include "RightFrontWheel.h"
#include "FrontWheelBase.h"
#include "Player.h"
#include "PageNum.h"

RightFrontWheel::RightFrontWheel() {

}

RightFrontWheel::~RightFrontWheel() {

}

bool RightFrontWheel::Start() {
	m_frontwheelbase = FindGO<FrontWheelBase>("frontwheelbase");
	
	m_player = FindGO<Player>("player");
	switch (m_player->GetCarNum())
	{
	case ORECA07:
		m_FrontWheelModel.Init("Assets/modelData/Car/LMP2_Left.tkm");
		break;
	case TOYOTA86GT:
		m_FrontWheelModel.Init("Assets/modelData/Car/86GT/Tyre_Right.tkm");
		break;
	case TOYOTA90Supra:
		m_FrontWheelModel.Init("Assets/modelData/Car/A90Supra/Tyre_Right.tkm");
		break;
	case NissanGTR_17:
		m_FrontWheelModel.Init("Assets/modelData/Car/R35/Tyre_Right.tkm");
		break;
	case MazdaRX_7FD3SSpiritRTypeA:
		m_FrontWheelModel.Init("Assets/modelData/Car/FD3S/Tyre_Right.tkm");
		break;

	case LexusLFA:
		m_FrontWheelModel.Init("Assets/modelData/Car/LFA/TyreRolLeftFront.tkm");
		m_NonRFrontWheelModel.Init("Assets/modelData/Car/LFA/TyreLeftFront.tkm");
		BreakState = true;
		break;
	case FordMustangGT3:
		m_FrontWheelModel.Init("Assets/modelData/Car/MustangGT3/TyreRolLeftFront.tkm");
		m_NonRFrontWheelModel.Init("Assets/modelData/Car/MustangGT3/TyreLeftFront.tkm");
		BreakState = true;
		break;
	case NissanR35GT3:
		m_FrontWheelModel.Init("Assets/modelData/Car/R35GT3/TyreRolLeftFront.tkm");
		m_NonRFrontWheelModel.Init("Assets/modelData/Car/R35GT3/TyreLeftFront.tkm");
		BreakState = true;
		break;
	case FordGTLMRaceCarSpecii:
		m_FrontWheelModel.Init("Assets/modelData/Car/FordGTLM/TyreRolLeftFront.tkm");
		m_NonRFrontWheelModel.Init("Assets/modelData/Car/FordGTLM/TyreLeftFront.tkm");
		BreakState = true;
		break;
	case FordGTGT3GTE:
		m_FrontWheelModel.Init("Assets/modelData/Car/FordGTGT3/TyreRolLeftFront.tkm");
		m_NonRFrontWheelModel.Init("Assets/modelData/Car/FordGTGT3/TyreLeftFront.tkm");
		BreakState = true;
		break;
	case FordGT2006:
		m_FrontWheelModel.Init("Assets/modelData/Car/FordGT/TyreRolLeftFront.tkm");
		m_NonRFrontWheelModel.Init("Assets/modelData/Car/FordGT/TyreLeftFront.tkm");
		BreakState = true;
		break;
	case SauberMercedesC9:
		m_FrontWheelModel.Init("Assets/modelData/Car/C9/TyreRolLeftFront.tkm");
		m_NonRFrontWheelModel.Init("Assets/modelData/Car/C9/TyreLeftFront.tkm");
		BreakState = true;
		break;
	case BMWMHybridV8:
		m_FrontWheelModel.Init("Assets/modelData/Car/BMWMV8LMDh/TyreRolRightFront.tkm");
		m_NonRFrontWheelModel.Init("Assets/modelData/Car/BMWMV8LMDh/TyreRightFront.tkm");
		BreakState = true;
		break;
	case Porsche962C:
		m_FrontWheelModel.Init("Assets/modelData/Car/962C/TyreRolLeftFront.tkm");
		m_NonRFrontWheelModel.Init("Assets/modelData/Car/962C/TyreLeftFront.tkm");
		BreakState = true;
		break;
	case Porsche911GT3RSR:
		m_FrontWheelModel.Init("Assets/modelData/Car/911GT3RSR/TyreRolLeftFront.tkm");
		m_NonRFrontWheelModel.Init("Assets/modelData/Car/911GT3RSR/TyreLeftFront.tkm");
		BreakState = true;
		break;
	case Porsche911GT3RS:
		m_FrontWheelModel.Init("Assets/modelData/Car/911GT3RS/TyreRolLeftFront.tkm");
		m_NonRFrontWheelModel.Init("Assets/modelData/Car/911GT3RS/TyreLeftFront.tkm");
		BreakState = true;
		break;
	case Mazda787B:
		m_FrontWheelModel.Init("Assets/modelData/Car/787B/TyreRolLeftFront.tkm");
		m_NonRFrontWheelModel.Init("Assets/modelData/Car/787B/TyreLeftFront.tkm");
		BreakState = true;
		break;
	case Ferrari499P:
		m_FrontWheelModel.Init("Assets/modelData/Car/499P/TyreRolRightFront.tkm");
		m_NonRFrontWheelModel.Init("Assets/modelData/Car/499P/TyreRightFront.tkm");
		BreakState = true;
		break;
	case RedBullRB19:
		m_FrontWheelModel.Init("Assets/modelData/Car/RB19/TyreRolLeftFront.tkm");
		break;
	case RedBullX2010:
		m_FrontWheelModel.Init("Assets/modelData/Car/X2010/TyreRolLeftFront.tkm");
		break;
	case TOYOTAGR010HYBRID:
		m_FrontWheelModel.Init("Assets/modelData/Car/GR010/TyreRolLeftFront.tkm");
		m_NonRFrontWheelModel.Init("Assets/modelData/Car/GR010/TyreLeftFront.tkm");
		BreakState = true;
		break;
	case TOYOTATS050HYBRID:
		m_FrontWheelModel.Init("Assets/modelData/Car/TS050/TyreRolLeftFront.tkm");
		m_NonRFrontWheelModel.Init("Assets/modelData/Car/TS050/TyreLeftFront.tkm");
		BreakState = true;
		break;
	default:
		break;
	}

	

	return true;
}

void RightFrontWheel::Update() {
	if (GameEnd == true) {
		DeleteGO(this);
	}
	
		//ローカルポジションを教える
		Vector3 lp = m_LocalPosition;


		//プレイヤーの回転量を教える
		Quaternion originRotation = m_frontwheelbase->GetRotation();


		//プレイヤーのポジションを教える
		m_FrontWheelPosition = m_frontwheelbase->GetPosition();


		//乗算
		originRotation.Multiply(lp);


		//ポジションにローカルポジションを足す
		m_FrontWheelPosition += lp;


		//最終的な回転量を教える
		m_FrontWheelRotation = originRotation;


		m_FrontWheelModel.SetPosition(m_FrontWheelPosition);
		m_FrontWheelModel.SetRotation(m_FrontWheelRotation);
		m_FrontWheelModel.Update();


		m_NonRFrontWheelModel.SetPosition(m_FrontWheelPosition);
		m_NonRFrontWheelModel.SetRotation(m_FrontWheelRotation);
		m_NonRFrontWheelModel.Update();
		//Move();
		
		if (m_PauseState == 0 || m_PauseState == -1) {
			Rotation();
		}
}

void RightFrontWheel::Move() {

	//スティックを倒した量の取得
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();

	Vector3 WheelRemit = Calc(m_FrontWheelLocalRotation);

	if (g_pad[0]->GetLStickXF() != 0.0f) {
		Vector3 FlontWheelAngle = Calc(m_FrontWheelLocalRotation);
		if (stickL.x > 0.0f) {
			if (stickL.x < LsatStickL.x) {
				if (FlontWheelAngle.y <= stickL.x * 30.0f) {
					m_FrontWheelForward.x = m_FrontWheelForwardCatch.x * cos(stickL.x * 0.01) - m_FrontWheelForwardCatch.z * sin(stickL.x * 0.01);
					m_FrontWheelForward.z = m_FrontWheelForwardCatch.x * sin(stickL.x * 0.01) + m_FrontWheelForwardCatch.z * cos(stickL.x * 0.01);

					m_FrontWheelLocalRotation.SetRotationY(atan2(m_FrontWheelForward.x, m_FrontWheelForward.z));
				}
			}
			else {
				if (FlontWheelAngle.y >= stickL.x * -30.0f && FlontWheelAngle.y <= stickL.x * 30.0f) {
					m_FrontWheelForward.x = m_FrontWheelForwardCatch.x * cos(stickL.x * -0.05) - m_FrontWheelForwardCatch.z * sin(stickL.x * -0.05);
					m_FrontWheelForward.z = m_FrontWheelForwardCatch.x * sin(stickL.x * -0.05) + m_FrontWheelForwardCatch.z * cos(stickL.x * -0.05);

					m_FrontWheelLocalRotation.SetRotationY(atan2(m_FrontWheelForward.x, m_FrontWheelForward.z));
				}
			}
		}
		else {
			if (stickL.x > LsatStickL.x) {
				if (FlontWheelAngle.y >= stickL.x * 30.0f) {
					m_FrontWheelForward.x = m_FrontWheelForwardCatch.x * cos(stickL.x * 0.01) - m_FrontWheelForwardCatch.z * sin(stickL.x * 0.01);
					m_FrontWheelForward.z = m_FrontWheelForwardCatch.x * sin(stickL.x * 0.01) + m_FrontWheelForwardCatch.z * cos(stickL.x * 0.01);

					m_FrontWheelLocalRotation.SetRotationY(atan2(m_FrontWheelForward.x, m_FrontWheelForward.z));
				}
			}
			else {
				if (FlontWheelAngle.y <= stickL.x * -30.0f && FlontWheelAngle.y >= stickL.x * 30.0f) {
					m_FrontWheelForward.x = m_FrontWheelForwardCatch.x * cos(stickL.x * -0.05) - m_FrontWheelForwardCatch.z * sin(stickL.x * -0.05);
					m_FrontWheelForward.z = m_FrontWheelForwardCatch.x * sin(stickL.x * -0.05) + m_FrontWheelForwardCatch.z * cos(stickL.x * -0.05);

					m_FrontWheelLocalRotation.SetRotationY(atan2(m_FrontWheelForward.x, m_FrontWheelForward.z));
				}
			}
		}
		m_FrontWheelRotation *= m_FrontWheelLocalRotation;
		m_FrontWheelModel.SetPosition(m_FrontWheelPosition);
		m_FrontWheelModel.SetRotation(m_FrontWheelRotation);
		m_FrontWheelModel.Update();

	}
	else {
		m_FrontWheelLocalRotation = m_FrontWheelRotation;
		m_FrontWheelForward = m_FrontWheelForwardCatch;
	}



	LsatStickL.x = stickL.x;
}

void RightFrontWheel::Rotation() {
		m_FrontWheelRightRotation.AddRotationDegX(m_frontwheelbase->GetTireRotation());
		m_FrontWheelRotation *= m_FrontWheelRightRotation;
		m_FrontWheelModel.SetRotation(m_FrontWheelRotation);
		m_FrontWheelModel.Update();
}

void RightFrontWheel::Render(RenderContext& rc) {
	m_FrontWheelModel.SetAlwaysOnDisplay(true);
	m_FrontWheelModel.Draw(rc);
	if (BreakState == true) {
		m_NonRFrontWheelModel.SetAlwaysOnDisplay(true);
		m_NonRFrontWheelModel.Draw(rc);
	}
}