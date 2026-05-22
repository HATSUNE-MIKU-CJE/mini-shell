#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"



int parser(char buffer[],struct command *cmds)
{
    char *token;
    int i=0;
    int j=0;
    const char *s = " \t";
    token   = strtok(buffer,s);
    while (token != NULL)
    {
        if (i>=4095)
        {break;}
        if (strcmp(token,">>")==0)
        {
            cmds[j].append   = 1;
            token = strtok(NULL,s);
            cmds[j].out_file = token;
            token = strtok(NULL,s);
            continue;
        }
        if (strcmp(token,">")==0)
        {
            cmds[j].append   = 0;
            token = strtok(NULL,s);
            cmds[j].out_file = token;
            token = strtok(NULL,s);
            continue;
        }
        if (strcmp(token,"<")==0)
        {
            token = strtok(NULL,s);
            cmds[j].in_file = token;
            token = strtok(NULL,s);
            continue;
        }
        if (strcmp(token,"|")==0)
        {
            cmds[j].args[i] = NULL;
            i=0;
            j++;
            token = strtok(NULL,s);
            continue;
        }
        cmds[j].args[i] = token;
        token   = strtok(NULL,s);
        i++;
    }
    cmds[j].args[i] = NULL;
    return j+1;
}

