#include <string.h>
#include <stdlib.h>
#include "../include/parser.h"

int parse_command(char *line, char *argv[]){
	int argc=0;
	char* token=strtok(line, " ");
	while(token){
		argv[argc]=token;
		argc++;
		token = strtok(NULL, " ");
	}
	argv[argc]=NULL;
	return argc;
}
