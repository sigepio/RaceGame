#pragma once

class Sebring;

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

private:
    Sebring* m_Sebring;
    bool GameEnd;
};
