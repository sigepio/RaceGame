#pragma once

class Sebring;
class LeMans;
class Monza;
class Imola;
class SilverStone;

class BackGround : public IGameObject, Noncopyable
{
public:
    BackGround();
    ~BackGround();

    bool Start() override;
    void Update() override;
    void Render(RenderContext& rc) override;

    void SetGameEnd(bool m_GameEnd) {
        GameEnd = m_GameEnd;
    }

    void SetCourse(int m_CourseNum) {
        CourseNum = m_CourseNum;
    }

    void SetLicenseNum(int m_LicenseNum) {
        LicenseNum = m_LicenseNum;
    }

    void SetFinishPoint(Vector3 m_FinishPoint) {
        FinishPoint = m_FinishPoint;
    }

    void SetFinishLineHigh(float M_FinishLineHigh) {
        FinishLineHigh = M_FinishLineHigh;
    }

    Vector3 GetStartPosition() {
        return StartPosition;
    }

    Vector3 GetStartForward() {
        return StartForward;
    }

    Vector3 GetFinishPoint() {
        return FinishPoint;
    }


private:
    Vector3 StartPosition = { 0.0f,0.0f,0.0f };
    Vector3 StartForward = { 0.0f,0.0f,1.0f };
    Vector3 FinishPoint = {0.0f,0.0f,0.0f};
    
    float FinishLineHigh = 0.0f;
    Sebring* m_Sebring;
    LeMans* m_LeMans;
    Monza* m_Monza;
    Imola* m_Imola;
    SilverStone* m_SilverStone;

    ModelRender FinishLine;

    bool GameEnd;

    int LicenseNum = 0;//1Å`5:B 6Å`10:A 11Å`15:IB 16Å`20:IA 21Å`25:S
    int CourseNum;
};
