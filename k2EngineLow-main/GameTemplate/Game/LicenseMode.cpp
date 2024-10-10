#include "stdafx.h"
#include "LicenseMode.h"
#include "Player.h"
#include "Loading.h"
#include "PageNum.h"

LicenseMode::LicenseMode() {

}

LicenseMode::~LicenseMode() {

}

bool LicenseMode::Start() {
	m_Player = FindGO<Player>("player");

	m_Player->SetRideCarNum(m_Player->GetRideCarCache());
	FadeSprite.Init("Assets/sprite/BlackOut.DDS", 1600.0f, 900.0f);

	//ライセンスクリア状況の初期化
	for (int i = 0; i < 5; i++) {
		//ライセンスの取得状況の初期化
		LicenseAcquisitionStatus[i] = m_Player->GetLicenseAcquisitionStatus(i);
		for (int j = 0; j < 5; j++) {
			LicenseClearStatus[i][j] = m_Player->GetLicenseClear(i,j);
		}
	}
	SpriteSet();
	StateSet(0);

	BGM = NewGO<SoundSource>(0);
	BGM->Init(10);
	BGM->SetVolume(m_Player->GetBGMVolume());
	BGM->Play(true);

	return true;
}

void LicenseMode::SpriteSet() {
	//背景の設定
	Base.Init("Assets/sprite/LicenseMode/Base.DDS", 1600.0f, 900.0f);

	//アローの設定
	ArrowSprite.Init("Assets/sprite/LicenseMode/Arrow.DDS", 36.0f, 30.0f);
	ArrowSprite.SetPosition(ArrowPosition);
	ArrowDiffPos = Arrow1Pos - ArrowPosition;

	ArrowXMoveDistance = ArrowDiffPos.x / 50.0f;
	ArrowYMoveDistance = ArrowDiffPos.y / 50.0f;

	ErrorWindowSprite.Init("Assets/Sprite/MyHome/ErrorWindow.DDS", 1632.0f, 918.0f);
	WindowBottonOKSprite.Init("Assets/Sprite/MyHome/WindowBottonOK.DDS", 1632.0f, 918.0f);

	ErrorWindowSprite.SetMulColor(m_WindowSpriteColor);
	WindowBottonOKSprite.SetMulColor(m_WindowSpriteColor);

	ErrorWindowSprite.SetPosition(m_WindowSpritePosition);
	WindowBottonOKSprite.SetPosition(m_WindowSpritePosition);

	ErrorWindowSprite.Update();
	WindowBottonOKSprite.Update();

	//ライセンスタイプに応じて背景の一部を変更するため読み込み
	BaseDomesticB.Init("Assets/sprite/LicenseMode/BaseDomesticB.DDS", 1600.0f, 900.0f);

	//ライセンスのクリア状況に応じてタブの種類の切り替え
	//クリア済みと挑戦中は色付き・未開放は色なし
	//国内B級のみ絶対的に表示
	DomesticBTabSprite.Init("Assets/sprite/LicenseMode/DomesticBSelect.DDS", 1600.0f, 900.0f);
	
	//国内A級
	if (LicenseAcquisitionStatus[1] == true || LicenseAcquisitionStatus[0] == true) {
		DomesticATabSprite.Init("Assets/sprite/LicenseMode/DomesticASelect.DDS", 1600.0f, 900.0f);
	}
	else {
		DomesticATabSprite.Init("Assets/sprite/LicenseMode/DomesticANonSelect.DDS", 1600.0f, 900.0f);
	}

	//国際B級
	if (LicenseAcquisitionStatus[1] == true || LicenseAcquisitionStatus[0] == true) {
		InternationaBTabSprite.Init("Assets/sprite/LicenseMode/InternationalBSelect.DDS", 1600.0f, 900.0f);
	}
	else {
		InternationaBTabSprite.Init("Assets/sprite/LicenseMode/InternationalBNonSelect.DDS", 1600.0f, 900.0f);
	}

	//国際A級
	if (LicenseAcquisitionStatus[1] == true || LicenseAcquisitionStatus[0] == true) {
		InternationaATabSprite.Init("Assets/sprite/LicenseMode/InternationalASelect.DDS", 1600.0f, 900.0f);
	}
	else {
		InternationaATabSprite.Init("Assets/sprite/LicenseMode/InternationalANonSelect.DDS", 1600.0f, 900.0f);
	}

	//スーパーライセンス
	if (LicenseAcquisitionStatus[1] == true || LicenseAcquisitionStatus[0] == true) {
		SuperTabSprite.Init("Assets/sprite/LicenseMode/SuperSelect.DDS", 1600.0f, 900.0f);
	}
	else {
		SuperTabSprite.Init("Assets/sprite/LicenseMode/SuperNonSelect.DDS", 1600.0f, 900.0f);
	}

	//ライセンス内容の設定
	//国内B級
	LicenseDetailsDomesticB_1Sprite.Init("Assets/sprite/LicenseMode/DomesticB-1.DDS", 209.0f, 465.0f);
	LicenseDetailsDomesticB_2Sprite.Init("Assets/sprite/LicenseMode/DomesticB-2.DDS", 209.0f, 465.0f);
	LicenseDetailsDomesticB_3Sprite.Init("Assets/sprite/LicenseMode/DomesticB-3.DDS", 209.0f, 465.0f);
	LicenseDetailsDomesticB_4Sprite.Init("Assets/sprite/LicenseMode/DomesticB-4.DDS", 209.0f, 465.0f);
	LicenseDetailsDomesticB_5Sprite.Init("Assets/sprite/LicenseMode/DomesticB-5.DDS", 209.0f, 465.0f);

	LicenseDetailsDomesticB_1Sprite.SetPosition(LicenseDetails1SpritePosition);
	LicenseDetailsDomesticB_2Sprite.SetPosition(LicenseDetails2SpritePosition);
	LicenseDetailsDomesticB_3Sprite.SetPosition(LicenseDetails3SpritePosition);
	LicenseDetailsDomesticB_4Sprite.SetPosition(LicenseDetails4SpritePosition);
	LicenseDetailsDomesticB_5Sprite.SetPosition(LicenseDetails5SpritePosition);

	LicenseDetailsDomesticB_1Sprite.SetMulColor(LicenseDetails1SpriteColor);
	LicenseDetailsDomesticB_2Sprite.SetMulColor(LicenseDetails2SpriteColor);
	LicenseDetailsDomesticB_3Sprite.SetMulColor(LicenseDetails3SpriteColor);
	LicenseDetailsDomesticB_4Sprite.SetMulColor(LicenseDetails4SpriteColor);
	LicenseDetailsDomesticB_5Sprite.SetMulColor(LicenseDetails5SpriteColor);

//ライセンスごとのクリア状況の設定
//国内B級
//B-1
if (LicenseClearStatus[0][0] == 3) {
	B_1Sprite.Init("Assets/sprite/LicenseMode/B-1Gold.DDS", 209.0f, 465.0f);
}
else if (LicenseClearStatus[0][0] == 2) {
	B_1Sprite.Init("Assets/sprite/LicenseMode/B-1Silver.DDS", 209.0f, 465.0f);
}
else if (LicenseClearStatus[0][0] == 1) {
	B_1Sprite.Init("Assets/sprite/LicenseMode/B-1Bronze.DDS", 209.0f, 465.0f);
}
B_1Sprite.SetPosition(LicenseDetails1SpritePosition);
B_1Sprite.SetMulColor(LicenseDetails1SpriteColor);
//B-2
if (LicenseClearStatus[0][1] == 3) {
	B_2Sprite.Init("Assets/sprite/LicenseMode/B-2Gold.DDS", 209.0f, 465.0f);
}
else if (LicenseClearStatus[0][1] == 2) {
	B_2Sprite.Init("Assets/sprite/LicenseMode/B-2Silver.DDS", 209.0f, 465.0f);
}
else if (LicenseClearStatus[0][1] == 1) {
	B_2Sprite.Init("Assets/sprite/LicenseMode/B-2Bronze.DDS", 209.0f, 465.0f);
}
B_2Sprite.SetPosition(LicenseDetails2SpritePosition);
B_2Sprite.SetMulColor(LicenseDetails2SpriteColor);
//B-3
if (LicenseClearStatus[0][2] == 3) {
	B_3Sprite.Init("Assets/sprite/LicenseMode/B-3Gold.DDS", 209.0f, 465.0f);
}
else if (LicenseClearStatus[0][2] == 2) {
	B_3Sprite.Init("Assets/sprite/LicenseMode/B-3Silver.DDS", 209.0f, 465.0f);
}
else if (LicenseClearStatus[0][2] == 1) {
	B_3Sprite.Init("Assets/sprite/LicenseMode/B-3Bronze.DDS", 209.0f, 465.0f);
}
B_3Sprite.SetPosition(LicenseDetails3SpritePosition);
B_3Sprite.SetMulColor(LicenseDetails3SpriteColor);
//B-4
if (LicenseClearStatus[0][3] == 3) {
	B_4Sprite.Init("Assets/sprite/LicenseMode/B-4Gold.DDS", 209.0f, 465.0f);
}
else if (LicenseClearStatus[0][3] == 2) {
	B_4Sprite.Init("Assets/sprite/LicenseMode/B-4Silver.DDS", 209.0f, 465.0f);
}
else if (LicenseClearStatus[0][3] == 1) {
	B_4Sprite.Init("Assets/sprite/LicenseMode/B-4Bronze.DDS", 209.0f, 465.0f);
}
B_4Sprite.SetPosition(LicenseDetails4SpritePosition);
B_4Sprite.SetMulColor(LicenseDetails4SpriteColor);
//B-5
if (LicenseClearStatus[0][4] == 3) {
	B_5Sprite.Init("Assets/sprite/LicenseMode/B-5Gold.DDS", 209.0f, 465.0f);
}
else if (LicenseClearStatus[0][4] == 2) {
	B_5Sprite.Init("Assets/sprite/LicenseMode/B-5Silver.DDS", 209.0f, 465.0f);
}
else if (LicenseClearStatus[0][4] == 1) {
	B_5Sprite.Init("Assets/sprite/LicenseMode/B-5Bronze.DDS", 209.0f, 465.0f);
}
B_5Sprite.SetPosition(LicenseDetails5SpritePosition);
B_5Sprite.SetMulColor(LicenseDetails5SpriteColor);

//国内A級


//オールクリア状況
AllBronzeClearSprite.Init("Assets/sprite/LicenseMode/AllBronzeClear.DDS", 1600.0f, 900.0f);
AllSilverClearSprite.Init("Assets/sprite/LicenseMode/AllSilverClear.DDS", 1600.0f, 900.0f);
AllGoldClearSprite.Init("Assets/sprite/LicenseMode/AllGoldClear.DDS", 1600.0f, 900.0f);

AllBronzeClearSprite.SetPosition(BaseDomesticBPosition);
AllSilverClearSprite.SetPosition(BaseDomesticBPosition);
AllGoldClearSprite.SetPosition(BaseDomesticBPosition);
//スプライトのアップデート
ArrowSprite.Update();
B_1Sprite.Update();
B_2Sprite.Update();
B_3Sprite.Update();
B_4Sprite.Update();
B_5Sprite.Update();

AllGoldClearSprite.Update();
AllSilverClearSprite.Update();
AllBronzeClearSprite.Update();

LicenseDetailsDomesticB_1Sprite.Update();
LicenseDetailsDomesticB_2Sprite.Update();
LicenseDetailsDomesticB_3Sprite.Update();
LicenseDetailsDomesticB_4Sprite.Update();
LicenseDetailsDomesticB_5Sprite.Update();
}

