#pragma once
class RaceMenu;


class WorldMode:public IGameObject
{
public:
	WorldMode();
	~WorldMode();
	bool Start();
	void Update();
	void Render(RenderContext&rc);
private:
	
	SpriteRender BaseSprite;				//�w�i
	SpriteRender MyGarageSprite;			//�K���[�W
	SpriteRender MyGarageSelectSprite;		//�K���[�W�Z���N�g��
	SpriteRender CarDealerSprite;			//�f�B�[���[
	SpriteRender CarDealerSelectSprite;		//�f�B�[���[�Z���N�g��
	SpriteRender TuningSprite;				//�`���[�j���O
	SpriteRender TuningSelectSprite;		//�`���[�j���O�Z���N�g��
	SpriteRender MaintenanceSprite;			//�����e�i���X
	SpriteRender MaintenanceSelectSprite;	//�����e�i���X�Z���N�g��
	SpriteRender LicenseSprite;				//���C�Z���X
	SpriteRender LicenseSelectSprite;		//���C�Z���X�Z���N�g��
	SpriteRender WprldRaceSprite;			//���[�X
	SpriteRender WprldRaceSelectSprite;		//���[�X�Z���N�g��
	SpriteRender OptionSprite;				//�ݒ�
	SpriteRender OptionSelectSprite;		//�ݒ�Z���N�g��
	SpriteRender SelectArrowSprite;			//���
	SpriteRender MyCarSprite;				//������Ă���Ԃ̖��O
	SpriteRender TestSprite;				//�e�X�g�p�̃X�v���C�g

	RaceMenu* m_racemenu;					

	Vector3 SelectArrowPosition = Vector3::Zero;

	Vector4 SelectAppealColor = { 1.0f,1.0f,1.0f,0.0f };

	int SelectState = 0; //0:MyGarage 1:WorldRace 2:License 3:CarDealer 4:Tuning 5:Maintenance


};

