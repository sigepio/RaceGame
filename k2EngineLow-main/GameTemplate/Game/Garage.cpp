#include "stdafx.h"
#include "Garage.h"
#include "vector"
#include "GameCamera.h"
#include "Loading.h"
#include "PageNum.h"
#include "Player.h"
#include "Lighting.h"

Garage::Garage() {

}

Garage::~Garage() {

}

bool Garage::Start() {

	m_Player = FindGO<Player>("player");
	m_GameCamera = NewGO<GameCamera>(0, "gamecamera");
	m_Lighting = NewGO<Lighting>(0, "lighting");


	RideCarNum = m_Player->GetCarNum();
	PossessionCar = m_Player->GetPossessionCar();

	BaseModel.Init("Assets/modelData/Car/Garage/Base/Garage.tkm");
	NowCarModel.Init("Assets/modelData/Car/Garage/ORECA07/ORECA07.tkm");
	Rotation.SetRotationDegY(290.0f);
	NowCarModel.SetRotation(Rotation);
	NowCarModel.Update();
	return true;
}

void Garage::Update() {
	/*if (FadeCount < 5) {

		BlackOutColor.w -= 0.2f;
		FadeSprite.SetMulColor(BlackOutColor);
		FadeCount++;
	}
	else {
		if (g_pad[0]->IsPress(enButtonB)) {
			m_Loading = NewGO<Loading>(10, "loading");
			m_Loading->SetWhereCome(GaragePage);
			m_Loading->SetWhereGo(WorldMenuPage);
			DeleteGO(m_GameCamera);
			DeleteGO(this);
		}
	}*/
}

void Garage::Render(RenderContext& rc) {
	BaseModel.Draw(rc);
	NowCarModel.Draw(rc);
}