#include "stdafx.h"
#include "Menu.h"
#include "TimeTrialMode.h"
#include "WorldMode.h"

Menu::Menu() {

}

Menu::~Menu() {

}
bool Menu::Start() {
	
	return true;
}

void Menu::Update() {
	switch (SelectNow)
	{
	case 0:
		if (g_pad[0]->IsTrigger(enButtonA)) {
			m_worldmode = NewGO<WorldMode>(0, "worldmode");
			DeleteGO(this);
		}
		if (g_pad[0]->IsTrigger(enButtonRight)) {
			SelectNow = 1;
		}
		break;
	case 1:
		if (g_pad[0]->IsTrigger(enButtonA)) {
			m_timetrialmode = NewGO<TimeTrialMode>(0, "timetrialmode");
			DeleteGO(this);
		}
		break;
	default:
		break;
	}
}

void Menu::Render(RenderContext& rc) {

}