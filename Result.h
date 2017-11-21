#ifndef RESULT
#define RESULT

#include <map>
#include "Team.h"

class Result{
public:
	// 球队数据
	struct Statistic{
		void set_sta(int score, int scoreOfOther){
			W += (score > scoreOfOther? 1: 0);
			D += (score == scoreOfOther? 1: 0);
			L += (score < scoreOfOther? 1: 0);
			GF += score;
			GA += scoreOfOther;
			GD += score - scoreOfOther;
			Pts += (score > scoreOfOther? 3: (score == scoreOfOther? 1: 0));
		}
		//  胜      平      负     进球	  失球    净胜球    积分
		int W = 0, D = 0, L = 0, GF = 0, GA = 0, GD = 0, Pts = 0;
		
		bool operator<(const Statistic &sta) const{
			if(Pts != sta.Pts)
				return Pts < sta.Pts;
			if(GD != sta.GD)
				return GD < sta.GD;
			return GF < sta.GF;
		}

		bool operator==(const Statistic &sta) const{
			return Pts == sta.Pts && GD == sta.GD && GF == sta.GF;
		}
	};

	// 初始化各队积分
	Result(const vector<Team> groups[8]);

	void matchResult(const Team &teamA, const Team &teamB, int scoreOfA, int scoreOfB);

	// 统计并打印小组赛结果, 将结果写在top16里
	void groupStageResult(vector<Team> &top16);

	// 生成所有队伍排名，按规则排
	void finalResult(){}

	// 该球员获得一个进球
	void goal(const Player &ply);

	void printGoalScorers(ostream &out);
private:
	static bool cmp1(const pair<Team, Statistic> &A, const pair<Team, Statistic> &B);
	static bool cmp2(const pair<Player, int> &A, const pair<Player, int> &B);
	void printResult(ostream &out);

	map<Team, Statistic> Ranklist;                 // 所有球队总排名 
	vector<pair<Team, Statistic> > groupResult[8]; // 小组赛结果统计
	vector<pair<Player, int> > GoalScorers;        // 后一个int为进球数
};

#endif