#include "stdafx.h"
#include "RightRearWheel.h"
#include "FrontWheelBase.h"
#include "Player.h"
#include "PageNum.h"

RightRearWheel::RightRearWheel() {

}

RightRearWheel::~RightRearWheel() {

}

bool RightRearWheel::Start() {
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
		m_FrontWheelModel.Init("Assets/modelData/Car/LFA/TyreRolLeftRear.tkm");
		m_NonRFrontWheelModel.Init("Assets/modelData/Car/LFA/TyreLeftRear.tkm");
		BreakState = true;
		break;
	case FordMustangGT3:
		m_FrontWheelModel.Init("Assets/modelData/Car/MustangGT3/TyreRolLeftRear.tkm");
		m_NonRFrontWheelModel.Init("Assets/modelData/Car/MustangGT3/TyreLeftRear.tkm");
		BreakState = true;
		break;
	case NissanR35GT3:
		m_FrontWheelModel.Init("Assets/modelData/Car/R35GT3/TyreRolLeftRear.tkm");
		m_NonRFrontWheelModel.Init("Assets/modelData/Car/R35GT3/TyreLeftRear.tkm");
		BreakState = true;
		break;
	case FordGTLMRaceCarSpecii:
		m_FrontWheelModel.Init("Assets/modelData/Car/FordGTLM/TyreRolLeftRear.tkm");
		m_NonRFrontWheelModel.Init("Assets/modelData/Car/FordGTLM/TyreLeftRear.tkm");
		BreakState = true;
		break;
	case FordGTGT3GTE:
		m_FrontWheelModel.Init("Assets/modelData/Car/FordGTGT3/TyreRolLeftRear.tkm");
		m_NonRFrontWheelModel.Init("Assets/modelData/Car/FordGTGT3/TyreLeftRear.tkm");
		BreakState = true;
		break;
	case FordGT2006:
		m_FrontWheelModel.Init("Assets/modelData/Car/FordGT/TyreRolLeftRear.tkm");
		m_NonRFrontWheelModel.Init("Assets/modelData/Car/FordGT/TyreLeftRear.tkm");
		BreakState = true;
		break;
	case SauberMercedesC9:
		m_FrontWheelModel.Init("Assets/modelData/Car/C9/TyreRolLeftRear.tkm");
		m_NonRFrontWheelModel.Init("Assets/modelData/Car/C9/TyreLeftRear.tkm");
		BreakState = true;
		break;
	case BMWMHybridV8:
		m_FrontWheelModel.Init("Assets/modelData/Car/BMWMV8LMDh/TyreRolRightRear.tkm");
		m_NonRFrontWheelModel.Init("Assets/modelData/Car/BMWMV8LMDh/TyreRightRear.tkm");
		BreakState = true;
		break;
	case Porsche962C:
		m_FrontWheelModel.Init("Assets/modelData/Car/962C/TyreRolLeftRear.tkm");
		m_NonRFrontWheelModel.Init("Assets/modelData/Car/962C/TyreLeftRear.tkm");
		BreakState = true;
		break;
	case Porsche911GT3RSR:
		m_FrontWheelModel.Init("Assets/modelData/Car/911GT3RSR/TyreRolLeftRear.tkm");
		m_NonRFrontWheelModel.Init("Assets/modelData/Car/911GT3RSR/TyreLeftRear.tkm");
		BreakState = true;
		break;
	case Porsche911GT3RS:
		m_FrontWheelModel.Init("Assets/modelData/Car/911GT3RS/TyreRolLeftRear.tkm");
		m_NonRFrontWheelModel.Init("Assets/modelData/Car/911GT3RS/TyreLeftRear.tkm");
		BreakState = true;
		break;
	case Mazda787B:
		m_FrontWheelModel.Init("Assets/modelData/Car/787B/TyreRolLeftRear.tkm");
		m_NonRFrontWheelModel.Init("Assets/modelData/Car/787B/TyreLeftRear.tkm");
		BreakState = true;
		break;

	case Ferrari499P:
		m_FrontWheelModel.Init("Assets/modelData/Car/499P/TyreRolRightRear.tkm");
		m_NonRFrontWheelModel.Init("Assets/modelData/Car/499P/TyreRightRear.tkm");
		BreakState = true;
		break;
	case RedBullRB19:
		m_FrontWheelModel.Init("Assets/modelData/Car/RB19/TyreRolLeftRear.tkm");
		break;
	case RedBullX2010:
		m_FrontWheelModel.Init("Assets/modelData/Car/X2010/TyreRolLeftRear.tkm");
		break;
	case TOYOTAGR010HYBRID:
		m_FrontWheelModel.Init("Assets/modelData/Car/GR010/TyreRolLeftRear.tkm");
		m_NonRFrontWheelModel.Init("Assets/modelData/Car/GR010/TyreLeftRear.tkm");
		BreakState = true;
		break;
	case TOYOTATS050HYBRID:
		m_FrontWheelModel.Init("Assets/modelData/Car/TS050/TyreRolLeftRear.tkm");
		m_NonRFrontWheelModel.Init("Assets/modelData/Car/TS050/TyreLeftRear.tkm");
		BreakState = true;
		break;
	default:
		break;
	}
	return true;
}

void RightRearWheel::Update() {
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

	if (m_PauseState == 0 || m_PauseState == -1) {
		Rotation();
	}
}

void RightRearWheel::Rotation() {
	m_FrontWheelRotationRotation.AddRotationDegX(m_frontwheelbase->GetTireRotation());
	m_FrontWheelRotation *= m_FrontWheelRotationRotation;
	m_FrontWheelModel.SetRotation(m_FrontWheelRotation);
	m_FrontWheelModel.Update();
}

void RightRearWheel::Render(RenderContext& rc) {
	m_FrontWheelModel.SetAlwaysOnDisplay(true);
	m_FrontWheelModel.Draw(rc);
	if (BreakState == true) {
		m_NonRFrontWheelModel.SetAlwaysOnDisplay(true);
		m_NonRFrontWheelModel.Draw(rc);
	}
}