#include "stdafx.h"
#include "CarChange.h"
#include "Player.h"
#include <vector>
#include "Loading.h"


CarChange::CarChange() {

}

CarChange::~CarChange() {

}

bool CarChange::Start() {
    m_player = FindGO<Player>("player");

    FadeSprite.Init("Assets/Sprite/BlackOut.DDS", 1600.0f, 900.0f);
    CarListSprite.Init("Assets/Sprite/CarChange/CarList.DDS", 2879.0f, 699.0f);

    CarListSprite.SetPosition(CarListPos);

    CarListSprite.Update();


    BaseSprite.Init("Assets/Sprite/CarChange/Base.DDS", 1600.0f, 900.0f);

    ArrowSprite.Init("Assets/Sprite/Lobby/Arrow.DDS", 39.0f, 36.5f);
    ArrowSprite.SetPosition(ArrowSpritePos);
    ArrowSprite.Update();


    BGM = NewGO<SoundSource>(0);
    BGM->Init(13);
    BGM->SetVolume(m_player->GetBGMVolume());
    BGM->Play(true);
    return true;
}



void CarChange::Update() {
    if (FadeCount < 5) {

        BlackOutColor.w -= 0.2f;
        FadeSprite.SetMulColor(BlackOutColor);
        FadeSprite.Update();
        FadeCount++;
    }
    else {
        if (g_pad[0]->IsTrigger(enButtonDown) && LocalSecectPointY < 2 && LocalSecectPointY >= 0) {
            CursorSE = NewGO<SoundSource>(0);
            CursorSE->Init(100);
            CursorSE->SetVolume(m_player->GetSEVolume());
            CursorSE->Play(false);

            ArrowSpritePos.y -= 250.0f;

            WorldSecectPointY++;
            LocalSecectPointY++;
        }
        if (g_pad[0]->IsTrigger(enButtonUp) && LocalSecectPointY <= 2 && LocalSecectPointY > 0) {
            CursorSE = NewGO<SoundSource>(0);
            CursorSE->Init(100);
            CursorSE->SetVolume(m_player->GetSEVolume());
            CursorSE->Play(false);

            ArrowSpritePos.y += 250.0f;

            WorldSecectPointY--;
            LocalSecectPointY--;
        }
        if (g_pad[0]->IsTrigger(enButtonLeft)) {

            if (LocalSelectPointX <= 3 && LocalSelectPointX > 0) {
                CursorSE = NewGO<SoundSource>(0);
                CursorSE->Init(100);
                CursorSE->SetVolume(m_player->GetSEVolume());
                CursorSE->Play(false);

                ArrowSpritePos.x -= 360.0f;
                LocalSelectPointX--;
                WorldSelectPointX--;
            }
            else if (LocalSelectPointX == 0 && WorldSelectPointX > 0) {
                CursorSE = NewGO<SoundSource>(0);
                CursorSE->Init(100);
                CursorSE->SetVolume(m_player->GetSEVolume());
                CursorSE->Play(false);

                CarListPos.x += 360.0f;
                WorldSelectPointX--;
            }

        }
        else if (g_pad[0]->IsTrigger(enButtonRight)) {
            if (LocalSelectPointX < 3 && LocalSelectPointX >= 0) {
                CursorSE = NewGO<SoundSource>(0);
                CursorSE->Init(100);
                CursorSE->SetVolume(m_player->GetSEVolume());
                CursorSE->Play(false);

                ArrowSpritePos.x += 360.0f;
                LocalSelectPointX++;
                WorldSelectPointX++;
            }
            else if (LocalSelectPointX == 3 && WorldSelectPointX < 7) {
                CursorSE = NewGO<SoundSource>(0);
                CursorSE->Init(100);
                CursorSE->SetVolume(m_player->GetSEVolume());
                CursorSE->Play(false);

                CarListPos.x -= 360.0f;
                WorldSelectPointX++;
            }

        }
        else if (g_pad[0]->IsTrigger(enButtonA)) {
            if (WorldSelectPoint[WorldSecectPointY][WorldSelectPointX] != -1) {
                DecisionSE = NewGO<SoundSource>(0);
                DecisionSE->Init(101);
                DecisionSE->SetVolume(m_player->GetSEVolume());
                DecisionSE->Play(false);

                m_player->SetRideCarNum(WorldSelectPoint[WorldSecectPointY][WorldSelectPointX]);
                FadeCount = 0;
                FadeState = true;
            }
        }
        else if (g_pad[0]->IsTrigger(enButtonB)) {
            

            CancelSE = NewGO<SoundSource>(0);
            CancelSE->Init(102);
            CancelSE->SetVolume(m_player->GetSEVolume());
            CancelSE->Play(false);


            FadeCount = 0;
            FadeState = true;
        }

        if (FadeState == true) {
            if (FadeCount < 5) {
                BlackOutColor.w += 0.2f;
                FadeSprite.SetMulColor(BlackOutColor);
                FadeSprite.Update();
                FadeCount++;
            }
            else {
                m_Loading = NewGO<Loading>(10, "loading");
                m_Loading->SetWhereCome(CarChangePage);
                m_Loading->SetWhereGo(GaragePage);
                DeleteGO(BGM);
                DeleteGO(this);
            }
        }

        CarListSprite.SetPosition(CarListPos);
        CarListSprite.Update();

        ArrowSprite.SetPosition(ArrowSpritePos);
        ArrowSprite.Update();
    }
}

void CarChange::Render(RenderContext& rc) {
    BaseSprite.Draw(rc);

    CarListSprite.Draw(rc);

    ArrowSprite.Draw(rc);

    FadeSprite.Draw(rc);
}