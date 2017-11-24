#include <sstream>
#include "KonckoutStage.h"
using namespace std;

void KonckoutStage:: reArrange(){
	vector<Team> temp(top16);
	top16[1] = temp[3];	top16[8] = temp[11];
	top16[2] = temp[4];	top16[10] = temp[12];
	top16[3] = temp[7]; top16[11] = temp[15];
	top16[4] = temp[1]; top16[12] = temp[9];
	top16[5] = temp[6]; top16[13] = temp[14];
	top16[7] = temp[5]; top16[15] = temp[13];
}
/*
  pre:schedule8.txt 里有八场比赛的日期和场馆，top16 里有16强队伍.
  pos:把16个队伍安排到8场比赛中，并把安排结果重新放入 schedule8.txt，将比赛放入 Round16里(时间顺序).
*/
void KonckoutStage:: scheduling16(const vector<string> &venues){
	cout << "Schedule for round of 16:\n";
	reArrange();
	for(int i = 0; i < 8; i++){
		Match cur_match(top16[2 * i], top16[2 * i + 1]);
		Round16.push_back(cur_match);
	}
	readSchedule("data/schedule8.txt", Round16);//读入时间和场馆信息.
	ofstream out("data/schedule8.txt");
	writeSchedule(out , Round16);
	writeSchedule(cout , Round16);
	out.close();
}

/*
pre:Round16 里有非时间顺序的8场比赛.
pos:按时间顺序开始比赛，并把结果保存到result8.txt 里，把晋级队伍保存到top8.
 */
void KonckoutStage::playing16(Result& result){
	pair<int, int> score, penalty;
	for(int i = 0; i < Round16.size(); i++){
		pair<Team, Team> rank = play(Round16[i], score, penalty, result);
		top8.push_back(rank.first);
		AllScore.push_back(score);
		AllPenalty.push_back(penalty);
	}
	swap(top8[2], top8[4]);
	swap(top8[3], top8[5]);
	swap(AllScore[9], AllScore[10]);
	swap(AllPenalty[9], AllPenalty[10]);
	for(int i = 0; i < 4; i++)
		swap(top16[i + 4], top16[i + 8]);
	for(int i = 0; i < 2; i++){
		swap(AllScore[i+2], AllScore[i+4]);
		swap(AllPenalty[i+2], AllPenalty[i+4]);
	}
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
	for(int i = 0; i < 4; i++){
		Match cur_match(top8[2 * i], top8[2 * i + 1]);
	}
	readSchedule("data/schedule4.txt", Quarter_finals);
	ofstream out("data/schedule4.txt");
	writeSchedule(out , Quarter_finals);
	writeSchedule(cout , Quarter_finals);
	out.close();
}

/*
pre:Quarter_finals 里4场比赛.
pos:按时间顺序开始比赛，并把结果保存到result4.txt(队伍，比分) 里，把晋级队伍保存到top4.
 */
void KonckoutStage::playingQuarter(Result& result){
	pair<int, int> score, penalty;
	for(int i = 0; i < Quarter_finals.size(); i++){
		pair<Team, Team> rank = play(Quarter_finals[i], score, penalty, result);
		top4.push_back(rank.first);
		AllScore.push_back(score);
		AllPenalty.push_back(penalty);
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
		Semi_finals.push_back(cur_match);
	}
	readSchedule("data/schedule2.txt", Semi_finals);
	ofstream out("data/schedule2.txt");
	writeSchedule(out, Semi_finals);
	writeSchedule(cout, Semi_finals);
	out.close();
}


/*
pre:Semi_finals 里有的2场比赛.
pos:按时间顺序开始比赛，并把结果保存到result2.txt 里，四个队伍按结果重排，放到FinalTeams.
 */
void KonckoutStage::playingSemi(Result& result){
	FinalTeams.resize(4);
	pair<int, int> score, penalty;
	for(int i = 0; i < Semi_finals.size(); i++){
		pair<Team, Team> rank = play(Semi_finals[i], score, penalty, result);
		FinalTeams[i+2] = rank.first;
		FinalTeams[i] = rank.second; //季军赛先开始.
		AllScore.push_back(score);
		AllPenalty.push_back(penalty);
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
		Final.push_back(cur_match);
	}
	readSchedule("data/schedule1.txt", Final);
	ofstream out("data/schedule1.txt");
	writeSchedule(out, Final);
	writeSchedule(cout, Final);
	out.close();
}

/*
pre:Final 里有2场比赛.
pos:按时间顺序开始比赛，并把结果保存到result1.txt 里，把四个队伍重排放到rank.
*/
void KonckoutStage:: playingFinal(Result& result){
	Rank.resize(4);
	pair<int, int> score, penalty;
	for(int i = 0; i < Semi_finals.size(); i++){
		pair<Team, Team> rank = play(Semi_finals[i], score, penalty, result);
		Rank[2*i] = rank.first;
		Rank[2*i+1] = rank.second;
		AllScore.push_back(score);
		AllPenalty.push_back(penalty);
	}
}

