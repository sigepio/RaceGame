#include "stdafx.h"
#include "Title.h"
#include "PageNum.h"
#include "Menu.h"
#include "TimeTrialMode.h"
#include "Loading.h"
#include "Sound.h"
Title::Title() {

}
Title::~Title() {

}
bool Title::Start() {
	m_Sound = NewGO<Sound>(0,"sound");

	m_TitleSprite.Init("Assets/sprite/Title/Title_Logo.DDS", 960.0f, 540.0f);
	m_PressStartSprite.Init("Assets/sprite/Title/Press_any_button.DDS", 1920.0f, 1080.0f);
	m_FadeSprite.Init("Assets/Sprite/BlackOut.DDS", 1600.0f, 900.0f);
	
	m_PressStartSprite.SetMulColor(m_PressStartSpriteColor);
	m_FadeSprite.SetMulColor(m_FadeColor);

	return true;
}
void Title::Update() {
	if (m_PressColorTime % 100 == 0) {
		m_PressDirection *= -1;
	}
	
	m_PressStartSpriteColor.w -= 0.01 * m_PressDirection;
	m_PressStartSprite.SetMulColor(m_PressStartSpriteColor);
	
	if (g_pad[0]->IsTrigger(enButtonA)) {
		//TimeTrialMode* m_timetrialmode = NewGO<TimeTrialMode>(0, "timetrialmode");
		FadeState = 1;
		
	}

	if (FadeState == 1) {
		if (FadeCount > 5) {
			m_loading = NewGO<Loading>(10, "loading");
			m_loading->SetWhereCome(TitlePage);
			DeleteGO(this);
		}
		else {
			m_FadeColor.w += 0.2f;
			m_FadeSprite.SetMulColor(m_FadeColor);
			FadeCount++;
		}
	}

	m_PressColorTime++;
	m_PressStartSprite.Update();
}
void Title::Render(RenderContext& rc) {
	m_TitleSprite.Draw(rc);
	m_PressStartSprite.Draw(rc);
}