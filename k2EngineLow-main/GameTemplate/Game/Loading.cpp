#include "stdafx.h"
#include "PageNum.h"
#include "Loading.h"
#include "Menu.h"
#include "RaceMenu.h"
#include "Garage.h"
#include "MainRaceManager.h"
#include "TimeTrialMode.h"
#include "Tips.h"
#include "GameCamera.h"
#include "LicenseMode.h"
#include "LicenseRace.h"
#include "OptionMenu.h"
#include <math.h>
#include <map>
#include <random>
#include "BackGround.h"

//このクラスの呼び出しは一番重くする。

Loading::Loading() {

}

Loading::~Loading() {

}

bool Loading::Start() {
    if (WhereGo==LicenseModePage|| WhereGo==RaceMenuPage) {
        m_BackGround = FindGO<BackGround>("background");
        if (m_BackGround != nullptr) {
            m_BackGround->SetGameEnd(true);
        }
    }

    Base.Init("Assets/Sprite/Loading/Base.DDS", 1600.0f, 900.0f);
    

	BlackOut.Init("Assets/Sprite/Loading/BlackOut.DDS", 1600.0f, 900.0f);
	BlackOut.SetMulColor(BlackOutColor);

	BlackOut.Update();
	SetTips(CarState, CourseState);
	return true;
}

// ランダムにTipsを選ぶ関数
// ランダムにTipsを選ぶ関数
const char* getRandomTip(const std::map<int, const char*>& tipsList) {
    if (tipsList.empty()) return "No Tips Available";
    int randomIndex = rand() % tipsList.size();
    return getTipsFromList(tipsList, randomIndex);
}

// すべてのTipsを集める関数
std::vector<const char*> collectAllTips() {
    std::vector<const char*> allTips;

    // コースのTipsを集める
    for (const auto& tip : SebringTipsList) {
        allTips.push_back(tip.second);
    }
    for (const auto& tip : LeMansTipsList) {
        allTips.push_back(tip.second);
    }
    for (const auto& tip : MonzaTipsList) {
        allTips.push_back(tip.second);
    }
    // 車種のTipsを集める
    for (const auto& tip : ORECA07TipsList) {
        allTips.push_back(tip.second);
    }
    for (const auto& tip : TOYOTA86GTTipsList) {
        allTips.push_back(tip.second);
    }
    for (const auto& tip : FD3STipsList) {
        allTips.push_back(tip.second);
    }
    for (const auto& tip : A90SupraTipsList) {
        allTips.push_back(tip.second);
    }
    for (const auto& tip : GTRR35TipsList) {
        allTips.push_back(tip.second);
    }

    return allTips;
}

// すべてのTipsからランダムに1つ選ぶ関数
const char* getRandomTipFromAll() {
    std::vector<const char*> allTips = collectAllTips();
    if (allTips.empty()) return "No Tips Available";
    int randomIndex = rand() % allTips.size();
    return allTips[randomIndex];
}

// コースまたは車種に基づいてランダムに1つのTipsを選ぶ関数
const char* getLoadingScreenTip(int course, int car) {
    const char* tip = "Unknown";

    // コースと車種のTipsリストをランダムに選択する
    if (course >= 0 || car >= 0) {
        int choice = rand() % 2; // 0か1をランダムに選ぶ

        if (choice == 0) {
            // コースのTipsを選択
            if (course == 0) {
                tip = getRandomTip(SebringTipsList);
            }
            else if (course == 1) {
                tip = getRandomTip(LeMansTipsList);
            }
            else if (course == 2) {
                tip = getRandomTip(MonzaTipsList);
            }

        }
        else {
            // 車種のTipsを選択
            if (car == 0) {
                tip = getRandomTip(ORECA07TipsList);
            }
            else if (car == 1) {
                tip = getRandomTip(TOYOTA86GTTipsList);
            }
            else if (car == 2) {
                tip = getRandomTip(A90SupraTipsList);
            }
            else if (car == 3) {
                tip = getRandomTip(GTRR35TipsList);
            }
            else if (car == 4) {
                tip = getRandomTip(FD3STipsList);
            }

        }
    }
    else {
        // コースと車の情報がない場合はすべてのTipsからランダムに選択
        tip = getRandomTipFromAll();
    }

    return tip;
}


