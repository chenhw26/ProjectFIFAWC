#include <queue>
#include <fstream>
#include <iostream>
using namespace std;

#include "GroupStage.h"

void GroupStage::schedueling(const vector<Team> groups[8]){
	vector<pair<int, string> > sche(48);
	ifstream fin("data/GroupStageSchedule.txt");
	for(int i = 0; i < 48; ++i){
		fin >> sche[i].first;
		fin.ignore(999, '\n');
		getline(fin, sche[i].second, '\n');
	}
	queue<Match> allMatches;
	for(int i = 0; i < 8; ++i){
		allMatches.push(Match(groups[i][0], groups[i][1]));
		allMatches.push(Match(groups[i][2], groups[i][3]));
	}
	for(int i = 0; i < 8; ++i){
		allMatches.push(Match(groups[i][0], groups[i][2]));
		allMatches.push(Match(groups[i][3], groups[i][1]));
	}
	for(int i = 0; i < 8; ++i){
		allMatches.push(Match(groups[i][3], groups[i][0]));
		allMatches.push(Match(groups[i][1], groups[i][2]));
	}
	for(int i = 0; i < 48; ++i){
		Match curMatch(allMatches.front());
		allMatches.pop();
		curMatch.venue = sche[i].second;
		curMatch.date = sche[i].first;
		matchesByDate[sche[i].first - 14].push_back(curMatch);
		matchesBySquads[curMatch.teamA.group].push_back(curMatch);
	}
	printScheduel(cout);
	ofstream fout("data/scheduel16.txt");
	printScheduel(fout);
	fout.close();
}

void GroupStage::printScheduel(ostream &out) const{
	out << "Matches by squads" << endl;
	for(int i = 0; i < 8; ++i){
		out << "Group " << char('A'+i) << endl;
		for(const Match &m: matchesBySquads[i])
			out << ' ' << m.teamA.country << " vs " << m.teamB.country << " , "
		         << m.venue << "  June " << m.date << endl;
		out << endl; 
	}
	out << endl << "Matches by date" << endl;
	for(int i = 0; i < 15; ++i){
		out << "June " << i + 14 << endl;
		for(const Match &m: matchesByDate[i])
			out << ' ' << m.teamA.country << " vs " << m.teamB.country << " , " << m.venue << endl;
		out << endl;
	}
}

void GroupStage::playing(Result &res) const{
	for(int i = 0; i < 15; ++i)
		for(const Match &m: matchesByDate[i])
			m.match(res);
}