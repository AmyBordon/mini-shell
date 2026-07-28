#ifndef COMMAND_H
#define COMMAND_H
#define MAX_ARGS 64
typedef struct Command{
    char *argv[MAX_ARGS];

    char *input_file;

    char *output_file;

    int append;

    struct Command* next;

} Command;

#endif
