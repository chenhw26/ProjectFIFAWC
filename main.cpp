#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>

#include "Team.h"
#include "Draw.h"
#include "GroupStage.h"
#include "Result.h"
#include "KonckoutStage.h"

using namespace std;

vector<Team> allTeams;                         // key:球队名
vector<Team> groups[8];                        // 小组赛分组
vector<Team> top16;                            // 16强
vector<Team> rank16_32;                        // 最终排名在16~32名的队伍
vector<Team> rank8_16;                         // 最终排名在8~16名的队伍
vector<Team> rank4_8;                          // 最终排名在4~8名的队伍  
vector<Team> rank1_4(4);                       // 最终排名在1~4名的队伍
vector<string> venues;                         // 场馆

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
	res.groupStageResult(top16, groups, rank16_32);
	KonckoutStage konckoutStage(top16);
	konckoutStage.scheduling16(venues);
	konckoutStage.playing16(res, rank8_16);
	konckoutStage.printBracket(cout, 16);
	konckoutStage.schedulingQuarter(venues);
	konckoutStage.playingQuarter(res, rank4_8);
	konckoutStage.printBracket(cout, 8);
	konckoutStage.schedulingSemi(venues);
	konckoutStage.playingSemi(res);
	konckoutStage.printBracket(cout, 4);
	konckoutStage.schedulingFinal(venues);
	konckoutStage.playingFinal(res, rank1_4);
	konckoutStage.printBracket(cout, 2);
	res.finalResult(rank16_32, rank8_16, rank4_8, rank1_4);
	res.printFinalRanklist(cout);
	res.printGoalScorers(cout);
	ofstream out1("data/finalRanklist.txt"), out2("data/GoalScorers.txt");
	res.printFinalRanklist(out1);
	res.printGoalScorers(out2);
	return 0;
}