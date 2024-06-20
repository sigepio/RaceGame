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
	//モデルを更新する。
	m_groundModel->Update();
	//静的物理オブジェクトを作成。
	m_physicsStaticObject.CreateFromModel(m_groundModel->GetModel(), m_groundModel->GetModel().GetWorldMatrix());

	m_NonCollisionModel.Init("Assets/modelData/course/Sebring/NonCollisionObject.tkm", false);

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
	m_groundModel->Draw(rc);
	m_NonCollisionModel.Draw(rc);
}