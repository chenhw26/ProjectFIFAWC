#ifndef TEAM
#define TEAM
#define pi 3.141592654

#include <string>
#include <vector>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include "Random.h"
using namespace std;

extern map<string, Team> allTeams;

class Team{
	// 模拟比赛，更新球队的statistic，用Result类成员函数统计球员数据
	// 要求结果与球队排名相关
	// 在频幕上打印相关信息
	friend void match(const string &teamA, const string &teamB);
	friend void randomPick(const string &team, vector<Team::Player> &ply);
	friend void show_ply(const string &team, const vector<Team::Player> &ply);

public:
	struct Player{
		std::string name, team, pos;  // 位置
		int num;              // 球衣号
	};

	// 球队数据
	struct Statistic{
		int W = 0, D = 0, L = 0, GF = 0, GA = 0, GD = 0, Pts = 0;
		//  胜      平      负     进球	  失球    净胜球    积分
	};
	
	// 将文件中所有队伍信息读入allTeams中，自行写文件
	static void readin();

private:
	enum Region {AFC, CAF, OFC, CONCACAF, CONMEBOL, UEFA};
	std::string country;
	int rank;                  // 世界排名
	int group;                 // 小组赛分组
	enum Region rgn;
	Statistic sta;
	std::vector<Player> GK, DF, MF, FW;   // 球员
};

void randomPick(const string &team, vector<Team::Player> &ply){
	vector<Team::Player> GKcopy(allTeams[team].GK);
	int num = rand() % GKcopy.size();
	ply.push_back(GKcopy[num]);	
	
	vector<Team::Player> DFcopy(allTeams[team].DF);
	for(int i = 0; i < 4; ++i){
		num = rand() % DFcopy.size();
		ply.push_back(DFcopy[num]);
		DFcopy.erase(DFcopy.begin() + num);
	}
	
	vector<Team::Player> MFcopy(allTeams[team].MF);
	for(int i = 0; i < 4; ++i){
		num = rand() % MFcopy.size();
		ply.push_back(MFcopy[num]);
		MFcopy.erase(MFcopy.begin() + num);
	}

	vector<Team::Player> FWcopy(allTeams[team].FW);
	for(int i = 0; i < 2; ++i){
		num = rand() % FWcopy.size();
		ply.push_back(FWcopy[num]);
		FWcopy.erase(FWcopy.begin() + num);
	}	
}

void show_ply(const string &teamA, const string &teamB,
	          const vector<Team::Player> &plyA, const vector<Team::Player> &plyB){
	printf("%-40s%s\n", teamA.c_str(), teamB.c_str());
	for(int i = 0; i < 11; ++i){
		Team::Player A(plyA[i]), B(plyB[i]);
		printf("#%-2d, %-25s, %s      #%-2d, %-25s, %s\n", A.num, A.name.c_str(), A.pos.c_str(),
			                                               B.num, B.name.c_str(), B.pos.c_str());
	}
}

void match(string &teamA, string &teamB){
	cout << teamA.country << " vs " << teamB.country << endl;
	vector<Team::Player> teamAPly, teamBPly;
	randomPick(teamA, teamAPly);
	randomPick(teamB, teamBPly);
	show_ply(teamA, teamB, teamAPly, teamBPly);
	double expGoalOfA = 2 * sin(pi * (teamA.rank - teamB.rank) / 124) + 2;
	double expGoalOfB = 4 - expGoalOfA;
	int scoreOfA = 0, scoreOfB = 0;
	cout << "Playing..." << endl;
	for(int i = 0; i < 10; ++i){
		int GoalOfA = Random::poisson(expGoalOfA / 10), GoalOfB = Random::poisson(expGoalOfB / 10);
		scoreOfA += GoalOfA; scoreOfB += GoalOfB;
		if(GoalOfA || GoalOfB){
			printf("%d:00 ~ %d:00\n", i * 10, (i + 1) * 10);
			for(int j = 0; j < GoalOfA; ++j){
				Team::Player goalScorer = teamAPly[rand() % 10 + 1];
				printf("%s did a goal, and it was #%d, %s did the goal.\n", teamA.c_str(), goalScorer.num
					                                                        goalScorer.name.c_str());
			}
			for(int j = 0; j < GoalOfB; ++j){
				Team::Player goalScorer = teamBPly[rand() % 10 + 1];
				printf("%s did a goal, and it was #%d, %s did the goal.\n", teamB.c_str(), goalScorer.num
					                                                        goalScorer.name.c_str());
			}
			printf("Now is  %s %d:%d %s\n", teamA.name.c_str(), scoreOfA, scoreOfB, teamB.name.c_str());
		}	
	}
	
}

#endif