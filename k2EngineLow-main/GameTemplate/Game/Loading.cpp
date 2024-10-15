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
#include "PageNum.h"
#include "CarChange.h"
#include "ModeSelect.h"

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

    for (const auto& tip : LFATipsList) {
        allTips.push_back(tip.second);
    }
    for (const auto& tip : MustangGT3TipsList) {
        allTips.push_back(tip.second);
    }
    for (const auto& tip : R35GT3TipsList) {
        allTips.push_back(tip.second);
    }
    for (const auto& tip : FordGTLMTipsList) {
        allTips.push_back(tip.second);
    }
    for (const auto& tip : FordGTGT3TipsList) {
        allTips.push_back(tip.second);
    }
    for (const auto& tip : FordGTTipsList) {
        allTips.push_back(tip.second);
    }
    for (const auto& tip : C9TipsList) {
        allTips.push_back(tip.second);
    }
    for (const auto& tip : BMWMHybridV8TipsList) {
        allTips.push_back(tip.second);
    }
    for (const auto& tip : Porsche962CTipsList) {
        allTips.push_back(tip.second);
    }
    for (const auto& tip : Porsche911GT3RSRTipsList) {
        allTips.push_back(tip.second);
    }
    for (const auto& tip : Porsche911GT3RSTipsList) {
        allTips.push_back(tip.second);
    }
    for (const auto& tip : Mazda787BTipsList) {
        allTips.push_back(tip.second);
    }
    for (const auto& tip :Ferrari499PTipsList) {
        allTips.push_back(tip.second);
    }
    for (const auto& tip :RB19TipsList) {
        allTips.push_back(tip.second);
    }
    for (const auto& tip : X2010TipsList) {
        allTips.push_back(tip.second);
    }
    for (const auto& tip : GR010TipsList) {
        allTips.push_back(tip.second);
    }
    for (const auto& tip : TS050TipsList) {
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
           if (course == 1) {
                tip = getRandomTip(LeMansTipsList);
            }
            else if (course == 2) {
                tip = getRandomTip(MonzaTipsList);
            }
            else if (course == 3) {
                tip = getRandomTip(ImolaTipsList);
            }
            else if (course == 4) {
                tip = getRandomTip(SilverStoneTipsList);
            }
            //�Ȃ������ꍇ
            else {
                // �R�[�X�ƎԂ̏�񂪂Ȃ��ꍇ�͂��ׂĂ�Tips���烉���_���ɑI��
                tip = getRandomTipFromAll();
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

            else if (car == LexusLFA) {
                tip = getRandomTip(LFATipsList);
            }
            else if (car == FordMustangGT3) {
                tip = getRandomTip(MustangGT3TipsList);
            }
            else if (car == NissanR35GT3) {
                tip = getRandomTip(R35GT3TipsList);
            }
            else if (car == FordGTLMRaceCarSpecii) {
                tip = getRandomTip(FordGTLMTipsList);
            }
            else if (car == FordGTGT3GTE) {
                tip = getRandomTip(FordGTGT3TipsList);
            }
            else if (car == FordGT2006) {
                tip = getRandomTip(FordGTTipsList);
            }
            else if (car == SauberMercedesC9) {
                tip = getRandomTip(C9TipsList);
            }
            else if (car == BMWMHybridV8) {
                tip = getRandomTip(BMWMHybridV8TipsList);
            }
            else if (car == Porsche962C) {
                tip = getRandomTip(Porsche962CTipsList);
            }
            else if (car == Porsche911GT3RSR) {
                tip = getRandomTip(Porsche911GT3RSRTipsList);
            }
            else if (car == Porsche911GT3RS) {
                tip = getRandomTip(Porsche911GT3RSTipsList);
            }
            else if (car == Mazda787B) {
                tip = getRandomTip(Mazda787BTipsList);
            }
            else if (car == Ferrari499P) {
                tip = getRandomTip(Ferrari499PTipsList);
            }
            else if (car == RedBullRB19) {
                tip = getRandomTip(RB19TipsList);
            }
            else if (car == RedBullX2010) {
                tip = getRandomTip(X2010TipsList);
            }
            else if (car == TOYOTAGR010HYBRID) {
                tip = getRandomTip(GR010TipsList);
            }
            else if (car == TOYOTATS050HYBRID) {
                tip = getRandomTip(TS050TipsList);
            }

            //�Ȃ������ꍇ
            else {
                // �R�[�X�ƎԂ̏�񂪂Ȃ��ꍇ�͂��ׂĂ�Tips���烉���_���ɑI��
                tip = getRandomTipFromAll();
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

        case LexusLFA:
            CarLogo.Init("Assets/Sprite/Loading/LexusLogo.DDS", 1600.0f, 900.0f);
            break;
        case FordMustangGT3:
            CarLogo.Init("Assets/Sprite/Loading/FordLogo.DDS", 1600.0f, 900.0f);
            break;
        case NissanR35GT3:
            CarLogo.Init("Assets/Sprite/Loading/NISSANLogo.DDS", 1600.0f, 900.0f);
            break;
        case FordGTLMRaceCarSpecii:
            CarLogo.Init("Assets/Sprite/Loading/FordLogo.DDS", 1600.0f, 900.0f);
            break;
        case FordGTGT3GTE:
            CarLogo.Init("Assets/Sprite/Loading/FordLogo.DDS", 1600.0f, 900.0f);
            break;
        case FordGT2006:
            CarLogo.Init("Assets/Sprite/Loading/FordLogo.DDS", 1600.0f, 900.0f);
            break;
        case SauberMercedesC9:
            CarLogo.Init("Assets/Sprite/Loading/MercedesLogo.DDS", 1600.0f, 900.0f);
            break;
        case BMWMHybridV8:
            CarLogo.Init("Assets/Sprite/Loading/BMWLogo.DDS", 1600.0f, 900.0f);
            break;
        case Porsche962C:
            CarLogo.Init("Assets/Sprite/Loading/PorscheLogo.DDS", 1600.0f, 900.0f);
            break;
        case Porsche911GT3RSR:
            CarLogo.Init("Assets/Sprite/Loading/PorscheLogo.DDS", 1600.0f, 900.0f);
            break;
        case Porsche911GT3RS:
            CarLogo.Init("Assets/Sprite/Loading/PorscheLogo.DDS", 1600.0f, 900.0f);
            break;
        case Mazda787B:
            CarLogo.Init("Assets/Sprite/Loading/MAZDALogo.DDS", 1600.0f, 900.0f);
            break;
        case Ferrari499P:
            CarLogo.Init("Assets/Sprite/Loading/FerrariLogo.DDS", 1600.0f, 900.0f);
            break;
        case RedBullRB19:
            CarLogo.Init("Assets/Sprite/Loading/RedBullLogo.DDS", 1600.0f, 900.0f);
            break;
        case RedBullX2010:
            CarLogo.Init("Assets/Sprite/Loading/RedBullLogo.DDS", 1600.0f, 900.0f);
            break;
        case TOYOTAGR010HYBRID:
            CarLogo.Init("Assets/Sprite/Loading/TOYOTALogo.DDS", 1600.0f, 900.0f);
            break;
        case TOYOTATS050HYBRID:
            CarLogo.Init("Assets/Sprite/Loading/TOYOTALogo.DDS", 1600.0f, 900.0f);
            break;
        default:
            break;
        }
    }

    if (CourseState != -1) {
        switch (CourseState)
        {
        case CircuitDeLaSarthe:
            CourseLogo.Init("Assets/Sprite/Loading/LeMansLogo.DDS", 1600.0f, 900.0f);
            break;
        case AutodromoNazionaleDiMonza:
            CourseLogo.Init("Assets/Sprite/Loading/MonzaLogo.DDS", 1600.0f, 900.0f);
            break;
        case SilverstoneCircuit:
            CourseLogo.Init("Assets/Sprite/Loading/SilverStoneLogo.DDS", 1600.0f, 900.0f);
            break;
        case ImolaCircuit:
            CourseLogo.Init("Assets/Sprite/Loading/ImolaLogo.DDS", 1600.0f, 900.0f);
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
    case CarChangePage:
        HandleCarChangePageTransition();
        break;
    case ModeSelectPage:
        HandleModeSelectPageTransition();
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
    //���[�h�I����
    if (WhereGo == ModeSelectPage) {
        if (FadeCount == 0)
            m_ModeSelect = NewGO<ModeSelect>(0, "modeselect");
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
    //��芷���y�[�W��
    if (WhereGo == CarChangePage) {
        if (FadeCount == 0)
            m_CarChange = NewGO<CarChange>(1, "carchange");
        HandleFadeOutTransition();
    }
}

//���[�h�I������
void Loading::HandleModeSelectPageTransition() {
    //���[�X���j���[��
    if (WhereGo == RaceMenuPage) {
        if (FadeCount == 0) {
            m_racemenu = NewGO<RaceMenu>(0, "racemenu");
            m_racemenu->SetModeState(ModeState);
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

//���[�X���j���[����
void Loading::HandleRaceMenuPageTransition() {
    //���[�X���r�[��
    if (WhereGo == RaceLobbyPage) {
        if (FadeCount == 0) {
            m_MainRaceManager = NewGO<MainRaceManager>(0, "mainracemanager");
            m_MainRaceManager->SetCourseNum(CourseState);
            m_MainRaceManager->SetCarInformation(CarState);
            m_MainRaceManager->SetModeState(ModeState);
        }
            HandleFadeOutTransition();
    }
    
    //���[�h�I����
    if (WhereGo == ModeSelectPage) {
        if (FadeCount == 0)
            m_ModeSelect = NewGO<ModeSelect>(0, "modeselect");
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
                m_TimeTrialMode->SetGameMode(ModeState);
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

//��芷���y�[�W����
void Loading::HandleCarChangePageTransition() {
    //�K���[�W��
    if (WhereGo == GaragePage) {
        if (FadeCount == 0)
            m_Garage = NewGO<Garage>(0, "garage");
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
