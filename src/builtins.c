#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "../include/builtins.h"

#define COLOR_PURPLE "\033[38;5;141m"

#define COLOR_RESET  "\033[0m"
int execute_builtin(Command* cmd)
{
    if (cmd->argv[0] == NULL)
        return 1;

    if (strcmp(cmd->argv[0], "exit") == 0)
    {
        printf(COLOR_PURPLE "Goodbye!\n" COLOR_RESET);
        exit(0);
    }

    if(strcmp(cmd->argv[0], "cd")==0){
	if (cmd->argv[1] == NULL)
		fprintf(stderr, "cd: missing argument\n");
	else if (chdir(cmd->argv[1]) != 0)
			perror("cd");

	return 1;
    }

    return 0;
}
