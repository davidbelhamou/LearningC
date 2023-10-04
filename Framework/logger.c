
#include"logger.h"
#include <time.h>
#include <errno.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

#define max_log 1024
#define file "log/file.log"

void print_stdout(char format[], va_list myList);
void print_stdfile(FILE* ptr_log, char format[], va_list myList);

// instanciate gloabal static logger
static Logger Mylogger = { LOG_OUTPUT_POLICY_NONE , NULL , LOG_LEVEL_INFO};

const char* getPolicyLevelName(POLICY_LEVEL level) {
	switch (level) {
	case LOG_LEVEL_DEBUG: return "DEBUG";
	case LOG_LEVEL_INFO: return "INFO";
	case LOG_LEVEL_WARNING: return "WARNING";
	case LOG_LEVEL_ERROR: return "ERROR";
	case LOG_LEVEL_CRITICAL: return "CRITICAL";
	default: return "Unknown";
	}
}


void logger_init(LOG_OUTPUT_POLICY new_policy, POLICY_LEVEL level) {
	// ovveride default policy and level
	Mylogger.policy = new_policy;
	Mylogger.level = level;
	
	// if the policy is file or both stdout and file then create the file itself and just close it
	if (Mylogger.policy == LOG_OUTPUT_POLICY_FILE || Mylogger.policy == LOG_OUTPUT_POLICY_BOTH){
		Mylogger.ptr_log = fopen(file, "a");
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

void logger_log(char msg[], POLICY_LEVEL level,...) {

	// Initializing argument to the list pointer
	va_list args;
	va_start(args, level);

	// Get The first argument (should alway be the return format)
	char *format = va_arg(args, char*);

	// IF level send i >= of the logger then print
	if (level >= Mylogger.level) {

		if (Mylogger.policy == LOG_OUTPUT_POLICY_STDOUT) {

			print_stdout(format, args);
		}

		else if (Mylogger.policy == LOG_OUTPUT_POLICY_FILE) {

			print_stdfile(Mylogger.ptr_log, format, args);
		}

		else if (Mylogger.policy == LOG_OUTPUT_POLICY_BOTH) {

			print_stdout(format, args);
			print_stdfile(Mylogger.ptr_log, format, args);
		}
	}

	va_end(args);
}

void print_stdout(char format[], va_list myList) {
	vprintf(format, myList);
}

void print_stdfile(FILE* ptr_log, char format[], va_list myList) {
	ptr_log = fopen(file, "a");

	if (Mylogger.ptr_log != NULL) {

		vfprintf(ptr_log, format, myList);
	}
}