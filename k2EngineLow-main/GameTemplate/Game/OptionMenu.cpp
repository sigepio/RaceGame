#include "stdafx.h"
#include "OptionMenu.h"
#include "Player.h"
#include "Loading.h"
#include "PageNum.h"
#include "Sound.h"

OptionMenu::OptionMenu() {

}

OptionMenu::~OptionMenu() {

}

bool OptionMenu::Start() {
	m_player = FindGO<Player>("player");
	BGMVolume = m_player->GetBGMVolume();
	SEVolume = m_player->GetSEVolume();
	EngineSoundVolume = m_player->GetEngineSoundVolume();
	Transmission = m_player->GetTransmission();
	Sound* mSound = FindGO<Sound>("sound");

	//画像の読み込み
	BaseSprite.Init("Assets/Sprite/Option/Base.DDS", 1600.0f, 900.0f);
	SelectSprite.Init("Assets/Sprite/Option/Select.DDS", 17.0f, 47.0f);
	MainSprite.Init("Assets/Sprite/Option/Main.DDS", 1600.0f, 900.0f);
	TransmissionSprite.Init("Assets/Sprite/Option/Transmission.DDS", 1600.0f, 900.0f);
	SoundSprite.Init("Assets/Sprite/Option/Sound.DDS", 1600.0f, 900.0f);
	TransitionsSpriteA.Init("Assets/Sprite/Option/Transitions.DDS", 440.0f, 40.0f);
	TransitionsSpriteB.Init("Assets/Sprite/Option/Transitions.DDS", 440.0f, 40.0f);
	TransitionsSpriteC.Init("Assets/Sprite/Option/Transitions.DDS", 440.0f, 40.0f);
	BGMGage.Init("Assets/Sprite/Option/SoundGage.DDS", 250.0f, 24.0f);
	SEGage.Init("Assets/Sprite/Option/SoundGage.DDS", 250.0f, 24.0f);
	EngineSoundGage.Init("Assets/Sprite/Option/SoundGage.DDS", 250.0f, 24.0f);
	FadeSprite.Init("Assets/Sprite/BlackOut.DDS", 1600.0f, 900.0f);

	//画像の初期化
	SelectSprite.SetPosition(SelectSpritePosition);
	SelectSprite.SetMulColor(SelectSpriteColor);
	MainSprite.SetMulColor(MainSpriteColor);
	TransmissionSprite.SetMulColor(TransmissionSpriteColor);
	SoundSprite.SetMulColor(SoundSpriteColor);
	BGMGage.SetPosition(BGMGagePosition);
	BGMGage.SetPivot(0.0, 0.5);
	BGMGage.SetScale(BGMVolume, 1.0f, 0.0f);
	SEGage.SetPosition(SEGagePosition);
	SEGage.SetPivot(0.0, 0.5);
	SEGage.SetScale(SEVolume, 1.0f, 0.0f);
	EngineSoundGage.SetPosition(EngineSoundGagePosition);
	EngineSoundGage.SetPivot(0.0, 0.5);
	EngineSoundGage.SetScale(EngineSoundVolume,1.0f , 0.0f);
	FadeSprite.SetMulColor(FadeColor);

	//画像の更新
	SelectSprite.Update();
	MainSprite.Update();
	TransmissionSprite.Update();
	SoundSprite.Update();
	TransitionsSpriteA.Update();
	TransitionsSpriteB.Update();
	TransitionsSpriteC.Update();
	BGMGage.Update();
	SEGage.Update();
	EngineSoundGage.Update();
	FadeSprite.Update();

	//BGM
	BGM = NewGO<SoundSource>(0);
	BGM->Init(11);
	BGM->SetVolume(m_player->GetBGMVolume());
	BGM->Play(true);

	return true;
}

