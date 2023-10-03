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

void format_date(char* new_format, char* current) {
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
	char *final_day = day < 9 ? "%02d/" : "%2d/";
	char *final_month = month < 9 ? "0%02d/" : "%2d/";
	char final_format[50] = "";
	strcat(final_format, final_day);
	strcat(final_format, final_month);
	strcat(final_format, "%d");
	sprintf(new_format, final_format, day, month, year);
	return;

}