#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <ctime>
#include "team.h"
#include "Result.h"
using namespace std;

void match(Team &teamA, Team &teamB, Result &res);
void randomPick(const Team &team, vector<Player> &ply);
void show_ply(const Team &teamA, const Team &teamB,
	          const vector<Player> &plyA, const vector<Player> &plyB);

vector<Team> allTeams;                           // key:球队名
vector<Team> groups[8];                        // 小组赛分组
vector<Team> top16, top8, top4, top2;         // 16强 ~ 2强
Team goal, silver, bronze, forthPalce;        // 1,2,3,4名

int main(){
	srand(time(NULL));
	Team::readin(allTeams);
	Result res;
	match(allTeams[0], allTeams[1], res);
	return 0;
}