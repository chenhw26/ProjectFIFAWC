#include <iomanip>
#include "KonckoutStage.h"
using namespace std;

void KonckoutStage:: reArrange(){
	vector<Team> temp(top16);
	top16[1] = temp[3];	top16[9] = temp[11];
	top16[2] = temp[4];	top16[10] = temp[12];
	top16[3] = temp[7]; top16[11] = temp[15];
	top16[4] = temp[2]; top16[12] = temp[10];
	top16[5] = temp[1]; top16[13] = temp[9];
	top16[7] = temp[5]; top16[15] = temp[13];
}
/*
  pre:schedule8.txt 里有八场比赛的日期和场馆，top16 里有16强队伍.
  pos:把16个队伍安排到8场比赛中，并把安排结果重新放入 schedule8.txt，将比赛放入 Round16里(时间顺序).
*/
void KonckoutStage:: scheduling16(const vector<string> &venues){
	cout << "Schedule for round of 16:\n";
	reArrange();
	for(int i = 0; i < 16; i += 2){
		Match cur_match(top16[i], top16[i + 1]);
		Round16[i / 4].push_back(cur_match);
	}
	readSchedule("data/KnockoutStageSchedule/schedule8.txt", Round16, 4, 2);//读入时间和场馆信息.
	ofstream out("data/schedule8.txt");
	writeSchedule(out , Round16, 4);
	writeSchedule(cout , Round16, 4);
	out.close();
}

/*
pre:Round16 里有非时间顺序的8场比赛.
pos:按时间顺序开始比赛，并把结果保存到result8.txt 里，把晋级队伍保存到top8.
 */
void KonckoutStage::playing16(Result& result, vector<Team> &rank8_16){
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 2; ++j){
			pair<int, int> score(0, 0), penalty(0, 0);
			if(play(Round16[i][j], score, penalty, result)){
				top8.push_back(Round16[i][j].teamA);
				rank8_16.push_back(Round16[i][j].teamB);
			}
			else{
				top8.push_back(Round16[i][j].teamB);
				rank8_16.push_back(Round16[i][j].teamA);
			}
			AllScoreOfRound16.push_back(score);
			AllPenaltyOfRound16.push_back(penalty);
		}
	}
	swap(top8[2], top8[4]);
	swap(top8[3], top8[5]);
	swap(AllScoreOfRound16[2], AllScoreOfRound16[4]);
	swap(AllScoreOfRound16[3], AllScoreOfRound16[5]);
	swap(AllPenaltyOfRound16[2], AllPenaltyOfRound16[4]);
	swap(AllPenaltyOfRound16[3], AllPenaltyOfRound16[5]);
	for(int i = 4; i < 8; ++i)
		swap(top16[i], top16[i + 4]);
	cout << "Qualified for quarter final:\n";
	for(int i = 0; i < top8.size(); i++)
		cout << top8[i].country << endl;
	cout << endl;
}

/*
pre:schedule4.txt 里有四场比赛的比赛日期和场馆，top8 里有8强队伍.
pos:把8个队伍安排到4场比赛中，并把安排结果重新放入 schedule4.txt，将比赛放入 Quarter_finals里.
 */
void KonckoutStage:: schedulingQuarter(const vector<string> &venues){
	cout << "Schedule for quarter finals:\n";
	for(int i = 0; i < 4; ++i){
		Match cur_match(top8[2 * i], top8[2 * i + 1]);
		Quarter_finals[i / 2].push_back(cur_match);
	}
	readSchedule("data/KnockoutStageSchedule/schedule4.txt", Quarter_finals, 2, 2);
	ofstream out("data/schedule4.txt");
	writeSchedule(out , Quarter_finals, 2);
	writeSchedule(cout , Quarter_finals, 2);
	out.close();
}

/*
pre:Quarter_finals 里4场比赛.
pos:按时间顺序开始比赛，并把结果保存到result4.txt(队伍，比分) 里，把晋级队伍保存到top4.
 */
void KonckoutStage::playingQuarter(Result& result, vector<Team> &rank4_8){
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < 2; ++j){
			pair<int, int> score, penalty;
			if(play(Quarter_finals[i][j], score, penalty, result)){
				top4.push_back(Quarter_finals[i][j].teamA);
				rank4_8.push_back(Quarter_finals[i][j].teamB);
			}
			else{ 
				top4.push_back(Quarter_finals[i][j].teamB);
				rank4_8.push_back(Quarter_finals[i][j].teamA);
			}
			AllScoreOfQutFin.push_back(score);
			AllPenaltyOfQutFin.push_back(penalty);
		}
	}
	cout << "Qualified for semi finals:\n";
	for(int i = 0; i < top4.size(); i++)
		cout << top4[i].country << endl;
	cout << endl;
}

