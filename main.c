#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "readline.h"
#include "parser.h"
#include "builtin.h"
#include "executor.h"



int main()
{
    char instruction[4096]={0};
    size_t size=sizeof (instruction);
    struct command cmds[MAX_CMDS] = {0};
    int n = 0;

    while (1) 
    {
        readline(instruction,size);
        n = parser(instruction,cmds);
        if (n == 1 && builtin(cmds[0].args[0],cmds[0].args)==0)
        {
            continue;
        }
        else if (executor(cmds,n)==0)
        {
            continue;
        }
        else
        {
            continue;
        }

    }
    return 0;
}

