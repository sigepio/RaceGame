#include "stdafx.h"
#include "BackGround.h"
#include "Sebring.h"

BackGround::BackGround()
{

}

BackGround::~BackGround()
{

}
bool BackGround::Start()
{

	m_Sebring = NewGO<Sebring>(0, "sebring");

	return true;
}
void BackGround::Update()
{

	if (GameEnd == true) {
		DeleteGO(this);
	}
	m_Sebring->SetGameEnd(GameEnd);
}

void BackGround::Render(RenderContext& rc)
{
}