/*
pre:schedule2.txt 里有2场比赛的比赛日期和场馆，top4 里有4强队伍.
pos:把4个队伍安排到2场比赛中，并把安排结果重新放入 schedule2.txt，将比赛放入 Semi_finals里.
 */
void KonckoutStage:: schedulingSemi(const vector<string> &venues){
	cout << "Schedule for semi finals:\n";
	for(int i = 0; i < 2; i++){
		Match cur_match(top4[2 * i], top4[2 * i + 1]);
		Semi_finals[i].push_back(cur_match);
	}
	readSchedule("data/KnockoutStageSchedule/schedule2.txt", Semi_finals, 2, 1);
	ofstream out("data/schedule2.txt");
	writeSchedule(out, Semi_finals, 2);
	writeSchedule(cout, Semi_finals, 2);
	out.close();
}


/*
pre:Semi_finals 里有的2场比赛.
pos:按时间顺序开始比赛，并把结果保存到result2.txt 里，四个队伍按结果重排，放到FinalTeams.
 */
void KonckoutStage::playingSemi(Result& result){
	FinalTeams.resize(4);
	pair<int, int> score, penalty;
	for(int i = 0; i < 2; ++i){
		if(play(Semi_finals[i][0], score, penalty, result)){
			FinalTeams[2 + i] = Semi_finals[i][0].teamA;
			FinalTeams[i] = Semi_finals[i][0].teamB;
		}
		else{
			FinalTeams[2 + i] = Semi_finals[i][0].teamB;
			FinalTeams[i] = Semi_finals[i][0].teamA;			
		}
		AllScoreOfSemiFin.push_back(score);
		AllPenaltyOfSemiFin.push_back(penalty);
	}
	cout << "Qualified for final:\n";
	cout << FinalTeams[0].country << endl;
	cout << FinalTeams[1].country << endl << endl;
	cout << "Qualified for third:\n";
	cout << FinalTeams[2].country << endl;
	cout << FinalTeams[3].country << endl << endl;
}

/*
pre:schedule1.txt 里有2场比赛的比赛日期和场馆，FinalTeams 里有4个队伍.
pos:把4个队伍安排到2场比赛中，并把安排结果重新放入 schedule1.txt，将比赛放入 Finals里（决赛在前，季军赛在后）.
 */
void KonckoutStage:: schedulingFinal(const vector<string> &venues){
	cout << "Schedule for final and third:\n";
	for(int i = 0; i < 2; i++){
		Match cur_match(FinalTeams[2*i], FinalTeams[2*i+1]);
		Final[i].push_back(cur_match);
	}
	readSchedule("data/KnockoutStageSchedule/schedule1.txt", Final, 2, 1);
	ofstream out("data/schedule1.txt");
	writeSchedule(out, Final, 2);
	writeSchedule(cout, Final, 2);
	out.close();
}

/*
pre:Final 里有2场比赛.
pos:按时间顺序开始比赛，并把结果保存到result1.txt 里，把四个队伍重排放到rank.
*/
void KonckoutStage:: playingFinal(Result& result, vector<Team> &rank1_4){
	pair<int, int> score, penalty;
	for(int i = 0; i < 2; i++){
		if(play(Final[i][0], score, penalty, result)){
			rank1_4[(1 - i) * 2] = Final[i][0].teamA;
			rank1_4[(1 - i) * 2 + 1] = Final[i][0].teamB;
		}
		else{
			rank1_4[(1 - i) * 2] = Final[i][0].teamB;
			rank1_4[(1 - i) * 2 + 1] = Final[i][0].teamA;			
		}
		AllScoreOfFin.push_back(score);
		AllPenaltyOfFin.push_back(penalty);
	}
	cout << "Final over!\n";
}

/*从文件中读入比赛时间和场地*/
void KonckoutStage:: readSchedule(const char* fileName, vector<Match> matches[], int day, int numofmtc){
	ifstream fin(fileName);
	int date = 0;
	for(int i = 0; i < day; ++i){
		fin >> date;
		fin.ignore(999, '\n');
		for(int j = 0; j < numofmtc; ++j){
			matches[i][j].date = date;
			getline(fin, matches[i][j].venue, '\r');
			fin.ignore(999, '\n');
		}
	}
}

/*把比赛双方队伍名称写入文件*/
void KonckoutStage:: writeSchedule(ostream &out, vector<Match> matches[], int day){
	for(int i = 0; i < day; ++i){
		out << (matches[i][0].date == 30? "June ": "July ") << matches[i][0].date << endl;
		for(auto &p: matches[i])
			out << p.teamA.country << " vs " << p.teamB.country << ", " << p.venue << endl;
		out << endl; 
	}
}

