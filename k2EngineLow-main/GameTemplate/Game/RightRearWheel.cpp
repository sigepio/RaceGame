#include "stdafx.h"
#include "RightRearWheel.h"
#include "FrontWheelBase.h"
#include "CarData.h"

RightRearWheel::RightRearWheel() {

}

RightRearWheel::~RightRearWheel() {

}

bool RightRearWheel::Start() {
	m_frontwheelbase = FindGO<FrontWheelBase>("frontwheelbase");
	switch (m_NowCar)
	{
	case AE86:
		m_FrontWheelModel.Init("Assets/modelData/Car/AE86_Right.tkm");
		break;
	default:
		break;
	}

	return true;
}

void RightRearWheel::Update() {
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