#ifndef PARSER_H
#define PARSER_H
#include "command.h"

//static void parse_single_command(char *line, Command* cmd);
Command *create_command(void);
void free_commands(Command* head);
Command* parse_line(char* line);
#endif
