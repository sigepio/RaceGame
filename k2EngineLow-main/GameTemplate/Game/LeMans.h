#pragma once
class LeMans : public IGameObject, Noncopyable
{
public:
    LeMans();
    ~LeMans();
    bool Start();

    //�����蔻��̂���I�u�W�F�N�g�̐ݒ�
    void SetOnObject();

    //�����蔻��̂Ȃ��I�u�W�F�N�g�̐ݒ�
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
    Vector3 StartPosition = { -31433.0f,1907.0f,-2440.0f };

    //�����蔻��̂���I�u�W�F�N�g
    std::unique_ptr<ModelRender> m_groundModel;
    PhysicsStaticObject m_physicsStaticObject;//�ÓI�����I�u�W�F�N�g�B

    std::unique_ptr<ModelRender> m_CollisionModel;
    PhysicsStaticObject m_CollisionModelphysicsStaticObject;//�ÓI�����I�u�W�F�N�g�B
    std::unique_ptr<ModelRender> m_CollisionAlphaBlendModel;
    PhysicsStaticObject m_CollisionAlphaBlendModelphysicsStaticObject;//�ÓI�����I�u�W�F�N�g�B

    //�����蔻��̂Ȃ��I�u�W�F�N�g
    ModelRender m_NonCollisionModel; 
    ModelRender m_NonCollisionAlphaBlendModel;
    ModelRender m_NonCollisionAdvertisementModel;
    ModelRender TreeModel;

    CircuitExperienceTime circuit_experience_time;

    bool GameEnd = false;
};
