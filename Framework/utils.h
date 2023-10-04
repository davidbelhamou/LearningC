#pragma once
#include "logger.h"


void get_string_user_input(char* input);
char* now(char* datetime);
char* format_date(char* current);
POLICY_LEVEL getPolicyLevel();
void getLoggerConfigFromUserInput();