void LicenseMode::StateSet(int m_LicensePage) {
	//画面下のオールクリア状況のステート管理
	switch (m_LicensePage)
	{
	case 0:
		if (LicenseClearStatus[m_LicensePage][0] == 1 && LicenseClearStatus[m_LicensePage][1] == 1 && LicenseClearStatus[m_LicensePage][2] == 1 && LicenseClearStatus[m_LicensePage][3] == 1 && LicenseClearStatus[m_LicensePage][4] == 1)
		{
			AllBronzeState = true;
			if (LicenseClearStatus[m_LicensePage][0] == 2 && LicenseClearStatus[m_LicensePage][1] == 2 && LicenseClearStatus[m_LicensePage][2] == 2 && LicenseClearStatus[m_LicensePage][3] == 2 && LicenseClearStatus[m_LicensePage][4] == 2)
			{
				AllSilverState = true;
				if (LicenseClearStatus[m_LicensePage][0] == 3 && LicenseClearStatus[m_LicensePage][1] == 3 && LicenseClearStatus[m_LicensePage][2] == 3 && LicenseClearStatus[m_LicensePage][3] == 3 && LicenseClearStatus[m_LicensePage][4] == 3)
				{
					AllGoldState = true;
				}
			}
		}
		break;
	case 1:
		break;
	default:
		break;
	}
}