void Loading::SetTips(int CarState, int CourseState) {
    srand(static_cast<unsigned int>(time(0)));

    // ロード画面で表示するTipsを取得
    TipsSprite.Init(getLoadingScreenTip(CourseState, CarState), 1600.0f, 900.0f);

    if (CarState != -1) {
        switch (CarState)
        {
        case ORECA07:
            CarLogo.Init("Assets/Sprite/Loading/ORECALogo.DDS", 1600.0f, 900.0f);
            break;
        case TOYOTA86GT:
            CarLogo.Init("Assets/Sprite/Loading/TOYOTALogo.DDS", 1600.0f, 900.0f);
            break;
        case TOYOTA90Supra:
            CarLogo.Init("Assets/Sprite/Loading/TOYOTALogo.DDS", 1600.0f, 900.0f);
            break;
        case NissanGTR_17:
            CarLogo.Init("Assets/Sprite/Loading/NISSANLogo.DDS", 1600.0f, 900.0f);
            break;
        case MazdaRX_7FD3SSpiritRTypeA:
            CarLogo.Init("Assets/Sprite/Loading/MAZDALogo.DDS", 1600.0f, 900.0f);
            break;
        default:
            break;
        }
    }

    if (CourseState != -1) {
        switch (CourseState)
        {
        case sebring:
            CourseLogo.Init("Assets/Sprite/Loading/SebringLogo.DDS", 1600.0f, 900.0f);
            break;
        case CircuitDeLaSarthe:
            CourseLogo.Init("Assets/Sprite/Loading/LeMansLogo.DDS", 1600.0f, 900.0f);
            break;
        case AutodromoNazionaleDiMonza:
            CourseLogo.Init("Assets/Sprite/Loading/MonzaLogo.DDS", 1600.0f, 900.0f);
            break;
        default:
            break;
        }
    }
}

void Loading::Update() {
    
    if (LoadCount < 5) {
        BlackOutColor.w -= 0.2f;
        BlackOut.SetMulColor(BlackOutColor);
    }
    else if (LoadCount > 6) {
        HandleSceneTransition();
    }

    BlackOut.Update();
    LoadCount++;
}


//どこから来たの選別
void Loading::HandleSceneTransition() {
    switch (WhereCome) {
    case TitlePage:
        HandleTitlePageTransition();
        break;
    case WorldMenuPage:
        HandleWorldMenuPageTransition();
        break;
    case GaragePage:
        HandleGaragePageTransition();
        break;
    case LicenseModePage:
        HandleLicenseModeTransition();
        break;
    case RaceMenuPage:
        HandleRaceMenuPageTransition();
        break;
    case RaceLobbyPage:
        HandleRaceLobbyPageTransition();
        break;
    case PlayPage:
        HandlePlayPageTransition();
        break;
    case OptionPage:
        HandleOptionPageTransition();
        break;
    default:
        break;
    }
}

//タイトルから
void Loading::HandleTitlePageTransition() {
    if (FadeCount == 0) 
        m_menu = NewGO<Menu>(1, "menu");
        HandleFadeOutTransition();
}


//メインメニュー(ワールドメニュー)から
void Loading::HandleWorldMenuPageTransition() {
    //レースメニューへ
    if (WhereGo == RaceMenuPage) {
        if (FadeCount == 0) 
            m_racemenu = NewGO<RaceMenu>(0, "racemenu");
           HandleFadeOutTransition();
    }
    else if (WhereGo == LicenseModePage) {
        if (FadeCount == 0)
            m_LicenseMode = NewGO<LicenseMode>(0, "licensemode");
        HandleFadeOutTransition();
    }
    else if (WhereGo == GaragePage) {
        if (FadeCount == 0)
            m_Garage = NewGO<Garage>(0, "garage");
        HandleFadeOutTransition();
    }
    else if (WhereGo == OptionPage) {
        if (FadeCount == 0) {
            m_OptionMenu = NewGO<OptionMenu>(0, "optionmenu");
            m_OptionMenu->SetWhereComePage(WhereCome);
        }
        HandleFadeOutTransition();
    }
}


//ガレージから
void Loading::HandleGaragePageTransition() {
    //ワールドメニューへ戻る
    if (WhereGo == WorldMenuPage) {
        if (FadeCount == 0)
            m_menu = NewGO<Menu>(1, "menu");
        HandleFadeOutTransition();
    }
}

//レースメニューから
void Loading::HandleRaceMenuPageTransition() {
    //レースロビーへ
    if (WhereGo == RaceLobbyPage) {
        if (FadeCount == 0) {
            m_MainRaceManager = NewGO<MainRaceManager>(0, "mainracemanager");
            m_MainRaceManager->SetCourseNum(CourseState);
            m_MainRaceManager->SetCarInformation(CarState);
        }
            HandleFadeOutTransition();
    }
    
    //ワールドメニューへ戻る
    if (WhereGo == WorldMenuPage) {
        if (FadeCount == 0)
            m_menu = NewGO<Menu>(1, "menu");
        HandleFadeOutTransition();
    } 
}

