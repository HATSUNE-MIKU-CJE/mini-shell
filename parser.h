#ifndef PARSER_H
#define PARSER_H

#define MAX_ARGS 64
#define MAX_CMDS 16

struct command
{
    char *args[MAX_ARGS];
    char *in_file;
    char *out_file;
    int append;
    int background;
};

int parser(char buffer[],struct command *cmds);



#endif