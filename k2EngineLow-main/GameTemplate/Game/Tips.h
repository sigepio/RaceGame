#pragma once
// 各コースのTipsを保持する連想配列
const std::map<int, const char*> SebringTipsList = {
	{0, "Assets/Sprite/Loading/SebringTips01.DDS"},
	{1, "Assets/Sprite/Loading/SebringTips02.DDS"},
	{2, "Assets/Sprite/Loading/SebringTips03.DDS"},
	{3, "Assets/Sprite/Loading/SebringTips04.DDS"}
}; 
const std::map<int, const char*> LeMansTipsList = {
	{0, "Assets/Sprite/Loading/LeMansTips01.DDS"},
	{1, "Assets/Sprite/Loading/LeMansTips02.DDS"},
	{2, "Assets/Sprite/Loading/LeMansTips03.DDS"},
	{3, "Assets/Sprite/Loading/LeMansTips04.DDS"}
};
const std::map<int, const char*> MonzaTipsList = {
	{0, "Assets/Sprite/Loading/MonzaTips01.DDS"},
	{1, "Assets/Sprite/Loading/MonzaTips02.DDS"},
	{2, "Assets/Sprite/Loading/MonzaTips03.DDS"},
	{3, "Assets/Sprite/Loading/MonzaTips04.DDS"}
};


// 各車種のTipsを保持する連想配列
const std::map<int, const char*> ORECA07TipsList = {
	{0, "Assets/Sprite/Loading/ORECA07Tips01.DDS"},
	{1, "Assets/Sprite/Loading/ORECA07Tips02.DDS"},
	{2, "Assets/Sprite/Loading/ORECA07Tips03.DDS"},
	{3, "Assets/Sprite/Loading/ORECA07Tips04.DDS"}
};
const std::map<int, const char*> TOYOTA86GTTipsList = {
	{0, "Assets/Sprite/Loading/TOYOTA86GTTips01.DDS"},
	{1, "Assets/Sprite/Loading/TOYOTA86GTTips02.DDS"},
	{2, "Assets/Sprite/Loading/TOYOTA86GTTips03.DDS"},
	{3, "Assets/Sprite/Loading/TOYOTA86GTTips04.DDS"}
};
const std::map<int, const char*> A90SupraTipsList = {
	{0, "Assets/Sprite/Loading/A90SupraTips01.DDS"},
	{1, "Assets/Sprite/Loading/A90SupraTips02.DDS"},
	{2, "Assets/Sprite/Loading/A90SupraTips03.DDS"},
	{3, "Assets/Sprite/Loading/A90SupraTips04.DDS"}
};
const std::map<int, const char*> GTRR35TipsList = {
	{0, "Assets/Sprite/Loading/GTRR35Tips01.DDS"},
	{1, "Assets/Sprite/Loading/GTRR35Tips02.DDS"},
	{2, "Assets/Sprite/Loading/GTRR35Tips03.DDS"},
	{3, "Assets/Sprite/Loading/GTRR35Tips04.DDS"}
};
const std::map<int, const char*> FD3STipsList = {
	{0, "Assets/Sprite/Loading/FD3STips01.DDS"},
	{1, "Assets/Sprite/Loading/FD3STips02.DDS"},
	{2, "Assets/Sprite/Loading/FD3STips03.DDS"},
	{3, "Assets/Sprite/Loading/FD3STips04.DDS"}
};


const char* getTipsFromList(const std::map<int, const char*>& tipsList, int key) {
	auto it = tipsList.find(key);
	if (it != tipsList.end()) {
		return it->second;
	}
	return "Unknown"; 
}