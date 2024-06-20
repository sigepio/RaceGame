#pragma once
class Sebring;

class BackGround : public IGameObject, Noncopyable
{
public:
    BackGround();
    ~BackGround();

    bool Start();
    void Update();
    void Render(RenderContext& rc);
    void SetGameEnd(bool m_GameEnd) {
        GameEnd = m_GameEnd;
    }
private:
    Sebring* m_Sebring;
    bool GameEnd = false;
};