void KonckoutStage:: showBlacket(){
	vector<string> teamA, teamB;
	for(int i = 0; i < 8; i++){
		teamA[i] = top16[2*i].country;
		teamB[i] = top16[2*i+1].country;
	}
	for(int i = 0; i < 4; i++){
		teamA[i+8] = top8[2*i].country;
		teamB[i+8] = top8[2*i+1].country;
	}
	for(int i = 0; i < 2; i++){
		teamA[i+12] = top4[2*i].country;
		teamB[i+12] = top4[2*i+1].country;
	}
	for(int i = 0; i < 2; i++){
		teamA[i+14] = FinalTeams[2*i].country;
		teamB[i+14] = FinalTeams[2*i+1].country;
	}
	string line[30];
	for(int i = 0; i < 15; i++){
		if((i+1)%2 == 1){
			appendScore(line[2 * i], line[2 * i + 1], teamA[i/2], teamB[i/2], AllScore[i/2], AllPenalty[i/2]);
		}
		else {
			line[2 * i].append(20,' ');
			line[2 * i + 1].append(20, ' ');
			if((i+1) % 4 == 2){
				appendScore(line[2 * i], line[2 * i + 1], teamA[i/4+8], teamB[i/4+8], AllScore[i/4+8], AllPenalty[i/4+8]);
			}
			else{
				line[2 * i].append(20,' ');
				line[2 * i + 1].append(20, ' ');
				if((i+1) % 8 == 4){
					appendScore(line[2 * i], line[2 * i + 1], teamA[i/8+12], teamB[i/8+12], AllScore[i/8+12], AllPenalty[i/8+12]);
				}
				else{
					line[2 * i].append(20,' ');
					line[2 * i + 1].append(20, ' ');
					appendScore(line[2 * i], line[2 * i + 1], teamA[15], teamB[15], AllScore[15], AllPenalty[15]);
				}
			}
		}
	}
	appendScore(line[22], line[23], teamA[14], teamB[14], AllScore[14], AllPenalty[14]);
	for(int i = 0; i < 30; i++) cout << line[i] << endl;
}

/*从文件中读入比赛时间和场地*/
void KonckoutStage:: readSchedule(const char* fileName, vector<Match>& matches){
	ifstream in(fileName);
	int count = 0, date;
	string month;
	while(in >> month >> date){
		cout << month << endl;
		in.ignore(999, '\n');
		string temp;
		while(1){
			getline(in, temp);
			cout << temp << endl;
			if(temp == "\n") break;
			size_t pos2 = temp.find(" , ");
			matches[count].venue = temp.substr(pos2 + 2);
			matches[count].date = date;
			count++;
		}
	}
	in.close();
}

/*把比赛双方队伍名称写入文件*/
void KonckoutStage:: writeSchedule(ostream &out, vector<Match>& matches){
	for(int i = 0; i < matches.size(); i++){
		if(i == 0 || matches[i].date != matches[i - 1].date){
			if(i) cout << endl;
			if(matches[i].date == 30) out << "June " << matches[i].date << endl;
			else out << "July " <<  matches[i].date << endl;
		}
		out << matches[i].teamA.country << " vs " << matches[i].teamB.country << " , " << matches[i].venue << endl;
	}
}

pair<Team, Team> KonckoutStage::play(Match& match, pair<int, int>& score, pair<int, int>& penalty, Result &res)const {
	score = match.match(res);
	if(score.first == score.second){
		penalty = match.penalties();
		if(penalty.first > penalty.second) return pair<Team, Team> (match.teamA, match.teamB);
		else return pair<Team, Team> (match.teamB, match.teamA);
	}
	else if(score.first > score.second) return pair<Team, Team> (match.teamA, match.teamB);
	else return pair<Team, Team> (match.teamB, match.teamA);
}

//从 top16, top7, top4, FinalTeams, Allscore, Allpenalty 中获取信息，打印晋级图.
void KonckoutStage:: appendScore(string& a, string& b, const string& teamA, const string& teamB, 
						const pair<int, int>& score, const pair<int, int>& penalty){
	size_t size = a.size();
	size += 20;
	a += teamA;
	b += teamB;
	stringstream ss;
	if(score.first == score.second){
		string temp;
		ss << score.first;
		ss >> temp;
		ss.clear();
		a += " " + temp;
		ss << penalty.first;
		ss >> temp;
		ss.clear();
		a += " (" + temp + ")";
		ss << score.second;
		ss >> temp;
		ss.clear();
		b += " " + temp;
		ss << penalty.second;
		ss >> temp;
		ss.clear();
		b += " (" + temp + ")";
	}
	else{
		string temp;
		ss << score.first;
		ss >> temp;
		a += " " + temp;
		ss.clear();
		ss << score.second;
		ss >> temp;
		b += " " + temp;
	}
	a.resize(size);
	b.resize(size);
}