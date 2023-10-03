#include<stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include"..\\Framework\logger.h"
#include"..\\Framework\utils.h"
#define max_input 100

int main() {
	while (1)
	{
		printf("Please enter one of the following command: \n");
		printf("1. quit\n2.(LOG_OUTPUT_POLICY_NONE or LOG_OUTPUT_POLICY_FILE or LOG_OUTPUT_POLICY_STDOUT)\n");
		

		char user_input[max_input];
		get_string_user_input(user_input);

		if (strcmp(user_input, "quit") == 0) {
			printf("\n Exiting the program\n");
			exit(0);
		}
		else if (strcmp(user_input, "LOG_OUTPUT_POLICY_NONE") == 0) {
			// do nothing the policy is already in None Mode
			break;
		}
		else if (strcmp(user_input, "LOG_OUTPUT_POLICY_FILE") == 0) {
			logger_init(LOG_OUTPUT_POLICY_FILE);
			break;
		}
		else if (strcmp(user_input, "LOG_OUTPUT_POLICY_STDOUT") == 0) {
			logger_init(LOG_OUTPUT_POLICY_STDOUT);
			break;
		}
		else if ((strcmp(user_input, "LOG_OUTPUT_POLICY_STDOUT | LOG_OUTPUT_POLICY_FILE") == 0) || (strcmp(user_input,"LOG_OUTPUT_POLICY_FILE | LOG_OUTPUT_POLICY_STDOUT") == 0)){
			logger_init(LOG_OUTPUT_POLICY_FILE || LOG_OUTPUT_POLICY_STDOUT);
			break;
		}
		else
		{
			printf("You did not enter a valid input");
			continue;
		}
	
	}
	LOG("the function failed");
}