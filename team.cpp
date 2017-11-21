#include <fstream>

#include "Team.h"
#include "Result.h"

const string Team::allRegion[6] = {"AFC", "CAF", "OFC", "CONCACF", "CONMEBOL", "UEFA"};

void Team::readin(vector<Team> &allTeams){
	ifstream fin("data/team32.txt");
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