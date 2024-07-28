#include "stdafx.h"
#include "LeMans.h"

LeMans::LeMans() {

}

LeMans::~LeMans() {

}

bool LeMans::Start() {
	//メモリの確保
	m_groundModel = std::make_unique<ModelRender>();
	m_groundModel->Init("Assets/modelData/course/LeMans/GroundObject.tkm", false);
	m_CollisionModel = std::make_unique<ModelRender>();
	m_CollisionModel->Init("Assets/modelData/course/LeMans/CollisionObject.tkm", false);
	m_CollisionAlphaBlendModel = std::make_unique<ModelRender>();
	m_CollisionAlphaBlendModel->Init("Assets/modelData/course/LeMans/CollisionAlphaBlendObject.tkm", false, AlphaBlendMode_Trans);

	//m_groundModel->Init("Assets/modelData/course/Sebring/test.tkm", false);
	//m_groundModel->Init("Assets/modelData/course/test_track.tkm", false);
	//モデルを更新する。
	m_groundModel->Update();
	m_CollisionModel->Update();
	m_CollisionAlphaBlendModel->Update();
	//静的物理オブジェクトを作成。
	m_physicsStaticObject.CreateFromModel(m_groundModel->GetModel(), m_groundModel->GetModel().GetWorldMatrix());
	m_CollisionModelphysicsStaticObject.CreateFromModel(m_CollisionModel->GetModel(), m_CollisionModel->GetModel().GetWorldMatrix());
	m_CollisionAlphaBlendModelphysicsStaticObject.CreateFromModel(m_CollisionAlphaBlendModel->GetModel(), m_CollisionAlphaBlendModel->GetModel().GetWorldMatrix());

	m_NonCollisionModel.Init("Assets/modelData/course/LeMans/NonCollisionObject.tkm", false);
	m_NonCollisionAlphaBlendModel.Init("Assets/modelData/course/LeMans/NonCollisionAlphaBlendObject.tkm", false, AlphaBlendMode_Trans);
	m_NonCollisionAdvertisementModel.Init("Assets/modelData/course/LeMans/NonCollisionAdvertisementObject.tkm", false);
	TreeModel.Init("Assets/modelData/course/LeMans/Tree.tkm", false, AlphaBlendMode_Trans);
	//m_NonCollisionModel.Init("Assets/modelData/course/Sebring/testnon.tkm", false);
	circuit_experience_time = {
		91.000f,
		92.500f,
		100.000f
	};

	return true;
}

void LeMans::Update() {
	if (GameEnd == true) {
		DeleteGO(this);
	}
	//モデルの更新処理。
	m_groundModel->Update();
	m_CollisionModel->Update();
}

void LeMans::Render(RenderContext& rc) {
	m_groundModel->SetAlwaysOnDisplay(true);
	m_CollisionModel->SetAlwaysOnDisplay(true);
	m_NonCollisionModel.SetAlwaysOnDisplay(true);
	m_CollisionAlphaBlendModel->SetAlwaysOnDisplay(true);
	m_NonCollisionAlphaBlendModel.SetAlwaysOnDisplay(true);
	TreeModel.SetAlwaysOnDisplay(true);
	
	m_groundModel->Draw(rc);
	TreeModel.Draw(rc);
	m_CollisionModel->Draw(rc);
	m_CollisionAlphaBlendModel->Draw(rc);
	m_NonCollisionModel.Draw(rc);
	m_NonCollisionAdvertisementModel.Draw(rc);
	m_NonCollisionAlphaBlendModel.Draw(rc);
}