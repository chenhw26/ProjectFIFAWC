#include <vector>
#include <map>
#include "team.h"
#include "Result.h"
using namespace std;

void match(Team &teamA, Team &teamB, Result &res);
void randomPick(const Team &team, vector<Player> &ply);
void show_ply(const Team &teamA, const Team &teamB,
	          const vector<Player> &plyA, const vector<Player> &plyB);

map<string, Team> allTeams;                      // key:球队名
vector<string> groups[8];                        // 小组赛分组
vector<string> top16, top8, top4, top2;         // 16强 ~ 2强
string goal, silver, bronze, forthPalce;        // 1,2,3,4名

int main(){
	Team::readin(allTeams);
	Result res;
	match(allTeams["Japan"], allTeams["SouthKorea"], res);
	return 0;
}