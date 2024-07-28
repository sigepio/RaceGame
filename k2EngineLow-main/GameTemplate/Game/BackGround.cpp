#include "stdafx.h"
#include "BackGround.h"
#include "Sebring.h"
#include "LeMans.h"

BackGround::BackGround()
{
}

BackGround::~BackGround()
{
}

bool BackGround::Start()
{
    //m_Sebring = NewGO<Sebring>(0, "sebring");
    m_LeMans = NewGO<LeMans>(0, "lemans");
    StartPosition = m_LeMans->GetStartPosition();
    return true;
}

void BackGround::Update()
{
    if (GameEnd) {
        DeleteGO(this);
    }
    if (m_Sebring) {
        m_Sebring->SetGameEnd(GameEnd);
    }
}

void BackGround::Render(RenderContext& rc)
{
}
