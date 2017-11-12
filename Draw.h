#ifndef DRAW
#define DRAW

#include "Team.h"

extern map<string, Team> allTeams;
extern vector<string> groups[8];

// 分组抽签
class Draw{
public:
	// 将分组结果放在文件和groups里
	static void grouping();
};
#endif