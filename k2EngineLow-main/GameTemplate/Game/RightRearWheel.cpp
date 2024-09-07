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
	default:
		break;
	}
	return true;
}

void RightRearWheel::Update() {
	if (GameEnd == true) {
		DeleteGO(this);
	}
	if (m_PauseState == 0) {
		//���[�J���|�W�V������������
		Vector3 lp = m_LocalPosition;


		//�v���C���[�̉�]�ʂ�������
		Quaternion originRotation = m_frontwheelbase->GetRotation();


		//�v���C���[�̃|�W�V������������
		m_FrontWheelPosition = m_frontwheelbase->GetPosition();


		//��Z
		originRotation.Multiply(lp);


		//�|�W�V�����Ƀ��[�J���|�W�V�����𑫂�
		m_FrontWheelPosition += lp;


		//�ŏI�I�ȉ�]�ʂ�������
		m_FrontWheelRotation = originRotation;


		m_FrontWheelModel.SetPosition(m_FrontWheelPosition);
		m_FrontWheelModel.SetRotation(m_FrontWheelRotation);
		m_FrontWheelModel.Update();


		if (m_PauseState == 0) {
			Rotation();
		}
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
}