#pragma once
#include <random>
#include <time.h>

#define TEST_CASE_NUM (1000)
#define MIN_INT32 (-2147483647)
#define MAX_INT32 (2147483647)

#define TEST_LOGGER(TEST_NAME) TestLogger TEST_LOGGER = TestLogger(TEST_NAME);
class TestLogger {
private:
	const char* name;
	clock_t start;
public:
	TestLogger() {}
	TestLogger(const char name[]) : name(name) {
		printf("%s Test Start!\n", name);
		start = clock();
	}
	~TestLogger() {
		clock_t run_time = clock() - start;
		printf("%s Test Pass!(%lu ms)\n\n", name, (unsigned int)run_time);
	}
};

class RandomGenerator {
	static std::random_device rd;
public:
	static int generateRandomInt(int min, int max) {
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dis(min, max);
		return dis(gen);
	}
};
std::random_device RandomGenerator::rd;


class TestClass {
private:
	int value;
public:
	TestClass(int value) : value(value) {}
};