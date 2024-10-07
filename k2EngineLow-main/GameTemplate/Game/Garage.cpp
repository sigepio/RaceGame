#include "stdafx.h"
#include "Garage.h"
#include "vector"
#include "GameCamera.h"
#include "Loading.h"
#include "PageNum.h"
#include "Player.h"
#include "Lighting.h"


Garage::Garage() {

}

Garage::~Garage() {
	g_engine->TResourceBankRelease();
}

bool Garage::Start() {

	m_Player = FindGO<Player>("player");
	m_GameCamera = NewGO<GameCamera>(0, "gamecamera");
	m_GameCamera->SetGarageMode(true);
	m_Lighting = NewGO<Lighting>(0, "lighting");


	RideCarNum = m_Player->GetCarNum();
	PossessionCar = m_Player->GetPossessionCar();

	FadeSprite.Init("Assets/Sprite/BlackOut.DDS", 1600.0f, 900.0f);
	BaseSprite.Init("Assets/Sprite/Garage/Base.DDS", 1600.0f, 900.0f);

	BaseModel.Init("Assets/modelData/Car/Garage/Base/Garage.tkm");
	
	switch (RideCarNum)
	{
	case ORECA07:
		CarInformationSprite.Init("Assets/Sprite/Garage/ORECA07.DDS", 1600.0f, 900.0f);
		NowCarModel.Init("Assets/modelData/Car/Garage/ORECA07/ORECA07.tkm");
		break;
	
	case TOYOTA86GT:
		CarInformationSprite.Init("Assets/Sprite/Garage/86GT.DDS", 1600.0f, 900.0f);
		NowCarModel.Init("Assets/modelData/Car/Garage/86GT/86GT.tkm");
		AlphaModel.Init("Assets/modelData/Car/Garage/86GT/Alpha.tkm", true, AlphaBlendMode_Trans);
		AlphaState = true;
		break;
	case TOYOTA90Supra:
		CarInformationSprite.Init("Assets/Sprite/Garage/A90.DDS", 1600.0f, 900.0f);
		NowCarModel.Init("Assets/modelData/Car/Garage/A90/A90.tkm");
		break;

	case NissanGTR_17:
		CarInformationSprite.Init("Assets/Sprite/Garage/R35.DDS", 1600.0f, 900.0f);
		NowCarModel.Init("Assets/modelData/Car/Garage/R35/R35.tkm");
		AlphaModel.Init("Assets/modelData/Car/Garage/R35/Alpha.tkm", true, AlphaBlendMode_Trans);
		AlphaState = true;

		break;
	case MazdaRX_7FD3SSpiritRTypeA:
		CarInformationSprite.Init("Assets/Sprite/Garage/RX7.DDS", 1600.0f, 900.0f);
		NowCarModel.Init("Assets/modelData/Car/Garage/FD3S/FD3S.tkm");
		break;

	case LexusLFA:
		CarInformationSprite.Init("Assets/Sprite/Garage/LFA.DDS", 1600.0f, 900.0f);
		NowCarModel.Init("Assets/modelData/Car/Garage/LFA/LFA.tkm");
		break;

	case FordMustangGT3:
		CarInformationSprite.Init("Assets/Sprite/Garage/MustangGT3.DDS", 1600.0f, 900.0f);
		NowCarModel.Init("Assets/modelData/Car/Garage/MustangGT3/MustangGT3.tkm");
		AlphaModel.Init("Assets/modelData/Car/Garage/MustangGT3/Alpha.tkm", true, AlphaBlendMode_Trans);
		AlphaState = true;
		break;

	case NissanR35GT3:
		CarInformationSprite.Init("Assets/Sprite/Garage/R35GT3.DDS", 1600.0f, 900.0f);
		NowCarModel.Init("Assets/modelData/Car/Garage/R35GT3/R35GT3.tkm");
		break;

	case FordGTGT3GTE:
		CarInformationSprite.Init("Assets/Sprite/Garage/FordGTGT3.DDS", 1600.0f, 900.0f);
		NowCarModel.Init("Assets/modelData/Car/Garage/FordGTGT3/FordGTGT3.tkm");
		AlphaModel.Init("Assets/modelData/Car/Garage/FordGTGT3/Alpha.tkm", true, AlphaBlendMode_Trans);
		AlphaState = true;
		break;

	case FordGTLMRaceCarSpecii:
		CarInformationSprite.Init("Assets/Sprite/Garage/FordGTLM.DDS", 1600.0f, 900.0f);
		NowCarModel.Init("Assets/modelData/Car/Garage/FordGTLM/FordGTLM.tkm");
		break;

	case FordGT2006:
		CarInformationSprite.Init("Assets/Sprite/Garage/FordGT.DDS", 1600.0f, 900.0f);
		NowCarModel.Init("Assets/modelData/Car/Garage/FordGT/FordGT.tkm");
		AlphaModel.Init("Assets/modelData/Car/Garage/FordGT/Alpha.tkm", true, AlphaBlendMode_Trans);
		AlphaState = true;
		break;

	case SauberMercedesC9:
		CarInformationSprite.Init("Assets/Sprite/Garage/C9.DDS", 1600.0f, 900.0f);
		NowCarModel.Init("Assets/modelData/Car/Garage/C9/C9.tkm");
		AlphaModel.Init("Assets/modelData/Car/Garage/C9/Alpha.tkm", true, AlphaBlendMode_Trans);
		AlphaState = true;
		break;

	case BMWMHybridV8:
		CarInformationSprite.Init("Assets/Sprite/Garage/BMWMV8.DDS", 1600.0f, 900.0f);
		NowCarModel.Init("Assets/modelData/Car/Garage/BMWLMDH/BMWLMDH.tkm");
		AlphaModel.Init("Assets/modelData/Car/Garage/BMWLMDH/Alpha.tkm", true, AlphaBlendMode_Trans);
		AlphaState = true; 
		break;

	case Porsche962C:
		CarInformationSprite.Init("Assets/Sprite/Garage/962C.DDS", 1600.0f, 900.0f);
		NowCarModel.Init("Assets/modelData/Car/Garage/962C/962C.tkm");
		AlphaModel.Init("Assets/modelData/Car/Garage/962C/Alpha.tkm", true, AlphaBlendMode_Trans);
		AlphaState = true;
		break;

	case Porsche911GT3RSR:
		CarInformationSprite.Init("Assets/Sprite/Garage/911GT3RSR.DDS", 1600.0f, 900.0f);
		NowCarModel.Init("Assets/modelData/Car/Garage/911GT3RSR/911GT3RSR.tkm");
		AlphaModel.Init("Assets/modelData/Car/Garage/911GT3RSR/Alpha.tkm", true, AlphaBlendMode_Trans);
		AlphaState = true;
		break;

	case Porsche911GT3RS:
		CarInformationSprite.Init("Assets/Sprite/Garage/911GT3RS.DDS", 1600.0f, 900.0f);
		NowCarModel.Init("Assets/modelData/Car/Garage/911GT3RS/911GT3RS.tkm");
		break;

	case Mazda787B:
		CarInformationSprite.Init("Assets/Sprite/Garage/787B.DDS", 1600.0f, 900.0f);
		NowCarModel.Init("Assets/modelData/Car/Garage/787B/787B.tkm");
		AlphaModel.Init("Assets/modelData/Car/Garage/787B/Alpha.tkm", true, AlphaBlendMode_Trans);
		AlphaState = true;
		break;

	case Ferrari499P:
		CarInformationSprite.Init("Assets/Sprite/Garage/499P.DDS", 1600.0f, 900.0f);
		NowCarModel.Init("Assets/modelData/Car/Garage/499P/499P.tkm");
		break;

	case RedBullRB19:
		CarInformationSprite.Init("Assets/Sprite/Garage/RB19.DDS", 1600.0f, 900.0f);
		NowCarModel.Init("Assets/modelData/Car/Garage/RB19/RB19.tkm");
		AlphaModel.Init("Assets/modelData/Car/Garage/RB19/Alpha.tkm", true, AlphaBlendMode_Trans);
		AlphaState = true;
		break;

	case RedBullX2010:
		CarInformationSprite.Init("Assets/Sprite/Garage/X2010.DDS", 1600.0f, 900.0f);
		NowCarModel.Init("Assets/modelData/Car/Garage/X2010/X2010.tkm");
		AlphaModel.Init("Assets/modelData/Car/Garage/X2010/Alpha.tkm", true, AlphaBlendMode_Trans);
		AlphaState = true;
		break;

	case TOYOTAGR010HYBRID:
		CarInformationSprite.Init("Assets/Sprite/Garage/GR010.DDS", 1600.0f, 900.0f);
		NowCarModel.Init("Assets/modelData/Car/Garage/GR010/GR010.tkm");
		AlphaModel.Init("Assets/modelData/Car/Garage/GR010/Alpha.tkm", true, AlphaBlendMode_Trans);
		AlphaState = true;
		break;

	case TOYOTATS050HYBRID:
		CarInformationSprite.Init("Assets/Sprite/Garage/TS050.DDS", 1600.0f, 900.0f);
		NowCarModel.Init("Assets/modelData/Car/Garage/TS050/TS050.tkm");
		AlphaModel.Init("Assets/modelData/Car/Garage/TS050/Alpha.tkm", true, AlphaBlendMode_Trans);
		AlphaState = true;
		break;

	default:
		break;
	
	}

	Rotation.SetRotationDegY(305.0f);
	NowCarModel.SetRotation(Rotation);
	NowCarModel.Update();

	if (AlphaState == true) {
		AlphaModel.SetRotation(Rotation);
		AlphaModel.Update();
	}

	BGM = NewGO<SoundSource>(0);
	BGM->Init(12);
	BGM->SetVolume(m_Player->GetBGMVolume());
	BGM->Play(true);

	return true;
}

