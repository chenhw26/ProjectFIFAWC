#ifndef KONCKOUTSTAGE
#define KONCKOUTSTAGE

#include "Team.h"
#include "Match.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <string>

class Result;

class KonckoutStage{
friend class Result;

public:
	//构造函数，传入十六强队伍
	KonckoutStage(const vector<Team> &_top16):top16(_top16) { 
		FinalTeams = vector<Team>(4);
	}

	//给16强队伍安排8常比赛，从 7 月 1 日开始，每天两场比赛
	void scheduling16(const vector<string> &venues);
	
	//依次进行16强比赛，胜利的队伍晋级8强.
	void playing16(Result& result);
	
	// 7 月 7 日开始，每天两场比赛.
	void schedulingQuarter(const vector<string> &venues);
	
	//依次进行4场四分一决赛，胜利队伍晋级4强.
	void playingQuarter(Result& result);	
	
	//7月11日开始，每天1场比赛.
	void schedulingSemi(const vector<string> &venues);

	//依次进行两场半决赛，胜出的进行冠军赛，失败的进行季军赛.
	void playingSemi(Result& result);	
	
	//7月15季军赛，7月16冠军赛.
	void schedulingFinal(const vector<string> &venues);

	//决定冠军、亚军、季军.
	void playingFinal(Result& result);

private:
	void reArrange();//给16强队伍重排列，进行比赛.
	void showMatch(ostream& out, const string message, const string nameA, const string nameB, 
		const pair<int, int> &score, const pair<int, int> &penalty)const;
	void showSchedule(ostream& out, const string message, const Match &match)const;
	vector<Team> top16, top8, top4, FinalTeams, rank;
	vector<Match> Round16, Quarter_finals, Semi_finals, Final;
};

#endif