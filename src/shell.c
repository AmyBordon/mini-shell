#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/shell.h"
#include "../include/parser.h"
#include "../include/executor.h"
#include "../include/builtins.h"
#include "../include/command.h"
#define COLOR_PURPLE "\033[38;5;141m"
#define COLOR_RESET "\033[0m"
#define COLOR_PINK  "\033[38;5;169m"

void shell_loop(void)
{
    char* line = NULL;
    size_t len=100;
    while(1){
	printf(COLOR_PINK "🌸>" COLOR_RESET);
        if (getline(&line, &len, stdin) == -1)
        {
                break;
        }
        line[strcspn(line, "\n")] = '\0';
        
	Command cmd;

	parse_command(line, &cmd);
	if(execute_builtin(&cmd))
		continue;
	execute_command(&cmd);
    }
    free(line);
}
   
