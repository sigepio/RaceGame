#pragma once

class Sebring;
class LeMans;

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

    Vector3 GetStartPosition() {
        return StartPosition;
    }

private:
    Vector3 StartPosition = { 0.0f,0.0f,0.0f };
    Sebring* m_Sebring;
    LeMans* m_LeMans;
    bool GameEnd;
};
