#pragma once
#include "sound/SoundSource.h"


class MainRaceManager;
class Loading;

class RaceMenu : public IGameObject
{
public:
    RaceMenu();
    ~RaceMenu();
    bool Start();
    void CourseInformationinit(int CourseSelect);
    void Update();
    void Render(RenderContext& rc);

private:
    Vector4 m_FadeColor = { 1.0f,1.0f,1.0f,1.0f };

    Vector3 SebringPosition = { -494.0f,-290.0f,0.0f };
    Vector3 SelectPosition = { -494.0f,-290.0f,0.0f };

    MainRaceManager* m_mainracemanager;
    Loading* m_Loading;
    SoundSource* RaceMenuBGM;

    SpriteRender Main;
    SpriteRender Base;
    SpriteRender CourseExclusive;
    SpriteRender CourseSelect;
    SpriteRender CourseSelectBase_Sebring;
    SpriteRender CourseSelect_Sebring;

    SpriteRender m_FadeSprite;


    
    int CourseQuantity = 1;
    int CourseSelectPoint = 0;//0:Sebring 
    int FadeCount = 0;
    int FadeState = 0;


};
