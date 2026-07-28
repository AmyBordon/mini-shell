#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/executor.h"
#include "../include/command.h"
#include <errno.h>
#include <string.h>
#include <fcntl.h>

void execute_commands(Command* head){
	Command *current = head;
	int prev_read = -1;
	while(current != NULL){
		if (current->argv[0]==NULL){
			current = current->next;
			continue;
		}
		int pipefd[2];
		if(current->next != NULL){
			if(pipe(pipefd) < 0){
				perror("pipe");
				exit(EXIT_FAILURE);
			}
		}
		pid_t pid=fork();

		if(pid<0){
			perror("fork");
			exit(EXIT_FAILURE);
		}if(pid==0){//in child
			if(prev_read != -1){
				if(dup2(prev_read, STDIN_FILENO) < 0){
					perror("dup2");
					exit(EXIT_FAILURE);
				}
			}
			if(current->next != NULL){
				if(dup2(pipefd[1], STDOUT_FILENO) < 0){
					perror("dup2");
					exit(EXIT_FAILURE);
				}
			}

			if(prev_read != -1)
				close(prev_read);
			if(current->next != NULL){
				close(pipefd[0]);
				close(pipefd[1]);
			}
			if(current->output_file != NULL){
				int flags = O_WRONLY | O_CREAT;
				if(current->append)
					flags |=O_APPEND;
				else flags |= O_TRUNC;
				int fd = open(current->output_file,
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
			if (current->input_file != NULL){
				int fd = open(current->input_file,
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
			execvp(current->argv[0], current->argv);
			fprintf(stderr, "%s: %s\n", current->argv[0],strerror(errno));
			exit(EXIT_FAILURE);
		}
	//in parent

		if(prev_read != -1)
			close(prev_read);
		if(current->next !=NULL){
			close(pipefd[1]);
			prev_read = pipefd[0];
		}else prev_read = -1;
		current = current->next;
	}

	current = head;
	while(current){
		wait(NULL);
		current = current->next;
	}
}
