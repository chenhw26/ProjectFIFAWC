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
class KnockoutStage;

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
	friend class KnockoutStage;

public:
	// 根据排名给球队排序，东道主与其他队比较时总是返回true
	bool operator<(const Team &other) const{
		if(other.country == "Russia") return false;
		else if(country == "Russia") return true;
		else return rank < other.rank;
	}
	
	// 将文件中所有队伍信息读入allTeams中
	static void readin(vector<Team> &);

private:
	string country;            // 所属国
	int rank;                  // 世界排名
	int group;                 // 小组赛分组
	string rgn;                // 所属地区
	vector<Player> GK, DF, MF, FW;   // 球员
	static const string allRegion[6];   // 所有地区
};

#endif