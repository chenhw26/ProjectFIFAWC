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

vector<Team> allTeams;                         // key:球队名
vector<Team> groups[8];                        // 小组赛分组
vector<Team> top16;                            // 16强
vector<string> venues;                        // 场馆

int main(){
	srand(time(NULL));
	Team::readin(allTeams);
	Match m(allTeams[23], allTeams[0]);
	int A = 0, B = 0;
	for(int i = 0; i < 1000; ++i){
		pair<int, int> p = m.penalties();
		if(p.first > p.second) ++A;
		else ++B;
	}
	cout << "Germany win: " << A << endl;
	cout << "Australia win: " << B << endl;
	// Draw draw;
	// draw.putInPots(allTeams).showPots();
	// draw.grouping(groups);
	// Draw::showDrawResult(groups);
	// GroupStage groupStage;
	// GroupStage::readInVenue(venues);
	// groupStage.schedueling(groups, venues);
	// Result res(groups);
	// groupStage.playing(res);
	// res.groupStageResult(top16);
	// res.printGoalScorers(cout);
	return 0;
}