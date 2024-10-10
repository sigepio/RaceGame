#pragma once
#include"PageNum.h"

class Player;
class Loading;

class LicenseMode :public IGameObject
{
public:
	LicenseMode();
	~LicenseMode();
	bool Start();
	void StateSet(int m_LicensePage);
	void SpriteSet();
	void Update();
	void Render(RenderContext& rc);

	void FadeIn();
	void DomesticBlicenseDisplayTransition();

private:
	Vector4 FadeColor{ 1.0f,1.0f,1.0f,1.0f };

	Vector4 LicenseDetails1SpriteColor{ 1.0f,1.0f,1.0f,0.0f };
	Vector4 LicenseDetails2SpriteColor{ 1.0f,1.0f,1.0f,0.0f };
	Vector4 LicenseDetails3SpriteColor{ 1.0f,1.0f,1.0f,0.0f };
	Vector4 LicenseDetails4SpriteColor{ 1.0f,1.0f,1.0f,0.0f };
	Vector4 LicenseDetails5SpriteColor{ 1.0f,1.0f,1.0f,0.0f };

	Vector4 m_WindowSpriteColor = { 1.0f,1.0f,1.0f,0.0f };

	Vector3 m_WindowSpritePosition = { 0.0f,-50.0f,0.0f };


	Vector3 BaseDomesticBPosition{ 0.0f,-120.0f,0.0f };

	Vector3 LicenseDetails1SpritePosition = { -650.0f,-95.0f,0.0f };
	Vector3 LicenseDetails2SpritePosition = { -325.0f,-95.0f,0.0f };
	Vector3 LicenseDetails3SpritePosition = { 0.0f,-95.0f,0.0f };
	Vector3 LicenseDetails4SpritePosition = { 325.0f,-95.0f,0.0f };
	Vector3 LicenseDetails5SpritePosition = { 650.0f,-95.0f,0.0f };

	Vector3 ArrowPosition = { 0.0f,0.0f,0.0f };
	Vector3 Arrow1Pos = { -650.0f,-175.0f,0.0f };
	Vector3 Arrow2Pos = { -325.0f,-175.0f,0.0f };
	Vector3 Arrow3Pos = { 0.0f,-175.0f,0.0f };
	Vector3 Arrow4Pos = { 325.0f,-175.0f,0.0f };
	Vector3 Arrow5Pos = { 650.0f,-175.0f,0.0f };
	Vector3 ArrowDiffPos = { 0.0f,0.0f,0.0f };

	SpriteRender Base;

	SpriteRender BaseDomesticB;

	SpriteRender LicenseDetailsDomesticB_1Sprite;
	SpriteRender LicenseDetailsDomesticB_2Sprite;
	SpriteRender LicenseDetailsDomesticB_3Sprite;
	SpriteRender LicenseDetailsDomesticB_4Sprite;
	SpriteRender LicenseDetailsDomesticB_5Sprite;


	SpriteRender DomesticBTabSprite;

	SpriteRender DomesticATabSprite;

	SpriteRender InternationaBTabSprite;

	SpriteRender InternationaATabSprite;

	SpriteRender SuperTabSprite;

	SpriteRender B_1Sprite;

	SpriteRender B_2Sprite;

	SpriteRender B_3Sprite;

	SpriteRender B_4Sprite;

	SpriteRender B_5Sprite;

	SpriteRender ErrorWindowSprite;				//エラー時のポップアップウィンドウ
	SpriteRender WindowBottonOKSprite;			//ウィンドウのOKボタン

	SpriteRender AllGoldClearSprite;
	SpriteRender AllSilverClearSprite;
	SpriteRender AllBronzeClearSprite;

	SpriteRender FadeSprite;

	SpriteRender ArrowSprite;

	Player* m_Player;
	Loading* m_Loading;
	SoundSource* BGM;
	SoundSource* CursorSE;
	SoundSource* DecisionSE;
	SoundSource* CancelSE;
	SoundSource* ErrorSE;


	bool AllGoldState = false;
	bool AllSilverState = false;
	bool AllBronzeState = false;

	bool TransitionStatus = true;

	bool ArrowMoveRight = false;
	bool ArrowMoveLeft = false;


	bool LicenseAcquisitionStatus[5] = { false,false,false,false };
	int LicenseClearStatus[5][5];

	int FadeCount = 0;
	int TransitionCount = 0;
	int ArrowMoveCount = 0;

	int LicensePage = 0;	//-1:WM 0:B 1:A 2:IB 3:IA 4:S 5:RL

	int ArrowPoint = 0;

	int LicensedCar[5][5] = {{ TOYOTA86GT,TOYOTA90Supra,TOYOTA86GT,NissanGTR_17,MazdaRX_7FD3SSpiritRTypeA},
							 {MazdaRX_7FD3SSpiritRTypeA,MazdaRX_7FD3SSpiritRTypeA,MazdaRX_7FD3SSpiritRTypeA,MazdaRX_7FD3SSpiritRTypeA,MazdaRX_7FD3SSpiritRTypeA},
							 {MazdaRX_7FD3SSpiritRTypeA,MazdaRX_7FD3SSpiritRTypeA,MazdaRX_7FD3SSpiritRTypeA,MazdaRX_7FD3SSpiritRTypeA,MazdaRX_7FD3SSpiritRTypeA},
							 {MazdaRX_7FD3SSpiritRTypeA,MazdaRX_7FD3SSpiritRTypeA,MazdaRX_7FD3SSpiritRTypeA,MazdaRX_7FD3SSpiritRTypeA,MazdaRX_7FD3SSpiritRTypeA},
							 {MazdaRX_7FD3SSpiritRTypeA,MazdaRX_7FD3SSpiritRTypeA,MazdaRX_7FD3SSpiritRTypeA,MazdaRX_7FD3SSpiritRTypeA,MazdaRX_7FD3SSpiritRTypeA}
};
	int LicenseCourse[5][5] = { { AutodromoNazionaleDiMonza,AutodromoNazionaleDiMonza,AutodromoNazionaleDiMonza,AutodromoNazionaleDiMonza,0},
							    {SilverstoneCircuit,SilverstoneCircuit,SilverstoneCircuit,SilverstoneCircuit,SilverstoneCircuit},
								{SilverstoneCircuit,SilverstoneCircuit,SilverstoneCircuit,SilverstoneCircuit,SilverstoneCircuit},
								{SilverstoneCircuit,SilverstoneCircuit,SilverstoneCircuit,SilverstoneCircuit,SilverstoneCircuit},
								{SilverstoneCircuit,SilverstoneCircuit,SilverstoneCircuit,SilverstoneCircuit,SilverstoneCircuit}
	};

	int NextPage = 0;
	int LastPage = -1;
	int LicenseNum = 0;//1～5:B 6～10:A 11～15:IB 16～20:IA 21～25:S
	int ErrorWindowFlag = 0;//0:非表示 1:表示遷移 2:表示中 3:非表示遷移
	int WindowCount = 0;

	float ArrowXMoveDistance = 0;
	float ArrowYMoveDistance = 0;
};

