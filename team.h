#ifndef TEAM
#define TEAM

#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
using namespace std;

extern map<string, Team> allTeams;

class Team{
	// 模拟比赛，更新球队的statistic，用Result类成员函数统计球员数据
	// 要求结果与球队排名相关
	// 在频幕上打印相关信息
	friend void match(const string &teamA, const string &teamB);

	friend void randomPick(const string &team, vector<Team::Player> &ply);
public:
	struct Player{
		std::string name, team;
		int num;              // 球衣号
	};

	// 球队数据
	struct Statistic{
		int W = 0, D = 0, L = 0, GF = 0, GA = 0, GD = 0, Pts = 0;
		//  胜      平      负     进球	  失球    净胜球    积分
	};
	
	// 将文件中所有队伍信息读入allTeams中，自行写文件
	static void readin();

private:
	enum Region {AFC, CAF, OFC, CONCACAF, CONMEBOL, UEFA};
	std::string country;
	int rank;                  // 世界排名
	int group;                 // 小组赛分组
	enum Region rgn;
	Statistic sta;
	std::vector<Player> GK, DF, MF, FW;   // 球员
};

void randomPick(const string &team, vector<Team::Player> &ply){
	vector<Team::Player> GKcopy(allTeams[team].GK);
	int num = rand() % GKcopy.size();
	ply.push_back(GKcopy[num]);
	
}

void match(string &teamA, string &teamB){
	cout << teamA.country << " vs " << teamB.country << endl;
	vector<Team::Player> teamAPly, teamBPly;

}

#endif