#include "stdafx.h"
#include "GameCamera.h"
#include "Car_Oreca07.h"
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>
GameCamera::GameCamera() {
	
}

GameCamera::~GameCamera()
{

}

bool GameCamera::Start()
{

	//���_��ݒ�B
	m_toCameraPos.Set(0.0f, 50.0f, -200.0f);
	//m_toCameraPos.Set(0.0f, 0.0f, -5.0f);
	//�v���C���[�̃C���X�^���X��T���B
	m_carbase = FindGO<Car_Oreca07>("car_oreca07");

	//�J�����̃j�A�N���b�v�ƃt�@�[�N���b�v��ݒ肷��B
	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(100000.0f);

	return true;
}

void GameCamera::Update() {
	if (GameEnd == true) {
		DeleteGO(this);
	}
	if (m_PauseState == 0) {
		//�J�������X�V�B
		//�����_���v�Z����B
		//m_target = m_carbase->GetPosition();
		//�v���C���̑������炿����Ə�𒍎��_�Ƃ���B
		m_target.y += 50.0f;

		if (m_carbase->Returnm_throttle() != 0.0f) {
			Vector3 toCameraPosOld = m_toCameraPos;
			//�p�b�h�̓��͂��g���ăJ�������񂷁B
			float x = g_pad[0]->GetLStickXF();
			float y = g_pad[0]->GetRStickYF();
			//Y������̉�]
			/*Quaternion qRot;
			qRot.SetRotationDeg(Vector3::AxisY, RAngle);
			qRot.Apply(m_toCameraPos);*/
			//X������̉�]�B
			/*Vector3 axisX;
			axisX.Cross(Vector3::AxisY, m_toCameraPos);
			axisX.Normalize();
			qRot.SetRotationDeg(axisX, 1.3f * y);
			qRot.Apply(m_toCameraPos);*/
			//�J�����̉�]�̏�����`�F�b�N����B
			//�����_���王�_�܂ł̃x�N�g���𐳋K������B
			//���K������ƁA�x�N�g���̑傫�����P�ɂȂ�B
			//�傫�����P�ɂȂ�Ƃ������Ƃ́A�x�N�g�����狭�����Ȃ��Ȃ�A�����݂̂̏��ƂȂ�Ƃ������ƁB
			Vector3 toPosDir = m_toCameraPos;
			toPosDir.Normalize();
			if (toPosDir.y < -0.2f) {
				//�J����������������B
				m_toCameraPos = toCameraPosOld;
			}
			else if (toPosDir.y > 0.9f) {
				//�J�����������������B
				m_toCameraPos = toCameraPosOld;
			}
		}
		//���_���v�Z����B
		/*Quaternion m_CameraRot;
		float Angle = (std::acos(m_toCameraPos.Dot(m_carbase->GetForward()) / (m_toCameraPos.Length() * m_carbase->GetForward().Length()))) * 180.0 / M_PI;
		m_CameraRot.SetRotationDegY(Angle);
		m_CameraRot.Apply(m_toCameraPos);*/

		Vector3 pos = m_target + (DP * -1.0f);
		//���C���J�����ɒ����_�Ǝ��_��ݒ肷��B
		g_camera3D->SetTarget(m_target);
		g_camera3D->SetPosition(pos);

		//�J�����̍X�V�B
		g_camera3D->Update();
	}
}