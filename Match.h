#ifndef MATCH
#define MATCH

#include "Team.h"
#include "Result.h"

// 比赛信息
class Match{

friend class GroupStage;
friend class KonckoutStage;

public:		
	Match(const Team &A, const Team &B):teamA(A), teamB(B) {}
	
	// 模拟比赛，更新球队的statistic，用Result类成员函数统计球员数据
	// 结果与球队排名相关
	// 在频幕上打印相关信息
	pair<int, int> match(Result &res) const;

	pair<int, int> penalties() const;

private:	
	void randomPick(const Team &team, vector<Player> &ply) const;
	void show_ply(const vector<Player> &plyA, const vector<Player> &plyB) const;	

	Team teamA, teamB;
	string venue;      // 场馆
	int date;
};

#endif