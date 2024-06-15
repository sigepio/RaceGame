#include "stdafx.h"
#include "PageNum.h"
#include "Loading.h"
#include "Menu.h"
#include "RaceMenu.h"
#include "MainRaceManager.h"
#include "TimeTrialMode.h"
#include "Tips.h"
#include <math.h>
#include <map>
#include <random>

//このクラスの呼び出しは一番重くする。

Loading::Loading() {

}

Loading::~Loading() {

}

bool Loading::Start() {
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


    // 車種のTipsを集める
    for (const auto& tip : ORECA07TipsList) {
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

        }
        else {
            // 車種のTipsを選択
            if (car == 0) {
                tip = getRandomTip(ORECA07TipsList);
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
        default:
            break;
        }
    }

    if (CourseState != -1) {
        switch (CourseState)
        {
        case Sebring:
            CourseLogo.Init("Assets/Sprite/Loading/SebringLogo.DDS", 1600.0f, 900.0f);
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
    case RaceMenuPage:
        HandleRaceMenuPageTransition();
        break;
    case RaceLobbyPage:
        HandleRaceLobbyPageTransition();
        break;
    case PlayPage:
        HandlePlayPageTransition();
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

//レースロビーから
void Loading::HandleRaceLobbyPageTransition() {
    //インゲームへ
    if (WhereGo == PlayPage) {
        if (FadeCount == 0) 
            m_TimeTrialMode = NewGO<TimeTrialMode>(0, "timetrialmode");
        HandleFadeOutTransition();
    }
    //レースメニューへ戻る
    if (WhereGo == RaceMenuPage) {
        if (FadeCount == 0)
            m_racemenu = NewGO<RaceMenu>(0, "racemenu");
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
        }
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
