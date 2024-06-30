#include "stdafx.h"
#include "BackGround.h"
#include "Sebring.h"

BackGround::BackGround() : m_Sebring(nullptr), GameEnd(false)
{
}

BackGround::~BackGround()
{
}

bool BackGround::Start()
{
    m_Sebring = NewGO<Sebring>(0, "sebring");
    return m_Sebring != nullptr;
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
