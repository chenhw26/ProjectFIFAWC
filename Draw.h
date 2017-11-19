#ifndef DRAW
#define DRAW

#include "Team.h"

// 分组抽签
class Draw{
public:
	// 将所有队伍放在4个pot里
	Draw& putInPots(vector<Team> &allTeams);
	// 将4个pot的队伍分到8个小组
	Draw& grouping(vector<Team> groups[8]);
	// 打印4个pot的队伍
	const Draw& showPots() const;
	// 将4个pot信息存入文件
	const Draw& storePots() const;
	// 打印分组结果
	static void showDrawResult(const vector<Team> groups[8]);
	// 将分组结果存入文件中
	static void storeDrawResult(const vector<Team> groups[8]);

private:// 以下均为分组过程中的辅助函数
	static bool conflict(const vector<Team> &group, const Team &team);
	static bool pickTeam(const vector<Team> &pot, const vector<Team> &group, int &tar);
	static void solve_conflict(const vector<Team> &pot, const vector<Team> groups[8], 
								int potNum, int groupNum, int &potTar, int &gruopTar);
	
	vector<Team> pots[4];             // 四个pot
};

#endif