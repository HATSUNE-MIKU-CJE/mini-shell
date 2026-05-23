#define _GNU_SOURCE

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "readline.h"
#include "parser.h"
#include "builtin.h"
#include "executor.h"


volatile pid_t foreground_pids[MAX_CMDS];
volatile int fg_count = 0;

void sigchld_handler(int sig)
{
    while (waitpid(-1,NULL,WNOHANG)>0)
    {;}
}

void sigint_handler(int sig)
{
    for (int i=0;i<fg_count;i++)
    {
        kill(foreground_pids[i],SIGINT);
    }
}

int main()
{
    struct sigaction sa;
    struct sigaction sb;
    sa.sa_handler = sigchld_handler;
    sb.sa_handler = sigint_handler;
    sa.sa_flags = SA_RESTART;
    sb.sa_flags = SA_RESTART;
    sigemptyset(&sa.sa_mask);
    sigemptyset(&sb.sa_mask);
    sigaction(SIGCHLD,&sa,NULL);
    sigaction(SIGINT ,&sb,NULL);
    
    char instruction[4096]={0};
    size_t size=sizeof (instruction);
    struct command cmds[MAX_CMDS] = {0};
    int n = 0;

    while (1) 
    {
        memset(cmds, 0, sizeof(cmds));
        readline(instruction,size);
        n = parser(instruction,cmds);
        if (n == 0 || cmds[0].args[0]==NULL) 
        {
            continue;
        }
        else if (n == 1 && builtin(cmds[0].args[0],cmds[0].args)==0)
        {
            continue;
        }
        else if (executor(cmds,n)==0)
        {
            continue;
        }
        else
        {
            fprintf(stderr, "%s: command not found\n", cmds[0].args[0]);
        }

    }
    return 0;
}

