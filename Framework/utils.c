#include "logger.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// CR: Macro conventions is MAX_INPUT, but please me more explicit MAX_USER_INPUT_LENGTH
#define max_input 100

// CR: this function is not handling error flow
void get_string_user_input(char* input) {
	fgets(input, max_input, stdin);
	size_t input_size = strlen(input);
	if (input_size > 0 && input[input_size - 1] == '\n') {
		input[input_size - 1] = '\0';
	}
	// CR: no need for return here
	return;
}

// CR: No need, please just use __NOW__
void now(char* datetime) {
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	int r = snprintf(datetime, sizeof(datetime), "%d-%d-%d %d:%d:%d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	return;
}

// CR: Hmm not sure what benefit this function gives you, using __DATE__ should just be enough and ondon't bother with this complicated code
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

// CR: get_policy_level
// CR: This is not the right place to put such a function. utils.c you almost not contain anything, and everything should go to the appropriate module.
// CR: This is not what I wanted from the exercise, the application just needs a loop that receives commands, and when it gets set-logger-config you provide a policy level.
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

// CR: Move to new module called app or command_prompt or something of the sort, not util
// CR: this loop logic should be something like
/*
* while (TRUE) {
* 1. get user input
* 2. switch (with ifs) for the correct command
* 3. call a handle_command_... for each command
* 4. each command should parse more parms if needed (for example set-logger-config has two more ints)
* 5. execute command logic, so for set-logger-config we need a function logger__update_config(output_policy, level).
* }
*/
void getLoggerConfigFromUserInput() {
	// CR: prefer while(TRUE)
	while (1)
	{
		printf("Please enter one of the following command: \n");
		// CR: the usage should be something like:
		/* Please enter one of the following command:
		*      quit - quits the application
		*      set-log-config LOG_POLICY_OUTPUT LOG_POLICY_LEVEL
		             LOG_POLICY_OUTPUT can be a bitwise compbination of LOG_OUTPUT_POLICY_NONE LOG_OUTPUT_POLICY_FILE LOG_OUTPUT_POLICY_STDOUT
					 LOG_POLICY_LEVEL can be a number of POLICY_LEVEL
				     for example, `set-log-config 3, 1` means to update the log to write to both stdout and file for info level.
		*/
		// CR: You should receive a number for the log policy and just parse to enum, it will be much simpler
		printf("1. quit\n2.(LOG_OUTPUT_POLICY_NONE or LOG_OUTPUT_POLICY_FILE or LOG_OUTPUT_POLICY_STDOUT)\n");


		char user_input[max_input];
		get_string_user_input(user_input);
		POLICY_LEVEL level;

		if (strcmp(user_input, "quit") == 0) {
			printf("\n Exiting the program\n");
			exit(0);
		}
		else {// CR: remove this extra new line

			if (strcmp(user_input, "LOG_OUTPUT_POLICY_NONE") == 0) {
				// do nothing the policy is already in None Mode
				break;
		}
			else if (strcmp(user_input, "LOG_OUTPUT_POLICY_FILE") == 0) {
				// CR: this is duplicate call, you should avoid that.
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