void LicenseMode::Update() {
	//最初のFade
	if (FadeCount < 50) {
		FadeColor.w -= 0.02;
		FadeSprite.SetMulColor(FadeColor);
		//カウント関係の更新
		FadeCount++;
	}
	//遷移関係
	if (TransitionStatus == true) {
		switch (NextPage)
		{
		case -1:
			FadeIn();
			break;
		case 0:
			DomesticBlicenseDisplayTransition();
			break;
		case 5:
			FadeIn();
			break;
		default:
			break;
		}
	}
	else {
		if (ArrowMoveRight == true) {
			if (ArrowMoveCount < 10) {
				ArrowPosition.x += 32.5f;
				ArrowSprite.SetPosition(ArrowPosition);
			}
			else {
				ArrowMoveRight = false;
			}
			ArrowMoveCount++;
		}
		else if (ArrowMoveLeft == true) {
			if (ArrowMoveCount < 10) {
				ArrowPosition.x -= 32.5f;
				ArrowSprite.SetPosition(ArrowPosition);
			}
			else {
				ArrowMoveLeft = false;
			}
			ArrowMoveCount++;
		}
		else {
			if (ErrorWindowFlag == 0) {
				if (g_pad[0]->IsTrigger(enButtonA)) {
					if (ArrowPoint != 4) {
						DecisionSE = NewGO<SoundSource>(0);
						DecisionSE->Init(101);
						DecisionSE->SetVolume(m_Player->GetSEVolume());
						DecisionSE->Play(false);
						TransitionStatus = true;
						LicenseNum = (LicensePage + 1) * (ArrowPoint + 1);
						NextPage = 5;
						FadeCount = 0;
					}
					else if (ArrowPoint == 4) {
						if (ErrorWindowFlag == 0) {
							ErrorSE = NewGO<SoundSource>(0);
							ErrorSE->Init(105);
							ErrorSE->SetVolume(m_Player->GetSEVolume());
							ErrorSE->Play(false);
							WindowCount = 0;
							ErrorWindowFlag = 1;
						}
					}
				}
				else if (g_pad[0]->IsTrigger(enButtonB)) {
					CancelSE = NewGO<SoundSource>(0);
					CancelSE->Init(102);
					CancelSE->SetVolume(m_Player->GetSEVolume());
					CancelSE->Play(false);
					TransitionStatus = true;
					NextPage = -1;
					FadeCount = 0;
				}
				else if (g_pad[0]->IsTrigger(enButtonRight) && ArrowPoint < 4) {
					CursorSE = NewGO<SoundSource>(0);
					CursorSE->Init(100);
					CursorSE->SetVolume(m_Player->GetSEVolume());
					CursorSE->Play(false);
					ArrowMoveRight = true;
					ArrowMoveCount = 0;
					ArrowPoint++;
				}
				else if (g_pad[0]->IsTrigger(enButtonLeft) && ArrowPoint > 0) {
					CursorSE = NewGO<SoundSource>(0);
					CursorSE->Init(100);
					CursorSE->SetVolume(m_Player->GetSEVolume());
					CursorSE->Play(false);
					ArrowMoveLeft = true;
					ArrowMoveCount = 0;
					ArrowPoint--;
				}
				else if (g_pad[0]->IsTrigger(enButtonLB1)) {

				}
				else if (g_pad[0]->IsTrigger(enButtonRB1)) {

				}
			}
		}
	}

	if (ErrorWindowFlag == 1) {
		m_WindowSpriteColor.w += 0.1f;
		m_WindowSpritePosition.y += 5.0f;

		ErrorWindowSprite.SetMulColor(m_WindowSpriteColor);
		WindowBottonOKSprite.SetMulColor(m_WindowSpriteColor);

		ErrorWindowSprite.SetPosition(m_WindowSpritePosition);
		WindowBottonOKSprite.SetPosition(m_WindowSpritePosition);
		WindowCount++;
		if (WindowCount == 10) {
			ErrorWindowFlag = 2;
		}
	}
	else if (ErrorWindowFlag == 2) {
		if (g_pad[0]->IsTrigger(enButtonA)) {
			DecisionSE = NewGO<SoundSource>(0);
			DecisionSE->Init(101);
			DecisionSE->SetVolume(m_Player->GetSEVolume());
			DecisionSE->Play(false);
			ErrorWindowFlag = 3;
			WindowCount = 0;
		}
	}
	else if (ErrorWindowFlag == 3) {
		m_WindowSpriteColor.w -= 0.2f;
		m_WindowSpritePosition.y -= 10.0f;

		ErrorWindowSprite.SetMulColor(m_WindowSpriteColor);
		WindowBottonOKSprite.SetMulColor(m_WindowSpriteColor);

		ErrorWindowSprite.SetPosition(m_WindowSpritePosition);
		WindowBottonOKSprite.SetPosition(m_WindowSpritePosition);
		WindowCount++;
		if (WindowCount == 5) {
			ErrorWindowFlag = 0;
			WindowCount = 0;
		}
	}
	
	//スプライト関係のアップデート
	ArrowSprite.Update();
	FadeSprite.Update();
	ErrorWindowSprite.Update();
	WindowBottonOKSprite.Update();
}

