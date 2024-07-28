#include "stdafx.h"
#include "Sebring.h"

Sebring::Sebring() {
	
}

Sebring::~Sebring() {

}

bool Sebring::Start() {
	//メモリの確保
	m_groundModel = std::make_unique<ModelRender>();
	m_groundModel->Init("Assets/modelData/course/Sebring/CollisionObject.tkm", false);
	//m_groundModel->Init("Assets/modelData/course/Sebring/test.tkm", false);
	//m_groundModel->Init("Assets/modelData/course/test_track.tkm", false);
	//モデルを更新する。
	m_groundModel->Update();
	//静的物理オブジェクトを作成。
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
	//モデルの更新処理。
	m_groundModel->Update();
}

void Sebring::Render(RenderContext& rc) {
	m_groundModel->SetAlwaysOnDisplay(true);
	m_NonCollisionModel.SetAlwaysOnDisplay(true);
	m_groundModel->Draw(rc);
	m_NonCollisionModel.Draw(rc);
}