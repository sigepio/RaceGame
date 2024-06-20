#pragma once
#include "sound/SoundSource.h"




class Loading;


class WorldMode:public IGameObject
{
public:
	WorldMode();
	~WorldMode();
	bool Start();
	void Update();
	void Render(RenderContext&rc);

private:
	Vector4 m_SelectSpriteColor = { 1.0f,1.0f,1.0f,0.0f };
	Vector4 m_NonSelectSpriteColor = { 1.0f,1.0f,1.0f,0.0f };

	Vector4 m_WindowSpriteColor = { 1.0f,1.0f,1.0f,0.0f };

	Vector3 m_WindowSpritePosition = { 0.0f,-50.0f,0.0f };

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
	SpriteRender WorldRaceSprite;			//���[�X
	SpriteRender WorldRaceSelectSprite;		//���[�X�Z���N�g��
	SpriteRender OptionSprite;				//�ݒ�
	SpriteRender OptionSelectSprite;		//�ݒ�Z���N�g��
	SpriteRender SelectArrowSprite;			//���
	SpriteRender MyCarSprite;				//������Ă���Ԃ̖��O
	SpriteRender TestSprite;				//�e�X�g�p�̃X�v���C�g
	SpriteRender ErrorWindowSprite;				//�G���[���̃|�b�v�A�b�v�E�B���h�E
	SpriteRender WindowBottonOKSprite;			//�E�B���h�E��OK�{�^��

	SpriteRender BlackOut;

	Loading* m_loading;
	SoundSource* BGM;
	SoundSource* CursorSE;
	SoundSource* DecisionSE;
						

	Vector3 SelectArrowPosition = Vector3::Zero;

	Vector4 SelectAppealColor = { 1.0f,1.0f,1.0f,0.0f };
	Vector4 m_FadeColor = { 1.0f,1.0f,1.0f,1.0f };

	int SelectState = 0; //0:MyGarage 1:WorldRace 2:License 3:CarDealer 4:Tuning 5:Maintenance
	int ErrorWindowFlag = 0;//0:��\�� 1:�\���J�� 2:�\���� 3:��\���J��
	int FadeSate = -1;
	int WindowCount = 0;
	int Count = 0;		//�Z���N�g�`�J�`�J�̎���
	int SelectDirection = 1;
	int SelectFlag[6] = { 0,0,0,0,0,0 };
	int FadeCount = 0;
};

