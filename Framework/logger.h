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
}LOG_OUTPUT_POLICY;


typedef struct Logger {
	LOG_OUTPUT_POLICY policy;
	FILE* ptr_log;

}Logger;

void logger_init(LOG_OUTPUT_POLICY policy);
void logger_log(char msg[], ...);

// define the main macro
#define LOG(message, ...) logger_log(message, "%s [%s] %s: line %d: "message, __TIMESTAMP__, __func__, __FILE__, __LINE__ , ##__VA_ARGS__ )
