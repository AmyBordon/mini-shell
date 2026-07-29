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
	printf(COLOR_PURPLE "🌸Mini-Shell🌸\n" COLOR_RESET);
	printf(COLOR_PURPLE "Note: separate operators with spaces (|, <, >, >>).\n" COLOR_RESET);
    	while(1){
	printf(COLOR_PINK "🌸>" COLOR_RESET);
        if (getline(&line, &len, stdin) == -1)
        {
                break;
        }
        line[strcspn(line, "\n")] = '\0';
        
	Command *commands = parse_line(line);

	if (commands == NULL)
    		continue;

	if (!execute_builtin(commands))
    		execute_commands(commands);

	free_commands(commands);
    }
    free(line);
}
   
