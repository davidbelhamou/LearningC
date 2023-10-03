
#include"logger.h"
#include <time.h>
#include <errno.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

#define max_log 1024

// instanciate gloabal static logger
static Logger Mylogger = { LOG_OUTPUT_POLICY_NONE , NULL };


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

void logger_log(char msg[], ...) {

	// Initializing argument to the
	// list pointer
	va_list args;
	va_start(args, msg);

	// The first argument should alway be the format
	char *format = va_arg(args, char*);

	//printf("%s", va_arg(args, char*));
	//printf("%s", va_arg(args, char*));
	//printf("%s", va_arg(args, char*));
	//printf("%s", va_arg(args, char*));
		
	if (Mylogger.policy == LOG_OUTPUT_POLICY_STDOUT) {

		vprintf(format, args);
	}
	else if (Mylogger.policy == LOG_OUTPUT_POLICY_FILE) {
		Mylogger.ptr_log = fopen("log/file.log", "a");

		if (Mylogger.ptr_log != NULL) {

			vfprintf(Mylogger.ptr_log, format, args);
		}
		
	}
	va_end(args);
}