#ifndef _COMMANDS_ANALYZER_H_
#define _COMMANDS_ANALYZER_H_

#include "command_bind_to_flag.h"

// 一个命令(command_t)的格式应该是: Command Args



char *getCommand();
char *getArgs();


bool checkCommand_t();

int convertCommandToFlag();




#endif // _COMMANDS_ANALYZER_H_
