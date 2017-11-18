#ifndef RESULT
#define RESULT

#include "Team.h"

extern map<string, Team> allTeams;
extern vector<string> groups[8];
extern vector<string> top16, top8, top4, top2;         // 16强 ~ 2强
extern string goal, silver, bronze, forthPalce;        // 1,2,3,4名


class Result{
public:
	// 统计小组赛结果, 将结果写在top16里
	void groupStage(){}

	// 生成所有队伍排名，按规则排
	void finalResult(){}

	// 该球员获得一个进球
	void goal(Player ply){}
private:
	vector<string> groupStageResult[8];    // 小组内按名次排序
	vector<string> Ranklist;               // 所有球队总排名 
	vector<pair<Player, int> > GoalScorers;   // 后一个int为进球数
};

#endif