void OptionMenu::Update() {
	BGM->SetVolume(m_player->GetBGMVolume());
	//最初のフェードアウトと画像の準備
	if (FadeCount < 5) {
		FadeColor.w -= 0.2f;
		FadeSprite.SetMulColor(FadeColor);
	}
	else {
		//メインメニュー
		if (PageState == 0) {
			
			MainSpriteColor.w = 1.0f;
			MainSprite.SetMulColor(MainSpriteColor);
			if (g_pad[0]->IsTrigger(enButtonDown) && SelectPoint == 0) {
				SelectSpritePosition.y -= 230.0f;
				SelectSprite.SetPosition(SelectSpritePosition);
				SelectPoint++;
				CursorSE = NewGO<SoundSource>(0);
				CursorSE->Init(100);
				CursorSE->SetVolume(m_player->GetSEVolume());
				CursorSE->Play(false);
			}
			else if (g_pad[0]->IsTrigger(enButtonUp) && SelectPoint == 1) {
				SelectSpritePosition.y += 230.0f;
				SelectSprite.SetPosition(SelectSpritePosition);
				SelectPoint--;
				CursorSE = NewGO<SoundSource>(0);
				CursorSE->Init(100);
				CursorSE->SetVolume(m_player->GetSEVolume());
				CursorSE->Play(false);
			}
			else if (g_pad[0]->IsTrigger(enButtonA)) {
				DecisionSE = NewGO<SoundSource>(0);
				DecisionSE->Init(101);
				DecisionSE->SetVolume(m_player->GetSEVolume());
				DecisionSE->Play(false);
				NextPageCount = 0;
				NextPageState = true;
			}
			else if (g_pad[0]->IsTrigger(enButtonB)) {
				NextPageCount = 0;
				BackPageState = true;
				CancelSE = NewGO<SoundSource>(0);
				CancelSE->Init(102);
				CancelSE->SetVolume(SEVolume);
				CancelSE->Play(false);
			}
		}

		//サウンドメニュー
		if (PageState == 1) {

			SoundSpriteColor.w = 1.0f;
			SoundSprite.SetMulColor(SoundSpriteColor);
			if (VolumeChangeStatus == false) {
				if (g_pad[0]->IsTrigger(enButtonDown) && (SelectPoint == 0 || SelectPoint == 1)) {
					SelectSpritePosition.y -= 230.0f;
					SelectSprite.SetPosition(SelectSpritePosition);
					SelectPoint++;
					CursorSE = NewGO<SoundSource>(0);
					CursorSE->Init(100);
					CursorSE->SetVolume(m_player->GetSEVolume());
					CursorSE->Play(false);
				}
				else if (g_pad[0]->IsTrigger(enButtonUp) && (SelectPoint == 1 || SelectPoint == 2)) {
					SelectSpritePosition.y += 230.0f;
					SelectSprite.SetPosition(SelectSpritePosition);
					SelectPoint--;
					CursorSE = NewGO<SoundSource>(0);
					CursorSE->Init(100);
					CursorSE->SetVolume(m_player->GetSEVolume());
					CursorSE->Play(false);
				}
				else if (g_pad[0]->IsTrigger(enButtonA)) {
					DecisionSE = NewGO<SoundSource>(0);
					DecisionSE->Init(101);
					DecisionSE->SetVolume(m_player->GetSEVolume());
					DecisionSE->Play(false);
					SelectMoveCount = 0;
					Selectdirection = 1;
					VolumeChangeStatus = true;
				}
				else if (g_pad[0]->IsTrigger(enButtonB)) {
					CancelSE = NewGO<SoundSource>(0);
					CancelSE->Init(102);
					CancelSE->SetVolume(SEVolume);
					CancelSE->Play(false);
					NextPageCount = 0;
					BackPageState = true;
				}
			}
		}
		//トランスミッションメニュー
		if (PageState == 2) {
			TransmissionSpriteColor.w = 1.0f;
			TransmissionSprite.SetMulColor(TransmissionSpriteColor);
			
			
			if (TransMissionChangeStatus == true) {
				if (g_pad[0]->IsTrigger(enButtonDown) && SelectPoint == 0) {
					SelectSpritePosition.y -= 230.0f;
					SelectSprite.SetPosition(SelectSpritePosition);
					SelectPoint++;
					CursorSE = NewGO<SoundSource>(0);
					CursorSE->Init(100);
					CursorSE->SetVolume(m_player->GetSEVolume());
					CursorSE->Play(false);
					Transmission = false;
					
				}
				else if (g_pad[0]->IsTrigger(enButtonUp) && SelectPoint == 1) {
					SelectSpritePosition.y += 230.0f;
					SelectSprite.SetPosition(SelectSpritePosition);
					SelectPoint--;
					CursorSE = NewGO<SoundSource>(0);
					CursorSE->Init(100);
					CursorSE->SetVolume(m_player->GetSEVolume());
					CursorSE->Play(false);
					Transmission = true;
				}
				else if (g_pad[0]->IsTrigger(enButtonA)) {
					DecisionSE = NewGO<SoundSource>(0);
					DecisionSE->Init(101);
					DecisionSE->SetVolume(m_player->GetSEVolume());
					DecisionSE->Play(false);
					SelectSpriteColor.w = 1.0f;
					SelectSprite.SetMulColor(SelectSpriteColor);
					TransMissionChangeStatus = false;
					m_player->SetTransmission(Transmission);
				}
			}
			else {
				if (g_pad[0]->IsTrigger(enButtonA)) {
					DecisionSE = NewGO<SoundSource>(0);
					DecisionSE->Init(101);
					DecisionSE->SetVolume(m_player->GetSEVolume());
					DecisionSE->Play(false);
					SelectMoveCount = 0;
					Selectdirection = 1;
					TransMissionChangeStatus = true;
				}
				else if (g_pad[0]->IsTrigger(enButtonB)) {
					CancelSE = NewGO<SoundSource>(0);
					CancelSE->Init(102);
					CancelSE->SetVolume(SEVolume);
					CancelSE->Play(false);
					NextPageCount = 0;
					BackPageState = true;
				}
			}
		}

		//ページの移動
		if (NextPageState == true) {
			if (NextPageCount < 5) {
				FadeColor.w += 0.2f;
				FadeSprite.SetMulColor(FadeColor);
			}
			else if (NextPageCount < 10) {
				FadeColor.w -= 0.2f;
				FadeSprite.SetMulColor(FadeColor);
			}
			else {
				NextPageState = false;
			}
			//どのページを表示するか
			if (NextPageCount == 5) {
				//元のページがメインメニューの時
				if (PageState == 0) {
					//元のページの非表示
					MainSpriteColor.w = 0.0f;
					MainSprite.SetMulColor(MainSpriteColor);
					if (SelectPoint == 0) {
						SelectSpritePosition = { -685.75f,260.0f,0.0f };
						SelectSprite.SetPosition(SelectSpritePosition);
						PageState = 1;
						SelectPoint = 0;
						
					}
					else {
						PageState = 2;
						if (Transmission == true) {
							SelectSpritePosition = { -685.75f,260.0f,0.0f };
							SelectSprite.SetPosition(SelectSpritePosition);
							SelectPoint = 0;
						}
						else {
							SelectSpritePosition = { -685.75f,30.0f,0.0f };
							SelectSprite.SetPosition(SelectSpritePosition);
							SelectPoint = 1;
						}
						
					}
				}
			}
			NextPageCount++;
		}
		//戻る
		if (BackPageState == true) {
			if (NextPageCount < 5) {
				FadeColor.w += 0.2f;
				FadeSprite.SetMulColor(FadeColor);
			}
			else if (NextPageCount < 10) {
				FadeColor.w -= 0.2f;
				FadeSprite.SetMulColor(FadeColor);
			}
			else {
				BackPageState = false;
			}
			//どのページを表示するか
			if (NextPageCount == 5) {
				//元のページがメインメニューの時
				if (PageState == 0) {
					m_loading = NewGO<Loading>(10, "loading");
					m_loading->SetWhereCome(OptionPage);
					m_loading->SetWhereGo(WhereComePage);
					DeleteGO(this);
					DeleteGO(BGM);
				}
				else if(PageState == 1) {
					SelectSpritePosition = { -685.75f,260.0f,0.0f };
					SelectSprite.SetPosition(SelectSpritePosition);
					SoundSpriteColor.w = 0.0f;
					SoundSprite.SetMulColor(SoundSpriteColor);
					PageState = 0;
					SelectPoint = 0;
				}
				else if (PageState == 2) {
					SelectSpritePosition = { -685.75f,260.0f,0.0f };
					SelectSprite.SetPosition(SelectSpritePosition);
					TransmissionSpriteColor.w = 0.0f;
					TransmissionSprite.SetMulColor(TransmissionSpriteColor);
					PageState = 0;
					SelectPoint = 0;
				}
			}
			NextPageCount++;
		}

		//音量の変更状態
		if (VolumeChangeStatus == true) {
			if (SelectMoveCount % 50 == 0) {
				Selectdirection *= -1;
			}
			SelectSpriteColor.w += 0.02 * Selectdirection;
			SelectSprite.SetMulColor(SelectSpriteColor);
			switch (SelectPoint)
			{
				//BGMの音量変更
			case 0:
				if (g_pad[0]->IsPress(enButtonRight) && BGMVolume < 1.0f) {
					BGMVolume += 0.05;
					CursorSE = NewGO<SoundSource>(0);
					CursorSE->Init(100);
					CursorSE->SetVolume(m_player->GetSEVolume());
					CursorSE->Play(false);
				}
				else if (g_pad[0]->IsPress(enButtonLeft) && BGMVolume > 0.0f) {
					BGMVolume -= 0.05;
					CursorSE = NewGO<SoundSource>(0);
					CursorSE->Init(100);
					CursorSE->SetVolume(m_player->GetSEVolume());
					CursorSE->Play(false);
				}
				else if (g_pad[0]->IsTrigger(enButtonB)) {
					CancelSE = NewGO<SoundSource>(0);
					CancelSE->Init(102);
					CancelSE->SetVolume(SEVolume);
					CancelSE->Play(false);
					SelectSpriteColor.w = 1.0f;
					SelectSprite.SetMulColor(SelectSpriteColor);
					VolumeChangeStatus = false;
				}
				m_player->SetBGMVolume(BGMVolume);
				BGMGage.SetScale(BGMVolume,1.0f , 0.0f);
				break;
				//SEの音量変更
			case 1:
				if (g_pad[0]->IsPress(enButtonRight) && SEVolume < 1.0f) {
					SEVolume += 0.05;
					CursorSE = NewGO<SoundSource>(0);
					CursorSE->Init(100);
					CursorSE->SetVolume(m_player->GetSEVolume());
					CursorSE->Play(false);
				}
				else if (g_pad[0]->IsPress(enButtonLeft) && SEVolume > 0.0f) {
					SEVolume -= 0.05;
					CursorSE = NewGO<SoundSource>(0);
					CursorSE->Init(100);
					CursorSE->SetVolume(m_player->GetSEVolume());
					CursorSE->Play(false);
				}
				else if (g_pad[0]->IsTrigger(enButtonB)) {
					SelectSpriteColor.w = 1.0f;
					SelectSprite.SetMulColor(SelectSpriteColor);
					VolumeChangeStatus = false;
				}
				m_player->SetSEVolume(SEVolume);
				SEGage.SetScale(SEVolume, 1.0f, 0.0f);
				break;
				//EngineSoundの音量変更
			case 2:
				if (g_pad[0]->IsPress(enButtonRight) && EngineSoundVolume < 1.0f) {
					EngineSoundVolume += 0.05;
					CursorSE = NewGO<SoundSource>(0);
					CursorSE->Init(100);
					CursorSE->SetVolume(m_player->GetSEVolume());
					CursorSE->Play(false);
				}
				else if (g_pad[0]->IsPress(enButtonLeft) && EngineSoundVolume > 0.0f) {
					EngineSoundVolume -= 0.05;
					CursorSE = NewGO<SoundSource>(0);
					CursorSE->Init(100);
					CursorSE->SetVolume(m_player->GetSEVolume());
					CursorSE->Play(false);
				}
				else if (g_pad[0]->IsTrigger(enButtonB)) {
					SelectSpriteColor.w = 1.0f;
					SelectSprite.SetMulColor(SelectSpriteColor);
					VolumeChangeStatus = false;
				}
				m_player->SetEngineSoundVolume(EngineSoundVolume);
				EngineSoundGage.SetScale(EngineSoundVolume, 1.0f, 0.0f);
				break;
			default:
				break;
			}
			SelectMoveCount++;
		}

		if (TransMissionChangeStatus == true) {
			if (SelectMoveCount % 50 == 0) {
				Selectdirection *= -1;
			}
			SelectSpriteColor.w += 0.02 * Selectdirection;
			SelectSprite.SetMulColor(SelectSpriteColor);
			SelectMoveCount++;
		}
	}
	//画像の更新
	SelectSprite.Update();
	MainSprite.Update();
	TransmissionSprite.Update();
	SoundSprite.Update();
	TransitionsSpriteA.Update();
	TransitionsSpriteB.Update();
	TransitionsSpriteC.Update();
	BGMGage.Update();
	SEGage.Update();
	EngineSoundGage.Update();
	FadeSprite.Update();

	//カウントの更新
	FadeCount++;
	TransitionsCount++;
	
}

void OptionMenu::Render(RenderContext& rc) {
	BaseSprite.Draw(rc);
	SelectSprite.Draw(rc);
	MainSprite.Draw(rc);
	TransmissionSprite.Draw(rc);
	SoundSprite.Draw(rc);
	if (PageState == 1) {
		BGMGage.Draw(rc);
		SEGage.Draw(rc);
		EngineSoundGage.Draw(rc);
	}
	FadeSprite.Draw(rc);
}