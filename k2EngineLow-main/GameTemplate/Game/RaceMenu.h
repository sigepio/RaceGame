#pragma once
#include "sound/SoundSource.h"


class MainRaceManager;
class Loading;
class Player;

class RaceMenu : public IGameObject
{
public:
    RaceMenu();
    ~RaceMenu();
    bool Start();
    void CourseInformationinit(int CourseSelect);
    void Update();
    void Render(RenderContext& rc);

    void SetModeState(int m_ModeState) {
        SelectRaceMode = m_ModeState;
    }

private:
    Vector4 m_FadeColor = { 1.0f,1.0f,1.0f,1.0f };

    Vector3 LeMansPosition = { -620.0f,-290.0f,0.0f };
    Vector3 MonzaPosition = { -310.0f,-290.0f,0.0f };
    Vector3 ImolaPosition = { 0.0f,-290.0f,0.0f };
    Vector3 SilverStonePosition = { 310.0f,-290.0f,0.0f };

    Vector3 CEPosition = { -160.0f,-290.0f,0.0f };
    Vector3 TTPosition = { 160.0f, -290.0f,0.0f };
    Vector3 SelectPosition = { -620.0f,-290.0f,0.0f };

    MainRaceManager* m_mainracemanager;
    Loading* m_Loading;
    SoundSource* RaceMenuBGM;
    SoundSource* CursorSE;
    SoundSource* DecisionSE;
    SoundSource* CancelSE;
    Player* m_player;

    //背景
    SpriteRender Main_LeMans;
    SpriteRender Main_Monza;
    SpriteRender Main_Imola;
    SpriteRender Main_SilverStone;
    SpriteRender Base;
    //情報
    SpriteRender CourseExclusive_LeMans;
    SpriteRender CourseExclusive_Monza;
    SpriteRender CourseExclusive_Imola;
    SpriteRender CourseExclusive_SilverStone;
    //黄土色
    SpriteRender CourseSelect;
    //灰色     
    SpriteRender CourseSelectBase_LeMans;
    SpriteRender CourseSelectBase_Monza;
    SpriteRender CourseSelectBase_Imola;
    SpriteRender CourseSelectBase_SilverStone;

    SpriteRender ModeSelectBase_CE;
    SpriteRender ModeSelectBase_TT;
    //下の枠内
    SpriteRender CourseSelect_LeMans;
    SpriteRender CourseSelect_Monza;
    SpriteRender CourseSelect_Imola;
    SpriteRender CourseSelect_SilverStone;

    SpriteRender ModeSelect_CE;
    SpriteRender ModeSelect_TT;

    SpriteRender m_FadeSprite;


    
    int CourseQuantity = 1;
    int CourseSelectPoint = 0;  //0:Sebring 
    int FadeCount = 0;
    int FadeState = 0;
    int SelectRaceMode = 0;     //0:サーキットエクスペリエンス 1:タイムトライアル
    int MaxMode = 2;
    int SelectArea = 0;         //0:コース選択 1:モード選択

    int MaxCourseNum = 4;

    int RideCar = 0;

};
