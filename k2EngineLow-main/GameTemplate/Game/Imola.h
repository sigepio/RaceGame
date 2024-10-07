#pragma once
class Imola : public IGameObject, Noncopyable
{
public:
    Imola();
	~Imola();
	bool Start();

    void Update();
    void Render(RenderContext& rc);
    void SetGameEnd(bool m_GameEnd) {
        GameEnd = m_GameEnd;
    }

    Vector3 GetStartPosition() {
        return StartPosition;
    }

private:
    Vector3 StartPosition = { -15229.0,-3359.0,161.0f };

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

