#ifndef BGM_H_INCLUDED
#define BGM_H_INCLUDED
#pragma once

// 各BGMを保持する連想配列
const std::map<int, const char*> BGMList = {
	{0, "Assets/sound/BGM/WorldMenuBGM.wav"},           //WorldMenuBGM
	{1, "Assets/sound/BGM/RaceMenuBGM.wav"},            //RaceMenuBGM
	{2, "Assets/sound/BGM/BGM1.wav"},
	{3, "Assets/sound/BGM/BGM1.wav"}
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
    RaceMenuBGM
};



#endif // BGM_H_INCLUDED