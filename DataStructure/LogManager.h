#pragma once
#include <stdio.h>
#include <stdarg.h>
#include <assert.h>

void format_print(const char* format, ...) {
	va_list lpStart;
	va_start(lpStart, format);
	vprintf(format, lpStart);
	va_end(lpStart);
	printf("\n");
}

#define ASSERT_MSG(expression, format, ...) \
	if (expression == false) {\
		format_print(format, ##__VA_ARGS__);\
        assert(expression);\
	}

#define ERROR_LOG(ERROR_TAG, format, ...) \
	printf("[" #ERROR_TAG "] ");\
	format_print(format, ##__VA_ARGS__);

#define INFO_LOG(INFO_TAG, format, ...) \
	printf("[" #INFO_TAG "] ");\
	format_print(format, ##__VA_ARGS__);

#define TEST_LOG(TEST_TAG, test_function) \
	test_function(); \
	printf("[" #TEST_TAG "] " #test_function " : PASS\n");