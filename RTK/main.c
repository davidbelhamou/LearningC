#include<stdio.h>
#include <stddef.h>
#include <stdlib.h>
// CR: no relative includes, you should do #include "logger.h" and add the framework directory as include path. It's explained in the video.
#include"..\\Framework\logger.h"
#include"..\\Framework\utils.h"
#define max_input 100


// General notes:
// 1. You are mixing two different conventions for names. this_is_one and thisIsTwo. For functions_we_want_this_one, always.
int main() {
	// CR: The main logic should just be something like start_application_loop, not specific for logger since this this is just the first part.
	getLoggerConfigFromUserInput();
	LOG("this is a message info\n", LOG_LEVEL_INFO);
	LOG("this is a message warning\n", LOG_LEVEL_WARNING);
	LOG("this is a message error\n", LOG_LEVEL_ERROR);
	LOG("this is a message critical\n", LOG_LEVEL_CRITICAL);
}