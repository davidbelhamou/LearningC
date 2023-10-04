#include<stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include"..\\Framework\logger.h"
#include"..\\Framework\utils.h"
#define max_input 100

int main() {
	getLevelConfig();
	LOG("this is a message info\n", LOG_LEVEL_INFO);
	LOG("this is a message warning\n", LOG_LEVEL_WARNING);
	LOG("this is a message error\n", LOG_LEVEL_ERROR);
	LOG("this is a message critical\n", LOG_LEVEL_CRITICAL);
}