void Garage::Update() {
	if (FadeCount < 5) {

		BlackOutColor.w -= 0.2f;
		FadeSprite.SetMulColor(BlackOutColor);
		FadeSprite.Update();
		FadeCount++;
	}
	else {
		if (g_pad[0]->IsPress(enButtonB)) {
			CancelSE = NewGO<SoundSource>(0);
			CancelSE->Init(102);
			CancelSE->SetVolume(m_Player->GetSEVolume());
			CancelSE->Play(false);

			FadeState = true;
			FadeCount = 0;

		}
		else if (g_pad[0]->IsPress(enButtonA)) {
			DecisionSE = NewGO<SoundSource>(0);
			DecisionSE->Init(101);
			DecisionSE->SetVolume(m_Player->GetSEVolume());
			DecisionSE->Play(false);

			FadeState = true;
			CarChangeState = true;
			FadeCount = 0;
		}
	}
	if (FadeState == true) {
		if (FadeCount < 5) {
			BlackOutColor.w += 0.2f;
			FadeSprite.SetMulColor(BlackOutColor);
			FadeSprite.Update();
			FadeCount++;
		}
		else if (CarChangeState == true) {
			m_Loading = NewGO<Loading>(10, "loading");
			m_Loading->SetWhereCome(GaragePage);
			m_Loading->SetWhereGo(CarChangePage);
			DeleteGO(m_GameCamera);
			DeleteGO(BGM);
			DeleteGO(this);
		}
		else {
			m_Loading = NewGO<Loading>(10, "loading");
			m_Loading->SetWhereCome(GaragePage);
			m_Loading->SetWhereGo(WorldMenuPage);
			DeleteGO(m_GameCamera);
			DeleteGO(BGM);
			DeleteGO(this);
		}
	}
}

void Garage::Render(RenderContext& rc) {
	BaseModel.SetAlwaysOnDisplay(true);
	NowCarModel.SetAlwaysOnDisplay(true);
	BaseModel.Draw(rc);
	NowCarModel.Draw(rc);
	if (AlphaState == true) {
		AlphaModel.SetAlwaysOnDisplay(true);
		AlphaModel.Draw(rc);
	}

	BaseSprite.Draw(rc);
	CarInformationSprite.Draw(rc);
	FadeSprite.Draw(rc);
}