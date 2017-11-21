/* StudentID: 16337019
   Author: �º���
   File: Random.h
   Description: ���ڰ�װ����������ĺ�����
*/

#ifndef RANDOM
#define RANDOM

#include <cstdlib>
#include <ctime>
#include <cmath>

class Random{
public:
    // ����һ��[0, 1]֮������������
	static double random_real(){
		int ran = rand();
		return ran / double(RAND_MAX);
	}

	// �Ը���p����true
	static bool random_bool(double p){
		double t = random_real();
		if(t < p) return true;
		return false;
	}
	
	// ������meanΪlambdaֵ�Ĳ��������
	static int poisson(double mean){
		double limit = exp(-mean);
		double product = random_real();
		int count = 0;
		while(product > limit){
			++count;
			product *= random_real();
		}
		return count;
	}
};

#endif