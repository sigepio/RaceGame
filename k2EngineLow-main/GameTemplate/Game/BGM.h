#ifndef BGM_H_INCLUDED
#define BGM_H_INCLUDED
#pragma once

// 各BGMを保持する連想配列
const std::map<int, const char*> BGMList = {
	{0, "Assets/sound/BGM/WorldMenuBGM.wav"},           //WorldMenuBGM
	{1, "Assets/sound/BGM/RaceMenuBGM.wav"},            //RaceMenuBGM
	{2, "Assets/sound/BGM/RaceLobbyBGM.wav"},           //RaceLobbyBGM
	{3, "Assets/sound/BGM/RaceBGM1.wav"},
    {4, "Assets/sound/BGM/RaceBGM2.wav"},
    {5, "Assets/sound/BGM/RaceBGM3.wav"},
    {6, "Assets/sound/BGM/GoldBGM.wav"},
    {7, "Assets/sound/BGM/SilverBGM.wav"},
    {8, "Assets/sound/BGM/BronzeBGM.wav"},
    {9, "Assets/sound/BGM/DisqualificationBGM.wav"}
};


std::pair<int, const char*> getBGMFromList(const std::map<int, const char*>& BGMList, int key) {
    auto it = BGMList.find(key);
    if (it != BGMList.end()) {
        return { it->first, it->second };
    }
    return { -1, "Unknown" }; // キーが見つからなかった場合のデフォルト値
}

enum BGM {
    WorldMenuBGM,
    RaceMenuBGM,
    RaceLobbyBGM,
    RaceBGM1,
    RaceBGM2,
    RaceBGM3,
    GoldBGM,
    SilverBGM,
    BronzeBGM,
    DisqualificationBGM
};


// 各SEを保持する連想配列
const std::map<int, const char*> SEList = {
    {0, "Assets/sound/SE/Cursor.wav"},           //CursorSE
    {1, "Assets/sound/SE/DecisionSE.wav"},       //RaceMenuBGM
    {2, "Assets/sound/SE/CancelSE.wav"},        //CancelSE
    {3, "Assets/sound/SE/CountSignal.wav"},     //CountSignalSE
    {4, "Assets/sound/SE/StartSignal.wav"},     //StartSignalSE
    {5, "Assets/sound/SE/ErrorSE.wav"},          //ErrorSE
    {6, "Assets/sound/SE/ControlLineSE.wav"}
};


std::pair<int, const char*> getSEFromList(const std::map<int, const char*>& SEList, int key) {
    auto it = SEList.find(key);
    if (it != SEList.end()) {
        return { it->first, it->second };
    }
    return { -1, "Unknown" }; // キーが見つからなかった場合のデフォルト値
}

enum SE {
    CursorSE,
    DecisionSE,
    CancelSE,
    CountSignalSE,
    StartSignalSE,
    ErrorSE,
    ControlLineSE
};
#endif // BGM_H_INCLUDED