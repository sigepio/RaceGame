#pragma once
#include "sound/SoundSource.h"

class Lighting;
class GameCamera;
class BackGround;
class Car_RB6;
class Car_Oreca07;
class CarAFormula;
class Loading;
class Car_86GT;
class Player;
class Car_RX7FD;
class Car_A90Supra;
class Car_GTRR35;
class LicenseRace:public IGameObject
{
public:
	LicenseRace();
	~LicenseRace();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	void B_1();
	void B_2();
	void B_3();
	void B_4();
	void B_5();

	void SetPosition(Vector3 position) {
		m_NowPPosition = position;
	}

	void SetGameMode(int m_GameMode) {
		GameMode = m_GameMode;
	}

	void SetFinishPosition(Vector3 m_FinishPosition) {
		FinishPosition = m_FinishPosition;
	}

	void SetLicenseNum(int m_LicenseNum) {
		LicenseNum = m_LicenseNum;
	}

	void SetCourseNum(int m_CourseNum) {
		CourseNum = m_CourseNum;
	}

	void SetVelocity(float m_Velocity) {
		Velocity = m_Velocity;
	}

	void ResultSelect();


private:
	Vector3 m_NowPPosition = Vector3::Zero;
	Vector3 FinishPosition = Vector3::Zero;				//�t�B�j�b�V�����C���̈ʒu

	Vector3 m_TimeUIPosition = Vector3::Zero;			//�^�C����UI�̈ʒu
	Vector3 m_Pauseposition = { 0.0f,-50.0f,0.0f };		//�|�[�Y�̈ʒu

	//���U���g�֘A�̃|�W�V����
	Vector3 ResultScale = { 2.0f,2.0f,1.0f };
	Vector3 ResultSelectSpritePosition = { 0.0f,-100.0f,0.0f };
	Vector3 ResultSelectArrowPosition = { 0.0f,0.0f,0.0f };
	Vector3 ResultTimeFontPosition = { -300.0f,0.0f,0.0f };

	Vector3 ClearTime = Vector3::Zero;		//�N���A�^�C���̐ݒ� x:Gold y:Silver z:Bronze

	Vector4 m_Pausecolor = { 1.0f,1.0f,1.0f,0.0f };		//�|�[�Y��ʂ̃J���[

	//���U���g�֘A��color
	Vector4 ResultBaseColor = { 1.0f,1.0f,1.0f,0.0f };
	Vector4 ResultSpriteColor = { 1.0f,1.0f,1.0f,0.0f };
	Vector4 ResultSelectArrowColor = { 1.0f,1.0f,1.0f,0.0f };
	Vector4 FINISHColor = { 1.0f,1.0f,1.0f,0.0f };
	Vector4 ResultColor = { 1.0f,1.0f,1.0f,0.0f };
	Vector4 ResultTimeColor = { 1.0f,1.0f,1.0f,0.0f };


	Lighting* m_lighting;
	GameCamera* m_gamecamera;
	BackGround* m_background;
	Player* m_player;
	Car_RB6* m_RB6;
	Car_86GT* m_86GT;
	//Car_AE86* m_AE86;
	Car_Oreca07* m_Oreca07;
	Car_RX7FD* m_FD3S;
	Car_A90Supra* m_A90Supra;
	Car_GTRR35* m_GTRR35;
	SkyCube* m_skyCube = nullptr;
	CarAFormula* m_caraformula;
	Loading* m_Loading;

	SoundSource* BGM;
	SoundSource* CountSignalSE;
	SoundSource* StartSignalSE;
	SoundSource* ControlLineSE;

	SpriteRender PassedTimeBaseSprite;		//�ڕW�^�C���̃x�[�X
	SpriteRender PassedTimeSprite;			//�ڕW�^�C��
	SpriteRender TimeUIRender;				//���݂̃^�C����UI
	SpriteRender CourseMapUISprite;			//�R�[�X�}
	SpriteRender PauseSprite;				//�|�[�Y��UI
	SpriteRender ContinueSpriteNonSelect;	//�|�[�Y���̍ĊJ�p
	SpriteRender ContinueSpriteSelect;			
	SpriteRender ExitSpriteNonSelect;		//�|�[�Y����Exit�p
	SpriteRender ExitSpriteSelect;
	SpriteRender RetryNonSelect;			//�|�[�Y���̃��g���C�p
	SpriteRender RetrySelect;
	SpriteRender Count3Sprite;					//�X�^�[�g�J�E���g�p
	SpriteRender Count2Sprite;
	SpriteRender Count1Sprite;
	SpriteRender STARTSprite;
	SpriteRender ResultSprite;				//���U���g�֘A�̃X�v���C�g
	SpriteRender ResultBaseSprite;
	SpriteRender ResultSelectSprite;
	SpriteRender ResultSelectArrowSprite;
	SpriteRender FINISHSprite;

	FontRender TimeFont;
	FontRender ResultTimeFont;
	FontRender LapCountFont;

	ModelRender FinishLine;

	float m_timer;
	float KeepTime = 0.0f;
	float m_timersecont; 
	float BGMVolume = 0.0f;
	float Velocity = 0.0f;

	float ResultTimeScale = 3.0f;//���U���g��ʂ̃^�C���̃X�P�[��

	int GameMode = 0;//0:TimeTrial 1:CircuitExperience
	int CarNum = -1;//0:ORECA07 1:86GT 2:
	int LicenseNum = 0;//1�`5:B 6�`10:A 11�`15:IB 16�`20:IA 21�`25:S
	int CourseNum = 0;
	int PauseState = 0;	//�Q�[���̏��
	int PauseCount = 0;	//�|�[�Y�̃J�E���g
	int PauseWindowState = 0;//�|�[�Y�̃E�B���h�E�̏��
	int StartSignalCount = 0;
	int StartSignalSetCount = 0;
	int StartSignal = 0;
	int ResetCount = 0;
	int StartSignalState = 0;
	int StartSignalTime = 0;
	int BGMTrack = 1;
	int m_timerminit;//�^�C�}�[
	int m_timerintsecont;
	int m_timermsecont;
	int NowLap = 0;//���b�v��
	int ResultCount = 0;//���U���g�p�̃J�E���g
	int ResultSetectState = 0;//0:Retry 1:Exit
	int ResultSetectCount = 5;

	int ResultState = 0;

	int AutoDriveCount = 0;

	bool GameEnd = false;
	bool PassedState = false;
	bool ResultTimeState = false;
};

