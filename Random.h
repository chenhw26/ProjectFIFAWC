/* StudentID: 16337019
   Author: 陈浩玮
   File: Random.h
   Description: 用于包装产生随机数的函数。
*/

#ifndef RANDOM
#define RANDOM

#include <cstdlib>
#include <ctime>
#include <cmath>

class Random{
public:
    // 生成一个[0, 1]之间的随机浮点数
	static double random_real(){
		int ran = rand();
		return ran / double(RAND_MAX);
	}

	// 以概率p返回true
	static bool random_bool(double p){
		double t = random_real();
		if(t < p) return true;
		return false;
	}
	
	// 生成以mean为lambda值的泊松随机数
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