#include "stdafx.h"
#include "LeftRearWheel.h"
#include "FrontWheelBase.h"
#include "CarData.h"

LeftRearWheel::LeftRearWheel() {
}

LeftRearWheel::~LeftRearWheel() {

}

bool LeftRearWheel::Start() {
	m_frontwheelbase = FindGO<FrontWheelBase>("frontwheelbase");

	switch (m_NowCar)
	{
	case AE86:
		m_FrontWheelModel.Init("Assets/modelData/Car/AE86_Left.tkm");
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

		Rotation();
	}
}

void LeftRearWheel::Rotation() {
	if (m_frontwheelbase->Getm_Speed() != 0) {
		m_FrontWheelRotationRotation.AddRotationDegX(m_frontwheelbase->Getm_Speed());
		m_FrontWheelRotation *= m_FrontWheelRotationRotation;
		m_FrontWheelModel.SetRotation(m_FrontWheelRotation);
		m_FrontWheelModel.Update();
	}
}

void LeftRearWheel::Render(RenderContext& rc) {
	m_FrontWheelModel.Draw(rc);
}
