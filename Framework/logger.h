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
	// CR: Please remove this definition from the macro, it does not belong here, you can define it elsewhere if needed (I don't think we do)
	LOG_OUTPUT_POLICY_BOTH= LOG_OUTPUT_POLICY_FILE | LOG_OUTPUT_POLICY_STDOUT
}LOG_OUTPUT_POLICY;

// CR: In contrast to the policy, this should not be a bitwise enum, since it's not allowed to have more than one set at the same time. Please use standard values.
typedef enum {
	LOG_LEVEL_DEBUG = 0,
	LOG_LEVEL_INFO = 1,
	LOG_LEVEL_WARNING = 2,
	LOG_LEVEL_ERROR = LOG_LEVEL_WARNING << 1,
	LOG_LEVEL_CRITICAL = LOG_LEVEL_ERROR << 1
	// CR: rename POLICY_LEVEL to LOG_POLICY_LEVEL
}POLICY_LEVEL;


typedef struct Logger {
	LOG_OUTPUT_POLICY policy;
	// CR: rename ptr_log -> file_handle or just file
	FILE* ptr_log;
	POLICY_LEVEL level;
	// CR: rename Logger to LoggerContext
}Logger;

// CR: convention is logger__init etc, two _ after the module name
void logger_init(LOG_OUTPUT_POLICY policy, POLICY_LEVEL level);
// CR: char msg[] -> const char* format
void logger_log(char msg[], POLICY_LEVEL level, ...);
const char* getPolicyLevelName(POLICY_LEVEL level);

// CR: please put the level before the message
// define the main macro
#define LOG(message, level, ...) logger_log(message, level, "%s %s [%s] %s %s: line %d: "message"\n", format_date(__DATE__), __TIME__, __func__, getPolicyLevelName(level), __FILE__, __LINE__ , ##__VA_ARGS__ )
