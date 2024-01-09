#include "stdafx.h"
#include "RaceMenu.h"
#include "MainRaceManager.h"

RaceMenu::RaceMenu() {

}

RaceMenu::~RaceMenu() {

}

bool RaceMenu::Start() {

	return true;
}

void RaceMenu::Update() {
	if (g_pad[0]->IsTrigger(enButtonA)) {
		m_mainracemanager = NewGO<MainRaceManager>(0, "mainracemanager");
		DeleteGO(this);
	}
}

void RaceMenu::Render(RenderContext& rc) {

}