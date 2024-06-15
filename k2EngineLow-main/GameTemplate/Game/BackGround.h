#pragma once


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

    std::unique_ptr<ModelRender> m_groundModel;
    PhysicsStaticObject m_physicsStaticObject;//�ÓI�����I�u�W�F�N�g�B

    bool GameEnd = false;
};

