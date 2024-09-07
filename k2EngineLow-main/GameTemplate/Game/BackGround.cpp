#include "stdafx.h"
#include "BackGround.h"
#include "Sebring.h"
#include "LeMans.h"
#include "PageNum.h"
#include "Monza.h"

BackGround::BackGround()
{
}

BackGround::~BackGround()
{
    
}

bool BackGround::Start()
{
    
    if (LicenseNum == 0) {
        switch (CourseNum)
        {
        case sebring:
            m_Sebring = NewGO<Sebring>(0, "sebring");
            StartPosition = m_Sebring->GetStartPosition();
            StartForward = { 0.0f,0.0f,1.0f };
            break;
        case CircuitDeLaSarthe:
            m_LeMans = NewGO<LeMans>(0, "lemans");
            StartPosition = m_LeMans->GetStartPosition();
            StartForward = { 0.0f,0.0f,1.0f };
            break;
        case AutodromoNazionaleDiMonza:
            m_Monza = NewGO<Monza>(0, "monza");
            StartPosition = m_Monza->GetStartPosition();
            StartForward = { 0.0f,0.0f,1.0f };
            break;
        default:
            break;
        }
    }
    else {
        if (LicenseNum == 1 || LicenseNum == 2) {
            m_Monza = NewGO<Monza>(0, "monza");
            StartPosition = m_Monza->GetStartPosition();
        }
        else if (LicenseNum == 3 || LicenseNum == 4) {
            m_Monza = NewGO<Monza>(0, "monza");
            StartPosition = { -4589.0f , -226.0f , -16192.0f};
            StartForward = { -0.112f , 0.0f , -0.994f };
        }
        else if (LicenseNum == 5) {
            m_Sebring = NewGO<Sebring>(0, "sebring");
            StartPosition = { -10626,-40,2154 };
            StartForward = { 0.026,0.0,-1 };
        }
    }
    
    return true;
}

void BackGround::Update()
{
    if (GameEnd == true) {
        
        if (m_Sebring) {
            m_Sebring->SetGameEnd(GameEnd);
        }
        if (m_LeMans) {
            m_LeMans->SetGameEnd(GameEnd);
        }
        if (m_Monza) {
            m_Monza->SetGameEnd(GameEnd);
        }
        DeleteGO(this);
    }
}

void BackGround::Render(RenderContext& rc)
{
    
}
