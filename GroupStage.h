#ifndef GROUPSTAGE
#define GROUPSTAGE

#include "Team.h"
#include "Result.h"
#include "Match.h"

// 小组赛阶段
class GroupStage{
public:
	// 安排日程存在文件中，安排场馆，打印信息
	void schedueling(const vector<Team> groups[8]);
	
	void playing(Result &res) const;

private:
	// 打印日程，可打印在屏幕上或文件上
	void printScheduel(ostream &out) const;
	vector<Match> matchesBySquads[8];  // 日程，一维为小组，第二维为每天的比赛
	vector<Match> matchesByDate[15];   // 日程，一维为日期，第二维为每天的比赛，总共15天
};

#endif