void LicenseMode::FadeIn() {
	if (FadeCount < 50) {
		FadeColor.w += 0.02;
		FadeSprite.SetMulColor(FadeColor);
	}
	else {
		TransitionStatus = false;
		m_Loading = NewGO<Loading>(10, "loading");
		if (NextPage == -1) {
			m_Loading->SetWhereCome(LicensePage);
			m_Loading->SetWhereGo(WorldMenuPage);
		}
		if (NextPage == 5) {
			m_Loading->SetWhereCome(LicenseModePage);
			m_Loading->SetWhereGo(RaceLobbyPage);
			m_Loading->SetCar(LicensedCar[LicensePage][ArrowPoint]);
			m_Player->SetRideCarCache(m_Player->GetCarNum());
			m_Player->SetRideCarNum(LicensedCar[LicensePage][ArrowPoint]);
			m_Player->SetNowCourse(LicenseCourse[LicensePage][ArrowPoint]);
			m_Loading->SetCourse(LicenseCourse[LicensePage][ArrowPoint]);
			m_Loading->SetPlayMode(License);
			m_Loading->SetLicenseNum(LicenseNum);
		}

		DeleteGO(this);
		DeleteGO(BGM);
	}
	//カウント関係の更新
	FadeCount++;
	//スプライト関係のアップデート
	FadeSprite.Update();
}


