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

private:
    Vector4 m_FadeColor = { 1.0f,1.0f,1.0f,1.0f };

    Vector3 SebringPosition = { -620.0f,-290.0f,0.0f };
    Vector3 LeMansPosition = { -310.0f,-290.0f,0.0f };
    Vector3 MonzaPosition = { 0.0f,-290.0f,0.0f };

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

    //�w�i
    SpriteRender Main_Sebring;
    SpriteRender Main_LeMans;
    SpriteRender Main_Monza;
    SpriteRender Base;
    //���
    SpriteRender CourseExclusive_Sebring;
    SpriteRender CourseExclusive_LeMans;
    SpriteRender CourseExclusive_Monza;
    //���y�F
    SpriteRender CourseSelect;
    //�D�F
    SpriteRender CourseSelectBase_Sebring;          
    SpriteRender CourseSelectBase_LeMans;
    SpriteRender CourseSelectBase_Monza;

    SpriteRender ModeSelectBase_CE;
    SpriteRender ModeSelectBase_TT;
    //���̘g��
    SpriteRender CourseSelect_Sebring;
    SpriteRender CourseSelect_LeMans;
    SpriteRender CourseSelect_Monza;

    SpriteRender ModeSelect_CE;
    SpriteRender ModeSelect_TT;

    SpriteRender m_FadeSprite;


    
    int CourseQuantity = 1;
    int CourseSelectPoint = 0;  //0:Sebring 
    int FadeCount = 0;
    int FadeState = 0;
    int SelectRaceMode = 0;     //0:�T�[�L�b�g�G�N�X�y���G���X 1:�^�C���g���C�A��
    int MaxMode = 2;
    int SelectArea = 0;         //0:�R�[�X�I�� 1:���[�h�I��

    int MaxCourseNum = 3;

    int RideCar = 0;

};
