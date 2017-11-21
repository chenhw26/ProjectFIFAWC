#ifndef TEAM
#define TEAM

#include <string>
#include <vector>
#include <map>
using namespace std;

class Result;
class Draw;
class GroupStage;

struct Player{
	string name;
	string team;
	string pos;  // 位置
	int num;     // 球衣号
};

class Team{
	// 模拟比赛，更新球队的statistic，用Result类成员函数统计球员数据
	// 要求结果与球队排名相关
	// 在频幕上打印相关信息
	friend pair<int, int> match(const Team &teamA, const Team &teamB, Result &res);
	friend void randomPick(const Team &team, vector<Player> &ply);
	friend void show_ply(const Team &teamA, const Team &teamB,
	          const vector<Player> &plyA, const vector<Player> &plyB);
	
	friend class Draw;
	friend class GroupStage;
	friend class Result;

public:
	// 根据排名给球队排序
	bool operator<(const Team &other) const{
		if(other.country == "Russia") return false;
		else if(country == "Russia") return true;
		else return rank < other.rank;
	}
	
	// 将文件中所有队伍信息读入allTeams中，自行写文件
	static void readin(vector<Team> &);

private:
	string country;
	int rank;                  // 世界排名
	int group;                 // 小组赛分组
	string rgn;
	vector<Player> GK, DF, MF, FW;   // 球员
	static const string allRegion[6];
};

#endif