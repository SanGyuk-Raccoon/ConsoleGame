#pragma once
#include <random>

#define TEST_CASE_NUM (1000)
#define MIN_INT32 (-2147483647)
#define MAX_INT32 (2147483647)

class RandomGenerator {
	static std::random_device rd;
public:

	static const RandomGenerator& getInstance() {
		static RandomGenerator rg;
		return rg;
	}

	static int generateRandomInt(int min, int max) {
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dis(min, max);
		return dis(gen);
	}
};
std::random_device RandomGenerator::rd;
