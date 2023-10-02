
#include<stdio.h>
#include"logger.h"
#include <time.h>
#include <errno.h>

static LOG_OUTPUT_POLICY p = LOG_OUTPUT_POLICY_NONE;
static FILE* ptr_log = NULL;

void logger_init(LOG_OUTPUT_POLICY new_policy) {
	// instanciate policy
	p = new_policy;
	
	// if the policy is file then cerate the file itself and just close it
	if (p == LOG_OUTPUT_POLICY_FILE){
		FILE * ptr_log;
		ptr_log = fopen("log/file.log", "a");
		if (ptr_log == NULL) {
			printf("Failed to allocate a file pointer, finishing prog");
			exit(1);
		}
		else
		{	
			fclose(ptr_log);
		}
	}
}

void logger(char msg[]) {
	if (p == LOG_OUTPUT_POLICY_FILE){
		ptr_log = fopen("log/file.log", "a");
		if (ptr_log == NULL) {
			printf("Failed to allocate a file pointer, finishing prog");
			exit(1);
		}
		else {
			time_t t = time(NULL);
			struct tm tm = *localtime(&t);
			//fprintf("")
		}
	}
}

char* now() {
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	char* now_[50];
	int r = snprintf(now_, sizeof(now_), "%d-%d-%d %d:%d:%d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	printf("now = %s", now_);
}