void LicenseMode::DomesticBlicenseDisplayTransition() {
	if (TransitionCount < 60) {
		BaseDomesticBPosition.y += 2.0f;
		BaseDomesticB.SetPosition(BaseDomesticBPosition);

		AllBronzeClearSprite.SetPosition(BaseDomesticBPosition);
		AllSilverClearSprite.SetPosition(BaseDomesticBPosition);
		AllGoldClearSprite.SetPosition(BaseDomesticBPosition);
	}
	if (TransitionCount < 80) {
		LicenseDetails1SpritePosition.y += 0.5f;
		LicenseDetailsDomesticB_1Sprite.SetPosition(LicenseDetails1SpritePosition);

		

		LicenseDetails1SpriteColor.w += 0.0125f;
		LicenseDetailsDomesticB_1Sprite.SetMulColor(LicenseDetails1SpriteColor);

		B_1Sprite.SetPosition(LicenseDetails1SpritePosition);
		B_1Sprite.SetMulColor(LicenseDetails1SpriteColor);
	}
	if (TransitionCount >=10 && TransitionCount < 90) {
		LicenseDetails2SpritePosition.y += 0.5f;
		LicenseDetailsDomesticB_2Sprite.SetPosition(LicenseDetails2SpritePosition);

		

		LicenseDetails2SpriteColor.w += 0.0125f;
		LicenseDetailsDomesticB_2Sprite.SetMulColor(LicenseDetails2SpriteColor);

		B_2Sprite.SetPosition(LicenseDetails2SpritePosition);
		B_2Sprite.SetMulColor(LicenseDetails2SpriteColor);
	}
	if (TransitionCount >= 20 && TransitionCount < 100) {
		LicenseDetails3SpritePosition.y += 0.5f;
		LicenseDetailsDomesticB_3Sprite.SetPosition(LicenseDetails3SpritePosition);

		

		LicenseDetails3SpriteColor.w += 0.0125f;
		LicenseDetailsDomesticB_3Sprite.SetMulColor(LicenseDetails3SpriteColor);

		B_3Sprite.SetPosition(LicenseDetails3SpritePosition);
		B_3Sprite.SetMulColor(LicenseDetails3SpriteColor);
	}
	if (TransitionCount >= 30 && TransitionCount < 110) {
		LicenseDetails4SpritePosition.y += 0.5f;
		LicenseDetailsDomesticB_4Sprite.SetPosition(LicenseDetails4SpritePosition);

		

		LicenseDetails4SpriteColor.w += 0.0125f;
		LicenseDetailsDomesticB_4Sprite.SetMulColor(LicenseDetails4SpriteColor);

		B_4Sprite.SetPosition(LicenseDetails4SpritePosition);
		B_4Sprite.SetMulColor(LicenseDetails4SpriteColor);
	}
	if (TransitionCount >= 40 && TransitionCount < 120) {
		LicenseDetails5SpritePosition.y += 0.5f;
		LicenseDetailsDomesticB_5Sprite.SetPosition(LicenseDetails5SpritePosition);

		

		LicenseDetails5SpriteColor.w += 0.0125f;
		LicenseDetailsDomesticB_5Sprite.SetMulColor(LicenseDetails5SpriteColor);

		B_5Sprite.SetPosition(LicenseDetails5SpritePosition);
		B_5Sprite.SetMulColor(LicenseDetails5SpriteColor);
	}
	if (TransitionCount < 50) {
		ArrowPosition.x += ArrowXMoveDistance;
		ArrowPosition.y += ArrowYMoveDistance;

		ArrowSprite.SetPosition(ArrowPosition);
	}
	if (TransitionCount >= 120) {
		TransitionStatus = false;
	}

	

	//カウントの更新
	TransitionCount++;

	//スプライト関係のアップデート
	BaseDomesticB.Update();
	ArrowSprite.Update();
	B_1Sprite.Update();
	B_2Sprite.Update();
	B_3Sprite.Update();
	B_4Sprite.Update();
	B_5Sprite.Update();

	AllGoldClearSprite.Update();
	AllSilverClearSprite.Update();
	AllBronzeClearSprite.Update();

	LicenseDetailsDomesticB_1Sprite.Update();
	LicenseDetailsDomesticB_2Sprite.Update();
	LicenseDetailsDomesticB_3Sprite.Update();
	LicenseDetailsDomesticB_4Sprite.Update();
	LicenseDetailsDomesticB_5Sprite.Update();
}

