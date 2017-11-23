#include "KonckoutStage.h"
using namespace std;

void KonckoutStage:: reArrange(){
	vector<Team> teamAs(8), teamBs(8);
	for(int i = 0; i < 4; i++){
		teamAs[i] = top16[4*i];
		teamAs[4 + i] = top16[4*i+2];
		teamBs[i] = top16[4*i+3];
		teamBs[4+i] = top16[4*i+1];
	}
	for(int i = 0; i < 8; i++){
		top16[2*i] = teamAs[i];
		top16[2*i+1] = teamBs[i];
	}
}

void KonckoutStage:: scheduling16(const vector<string> &venues){
	reArrange();
	ofstream out("schedule8.txt");
	for(int i = 0; i < 8; i++){
		Match cur_match(top16[2 * i], top16[2 * i + 1]);
		cur_match.date = i / 2 + 1;
		cur_match.venue = venues[i];
		Round16.push_back(cur_match);
		showSchedule(out, "", Round16[i]);
		// showSchedule(cout, "", Round16[i]);
	}
	out.close();
}

void KonckoutStage:: schedulingQuarter(const vector<string> &venues){
	ofstream out("schedule4.txt");
	for(int i = 0; i < 4; i++){
		Match cur_match(top8[2 * i], top8[2 * i + 1]);
		cur_match.date = i / 2 + 7;
		cur_match.venue = venues[i + 8];
		Quarter_finals.push_back(cur_match);
		showSchedule(out, "", Quarter_finals[i]);
		// showSchedule(cout, "", Quarter_finals[i]);
	}
	out.close();
}

void KonckoutStage:: schedulingSemi(const vector<string> &venues){
	ofstream out("schedule2.txt");
	for(int i = 0; i < 2; i++){
		Match cur_match(top4[2 * i], top4[2 * i + 1]);
		cur_match.date = i + 11;
		cur_match.venue = venues[1 - i];
		Semi_finals.push_back(cur_match);
		showSchedule(out, "", Semi_finals[i]);
		// showSchedule(cout, "", Semi_finals[i]);
	}
	out.close();
}

void KonckoutStage:: schedulingFinal(const vector<string> &venues){
	ofstream out("schedule1.txt");
	string message[2] = {"Final\n", "Third\n"};
	for(int i = 0; i < 2; i++){
		Match cur_match(FinalTeams[2 * i], FinalTeams[2 * i + 1]);
		cur_match.date = 16 - i;
		cur_match.venue = venues[i];
		Final.push_back(cur_match);
		showSchedule(out, message[i], Final[i]);
		// showSchedule(cout, message[i], Final[i]);
	}
	out.close();
}

void KonckoutStage::playing16(Result& result){
	ofstream out("Result8.txt");
	cout << "\n\nRound of 16\n";
	pair<int, int> scores, penalty;
	for(int i = 0; i < Round16.size(); i++){
		scores = Round16[i].match(result);
		if(scores.first == scores.second){
			penalty = Round16[i].penalties();
			if(penalty.first > penalty.second)
				top8.push_back(Round16[i].teamA);
			else top8.push_back(Round16[i].teamB);
		}
		else if(scores.first > scores.second)
			top8.push_back(Round16[i].teamA);
		else top8.push_back(Round16[i].teamB);
		showMatch(out, "", Round16[i].teamA.country, Round16[i].teamB.country, scores, penalty);
	}
	out.close();
}

void KonckoutStage::playingQuarter(Result& result){
	ofstream out("Result4.txt");
	cout << "\n\nQuarter finals\n";
	pair<int, int> scores, penalty = {0, 0};
	for(int i = 0; i < Quarter_finals.size(); i++){
		scores = Quarter_finals[i].match(result);
		if(scores.first == scores.second){
			penalty = Quarter_finals[i].penalties();
			if(penalty.first > penalty.second)
				top4.push_back(Quarter_finals[i].teamA);
			else top4.push_back(Quarter_finals[i].teamB);
		}
		else if(scores.first > scores.second)
			top4.push_back(Quarter_finals[i].teamA);
		else top4.push_back(Quarter_finals[i].teamB);
		showMatch(out, "", Quarter_finals[i].teamA.country, Quarter_finals[i].teamB.country, scores, penalty);
	}
	out.close();
}

void KonckoutStage::playingSemi(Result& result){
	ofstream out("Result2.txt");
	cout << "\n\nSemi finals\n";
	pair<int, int> scores, penalty = {0, 0};
	for(int i = 0; i < Semi_finals.size(); i++){
		scores = Semi_finals[i].match(result);
		if(scores.first == scores.second){
			penalty = Semi_finals[i].penalties();
			if(penalty.first > penalty.second){
				FinalTeams[i] = Semi_finals[i].teamA;
				FinalTeams[i + 2] = Semi_finals[i].teamB;
			}
			else {
				FinalTeams[i] = Semi_finals[i].teamB;
				FinalTeams[i + 2] = Semi_finals[i].teamA;
			}
		}
		else if(scores.first > scores.second)
			{
				FinalTeams[i] = Semi_finals[i].teamA;
				FinalTeams[i + 2] = Semi_finals[i].teamB;
			}
		else {
				FinalTeams[i] = Semi_finals[i].teamB;
				FinalTeams[i + 2] = Semi_finals[i].teamA;
			}
		showMatch(out, "", Semi_finals[i].teamA.country, Semi_finals[i].teamB.country, scores, penalty);
	}
	out.close();
}

void KonckoutStage:: playingFinal(Result& result){
	ofstream out("Result1.txt");
	pair<int, int> scores, penalty = {0, 0};
	string message[2] = {"\n\nThird\n", "\n\nFinal\n"};
	for(int i = 1; i >= 0; i--){
		if(i == 1) cout << "Final\n";
		else cout << "Third\n";
		scores = Final[i].match(result);
		if(scores.first == scores.second){
			penalty = Final[i].penalties();
		}
		showMatch(out, message[i], Final[i].teamA.country, Final[i].teamB.country, scores, penalty);
	}
	out.close();
}

void KonckoutStage::showMatch(ostream& out, const string message, const string nameA, 
	const string nameB, const pair<int, int> &score, const pair<int, int> &penalty)const {
	out << endl << message << nameA << ' ' << score.first;
	if(penalty != pair<int, int>(0, 0)) out << '(' << penalty.first << ')';
	out << " VS " << score.second;
	if(penalty != pair<int, int>(0, 0)) out << '(' << penalty.second << ')';
	out << ' ' << nameB;
}

void KonckoutStage:: showSchedule(ostream& out, const string message, const Match &match)const{
	out << endl << message;
	out << "July " << match.date << " at " << match.venue << endl;
	out << match.teamA.country << " VS " << match.teamB.country << endl;
}