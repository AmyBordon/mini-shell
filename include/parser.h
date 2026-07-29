#ifndef PARSER_H
#define PARSER_H
#include "command.h"

//char* next_token(char** line);

Command *create_command(void);
void free_commands(Command* head);
Command* parse_line(char* line);

#endif
