#ifndef COMMAND_H
#define COMMAND_H

typedef struct
{
    char *argv[64];

    char *input_file;

    char *output_file;

    int append;

} Command;

#endif
