#include "stdafx.h"
#include "Sound.h"
#include "BGM.h"
#include <map>
#include<math.h>
#include "sound/SoundEngine.h"

Sound::Sound() {

}

Sound::~Sound() {

}

bool Sound::Start() {
	auto m_WorldMenuBGM = getBGMFromList(BGMList, WorldMenuBGM);
	g_soundEngine->ResistWaveFileBank(m_WorldMenuBGM.first, m_WorldMenuBGM.second);
	auto m_RaceMenuBGM = getBGMFromList(BGMList, RaceMenuBGM);
	g_soundEngine->ResistWaveFileBank(m_RaceMenuBGM.first, m_RaceMenuBGM.second);
	auto m_RaceLobbyBGM = getBGMFromList(BGMList, RaceLobbyBGM);
	g_soundEngine->ResistWaveFileBank(m_RaceLobbyBGM.first, m_RaceLobbyBGM.second);
	auto m_LicenseMenuBGM = getBGMFromList(BGMList, LicenseMenuBGM);
	g_soundEngine->ResistWaveFileBank(m_LicenseMenuBGM.first, m_LicenseMenuBGM.second);
	auto m_OptionMenuBGM = getBGMFromList(BGMList, OptionMenuBGM);
	g_soundEngine->ResistWaveFileBank(m_OptionMenuBGM.first, m_OptionMenuBGM.second);
	auto m_GarageBGM = getBGMFromList(BGMList, GarageBGM);
	g_soundEngine->ResistWaveFileBank(m_GarageBGM.first, m_GarageBGM.second);
	auto m_CarListBGM = getBGMFromList(BGMList, CarListBGM);
	g_soundEngine->ResistWaveFileBank(m_CarListBGM.first, m_CarListBGM.second);

	auto m_ModeSelectBGM = getBGMFromList(BGMList, ModeSelectBGM);
	g_soundEngine->ResistWaveFileBank(m_ModeSelectBGM.first, m_ModeSelectBGM.second);


	auto m_RaceBGM1 = getBGMFromList(BGMList, RaceBGM1);
	g_soundEngine->ResistWaveFileBank(m_RaceBGM1.first, m_RaceBGM1.second);
	auto m_RaceBGM2 = getBGMFromList(BGMList, RaceBGM2);
	g_soundEngine->ResistWaveFileBank(m_RaceBGM2.first, m_RaceBGM2.second);
	auto m_RaceBGM3 = getBGMFromList(BGMList, RaceBGM3);
	g_soundEngine->ResistWaveFileBank(m_RaceBGM3.first, m_RaceBGM3.second);

	auto m_GoldBGM = getBGMFromList(BGMList, GoldBGM);
	g_soundEngine->ResistWaveFileBank(m_GoldBGM.first, m_GoldBGM.second);
	auto m_SilverBGM = getBGMFromList(BGMList, SilverBGM);
	g_soundEngine->ResistWaveFileBank(m_SilverBGM.first, m_SilverBGM.second);
	auto m_BronzeBGM = getBGMFromList(BGMList, BronzeBGM);
	g_soundEngine->ResistWaveFileBank(m_BronzeBGM.first, m_BronzeBGM.second);
	auto m_DisqualificationBGM = getBGMFromList(BGMList, DisqualificationBGM);
	g_soundEngine->ResistWaveFileBank(m_DisqualificationBGM.first, m_DisqualificationBGM.second);

	auto m_CursorSE = getSEFromList(SEList, CursorSE);
	g_soundEngine->ResistWaveFileBank(100, m_CursorSE.second);
	auto m_DecisionSE = getSEFromList(SEList, DecisionSE);
	g_soundEngine->ResistWaveFileBank(101, m_DecisionSE.second);
	auto m_CancelSE = getSEFromList(SEList, CancelSE);
	g_soundEngine->ResistWaveFileBank(102, m_CancelSE.second);
	auto m_CountSignalSE = getSEFromList(SEList, CountSignalSE);
	g_soundEngine->ResistWaveFileBank(103, m_CountSignalSE.second);
	auto m_StartSignalSE = getSEFromList(SEList, StartSignalSE);
	g_soundEngine->ResistWaveFileBank(104, m_StartSignalSE.second);
	auto m_ErrorSE = getSEFromList(SEList, ErrorSE);
	g_soundEngine->ResistWaveFileBank(105, m_ErrorSE.second);
	auto m_ControlLineSE = getSEFromList(SEList, ControlLineSE);
	g_soundEngine->ResistWaveFileBank(106, m_ControlLineSE.second);

	//ƒGƒ“ƒWƒ“‰¹
	g_soundEngine->ResistWaveFileBank(200, "Assets/sound/5000RPM.wav");
	g_soundEngine->ResistWaveFileBank(201, "Assets/sound/EngineSound/86GT.wav");
	g_soundEngine->ResistWaveFileBank(202, "Assets/sound/EngineSound/A90.wav");
	g_soundEngine->ResistWaveFileBank(203, "Assets/sound/EngineSound/R35GTR.wav");
	g_soundEngine->ResistWaveFileBank(204, "Assets/sound/EngineSound/RX7FD3S.wav");

	g_soundEngine->ResistWaveFileBank(205, "Assets/sound/EngineSound/LFA.wav");
	g_soundEngine->ResistWaveFileBank(206, "Assets/sound/EngineSound/MustangGT3.wav");
	g_soundEngine->ResistWaveFileBank(207, "Assets/sound/EngineSound/GTRGT3.wav");
	g_soundEngine->ResistWaveFileBank(208, "Assets/sound/EngineSound/FordGTGT3.wav");
	g_soundEngine->ResistWaveFileBank(209, "Assets/sound/EngineSound/FordGT.wav");
	g_soundEngine->ResistWaveFileBank(210, "Assets/sound/EngineSound/C9.wav");
	g_soundEngine->ResistWaveFileBank(211, "Assets/sound/EngineSound/BMWMV8LMDH.wav");
	g_soundEngine->ResistWaveFileBank(212, "Assets/sound/EngineSound/962C.wav");
	g_soundEngine->ResistWaveFileBank(213, "Assets/sound/EngineSound/911GT3RSR.wav");
	g_soundEngine->ResistWaveFileBank(214, "Assets/sound/EngineSound/911GT3RS.wav");
	g_soundEngine->ResistWaveFileBank(215, "Assets/sound/EngineSound/787B.wav");
	g_soundEngine->ResistWaveFileBank(217, "Assets/sound/EngineSound/499P.wav");
	g_soundEngine->ResistWaveFileBank(218, "Assets/sound/EngineSound/RB19.wav");
	g_soundEngine->ResistWaveFileBank(219, "Assets/sound/EngineSound/X2010.wav");
	g_soundEngine->ResistWaveFileBank(220, "Assets/sound/EngineSound/GR010.wav");
	g_soundEngine->ResistWaveFileBank(221, "Assets/sound/EngineSound/TS050.wav");
	g_soundEngine->ResistWaveFileBank(222, "Assets/sound/EngineSound/MotorSound.wav");
	return true;
}