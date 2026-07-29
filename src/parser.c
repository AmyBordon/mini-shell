#include <string.h>
#include "../include/parser.h"
#include <stdlib.h>
#include <stdio.h>
#include "../include/command.h"

static char *next_token(char **line)
{
    while (**line == ' ')
        (*line)++;

    if (**line == '\0')
        return NULL;

    /* Operators */

    if (**line == '|')
    {
        (*line)++;
        return "|";
    }

    if (**line == '<')
    {
        (*line)++;
        return "<";
    }

    if (**line == '>')
    {
        if ((*line)[1] == '>')
        {
            (*line) += 2;
            return ">>";
        }

        (*line)++;
        return ">";
    }

    /* Quoted string */

    if (**line == '"' || **line == '\'')
    {
        char quote = **line;
        char *start = ++(*line);

        while (**line && **line != quote)
            (*line)++;

        if (**line == quote)
        {
            **line = '\0';
            (*line)++;
        }

        return start;
    }

    /* Normal word */

    char *start = *line;

    while (**line &&
           **line != ' ' &&
           **line != '|' &&
           **line != '<' &&
           **line != '>')
    {
        (*line)++;
    }

    if (**line != '\0'){
	    char c = **line;
	    **line = '\0';
	    if (c == ' ')
		    (*line)++;
    }
    return start;
}

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

/*static void  parse_single_command(char *line, Command *cmd)
{
    int argc = 0;

    char *cursor = line;
    char *token = next_token(&cursor);  

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

        token = next_token(&cursor);
    }

    cmd->argv[argc] = NULL;

    
}*/

Command *parse_line(char *line)
{
    char *cursor = line;
    char *token;

    Command *head = create_command();
    Command *current = head;

    int argc = 0;

    while ((token = next_token(&cursor)) != NULL)
    {
        if (strcmp(token, "|") == 0)
        {
            current->argv[argc] = NULL;

            current->next = create_command();
            current = current->next;

            argc = 0;
        }
        else if (strcmp(token, "<") == 0)
        {
            current->input_file = next_token(&cursor);
        }
        else if (strcmp(token, ">") == 0)
        {
            current->output_file = next_token(&cursor);
            current->append = 0;
        }
        else if (strcmp(token, ">>") == 0)
        {
            current->output_file = next_token(&cursor);
            current->append = 1;
        }
        else
        {
            current->argv[argc++] = token;
	
	    if (argc >= MAX_ARGS - 1){    
		    fprintf(stderr, "Too many arguments\n");    
		    free_commands(head);
		    return NULL;
	    }        
	}    
    }

    current->argv[argc] = NULL;

    return head;
}
