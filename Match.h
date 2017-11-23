#ifndef MATCH
#define MATCH

#include "Team.h"
#include "Result.h"

// ������Ϣ
class Match{

friend class GroupStage;
friend class KonckoutStage;

public:		
	Match(const Team &A, const Team &B):teamA(A), teamB(B) {}
	
	// ģ�������������ӵ�statistic����Result���Ա����ͳ����Ա����
	// ���������������
	// ��ƵĻ�ϴ�ӡ�����Ϣ
	pair<int, int> match(Result &res) const;

	pair<int, int> penalties() const;

private:	
	void randomPick(const Team &team, vector<Player> &ply) const;
	void show_ply(const vector<Player> &plyA, const vector<Player> &plyB) const;	

	Team teamA, teamB;
	string venue;      // ����
	int date;
};

#endif