//ライセンスモードから
void Loading::HandleLicenseModeTransition() {
    //レースロビーへ
    if (WhereGo == RaceLobbyPage) {
        if (FadeCount == 0) {
            m_MainRaceManager = NewGO<MainRaceManager>(0, "mainracemanager");
            m_MainRaceManager->SetCourseNum(CourseState);
            m_MainRaceManager->SetCarInformation(CarState);
            m_MainRaceManager->SetLicenseNum(LicenseNum);
        }
        HandleFadeOutTransition();
    }
    //ワールドメニューへ戻る
    if (WhereGo == WorldMenuPage) {
        if (FadeCount == 0)
            m_menu = NewGO<Menu>(1, "menu");
        HandleFadeOutTransition();
    }
}

//レースロビーから
void Loading::HandleRaceLobbyPageTransition() {
    //インゲームへ
    if (WhereGo == PlayPage) {
        if (FadeCount == 0) {
            m_gamecamera = FindGO<GameCamera>("gamecamera");
            if (LicenseNum == 0) {
                m_TimeTrialMode = NewGO<TimeTrialMode>(0, "timetrialmode");
                m_TimeTrialMode->SetGameMode(CircuitExperience);
            }
            else {
                m_LicenseRace = NewGO<LicenseRace>(0, "licenserace");
                m_LicenseRace->SetLicenseNum(LicenseNum);
                m_LicenseRace->SetCourseNum(CourseState);
            }
            m_gamecamera->SetPlayFlag(true);
        }
        HandleFadeOutTransition();
    }
    //レースメニューへ戻る
       if (WhereGo == RaceMenuPage) {
           if (FadeCount == 0)
               m_racemenu = NewGO<RaceMenu>(0, "racemenu");
           HandleFadeOutTransition();
       }
    //ライセンスモードの時
       else {
           if (FadeCount == 0)
               m_LicenseMode = NewGO<LicenseMode>(0, "licensemode");
           HandleFadeOutTransition();
       }

}

//インゲームから
void Loading::HandlePlayPageTransition() {
    //レースロビーへ戻る
    if (WhereGo == RaceLobbyPage) {
        if (FadeCount == 0) {
            m_MainRaceManager = NewGO<MainRaceManager>(0, "mainracemanager");
            m_MainRaceManager->SetCourseNum(CourseState);
            m_MainRaceManager->SetCarInformation(CarState);
            m_MainRaceManager->SetLicenseNum(LicenseNum);
            m_MainRaceManager->SetWhereComePage(WhereCome);
        }
        HandleFadeOutTransition();
    }
    
    if (WhereGo == PlayPage) {
        if (LicenseNum == 0) {
            if (FadeCount == 0) {
                m_gamecamera = FindGO<GameCamera>("gamecamera");
                m_TimeTrialMode = NewGO<TimeTrialMode>(0, "timetrialmode");
                m_gamecamera->SetPlayFlag(true);
            }
            HandleFadeOutTransition();
        }
        else {
            if (FadeCount == 0) {
                m_gamecamera = FindGO<GameCamera>("gamecamera");
                m_LicenseRace = NewGO<LicenseRace>(0, "licenserace");
                m_LicenseRace->SetLicenseNum(LicenseNum);
                m_LicenseRace->SetCourseNum(CourseState);
                m_gamecamera->SetPlayFlag(true);
            }
            HandleFadeOutTransition();
        }
    }
}

//オプションメニューから
void Loading::HandleOptionPageTransition() {
    //ワールドメニューへ戻る
    if (WhereGo == WorldMenuPage) {
        if (FadeCount == 0)
            m_menu = NewGO<Menu>(1, "menu");
        HandleFadeOutTransition();
    }
}

//遷移
void Loading::HandleFadeOutTransition() {
    if (FadeCount > 5) {
        DeleteGO(this);
    }
    else {
        BlackOutColor.w += 0.2f;
        BlackOut.SetMulColor(BlackOutColor);
        FadeCount++;
    }
}



void Loading::Render(RenderContext& rc) {
    Base.Draw(rc);
    TipsSprite.Draw(rc);
    if (CarState != -1) {
        CarLogo.Draw(rc);
    }
    if (CourseState != -1) {
        CourseLogo.Draw(rc);
    }
    BlackOut.Draw(rc);
}