bool KonckoutStage::play(Match& match, pair<int, int>& score, pair<int, int>& penalty, Result &res)const {
	score = match.match(res);
	if(score.first == score.second){
		penalty = match.penalties();
		if(penalty.first > penalty.second) return true;
		else return false;
	}
	else if(score.first > score.second) return true;
	else return false;
}

void KonckoutStage::printBracket(ostream &out, int period){
	out << right << setw(13) << "Round16" << setw(21) << "Quarter Finals";
	if(period <= 8) out << setw(19) << "Semi Finals";
	if(period <= 4) out << setw(18) << "Final";
	out << endl << endl;
	for(int i = 0; i < 30; ++i){
		if(i % 4 == 0){
			out << right << setw(11) << top16[i / 2].country << ' ' << AllScoreOfRound16[i / 4].first;
			if(AllScoreOfRound16[i / 4].first == AllScoreOfRound16[i / 4].second)
				out << '(' << AllPenaltyOfRound16[i / 4].first << ')';
		}
		if((i - 1) % 4 == 0){
			out << setw(11) << top16[(i - 1) / 2 + 1].country << ' ' << AllScoreOfRound16[i / 4].second;
			if(AllScoreOfRound16[i / 4].first == AllScoreOfRound16[i / 4].second)
				out << '(' << AllPenaltyOfRound16[i / 4].second << ')';			
		}
		if(i % 8 == 2){
			out << setw(20) << " ";
			out << setw(11) << top8[i / 4].country;
			if(period <= 8){
				out << ' ' << AllScoreOfQutFin[i / 8].first;
				if(AllScoreOfQutFin[i / 8].first == AllScoreOfQutFin[i / 8].second)
					out << '(' << AllPenaltyOfQutFin[i / 8].first << ')';
			}
		}
		if((i - 1) % 8 == 2){
			out << setw(20) << " ";
			out << setw(11) << top8[(i - 1) / 4 + 1].country;
			if(period <= 8){
				out << ' ' << AllScoreOfQutFin[i / 8].second;
				if(AllScoreOfQutFin[i / 8].first == AllScoreOfQutFin[i / 8].second)
					out << '(' << AllPenaltyOfQutFin[i / 8].second << ')';
			}
		}
		if(period <= 8 && (i % 16 == 6)){
			out << setw(40) << " ";
			out << setw(11) << top4[i / 8].country;
			if(period <= 4){
				out << ' ' << AllScoreOfSemiFin[i / 16].first;
				if(AllScoreOfSemiFin[i / 16].first == AllScoreOfSemiFin[i / 16].second)
					out << '(' << AllPenaltyOfSemiFin[i / 16].first << ')';
			}
		}
		if(period <= 8 && ((i - 1) % 16 == 6)){
			out << setw(40) << " ";
			out << setw(11) << top4[(i - 1) / 8 + 1].country;
			if(period <= 4){				
				out << ' ' << AllScoreOfSemiFin[i / 16].second;
				if(AllScoreOfSemiFin[i / 16].first == AllScoreOfSemiFin[i / 16].second)
					out << '(' << AllPenaltyOfSemiFin[i / 16].second << ')';
			}
		}
		if(period <= 4 && i == 14){
			out << setw(60) << " ";
			out << setw(11) << FinalTeams[2].country;
			if(period <= 2){
				out << ' ' << AllScoreOfFin[1].first;
				if(AllScoreOfFin[1].first == AllScoreOfFin[1].second)
					out << '(' << AllPenaltyOfFin[1].first << ')';
			}
		}
		if(period <= 4 && i == 15){
			out << setw(60) << " ";
			out << setw(11) << FinalTeams[3].country;
			if(period <= 2){
				out << ' ' << AllScoreOfFin[1].second;
				if(AllScoreOfFin[1].first == AllScoreOfFin[1].second)
					out << '(' << AllPenaltyOfFin[1].second << ')';
			}
		}
		if(period <= 4 && i == 23) out << setw(10) << " " << "Third place play-off";
		if(period <= 4 && i == 24){
			out << setw(47) << " ";
			out << setw(11) << FinalTeams[0].country;
			if(period <= 2){
				out << ' ' << AllScoreOfFin[0].first;
				if(AllScoreOfFin[0].second == AllScoreOfFin[0].first)
					out << '(' << AllPenaltyOfFin[0].first << ')';
			}
		}
		if(period <= 4 && i == 25){
			out << setw(47) << " ";
			out << setw(11) << FinalTeams[1].country;
			if(period <= 2){
				out << ' ' << AllScoreOfFin[0].second;
				if(AllScoreOfFin[0].second == AllScoreOfFin[0].first)
					out << '(' << AllPenaltyOfFin[0].second << ')';
			}
		}
		out << endl;
	}
	out << endl;
}