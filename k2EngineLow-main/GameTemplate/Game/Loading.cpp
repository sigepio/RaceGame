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

//���̃N���X�̌Ăяo���͈�ԏd������B

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
    for (const auto& tip : LeMansTipsList) {
        allTips.push_back(tip.second);
    }
    for (const auto& tip : MonzaTipsList) {
        allTips.push_back(tip.second);
    }
    // �Ԏ��Tips���W�߂�
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
            else if (course == 1) {
                tip = getRandomTip(LeMansTipsList);
            }
            else if (course == 2) {
                tip = getRandomTip(MonzaTipsList);
            }

        }
        else {
            // �Ԏ��Tips��I��
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


//�ǂ����痈���̑I��
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


//�K���[�W����
void Loading::HandleGaragePageTransition() {
    //���[���h���j���[�֖߂�
    if (WhereGo == WorldMenuPage) {
        if (FadeCount == 0)
            m_menu = NewGO<Menu>(1, "menu");
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

//���C�Z���X���[�h����
void Loading::HandleLicenseModeTransition() {
    //���[�X���r�[��
    if (WhereGo == RaceLobbyPage) {
        if (FadeCount == 0) {
            m_MainRaceManager = NewGO<MainRaceManager>(0, "mainracemanager");
            m_MainRaceManager->SetCourseNum(CourseState);
            m_MainRaceManager->SetCarInformation(CarState);
            m_MainRaceManager->SetLicenseNum(LicenseNum);
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
    //���[�X���j���[�֖߂�
       if (WhereGo == RaceMenuPage) {
           if (FadeCount == 0)
               m_racemenu = NewGO<RaceMenu>(0, "racemenu");
           HandleFadeOutTransition();
       }
    //���C�Z���X���[�h�̎�
       else {
           if (FadeCount == 0)
               m_LicenseMode = NewGO<LicenseMode>(0, "licensemode");
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

//�I�v�V�������j���[����
void Loading::HandleOptionPageTransition() {
    //���[���h���j���[�֖߂�
    if (WhereGo == WorldMenuPage) {
        if (FadeCount == 0)
            m_menu = NewGO<Menu>(1, "menu");
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