void LicenseMode::Render(RenderContext& rc) {
	//ベース関係のドロー
	Base.Draw(rc);

	//国内B級の時
	if (LicensePage == 0 || NextPage == 0 || LastPage == 0) {
		BaseDomesticB.Draw(rc);
		LicenseDetailsDomesticB_1Sprite.Draw(rc);
		LicenseDetailsDomesticB_2Sprite.Draw(rc);
		LicenseDetailsDomesticB_3Sprite.Draw(rc);
		LicenseDetailsDomesticB_4Sprite.Draw(rc);
		LicenseDetailsDomesticB_5Sprite.Draw(rc);
	}
	

	//タブのドロー
	SuperTabSprite.Draw(rc);
	InternationaATabSprite.Draw(rc);
	InternationaBTabSprite.Draw(rc);
	DomesticATabSprite.Draw(rc);
	DomesticBTabSprite.Draw(rc);

	//ライセンスごとのクリア状況のドロー
	switch (LicensePage)
	{
	case 0:
		if (LicenseClearStatus[0][0] != 0) {
			B_1Sprite.Draw(rc);
		}
		if (LicenseClearStatus[0][1] != 0) {
			B_2Sprite.Draw(rc);
		}
		if (LicenseClearStatus[0][2] != 0) {
			B_3Sprite.Draw(rc);
		}
		if (LicenseClearStatus[0][3] != 0) {
			B_4Sprite.Draw(rc);
		}
		if (LicenseClearStatus[0][4] != 0) {
			B_5Sprite.Draw(rc);
		}
		break;

	default:
		break;
	}

	//アローのドロー
	ArrowSprite.Draw(rc);

	//オールクリア状況のドロー
	if (AllGoldState == true) {
		AllGoldClearSprite.Draw(rc);
	}
	if (AllSilverState == true) {
		AllSilverClearSprite.Draw(rc);
	}
	if (AllBronzeState == true) {
		AllBronzeClearSprite.Draw(rc);
	}

	ErrorWindowSprite.Draw(rc);
	WindowBottonOKSprite.Draw(rc);
	FadeSprite.Draw(rc);
}