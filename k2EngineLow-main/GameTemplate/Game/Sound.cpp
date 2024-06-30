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
	return true;
}