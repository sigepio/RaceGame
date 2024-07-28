#include "stdafx.h"
#include "Sebring.h"

Sebring::Sebring() {
	
}

Sebring::~Sebring() {

}

bool Sebring::Start() {
	//�������̊m��
	m_groundModel = std::make_unique<ModelRender>();
	m_groundModel->Init("Assets/modelData/course/Sebring/CollisionObject.tkm", false);
	//m_groundModel->Init("Assets/modelData/course/Sebring/test.tkm", false);
	//m_groundModel->Init("Assets/modelData/course/test_track.tkm", false);
	//���f�����X�V����B
	m_groundModel->Update();
	//�ÓI�����I�u�W�F�N�g���쐬�B
	m_physicsStaticObject.CreateFromModel(m_groundModel->GetModel(), m_groundModel->GetModel().GetWorldMatrix());

	m_NonCollisionModel.Init("Assets/modelData/course/Sebring/NonCollisionObject.tkm", false);
	//m_NonCollisionModel.Init("Assets/modelData/course/Sebring/testnon.tkm", false);
	circuit_experience_time = {
		91.000f,
		92.500f,
		100.000f
	};

	return true;
}

void Sebring::Update() {
	if (GameEnd == true) {
		DeleteGO(this);
	}
	//���f���̍X�V�����B
	m_groundModel->Update();
}

void Sebring::Render(RenderContext& rc) {
	m_groundModel->SetAlwaysOnDisplay(true);
	m_NonCollisionModel.SetAlwaysOnDisplay(true);
	m_groundModel->Draw(rc);
	m_NonCollisionModel.Draw(rc);
}