#include <algorithm>
#include <fstream>
#include <iostream>
#include <iomanip>
#include "Result.h"

Result::Result(const vector<Team> groups[8]){
	for(int i = 0; i < 8; ++i)
		for(const Team &t: groups[i])
			Ranklist[t] = Statistic();
}

void Result::matchResult(const Team &teamA, const Team &teamB, int scoreOfA, int scoreOfB){
	Ranklist[teamA].set_sta(scoreOfA, scoreOfB);
	Ranklist[teamB].set_sta(scoreOfB, scoreOfA);
}

bool Result::cmp1(const pair<Team, Statistic> &A, const pair<Team, Statistic> &B){
	if(!(A.second == B.second))
		return !(A.second < B.second);
	else return A.first < B.first;
}

bool Result::cmp2(const pair<Player, int> &A, const pair<Player, int> &B){
	return A.second > B.second;
}

void Result::printResult(ostream &out, const vector<Team> groups[8]){
	const int A[4] = {2, 0, 3, 3}, B[4] = {3, 2, 1, 0};
	for(int i = 0; i < 8; ++i){
		out << "Final Result for Group " << char('A'+i) 
			<< "                                  Detail:" << endl;
		out << "Team          W   D   L   GF  GA  GD  Pts                  " 
		    << groups[i][0].country << ' ' << scoreResult[i][0].first << ':' 
		    << scoreResult[i][0].second << ' ' << groups[i][1].country << endl;
		int k = 0;
		for(const auto &p: groupResult[i]){
			out << left << setw(14) << p.first.country
			    << left << setw(4) << p.second.W
			    << left << setw(4) << p.second.D
			    << left << setw(4) << p.second.L
			    << left << setw(4) << p.second.GF
			    << left << setw(4) << p.second.GA
			    << left << setw(4) << p.second.GD
			    << left << setw(4) << p.second.Pts << "                 "
			    << groups[i][A[k]].country << ' ' << scoreResult[i][k + 1].first << ':'
			    << scoreResult[i][k + 1].second << ' ' << groups[i][B[k]].country << endl;
			++k;
		}
		out << "                                                           "
			<< groups[i][1].country << ' ' << scoreResult[i][5].first << ':'
			<< scoreResult[i][5].second << ' ' << groups[i][2].country << endl << endl; 
	}
}

void Result::groupStageResult(vector<Team> &top16, const vector<Team> groups[8]){
	for(const auto &p: Ranklist)
		groupResult[p.first.group].push_back(p);
	for(int i = 0; i < 8; ++i)
		sort(groupResult[i].begin(), groupResult[i].end(), cmp1);
	for(int i = 0; i < 8; ++i)
		for(int j = 0; j < 2; ++j)
			top16.push_back(groupResult[i][j].first);
	printResult(cout, groups);
	ofstream fout("data/Result16.txt");
	printResult(fout, groups);
	fout.close();
}

void Result::goal(const Player &ply){
	bool has = false;
	for(auto &p: GoalScorers){
		if(p.first.num == ply.num && p.first.team == ply.team){
			has = true;
			++p.second;
			break;
		}
	}
	if(!has)
		GoalScorers.push_back(pair<Player, int>(ply, 1));
}

void Result::printGoalScorers(ostream &out){
	sort(GoalScorers.begin(), GoalScorers.end(), cmp2);
	int goal = GoalScorers[0].second;
	out << endl << goal << " goal(s)" << endl;
	for(const auto &p: GoalScorers){
		if(p.second != goal){
			goal = p.second;
			out << endl << goal << " goal(s)" << endl;
		}
		out << ' ' << p.first.name << " , " << p.first.pos << " , " << p.first.team << endl;
	}
}