#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <string>
#include <ctime>

#include "Team.h"
#include "Draw.h"
#include "GroupStage.h"
#include "Result.h"
#include "KonckoutStage.h"

using namespace std;

vector<Team> allTeams;                         // key:球队名
vector<Team> groups[8];                        // 小组赛分组
vector<Team> top16;                            // 16强
vector<string> venues;                        // 场馆

bool cmp(const pair<string, int> &a, const pair<string, int> &b){
	return a.second > b.second;
}

int main(){
	srand(time(NULL));
	GroupStage::readInVenue(venues);
	Team::readin(allTeams);
	Draw draw;
	draw.putInPots(allTeams);
	draw.grouping(groups);
	Draw::showDrawResult(groups); Draw::storeDrawResult(groups);
	GroupStage groupStage;
	groupStage.schedueling(groups, venues);
	Result res(groups);
	groupStage.playing(res);
	res.groupStageResult(top16);
	// KonckoutStage konckoutStage(top16);
	// konckoutStage.scheduling16(venues);
	// konckoutStage.playing16(res);
	// konckoutStage.schedulingQuarter(venues);
	// konckoutStage.playingQuarter(res);
	// konckoutStage.schedulingSemi(venues);
	// konckoutStage.playingSemi(res);
	// konckoutStage.schedulingFinal(venues);
	return 0;
}