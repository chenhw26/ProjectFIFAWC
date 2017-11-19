#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cmath>

#include "Random.h"
#include "Team.h"
#include "Result.h"

#define pi 3.141592654

using namespace std;

const string Team::allRegion[6] = {"AFC", "CAF", "OFC", "CONCACF", "CONMEBOL", "UEFA"};

void randomPick(const Team &team, vector<Player> &ply){
	vector<Player> GKcopy(team.GK);
	int num = rand() % GKcopy.size();
	ply.push_back(GKcopy[num]);	
	
	vector<Player> DFcopy(team.DF);
	for(int i = 0; i < 4; ++i){
		num = rand() % DFcopy.size();
		ply.push_back(DFcopy[num]);
		DFcopy.erase(DFcopy.begin() + num);
	}
	
	vector<Player> MFcopy(team.MF);
	for(int i = 0; i < 4; ++i){
		num = rand() % MFcopy.size();
		ply.push_back(MFcopy[num]);
		MFcopy.erase(MFcopy.begin() + num);
	}

	vector<Player> FWcopy(team.FW);
	for(int i = 0; i < 2; ++i){
		num = rand() % FWcopy.size();
		ply.push_back(FWcopy[num]);
		FWcopy.erase(FWcopy.begin() + num);
	}	
}

void show_ply(const Team &teamA, const Team &teamB,
	          const vector<Player> &plyA, const vector<Player> &plyB){
	printf("%-35s%s\n", teamA.country.c_str(), teamB.country.c_str());
	for(int i = 0; i < 11; ++i){
		Player A(plyA[i]), B(plyB[i]);
		printf("#%-2d %-20s %s      #%-2d %-20s %s\n", A.num, A.name.c_str(), A.pos.c_str(),
			                                               B.num, B.name.c_str(), B.pos.c_str());
	}
}

void match(Team &teamA, Team &teamB, Result &res){
	cout << teamA.country << " vs " << teamB.country << endl;
	vector<Player> teamAPly, teamBPly;
	randomPick(teamA, teamAPly);
	randomPick(teamB, teamBPly);
	show_ply(teamA, teamB, teamAPly, teamBPly);
	double expGoalOfA = 2 * sin(pi * (teamB.rank - teamA.rank) / 124) + 2;
	double expGoalOfB = 4 - expGoalOfA;
	int scoreOfA = 0, scoreOfB = 0;
	cout << "Playing..." << endl;
	for(int i = 0; i < 10; ++i){
		int GoalOfA = Random::poisson(expGoalOfA / 10), GoalOfB = Random::poisson(expGoalOfB / 10);
		scoreOfA += GoalOfA; scoreOfB += GoalOfB;
		if(GoalOfA || GoalOfB){
			printf("%d:00 ~ %d:00\n", i * 10, (i + 1) * 10);
			for(int j = 0; j < GoalOfA; ++j){
				Player goalScorer = teamAPly[rand() % 10 + 1];
				res.goal(goalScorer);
				printf("%s did a goal, and it was #%d, %s did the goal.\n", teamA.country.c_str(), goalScorer.num,
					                                                        goalScorer.name.c_str());
			}
			for(int j = 0; j < GoalOfB; ++j){
				Player goalScorer = teamBPly[rand() % 10 + 1];
				res.goal(goalScorer);
				printf("%s did a goal, and it was #%d, %s did the goal.\n", teamB.country.c_str(), goalScorer.num,
					                                                        goalScorer.name.c_str());
			}
			printf("Now is  %s %d:%d %s\n\n", teamA.country.c_str(), scoreOfA, scoreOfB, teamB.country.c_str());
		}	
	}
	printf("Result: %s %d:%d %s", teamA.country.c_str(), scoreOfA, scoreOfB, teamB.country.c_str());
    teamA.sta.set_sta(scoreOfA, scoreOfB);
    teamB.sta.set_sta(scoreOfB, scoreOfA);
}

void Team::readin(vector<Team> &allTeams){
	ifstream fin("team32.txt");
	for(int i = 0; i < 6; ++i){
		string s;
		int tmp, amount;
		fin >> s >> amount;
		while(amount--){
			fin >> s >> tmp;
			Team team;
			team.country = s;
			team.rank = tmp;
			team.rgn = allRegion[i];
			allTeams.push_back(team);
		}
	}
	fin.close();
	for(Team &p: allTeams){
		ifstream fin("allTeam/" + p.country + ".txt");
		for(int i = 0; i < 4; ++i){
			string pos;
			int amount, num;
			fin >> pos >> amount;
			while(amount--){
				vector<Player> *ply;
				switch(i){
					case 0: ply = &p.GK; break;
					case 1: ply = &p.DF; break;
					case 2: ply = &p.MF; break;
					case 3: ply = &p.FW; break;
				}
				Player pl;
				pl.team = p.country;
				pl.pos = pos;
				fin >> pl.num;
				fin.ignore(999, '\n');
				getline(fin, pl.name, '\r');
				ply -> push_back(pl);
			}
		}
		fin.close();
	}
}