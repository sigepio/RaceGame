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


	auto m_CursorSE = getSEFromList(SEList, CursorSE);
	g_soundEngine->ResistWaveFileBank(100, m_CursorSE.second);
	auto m_DecisionSE = getSEFromList(SEList, DecisionSE);
	g_soundEngine->ResistWaveFileBank(101, m_DecisionSE.second);
	auto m_CancelSE = getSEFromList(SEList, CancelSE);
	g_soundEngine->ResistWaveFileBank(102, m_CancelSE.second);
	return true;
}