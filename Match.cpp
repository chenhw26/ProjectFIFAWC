#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>

#include "Random.h"
#include "Match.h"

#define pi 3.141592654


void Match::randomPick(const Team &team, vector<Player> &ply) const{
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

void Match::show_ply(const vector<Player> &plyA, const vector<Player> &plyB) const{
	printf("%-35s%s\n", teamA.country.c_str(), teamB.country.c_str());
	for(int i = 0; i < 11; ++i){
		Player A(plyA[i]), B(plyB[i]);
		printf("#%-2d %-20s %s      #%-2d %-20s %s\n", A.num, A.name.c_str(), A.pos.c_str(),
			                                               B.num, B.name.c_str(), B.pos.c_str());
	}
}

pair<int, int> Match::match(Result &res) const{
	cout << teamA.country << " vs " << teamB.country << endl;
	vector<Player> teamAPly, teamBPly;
	randomPick(teamA, teamAPly);
	randomPick(teamB, teamBPly);
	// show_ply(teamA, teamB, teamAPly, teamBPly);
	double expGoalOfA = 2 * sin(pi * (teamB.rank - teamA.rank) / 124) + 2;
	double expGoalOfB = 4 - expGoalOfA;
	int scoreOfA = 0, scoreOfB = 0;
	cout << "Playing..." << endl;
	for(int i = 0; i < 10; ++i){
		int GoalOfA = Random::poisson(expGoalOfA / 10), GoalOfB = Random::poisson(expGoalOfB / 10);
		scoreOfA += GoalOfA; scoreOfB += GoalOfB;
		if(GoalOfA || GoalOfB){
			// printf("%d:00 ~ %d:00\n", i * 10, (i + 1) * 10);
			for(int j = 0; j < GoalOfA; ++j){
				Player goalScorer = teamAPly[rand() % 10 + 1];
				res.goal(goalScorer);
				// printf("%s did a goal, and it was #%d, %s did the goal.\n", teamA.country.c_str(), goalScorer.num,
					                                                        // goalScorer.name.c_str());
			}
			for(int j = 0; j < GoalOfB; ++j){
				Player goalScorer = teamBPly[rand() % 10 + 1];
				res.goal(goalScorer);
				// printf("%s did a goal, and it was #%d, %s did the goal.\n", teamB.country.c_str(), goalScorer.num,
					                                                        // goalScorer.name.c_str());
			}
			// printf("Now is  %s %d:%d %s\n\n", teamA.country.c_str(), scoreOfA, scoreOfB, teamB.country.c_str());
		}	
	}
	printf("Result: %s %d:%d %s\n\n", teamA.country.c_str(), scoreOfA, scoreOfB, teamB.country.c_str());
    res.matchResult(teamA, teamB, scoreOfA, scoreOfB);
    return pair<int, int>(scoreOfA, scoreOfB);
}

pair<int, int> Match::penalties() const{
	printf("Now is penaltly shoot-out!!\n");
	int scoreOfA = 0, scoreOfB = 0;
	double goalRatioOfA, goalRatioOfB;
	if(teamA.rank < teamB.rank){
		goalRatioOfA = 0.8;
		int difference = teamB.rank - teamA.rank;
		goalRatioOfB = 0.8 - (difference < 30? difference / 100.0: 0.3); 
	}
	else{
		goalRatioOfB = 0.8;
		int difference = teamA.rank - teamB.rank;
		goalRatioOfA = 0.8 - (difference < 30? difference / 100.0: 0.3);		
	}
	for(int i = 0; i < 5; ++i){
		if(scoreOfA + 5 - i < scoreOfB) break;
		bool goalA = Random::random_bool(goalRatioOfA), goalB = Random::random_bool(goalRatioOfB);
		scoreOfA += (goalA? 1: 0);
		// printf("%s %s a goal, now is %s %d:%d %s\n", teamA.country.c_str(), (goalA? "did": "missed"), 
													 // teamA.country.c_str(), scoreOfA, scoreOfB, teamB.country.c_str());
		if(scoreOfA > scoreOfB + 5 - i) break;
		scoreOfB += (goalB? 1: 0);
		// printf("%s %s a goal, now is %s %d:%d %s\n", teamB.country.c_str(), (goalB? "did": "missed"), 
													 // teamA.country.c_str(), scoreOfA, scoreOfB, teamB.country.c_str());		
	}
	while(scoreOfA == scoreOfB){
		bool goalA = Random::random_bool(goalRatioOfA), goalB = Random::random_bool(goalRatioOfB);
		scoreOfA += (goalA? 1: 0);
		// printf("%s %s a goal, now is %s %d:%d %s\n", teamA.country.c_str(), (goalA? "did": "missed"), 
													 // teamA.country.c_str(), scoreOfA, scoreOfB, teamB.country.c_str());
		scoreOfB += (goalB? 1: 0);
		// printf("%s %s a goal, now is %s %d:%d %s\n", teamB.country.c_str(), (goalB? "did": "missed"), 
													 // teamA.country.c_str(), scoreOfA, scoreOfB, teamB.country.c_str());
	}
	printf("\nResult: %s %d:%d %s\n", teamA.country.c_str(), scoreOfA, scoreOfB, teamB.country.c_str());
	return pair<int, int>(scoreOfA, scoreOfB);
}