#ifndef GROUPSTAGE
#define GROUPSTAGE

#include "Team.h"

// 小组赛阶段
class GroupStage{
public:
	// 比赛信息
	struct MatchInfo{
		Team teamA, teamB;
		string venue;      // 场馆
	};

	// 安排日程存在文件中，安排场馆，打印信息，场馆从文件中读，文件自行写
	static void schedueling();
	
	/* 小组赛比赛, 要调用的函数: 
		void match(string &teamA, string &teamB)
		static vector<vector<Match> > scheduel();
		...
	*/
	static void groupStage();

private:
	vector<vector<Match> > scheduel;  // 日程，一维为日期，第二维为每天的比赛
};

#endif