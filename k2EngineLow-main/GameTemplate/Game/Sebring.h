#pragma once
class Sebring : public IGameObject, Noncopyable
{
public:
	Sebring();
	~Sebring();
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
private:
    //当たり判定のあるオブジェクト
    std::unique_ptr<ModelRender> m_groundModel;
    PhysicsStaticObject m_physicsStaticObject;//静的物理オブジェクト。

    //当たり判定のないオブジェクトの
    ModelRender m_NonCollisionModel;
    
    CircuitExperienceTime circuit_experience_time;

    bool GameEnd = false;
};

