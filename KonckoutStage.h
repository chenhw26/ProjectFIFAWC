#ifndef KONCKOUTSTAGE
#define KONCKOUTSTAGE

#include "Team.h"
#include "Match.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <string>
#include <algorithm>

class Result;

class KonckoutStage{
friend class Result;

public:
	//构造函数，传入十六强队伍
	KonckoutStage(const vector<Team> &_top16):top16(_top16) { }

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

	//打印分区晋级图.
	void showBlacket();

private:
	//按照比赛顺序重排列.
	void reArrange();

	//从文件中读取时间和场地.
	void readSchedule(const char* fileName, vector<Match>& matches);

	//写入每场比赛的队伍.
	void writeSchedule(const char* fileNmae, vector<Match>& matches);

	//执行一场比赛，记下胜出队伍，双方得分，点球数.
	pair<Team, Team> play(const match& match, pair<int, int>& score, pair<int, int>& penalty) const；

	//用于帮助显示晋级图.
	void appendScore(string& a, string& b, const string& teamA, const string& teamB, 
						const pair<int, int>& score, const pair<int, int>& penalty);

	vector<Team> top16, top8, top4, FinalTeams, Rank;
	vector<Match> Round16, Quarter_finals, Semi_finals, Final;
	vector<pair<int, int> > AllScore, AllPenalty;
};

#endif