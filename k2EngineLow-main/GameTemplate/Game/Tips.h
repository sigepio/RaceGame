#pragma once
// 各コースのTipsを保持する連想配列
const std::map<int, const char*> SebringTipsList = {
	{0, "Assets/Sprite/Loading/SebringTips01.DDS"},
	{1, "Assets/Sprite/Loading/SebringTips02.DDS"},
	{2, "Assets/Sprite/Loading/SebringTips03.DDS"},
	{3, "Assets/Sprite/Loading/SebringTips04.DDS"}
}; 


// 各車種のTipsを保持する連想配列
const std::map<int, const char*> ORECA07TipsList = {
	{0, "Assets/Sprite/Loading/ORECA07Tips01.DDS"},
	{1, "Assets/Sprite/Loading/ORECA07Tips02.DDS"},
	{2, "Assets/Sprite/Loading/ORECA07Tips03.DDS"},
	{3, "Assets/Sprite/Loading/ORECA07Tips04.DDS"}
};


const char* getTipsFromList(const std::map<int, const char*>& tipsList, int key) {
	auto it = tipsList.find(key);
	if (it != tipsList.end()) {
		return it->second;
	}
	return "Unknown"; 
}