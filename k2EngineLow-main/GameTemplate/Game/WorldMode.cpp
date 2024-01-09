#include "stdafx.h"
#include "WorldMode.h"
#include "RaceMenu.h"

WorldMode::WorldMode() {
	SelectState = 0;
}

WorldMode::~WorldMode() {

}

bool WorldMode::Start() {
	TestSprite.Init("Assets/Sprite/MyHome/MyHome.DDS", 1632.0f,918.0f);
	return true;
}

void WorldMode::Update() {
	switch (SelectState)
	{
	case 0:
		if (g_pad[0]->IsTrigger(enButtonA)) {

		}
		if (g_pad[0]->IsTrigger(enButtonRight)) {
			SelectState = 1;
		}
		break;
	case 1:
		if (g_pad[0]->IsTrigger(enButtonA)) {
			m_racemenu = NewGO<RaceMenu>(0, "racemenu");
			DeleteGO(this);
		}
	default:
		break;
	}
}

void WorldMode::Render(RenderContext& rc) {
	TestSprite.Draw(rc);
}