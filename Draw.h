#ifndef DRAW
#define DRAW
#include <algorithm>
#include <cstdio>

#include "Team.h"

// 分组抽签
class Draw{
public:
	// 将分组结果放在文件和groups里
	static void grouping(vector<Team> &allTeams, vector<Team> groups[8]);
	static bool conflict(const vector<Team> &group, const Team &team);
	static bool pickTeam(const vector<Team> &pot, const vector<Team> &group, int &tar);
	static void solve_conflict(const vector<Team> &pot, const vector<Team> groups[8], 
								int potNum, int groupNum, int &potTar, int gruopTar);
	static void showPots(vector<Team> pots[4]);
	static void drawResult(vector<Team> groups[8]);
};

void Draw::showPots(vector<Team> pots[4]){
	printf("%-18s%-18s%-18s%-s\n", "Pot1", "Pot2", "Pot3", "Pot4");
	for(int i = 0; i < 8; ++i){
		for(int j = 0; j < 4; ++j)
			printf("%s(%2d)%*s", pots[j][i].country, pots[j][i].rank, 14-pots[j][i].country.length(), " ");
		printf("\n");
	}
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
	while(int i = 0; i < pot.size() && conflict(group, pot[tar]); ++i)
		tar = (tar + 1) % pot[i].size();
	if(!conflict(group, pot[tar]))
		return true;
	else return false;
}

void Draw::solve_conflict(const vector<Team> &pot, const vector<Team> groups[8], 
	                int potNum, int groupNum, int &potTar, int gruopTar){
	potTar = rand() % pot.size();
	gruopTar = rand() % groupNum;
	for(int i = 0; i < groupNum; ++i, gruopTar = (gruopTar + 1) % groupNum)
		for(int j = 0; j < pot.size(); ++j, potTar = (potTar + 1) % pot.size())
			if(!conflict(groups[groupNum], groups[gruopTar][potNum]) && !conflict(groups[gruopTar], pot[potTar]))
				return;
}

void Draw::grouping(vector<Team> &allTeams, vector<Team> groups[8]){
	sort(allTeams.begin(), allTeams.end());
	vector<Team> pots[4];
	for(int i = 0; i < 4; ++i)
		for(int j = 0; j < 8; ++j)
			pots[i].push_back(allTeams[i * 8 + j]);
	groups[0].push_back(pots[0][0]);
	pots[0].erase(pots[0].begin());
	for(int i = 1; i < 4; ++i){
		int tar;
		pickTeam(pots[i], groups[0], tar);
		groups[0].push_back(pots[i][tar]);
		pots[0].erase(pots[0].begin() + tar);
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
}

#endif