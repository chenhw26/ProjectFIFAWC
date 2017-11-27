#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>
#include <windows.h>

#include "Team.h"
#include "Draw.h"
#include "GroupStage.h"
#include "Result.h"
#include "KnockoutStage.h"

using namespace std;

vector<Team> allTeams;                         // key:球队名
vector<Team> groups[8];                        // 小组赛分组
vector<Team> top16;                            // 16强
vector<Team> rank16_32;                        // 最终排名在16~32名的队伍
vector<Team> rank8_16;                         // 最终排名在8~16名的队伍
vector<Team> rank4_8;                          // 最终排名在4~8名的队伍  
vector<Team> rank1_4(4);                       // 最终排名在1~4名的队伍

int main(){
	ofstream fout("data/SimulationLog.txt", ios_base::trunc);
	fout << endl; fout.close();
	srand(time(NULL));
	Team::readin(allTeams);
	system("pause");
	Draw draw;
	draw.putInPots(allTeams).showPots().storePots();
	system("pause");
	draw.grouping(groups);
	Draw::showDrawResult(groups); Draw::storeDrawResult(groups);
	system("pause");
	GroupStage groupStage;
	groupStage.schedueling(groups);
	system("pause");
	Result res(groups);
	groupStage.playing(res);
	system("pause");
	res.groupStageResult(top16, groups, rank16_32);
	system("pause");
	KnockoutStage knockoutStage(top16);
	system("pause");
	knockoutStage.scheduling16();
	system("pause");
	knockoutStage.playing16(res, rank8_16);
	knockoutStage.printBracket(cout, 16);
	fout.open("data/Result8.txt");
	knockoutStage.printBracket(fout, 16);
	fout.close();
	system("pause");
	knockoutStage.schedulingQuarter();
	system("pause");
	knockoutStage.playingQuarter(res, rank4_8);
	knockoutStage.printBracket(cout, 8);
	fout.open("data/Result4.txt");
	knockoutStage.printBracket(fout, 8);
	fout.close();
	system("pause");
	knockoutStage.schedulingSemi();
	system("pause");
	knockoutStage.playingSemi(res);
	knockoutStage.printBracket(cout, 4);
	fout.open("data/Result2.txt");
	knockoutStage.printBracket(fout, 4);
	fout.close();
	system("pause");
	knockoutStage.schedulingFinal();
	system("pause");
	knockoutStage.playingFinal(res, rank1_4);
	knockoutStage.printBracket(cout, 2);
	fout.open("data/Result1.txt");
	knockoutStage.printBracket(fout, 2);
	fout.close();
	system("pause");
	res.finalResult(rank16_32, rank8_16, rank4_8, rank1_4);
	res.printFinalRanklist(cout);
	fout.open("data/FinalResult.txt");
	res.printFinalRanklist(fout);
	fout.close();
	system("pause");
	res.printGoalScorers(cout);
	fout.open("data/GoalScorers.txt");
	res.printGoalScorers(fout);
	fout.close();
	system("pause");
	return 0;
}