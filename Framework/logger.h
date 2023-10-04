#pragma once
#include <stdarg.h>
#include<stdio.h>
#include<sys/stat.h>
#include<time.h>
#include<string.h>
typedef enum {
	LOG_OUTPUT_POLICY_NONE=0,
	LOG_OUTPUT_POLICY_FILE=1,
	LOG_OUTPUT_POLICY_STDOUT=1<<1,
	LOG_OUTPUT_POLICY_BOTH= LOG_OUTPUT_POLICY_FILE | LOG_OUTPUT_POLICY_STDOUT
}LOG_OUTPUT_POLICY;


typedef enum {
	LOG_LEVEL_DEBUG = 0,
	LOG_LEVEL_INFO = 1,
	LOG_LEVEL_WARNING = 2,
	LOG_LEVEL_ERROR = LOG_LEVEL_WARNING << 1,
	LOG_LEVEL_CRITICAL = LOG_LEVEL_ERROR << 1
}POLICY_LEVEL;


typedef struct Logger {
	LOG_OUTPUT_POLICY policy;
	FILE* ptr_log;
	POLICY_LEVEL level;
}Logger;

void logger_init(LOG_OUTPUT_POLICY policy, POLICY_LEVEL level);
void logger_log(char msg[], POLICY_LEVEL level, ...);
const char* getPolicyLevelName(POLICY_LEVEL level);

// define the main macro
#define LOG(message, level, ...) logger_log(message, level, "%s %s [%s] %s %s: line %d: "message"\n", format_date(__DATE__), __TIME__, __func__, getPolicyLevelName(level), __FILE__, __LINE__ , ##__VA_ARGS__ )
