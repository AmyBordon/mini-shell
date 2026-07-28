#include <string.h>
#include "../include/parser.h"

int parse_command(char *line, Command *cmd)
{
    int argc = 0;

    cmd->input_file = NULL;
    cmd->output_file = NULL;
    cmd->append = 0;

    char *token = strtok(line, " ");

    while (token != NULL)
    {
        if (strcmp(token, "<") == 0)
        {
            token = strtok(NULL, " ");

            if (token != NULL)
                cmd->input_file = token;
        }
        else if (strcmp(token, ">") == 0)
        {
            token = strtok(NULL, " ");

            if (token != NULL)
            {
                cmd->output_file = token;
                cmd->append = 0;
            }
        }
        else if (strcmp(token, ">>") == 0)
        {
            token = strtok(NULL, " ");

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

        token = strtok(NULL, " ");
    }

    cmd->argv[argc] = NULL;

    return argc;
}
