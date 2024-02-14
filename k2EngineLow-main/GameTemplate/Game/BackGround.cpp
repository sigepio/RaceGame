#include "stdafx.h"
#include "BackGround.h"

BackGround::BackGround()
{

}

BackGround::~BackGround()
{

}
bool BackGround::Start()
{
	//�������̊m��
	m_groundModel = std::make_unique<ModelRender>();


	//���f����ǂݍ��ށB
	m_groundModel->Init("Assets/modelData/course/test_track.tkm", false);
	
	//���f�����X�V����B
	m_groundModel->Update();
	//�ÓI�����I�u�W�F�N�g���쐬�B
	m_physicsStaticObject.CreateFromModel(m_groundModel->GetModel(), m_groundModel->GetModel().GetWorldMatrix());
	// �����蔻���L��������B
	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	//m_courseparts = NewGO<CourseParts>(0, "courseparts");
	return true;
}
void BackGround::Update()
{
	//���f���̍X�V�����B
	m_groundModel->Update();
}

void BackGround::Render(RenderContext& rc)
{
	m_groundModel->Draw(rc);
}