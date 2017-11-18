#ifndef TEAM
#define TEAM

#include <string>
#include <vector>
#include <map>
using namespace std;

class Result;

struct Player{
	std::string name, team, pos;  // 位置
	int num;              // 球衣号
};

class Team{
	// 模拟比赛，更新球队的statistic，用Result类成员函数统计球员数据
	// 要求结果与球队排名相关
	// 在频幕上打印相关信息
	friend void match(Team &teamA, Team &teamB, Result &res);
	friend void randomPick(const Team &team, vector<Player> &ply);
	friend void show_ply(const Team &teamA, const Team &teamB,
	          const vector<Player> &plyA, const vector<Player> &plyB);

public:
	// 球队数据
	struct Statistic{
		void set_sta(int score, int scoreOfOther){
			W += (score > scoreOfOther? 1: 0);
			D += (score == scoreOfOther? 1: 0);
			L += (score < scoreOfOther? 1: 0);
			GF += score;
			GA += scoreOfOther;
			GD += score - scoreOfOther;
			Pts += (score > scoreOfOther? 3: (score == scoreOfOther? 1: 0));
		}
		int W = 0, D = 0, L = 0, GF = 0, GA = 0, GD = 0, Pts = 0;
		//  胜      平      负     进球	  失球    净胜球    积分
	};
	
	// 将文件中所有队伍信息读入allTeams中，自行写文件
	static void readin(map<string, Team> &);

private:
	std::string country;
	int rank;                  // 世界排名
	int group;                 // 小组赛分组
	string rgn;
	Statistic sta;
	std::vector<Player> GK, DF, MF, FW;   // 球员
	static const string allRegion[6];
};

#endif