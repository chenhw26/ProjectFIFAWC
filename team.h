#ifndef TEAM
#define TEAM

#include <string>
#include <vector>
#include <map>
using namespace std;

class Result;
class Draw;
class GroupStage;
class Match;

struct Player{
	string name;
	string team;
	string pos;  // 位置
	int num;     // 球衣号
};

class Team{
	friend class Draw;
	friend class GroupStage;
	friend class Result;
	friend class Match;

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