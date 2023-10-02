#include<stdio.h>
#include"..\\Framework\logger.h"
#include<sys/stat.h>
#include<time.h>

int main() {
	//while (1)
	//{
	//	
	//	char input[50];
	//	printf("Please enter one of the following command: \n");
	//	printf("1. quit\n2.(LOG_OUTPUT_POLICY_NONE or LOG_OUTPUT_POLICY_FILE or LOG_OUTPUT_POLICY_STDOUT)");
	//	if (strcmp(input, 'quit') == 0) {
	//		exit(0);
	//	}
	//	else if (strcmp(input, "LOG_OUTPUT_POLICY_NONE")) {
	//		// do nothing the policy is already in None Mode
	//		break;
	//	}
	//	else if (strcmp(input, "LOG_OUTPUT_POLICY_FILE")) {
	//		logger_init(LOG_OUTPUT_POLICY_FILE);
	//		break;
	//	}
	//	else if (strcmp(input, "LOG_OUTPUT_POLICY_STDOUT")) {
	//		logger_init(LOG_OUTPUT_POLICY_STDOUT);
	//		break;
	//	}
	//	else if ((strcmp(input, "LOG_OUTPUT_POLICY_STDOUT | LOG_OUTPUT_POLICY_FILE")) || (strcmp(input ,"LOG_OUTPUT_POLICY_FILE | LOG_OUTPUT_POLICY_STDOUT"))){
	//		logger_init(LOG_OUTPUT_POLICY_FILE || LOG_OUTPUT_POLICY_STDOUT);
	//		break;
	//	}
	//	else
	//	{
	//		printf("You did not enter a valid inut");
	//		continue;
	//	}
	//
	//}
	now();
}