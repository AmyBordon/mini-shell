#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/executor.h"
#include "../include/command.h"
#include <errno.h>
#include <string.h>
#include <fcntl.h>

void execute_command(Command* cmd){
	if (cmd->argv[0]==NULL)
		return;
	pid_t pid=fork();

	if(pid<0)
	{
		perror("Error creating process!");
		exit(EXIT_FAILURE);
	}

	if(pid==0){//in child
		if(cmd->output_file != NULL){
			int flags = O_WRONLY | O_CREAT;
			if(cmd->append)
				flags |=O_APPEND;
			else flags |= O_TRUNC;
			int fd = open(cmd->output_file,
			flags, 0644);
			if(fd < 0){
				perror("open");
				exit(EXIT_FAILURE);

			}
			if(dup2(fd, STDOUT_FILENO) < 0){
				perror("dup2");
				close(fd);
				exit(EXIT_FAILURE);
			}

			close(fd);

		}
		if (cmd->input_file != NULL){
			int fd = open(cmd->input_file,
				       	O_RDONLY, 0644);
			if(fd<0){
				perror("open");
				exit(EXIT_FAILURE);
			}
			if(dup2(fd, STDIN_FILENO) < 0){
				perror("dup2");
				close(fd);
				exit(EXIT_FAILURE);
			}
			close(fd);
			
		}
		execvp(cmd->argv[0], cmd->argv);
		fprintf(stderr, "%s: %s\n", cmd->argv[0],strerror(errno));
		exit(EXIT_FAILURE);
	}
	//in parent
	waitpid(pid, NULL, 0);
}
