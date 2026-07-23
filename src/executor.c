#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/executor.h"

void execute_command(char *argv[]){
	if (argv[0]==NULL)
		return;
	pid_t pid=fork();

	if(pid<0)
	{
		perror("Error creating process!");
		exit(1);
	}

	if(pid==0){//in child
		execvp(argv[0], argv);
		perror("execvp");
		exit(1);
	}
	//in parent
	waitpid(pid, NULL, 0);
}
