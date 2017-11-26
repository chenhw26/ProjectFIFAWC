#include <iostream>
#include <fstream>
#include <iomanip>
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

void Match::show_ply(const vector<Player> &plyA, const vector<Player> &plyB, ostream &out) const{
	out << left << setw(35) << teamA.country << teamB.country << endl;
	for(int i = 0; i < 11; ++i){
		Player A(plyA[i]), B(plyB[i]);
		out << '#' << left << setw(2) << A.num << ' ' << setw(20) << A.name << ' '
			<< A.pos << "      #" << setw(2) << B.num << ' ' << setw(20) << B.name
			<< ' ' << B.pos << endl;
	}
}

pair<int, int> Match::match(Result &res) const{
	ofstream fout("data/SimulationLog.txt", ios_base::app);
	if(date < 14 || ((date == 14 && venue == "Krestovsky Stadium, Saint Petersburg"))
		|| ((date == 15) && venue == "Luzhniki Stadium, Moscow")){
		cout << "July ";
		fout << "July ";
	}
	else{ 
		cout << "June ";
		fout << "June ";
	}
	cout << (date? date: 30) << ", " << venue << endl;
	cout << teamA.country << " vs " << teamB.country << endl;
	fout << (date? date: 30) << ", " << venue << endl;
	fout << teamA.country << " vs " << teamB.country << endl;
	vector<Player> teamAPly, teamBPly;
	randomPick(teamA, teamAPly);
	randomPick(teamB, teamBPly);
	show_ply(teamAPly, teamBPly, cout);
	show_ply(teamAPly, teamBPly, fout);
	double expGoalOfA = 2 * sin(pi * (teamB.rank - teamA.rank) / 124) + 2;
	double expGoalOfB = 4 - expGoalOfA;
	int scoreOfA = 0, scoreOfB = 0;
	cout << "Playing..." << endl;
	fout << "Playing..." << endl;
	for(int i = 0; i < 10; ++i){
		int GoalOfA = Random::poisson(expGoalOfA / 10), GoalOfB = Random::poisson(expGoalOfB / 10);
		scoreOfA += GoalOfA; scoreOfB += GoalOfB;
		if(GoalOfA || GoalOfB){
			cout << i * 10 << ":00 ~ " << (i + 1) * 10 << ":00\n";
			fout << i * 10 << ":00 ~ " << (i + 1) * 10 << ":00\n";
			for(int j = 0; j < GoalOfA; ++j){
				Player goalScorer = teamAPly[rand() % 10 + 1];
				res.goal(goalScorer);
				cout << teamA.country << " did a goal, and it was #" << goalScorer.num << ", " 
					 << goalScorer.name << " did the goal.\n";
				fout << teamA.country << " did a goal, and it was #" << goalScorer.num << ", " 
					 << goalScorer.name << " did the goal.\n";
			}
			for(int j = 0; j < GoalOfB; ++j){
				Player goalScorer = teamBPly[rand() % 10 + 1];
				res.goal(goalScorer);
				cout << teamB.country << " did a goal, and it was #" << goalScorer.num << ", " 
					 << goalScorer.name << " did the goal.\n";
				fout << teamB.country << " did a goal, and it was #" << goalScorer.num << ", " 
					 << goalScorer.name << " did the goal.\n";
			}
			cout << "Now is  " << teamA.country << ' ' << scoreOfA << ':' << scoreOfB << ' ' << teamB.country << endl << endl;
			fout << "Now is  " << teamA.country << ' ' << scoreOfA << ':' << scoreOfB << ' ' << teamB.country << endl << endl;
		}	
	}
	cout << "Result: " << teamA.country << ' ' << scoreOfA << ':' << scoreOfB << ' ' << teamB.country << endl << endl;
	fout << "Result: " << teamA.country << ' ' << scoreOfA << ':' << scoreOfB << ' ' << teamB.country << endl << endl;
    res.matchResult(teamA, teamB, scoreOfA, scoreOfB);
    res.scoreResult[teamA.group].push_back(pair<int, int>(scoreOfA, scoreOfB));
    return pair<int, int>(scoreOfA, scoreOfB);
}

pair<int, int> Match::penalties() const{
	ofstream fout("data/SimulationLog.txt", ios_base::app);
	cout << "Now is penaltly shoot-out!!\n";
	fout << "Now is penaltly shoot-out!!\n";
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
		cout << teamA.country << ' ' << (goalA? "did": "missed") << " a goal, now is "
			 << teamA.country << ' ' << scoreOfA << ':' << scoreOfB << ' ' << teamB.country << endl;
		fout << teamA.country << ' ' << (goalA? "did": "missed") << " a goal, now is "
			 << teamA.country << ' ' << scoreOfA << ':' << scoreOfB << ' ' << teamB.country << endl;
		if(scoreOfA > scoreOfB + 5 - i) break;
		scoreOfB += (goalB? 1: 0);
		cout << teamB.country << ' ' << (goalB? "did": "missed") << " a goal, now is "
			 << teamA.country << ' ' << scoreOfA << ':' << scoreOfB << ' ' << teamB.country << endl;
		fout << teamB.country << ' ' << (goalB? "did": "missed") << " a goal, now is "
			 << teamA.country << ' ' << scoreOfA << ':' << scoreOfB << ' ' << teamB.country << endl;
}
	while(scoreOfA == scoreOfB){
		bool goalA = Random::random_bool(goalRatioOfA), goalB = Random::random_bool(goalRatioOfB);
		scoreOfA += (goalA? 1: 0);
		cout << teamA.country << ' ' << (goalA? "did": "missed") << " a goal, now is "
			 << teamA.country << ' ' << scoreOfA << ':' << scoreOfB << ' ' << teamB.country << endl;
		fout << teamA.country << ' ' << (goalA? "did": "missed") << " a goal, now is "
			 << teamA.country << ' ' << scoreOfA << ':' << scoreOfB << ' ' << teamB.country << endl;
		scoreOfB += (goalB? 1: 0);
		cout << teamB.country << ' ' << (goalB? "did": "missed") << " a goal, now is "
			 << teamA.country << ' ' << scoreOfA << ':' << scoreOfB << ' ' << teamB.country << endl;
		fout << teamB.country << ' ' << (goalB? "did": "missed") << " a goal, now is "
			 << teamA.country << ' ' << scoreOfA << ':' << scoreOfB << ' ' << teamB.country << endl;
	}
	cout << "\nResult: " << teamA.country << ' ' << scoreOfA << ':' << scoreOfB << ' ' << teamB.country << endl;
	return pair<int, int>(scoreOfA, scoreOfB);
}