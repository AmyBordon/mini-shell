#include <string.h>
#include "../include/parser.h"
#include <stdlib.h>
#include "../include/command.h"

Command* create_command(void){
	Command* cmd = malloc(sizeof(Command));

	if(cmd==NULL)
		return NULL;

    	cmd->input_file = NULL;
    	cmd->output_file = NULL;
    	cmd->append = 0;
    	cmd->next = NULL;

    	for (int i = 0; i < MAX_ARGS; i++)
        	cmd->argv[i] = NULL;
	return cmd;
}

void free_commands(Command *head)
{
    while (head != NULL)
    {
        Command *next = head->next;
        free(head);
        head = next;
    }
}

static void  parse_single_command(char *line, Command *cmd)
{
    int argc = 0;

    char *saveptr;
    char *token = strtok_r(line, " ", &saveptr);
    
    while (token != NULL)
    {
        if (strcmp(token, "<") == 0)
        {
            token = strtok_r(NULL, " ", &saveptr);

            if (token != NULL)
                cmd->input_file = token;
        }
        else if (strcmp(token, ">") == 0)
        {
            token = strtok_r(NULL, " ", &saveptr);

            if (token != NULL)
            {
                cmd->output_file = token;
                cmd->append = 0;
            }
        }
        else if (strcmp(token, ">>") == 0)
        {
            token = strtok_r(NULL, " ", &saveptr);

            if (token != NULL)
            {
                cmd->output_file = token;
                cmd->append = 1;
            }
        }
        else
        {
            cmd->argv[argc++] = token;
        }

        token = strtok_r(NULL, " ", &saveptr);
    }

    cmd->argv[argc] = NULL;

    
}

Command* parse_line(char* line){
	//assume there are no leadning spaces!
	Command* head = NULL;
	Command* tail = NULL;
	char* saveptr;
	char* token = strtok_r(line, "|\n", &saveptr);

	while(token){
		//token[strlen(token)]=NULL;
		Command* cmd = create_command();
		if (cmd == NULL){
    			free_commands(head);
    			return NULL;

		}
		if (head == NULL){
    			head = cmd;
    			tail = cmd;
		}else{
    			tail->next = cmd;
    			tail = cmd;
		}		
		parse_single_command(token, cmd);
		token = strtok_r(NULL, "|\n", &saveptr);
	}

	return head;
}
