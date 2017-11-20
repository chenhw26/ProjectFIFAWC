#include <queue>
#include <fstream>
#include <iostream>
using namespace std;

#include "GroupStage.h"

void GroupStage::readInVenue(vector<string> &venues){
	ifstream fin("venues.txt");
	string venue;
	int amount;
	fin >> amount;
	fin.ignore(999, '\n');
	while(amount--){
		getline(fin, venue, '\r');
		fin.ignore(999, '\n');
		venues.push_back(venue);
	}
	fin.close();
}

void GroupStage::schedueling(const vector<Team> groups[8], const vector<string> &venues){
	queue<Match> allMatches[8];
	for(int i = 0; i < 8; ++i){
		allMatches[i].push(Match(groups[i][0], groups[i][1]));
		allMatches[i].push(Match(groups[i][2], groups[i][3]));
		allMatches[i].push(Match(groups[i][0], groups[i][2]));
		allMatches[i].push(Match(groups[i][3], groups[i][1]));
		allMatches[i].push(Match(groups[i][3], groups[i][0]));
		allMatches[i].push(Match(groups[i][1], groups[i][2]));
	}
	for(int i = 0; i < 48; ++i){
		Match curMatch(allMatches[i % 8].front());
		allMatches[i % 8].pop();
		curMatch.venue = venues[i % venues.size()];
		curMatch.date = i / 4;
		matchesByDate[i / 4].push_back(curMatch);
		matchesBySquads[i % 8].push_back(curMatch);
	}
	printScheduel(cout);
	ofstream fout("scheduel16.txt");
	printScheduel(fout);
	fout.close();
}

void GroupStage::printScheduel(ostream &out) const{
	out << "Matches by squads" << endl;
	for(int i = 0; i < 8; ++i){
		out << "Group " << char('A'+i) << endl;
		for(const Match &m: matchesBySquads[i])
			out << ' ' << m.teamA.country << " vs " << m.teamB.country << " , "
		         << m.venue << "  June " << m.date + 19 << endl;
		out << endl; 
	}
	out << endl << "Matches by date" << endl;
	for(int i = 0; i < 12; ++i){
		out << "June " << i + 19 << endl;
		for(const Match &m: matchesByDate[i])
			out << ' ' << m.teamA.country << " vs " << m.teamB.country << " , " << m.venue << endl;
		out << endl;
	}
}

void GroupStage::playing(Result &res) const{
	for(int i = 0; i < 12; ++i)
		for(const Match &m: matchesByDate[i])
			match(m.teamA, m.teamB, res);
}