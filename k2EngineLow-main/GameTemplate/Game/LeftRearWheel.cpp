#include "stdafx.h"
#include "LeftRearWheel.h"
#include "FrontWheelBase.h"
#include "Player.h"
#include "PageNum.h"

LeftRearWheel::LeftRearWheel() {
}

LeftRearWheel::~LeftRearWheel() {

}

bool LeftRearWheel::Start() {
	m_frontwheelbase = FindGO<FrontWheelBase>("frontwheelbase");
	m_player = FindGO<Player>("player");
	switch (m_player->GetCarNum())
	{
	case ORECA07:
		m_FrontWheelModel.Init("Assets/modelData/Car/LMP2_Right.tkm");
		break;
	case TOYOTA86GT:
		m_FrontWheelModel.Init("Assets/modelData/Car/86GT/Tyre_Left.tkm");
		break;
	case TOYOTA90Supra:
		m_FrontWheelModel.Init("Assets/modelData/Car/A90Supra/Tyre_Left.tkm");
		break;
	case NissanGTR_17:
		m_FrontWheelModel.Init("Assets/modelData/Car/R35/Tyre_Left.tkm");
		break;
	case MazdaRX_7FD3SSpiritRTypeA:
		m_FrontWheelModel.Init("Assets/modelData/Car/FD3S/Tyre_Left.tkm");
		break;
	default:
		break;
	}

	return true;
}

void LeftRearWheel::Update() {
	if (GameEnd == true) {
		DeleteGO(this);
	}
	if (m_PauseState == 0) {
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

		if (m_PauseState == 0) {
			//Move();
			Rotation();
		}
	}
}

void LeftRearWheel::Rotation() {
	m_FrontWheelRotationRotation.AddRotationDegX(m_frontwheelbase->GetTireRotation());
	m_FrontWheelRotation *= m_FrontWheelRotationRotation;
	m_FrontWheelModel.SetRotation(m_FrontWheelRotation);
	m_FrontWheelModel.Update();
}

void LeftRearWheel::Render(RenderContext& rc) {
	m_FrontWheelModel.SetAlwaysOnDisplay(true);
	m_FrontWheelModel.Draw(rc);
}
