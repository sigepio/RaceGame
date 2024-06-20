#ifndef BGM_H_INCLUDED
#define BGM_H_INCLUDED
#pragma once

// �eBGM��ێ�����A�z�z��
const std::map<int, const char*> BGMList = {
	{0, "Assets/sound/BGM/WorldMenuBGM.wav"},           //WorldMenuBGM
	{1, "Assets/sound/BGM/RaceMenuBGM.wav"},            //RaceMenuBGM
	{2, "Assets/sound/BGM/RaceLobbyBGM.wav"},           //RaceLobbyBGM
	{3, "Assets/sound/BGM/BGM1.wav"}
};


std::pair<int, const char*> getBGMFromList(const std::map<int, const char*>& BGMList, int key) {
    auto it = BGMList.find(key);
    if (it != BGMList.end()) {
        return { it->first, it->second };
    }
    return { -1, "Unknown" }; // �L�[��������Ȃ������ꍇ�̃f�t�H���g�l
}

enum BGM {
    WorldMenuBGM,
    RaceMenuBGM,
    RaceLobbyBGM
};


// �eSE��ێ�����A�z�z��
const std::map<int, const char*> SEList = {
    {0, "Assets/sound/SE/Cursor.wav"},           //CursorSE
    {1, "Assets/sound/SE/DecisionSE.wav"},       //RaceMenuBGM
    {2, "Assets/sound/SE/CancelSE.wav"},         //CancelSE
    {3, "Assets/sound/BGM/BGM1.wav"}
};


std::pair<int, const char*> getSEFromList(const std::map<int, const char*>& SEList, int key) {
    auto it = SEList.find(key);
    if (it != SEList.end()) {
        return { it->first, it->second };
    }
    return { -1, "Unknown" }; // �L�[��������Ȃ������ꍇ�̃f�t�H���g�l
}

enum SE {
    CursorSE,
    DecisionSE,
    CancelSE
};
#endif // BGM_H_INCLUDED