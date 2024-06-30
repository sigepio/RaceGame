#pragma once
class Sebring : public IGameObject, Noncopyable
{
public:
	Sebring();
	~Sebring();
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
private:
    //�����蔻��̂���I�u�W�F�N�g
    std::unique_ptr<ModelRender> m_groundModel;
    PhysicsStaticObject m_physicsStaticObject;//�ÓI�����I�u�W�F�N�g�B

    //�����蔻��̂Ȃ��I�u�W�F�N�g��
    ModelRender m_NonCollisionModel;
    
    CircuitExperienceTime circuit_experience_time;

    bool GameEnd = false;
};

