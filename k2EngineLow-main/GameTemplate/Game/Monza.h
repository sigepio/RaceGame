#pragma once
class Monza : public IGameObject, Noncopyable
{
public:
    Monza();
    ~Monza();
    bool Start();

    //当たり判定のあるオブジェクトの設定
    void SetOnObject();

    //当たり判定のないオブジェクトの設定
    void SetNonObject();

    void Update();
    void Render(RenderContext& rc);
    void SetGameEnd(bool m_GameEnd) {
        GameEnd = m_GameEnd;
    }

    Vector3 GetStartPosition() {
        return StartPosition;
    }

private:
    Vector3 StartPosition = { -17671.0f,-347.0f,-41703.0f };

    //当たり判定のあるオブジェクト
    std::unique_ptr<ModelRender> m_groundModel;
    PhysicsStaticObject m_physicsStaticObject;//静的物理オブジェクト。

    std::unique_ptr<ModelRender> m_CollisionModel;
    PhysicsStaticObject m_CollisionModelphysicsStaticObject;//静的物理オブジェクト。
    std::unique_ptr<ModelRender> m_CollisionAlphaBlendModel;
    PhysicsStaticObject m_CollisionAlphaBlendModelphysicsStaticObject;//静的物理オブジェクト。

    //当たり判定のないオブジェクト
    ModelRender m_NonCollisionModel;
    ModelRender m_NonCollisionAlphaBlendModel;
    ModelRender TreeModel;

    CircuitExperienceTime circuit_experience_time;

    bool GameEnd = false;
};

