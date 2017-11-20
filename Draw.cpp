#include <algorithm>
#include <cstdio>
#include <fstream>

#include "Draw.h"
#include "Team.h"

using namespace std;

const Draw& Draw::showPots() const{
	printf("%-18s%-18s%-18s%-s\n", "Pot1", "Pot2", "Pot3", "Pot4");
	for(int i = 0; i < 8; ++i){
		for(int j = 0; j < 4; ++j)
			printf("%s(%2d)%*s", pots[j][i].country.c_str(), pots[j][i].rank, 
				                 14-pots[j][i].country.length(), " ");
		printf("\n");
	}
	return *this; 
}

const Draw& Draw::storePots() const{
	ofstream fout("finalDraw.txt");
	fout << "The First Stage:" << endl;
	for(int i = 0; i < 4; ++i){
		fout << "pot" << i + 1 << ':' << endl;
		for(const Team &t: pots[i])
			fout << t.country << endl;
		fout << endl;
	}
	fout.close();
	return *this;
}

void Draw::showDrawResult(const vector<Team> groups[8]){
	for(int k = 0; k < 2; ++k){
		for(int i = 0; i < 4; ++i)
			printf("%s%c%20s", "Group", 'A'+k*4+i, "");
		printf("\n");
		for(int i = 0; i < 4; ++i){
			for(int j = 0; j < 4; ++j)
				printf("%-11s%8s%7s", groups[j+k*4][i].country.c_str(), groups[j+k*4][i].rgn.c_str(), " ");
			printf("\n");
		}
		printf("\n");
	}
}

void Draw::storeDrawResult(const vector<Team> groups[8]){
	ofstream fout("finalDraw.txt", ios_base::app);
	fout << "The Final Draw:" << endl;
	for(int i = 0; i < 8; ++i){
		fout << "Group " << char('A' + i) << endl;
		for(const Team &t: groups[i])
			fout << t.country << endl;
		fout << endl;
	}
	fout.close();
}

bool Draw::conflict(const vector<Team> &group, const Team &team){
	int cnt = 0;
	for(const Team &t: group)
		if(t.rgn == team.rgn && t.country != team.country)
			++cnt;
	if(team.rgn == "UEFA")
		return (cnt < 2? false: true);
	else
		return (cnt < 1? false: true);
}

bool Draw::pickTeam(const vector<Team> &pot, const vector<Team> &group, int &tar){
	tar = rand() % pot.size();
	for(int i = 0; i < pot.size() && conflict(group, pot[tar]); ++i)
		tar = (tar + 1) % pot.size();
	if(!conflict(group, pot[tar]))
		return true;
	else return false;
}

Draw& Draw::putInPots(vector<Team> &allTeams){
	sort(allTeams.begin(), allTeams.end());
	for(int i = 0; i < 4; ++i)
		for(int j = 0; j < 8; ++j)
			pots[i].push_back(allTeams[i * 8 + j]);
	return *this;
}

void Draw::solve_conflict(const vector<Team> &pot, const vector<Team> groups[8], 
	                int potNum, int groupNum, int &potTar, int &gruopTar){
	potTar = rand() % pot.size();
	gruopTar = rand() % groupNum;
	for(int i = 0; i < groupNum; ++i, gruopTar = (gruopTar + 1) % groupNum)
		for(int j = 0; j < pot.size(); ++j, potTar = (potTar + 1) % pot.size())
			if(!conflict(groups[groupNum], groups[gruopTar][potNum]) && !conflict(groups[gruopTar], pot[potTar]))
				return;
}

Draw& Draw::grouping(vector<Team> groups[8]){
	groups[0].push_back(pots[0][0]);
	pots[0].erase(pots[0].begin());
	for(int i = 1; i < 4; ++i){
		int tar;
		pickTeam(pots[i], groups[0], tar);
		groups[0].push_back(pots[i][tar]);
		pots[i].erase(pots[i].begin() + tar);
	}

	for(int i = 1; i < 8; ++i){
		for(int j = 0; j < 4; ++j){
			int tar;
			if(pickTeam(pots[j], groups[i], tar)){
				groups[i].push_back(pots[j][tar]);
				pots[j].erase(pots[j].begin() + tar);
			}
			else{
				int gruopTar, potTar;
				solve_conflict(pots[j], groups, j, i, potTar, gruopTar);
				groups[i].push_back(groups[gruopTar][j]);
				groups[gruopTar][j] = pots[j][potTar];
				pots[j].erase(pots[j].begin() + potTar);
			}
		}
	}
	return *this;
}
