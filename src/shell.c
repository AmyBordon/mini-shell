#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/shell.h"
#include "../include/parser.h"
#include "../include/executor.h"

void shell_loop(void)
{
    char* line = NULL;
    size_t len=100;
    while(1){
        printf(">");
        if (getline(&line, &len, stdin) == -1)
        {
                break;
        }
        line[strcspn(line, "\n")] = '\0';
        if(strcmp("exit", line)==0){
                //printf("Goodbye!\n");
                //break;
		if (strcmp(line, "exit") == 0)
		{
    			printf("Goodbye!\n");
    			free(line);
    			exit(0);
		}
	}
        char *argv[64];

	parse_command(line, argv);
	execute_command(argv);
    }
    free(line);
}
   
