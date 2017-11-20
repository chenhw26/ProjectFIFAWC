#ifndef GROUPSTAGE
#define GROUPSTAGE

#include "Team.h"
#include "Result.h"
#include "Match.h"

// 小组赛阶段
class GroupStage{
public:
	// 安排日程存在文件中，安排场馆，打印信息
	void schedueling(const vector<Team> groups[8], const vector<string> &venues);
	
	/* 小组赛比赛, 要调用的函数: 
		void match(string &teamA, string &teamB)
	*/
	void playing(Result &res) const;

	// 读入场馆信息
	static void readInVenue(vector<string> &venues);

private:
	// 打印日程，可打印在屏幕上或文件上
	void printScheduel(ostream &out) const;

	vector<Match> matchesBySquads[8];  // 日程，一维为小组，第二维为每天的比赛
	vector<Match> matchesByDate[12];   // 日程，一维为日期，第二维为每天的比赛，48场小组赛，每天4场，总共12天
};

#endif