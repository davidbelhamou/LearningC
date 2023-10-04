#include "logger.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define max_input 100

void get_string_user_input(char* input) {
	fgets(input, max_input, stdin);
	size_t input_size = strlen(input);
	if (input_size > 0 && input[input_size - 1] == '\n') {
		input[input_size - 1] = '\0';
	}
	return;
}


void now(char* datetime) {
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	int r = snprintf(datetime, sizeof(datetime), "%d-%d-%d %d:%d:%d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	return;
}

char*  format_date(char* current) {
	const char* months[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
	char cur_month[4];
	int day, year, month;

	// Check if the number of filled argument is not 3
	if (sscanf(current, "%s %d %d", cur_month, &day, &year) != 3) {
		printf("Failed filling enought argument");
		exit(1);
	}
	for (month = 1; month < sizeof(months); month++) {
		if (strcmp(cur_month, months[month]) == 0) {
			break;
		}
		month++;
	}
	// if number is less than 10 then ad a 0 before printing it
	char *final_day = day <= 9 ? "%02d/" : "%2d/";
	char *final_month = month <= 9 ? "%02d/" : "%2d/";

	// final format is the formt of the output we will concat to it each time another string 
	char final_format[50] = "";
	strcat(final_format, final_day);
	strcat(final_format, final_month);
	strcat(final_format, "%d");
	char* buffer = (char *)malloc(50);
	snprintf(buffer, 50, final_format, day, month, year);
	return buffer;

}

POLICY_LEVEL getPolicyLevel() {
	char input[50];
	while (1) {
		printf("Enter the desired log level (DEBUG, INFO, WARNING, ERROR, CRITICAL): ");
		scanf_s("%s", input, 50);

		if (strcmp(input, "DEBUG") == 0) {
			return LOG_LEVEL_DEBUG;
		}
		else if (strcmp(input, "INFO") == 0) {
			return LOG_LEVEL_INFO;
		}
		else if (strcmp(input, "WARNING") == 0) {
			return LOG_LEVEL_WARNING;
		}
		else if (strcmp(input, "ERROR") == 0) {
			return LOG_LEVEL_ERROR;
		}
		else if (strcmp(input, "CRITICAL") == 0) {
			return LOG_LEVEL_CRITICAL;
		}
		else {
			printf("Invalid input, please try again.\n");
		}
	}
}

void getLoggerConfigFromUserInput() {
	while (1)
	{
		printf("Please enter one of the following command: \n");
		printf("1. quit\n2.(LOG_OUTPUT_POLICY_NONE or LOG_OUTPUT_POLICY_FILE or LOG_OUTPUT_POLICY_STDOUT)\n");


		char user_input[max_input];
		get_string_user_input(user_input);
		POLICY_LEVEL level;

		if (strcmp(user_input, "quit") == 0) {
			printf("\n Exiting the program\n");
			exit(0);
		}
		else {

			if (strcmp(user_input, "LOG_OUTPUT_POLICY_NONE") == 0) {
				// do nothing the policy is already in None Mode
				break;
		}
			else if (strcmp(user_input, "LOG_OUTPUT_POLICY_FILE") == 0) {
				level = getPolicyLevel();
				logger_init(LOG_OUTPUT_POLICY_FILE, level);
				break;
				}
			else if (strcmp(user_input, "LOG_OUTPUT_POLICY_STDOUT") == 0) {
					level = getPolicyLevel();
					logger_init(LOG_OUTPUT_POLICY_STDOUT, level);
					break;
					}
			else if ((strcmp(user_input, "LOG_OUTPUT_POLICY_STDOUT | LOG_OUTPUT_POLICY_FILE") == 0) || (strcmp(user_input, "LOG_OUTPUT_POLICY_FILE | LOG_OUTPUT_POLICY_STDOUT") == 0)) {
						level = getPolicyLevel();
						logger_init(LOG_OUTPUT_POLICY_BOTH, level);
						break;
						}
			else
			{
				printf("You did not enter a valid input");
				continue;
				}
		}

	}
}