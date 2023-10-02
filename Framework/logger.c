
#include<stdio.h>
#include"logger.h"
#include <time.h>
#include <errno.h>
#include <string.h>
#include <stdarg.h>

char* now();


// instanciate gloabal static logger
static Logger Mylogger = { LOG_OUTPUT_POLICY_NONE , "log/file.log" };


void logger_init(LOG_OUTPUT_POLICY new_policy) {
	// ovveride default policy
	Mylogger.policy = new_policy;
	
	// if the policy is file then create the file itself and just close it
	if (Mylogger.policy == LOG_OUTPUT_POLICY_FILE){
		Mylogger.ptr_log = fopen("log/file.log", "a");
		if (Mylogger.ptr_log == NULL) {
			printf("Failed to allocate a file pointer, finishing prog");
			exit(1);
		}
		else
		{	
			fclose(Mylogger.ptr_log);
		}
	}
}

void logger(char msg[], ...) {

	// Initializing argument to the
	// list pointer
	va_list args;
	va_start(args, msg);


	if (Mylogger.policy == LOG_OUTPUT_POLICY_FILE){
		Mylogger.ptr_log = fopen("log/file.log", "a");
		if (Mylogger.ptr_log == NULL) {
			printf("Failed to allocate a file pointer, finishing prog");
			exit(1);
		}
		else {
			char current_time[] = now();
			char formatted_message[sizeof(current_time) + sizeof(msg) + 1];
			strcat(formatted_message, "%s %s", current_time, msg);
			fprintf(Mylogger.ptr_log, "%s", formatted_message);
		}
	}
}

char* now() {
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	char* now_[50];
	int r = snprintf(now_, sizeof(now_), "%d-%d-%d %d:%d:%d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	return now_;
}