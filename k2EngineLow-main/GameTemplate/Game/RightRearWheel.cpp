#include "stdafx.h"
#include "RightRearWheel.h"
#include "FrontWheelBase.h"

RightRearWheel::RightRearWheel() {

}

RightRearWheel::~RightRearWheel() {

}

bool RightRearWheel::Start() {
	m_frontwheelbase = FindGO<FrontWheelBase>("frontwheelbase");

	return true;
}

void RightRearWheel::Update() {
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

		Rotation();
	}
}

void RightRearWheel::Rotation() {
	if (m_frontwheelbase->Getm_Speed() != 0) {
		m_FrontWheelRotationRotation.AddRotationDegX(m_frontwheelbase->Getm_Speed());
		m_FrontWheelRotation *= m_FrontWheelRotationRotation;
		m_FrontWheelModel.SetRotation(m_FrontWheelRotation);
		m_FrontWheelModel.Update();
	}
}

void RightRearWheel::Render(RenderContext& rc) {
	m_FrontWheelModel.Draw(rc);
}