#ifndef MATCH
#define MATCH

#include "Team.h"

// 比赛信息
struct Match{
	Match(const Team &A, const Team &B):teamA(A), teamB(B) {}
	Team teamA, teamB;
	string venue;      // 场馆
	int date;
};

#endif