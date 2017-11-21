#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <ctime>

#include "team.h"
#include "Draw.h"
#include "GroupStage.h"
#include "Result.h"

using namespace std;

pair<int, int> match(const Team &teamA, const Team &teamB, Result &res);
void randomPick(const Team &team, vector<Player> &ply);
void show_ply(const Team &teamA, const Team &teamB,
	          const vector<Player> &plyA, const vector<Player> &plyB);

vector<Team> allTeams;                         // key:球队名
vector<Team> groups[8];                        // 小组赛分组
vector<Team> top16;                            // 16强
vector<string> venues;                        // 场馆

int main(){
	srand(time(NULL));
	Team::readin(allTeams);
	Draw draw;
	draw.putInPots(allTeams).showPots();
	draw.grouping(groups);
	Draw::showDrawResult(groups);
	GroupStage groupStage;
	GroupStage::readInVenue(venues);
	groupStage.schedueling(groups, venues);
	Result res(groups);
	groupStage.playing(res);
	res.groupStageResult(top16);
	res.printGoalScorers(cout);
	return 0;
}