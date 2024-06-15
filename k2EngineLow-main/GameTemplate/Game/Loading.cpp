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

//���̃N���X�̌Ăяo���͈�ԏd������B

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

// �����_����Tips��I�Ԋ֐�
// �����_����Tips��I�Ԋ֐�
const char* getRandomTip(const std::map<int, const char*>& tipsList) {
    if (tipsList.empty()) return "No Tips Available";
    int randomIndex = rand() % tipsList.size();
    return getTipsFromList(tipsList, randomIndex);
}

// ���ׂĂ�Tips���W�߂�֐�
std::vector<const char*> collectAllTips() {
    std::vector<const char*> allTips;

    // �R�[�X��Tips���W�߂�
    for (const auto& tip : SebringTipsList) {
        allTips.push_back(tip.second);
    }


    // �Ԏ��Tips���W�߂�
    for (const auto& tip : ORECA07TipsList) {
        allTips.push_back(tip.second);
    }


    return allTips;
}

// ���ׂĂ�Tips���烉���_����1�I�Ԋ֐�
const char* getRandomTipFromAll() {
    std::vector<const char*> allTips = collectAllTips();
    if (allTips.empty()) return "No Tips Available";
    int randomIndex = rand() % allTips.size();
    return allTips[randomIndex];
}

// �R�[�X�܂��͎Ԏ�Ɋ�Â��ă����_����1��Tips��I�Ԋ֐�
const char* getLoadingScreenTip(int course, int car) {
    const char* tip = "Unknown";

    // �R�[�X�ƎԎ��Tips���X�g�������_���ɑI������
    if (course >= 0 || car >= 0) {
        int choice = rand() % 2; // 0��1�������_���ɑI��

        if (choice == 0) {
            // �R�[�X��Tips��I��
            if (course == 0) {
                tip = getRandomTip(SebringTipsList);
            }

        }
        else {
            // �Ԏ��Tips��I��
            if (car == 0) {
                tip = getRandomTip(ORECA07TipsList);
            }

        }
    }
    else {
        // �R�[�X�ƎԂ̏�񂪂Ȃ��ꍇ�͂��ׂĂ�Tips���烉���_���ɑI��
        tip = getRandomTipFromAll();
    }

    return tip;
}


void Loading::SetTips(int CarState, int CourseState) {
    srand(static_cast<unsigned int>(time(0)));

    // ���[�h��ʂŕ\������Tips���擾
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


//�ǂ����痈���̑I��
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

//�^�C�g������
void Loading::HandleTitlePageTransition() {
    if (FadeCount == 0) 
        m_menu = NewGO<Menu>(1, "menu");
        HandleFadeOutTransition();
}


//���C�����j���[(���[���h���j���[)����
void Loading::HandleWorldMenuPageTransition() {
    //���[�X���j���[��
    if (WhereGo == RaceMenuPage) {
        if (FadeCount == 0) 
            m_racemenu = NewGO<RaceMenu>(0, "racemenu");
            HandleFadeOutTransition();
    }
}


//���[�X���j���[����
void Loading::HandleRaceMenuPageTransition() {
    //���[�X���r�[��
    if (WhereGo == RaceLobbyPage) {
        if (FadeCount == 0) {
            m_MainRaceManager = NewGO<MainRaceManager>(0, "mainracemanager");
            m_MainRaceManager->SetCourseNum(CourseState);
            m_MainRaceManager->SetCarInformation(CarState);
        }
            HandleFadeOutTransition();
    }
    //���[���h���j���[�֖߂�
    if (WhereGo == WorldMenuPage) {
        if (FadeCount == 0)
            m_menu = NewGO<Menu>(1, "menu");
        HandleFadeOutTransition();
    } 
}

//���[�X���r�[����
void Loading::HandleRaceLobbyPageTransition() {
    //�C���Q�[����
    if (WhereGo == PlayPage) {
        if (FadeCount == 0) 
            m_TimeTrialMode = NewGO<TimeTrialMode>(0, "timetrialmode");
        HandleFadeOutTransition();
    }
    //���[�X���j���[�֖߂�
    if (WhereGo == RaceMenuPage) {
        if (FadeCount == 0)
            m_racemenu = NewGO<RaceMenu>(0, "racemenu");
        HandleFadeOutTransition();
    }
}

//�C���Q�[������
void Loading::HandlePlayPageTransition() {
    //���[�X���r�[�֖߂�
    if (WhereGo == RaceLobbyPage) {
        if (FadeCount == 0) {
            m_MainRaceManager = NewGO<MainRaceManager>(0, "mainracemanager");
            m_MainRaceManager->SetCourseNum(CourseState);
            m_MainRaceManager->SetCarInformation(CarState);
        }
        HandleFadeOutTransition();
    }
}


//�J��
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
