#ifndef MATCH
#define MATCH

#include "Team.h"

// ������Ϣ
struct Match{
	Match(const Team &A, const Team &B):teamA(A), teamB(B) {}
	Team teamA, teamB;
	string venue;      // ����
	int date;
};

#endif