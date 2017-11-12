#ifndef KONCKOUTSTAGE
#define KONCKOUTSTAGE

extern map<string, Team> allTeams;
extern vector<string> top16, top8, top4, top2;         // 16强 ~ 2强
extern string goal, silver, bronze, forthPalce;        // 1,2,3,4名

class KonckoutStage{
public:
	// 16强赛日程，写在文件中
	static void scheduel16();
	// 根据文件中的日程比赛
	static void roundOf16();

	static void scheduel8();
	static void roundOf8();

	static void scheduel4();
	static void roundOf4();

	// 季军赛
	static void theThird();

	static void theFinal();
};

#endif