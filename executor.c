#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "parser.h"

extern volatile pid_t foreground_pids[MAX_CMDS];
extern volatile int fg_count;

int executor(struct command *cmd,int n)
{
    int pipes[MAX_CMDS-1][2];
    for (int i=0;i<n-1;i++)
    {
        if (pipe(pipes[i])==-1)
        {
            perror("pipe failed");                
            return -1;
        }
    }

    pid_t pid;
    pid_t pids[MAX_CMDS];
    int status;
    int child_num;
    for (int i=0;i<n;i++)
    {
        pid = fork();
        if (pid == 0)
        {
            child_num = i;
            break;
        }
        pids[i] = pid;
    }
    if (pid < 0)
    {
        perror("fork failed");
        return -1;
    }
    else if (pid == 0)
    {
        if (child_num>0)
        {
            dup2(pipes[child_num-1][0],STDIN_FILENO);
        }
        if (child_num < n-1)
        {
            dup2(pipes[child_num][1],STDOUT_FILENO);
        }
        for (int j=0;j<n-1;j++)
        {
            close(pipes[j][0]);
            close(pipes[j][1]);
        }
        if (cmd[child_num].in_file)
        {
            int fd = open(cmd[child_num].in_file,O_RDONLY);
            if (fd<0) {
                perror("open failed");
                _exit(1);
            }
            dup2(fd,STDIN_FILENO);
            close(fd);
        }
        if (cmd[child_num].out_file)
        {
            int fd=-1;
            if (cmd[child_num].append == 1)
            {
                fd = open(cmd[child_num].out_file,O_WRONLY | O_CREAT | O_APPEND, 0644);
            }
            else if (cmd[child_num].append == 0)
            {
                fd = open(cmd[child_num].out_file,O_WRONLY | O_CREAT | O_TRUNC, 0644);
            }
            if (fd<0) {
                perror("open failed");
                _exit(1);
            }
            dup2(fd,STDOUT_FILENO);
            close(fd);
        }
        execvp(cmd[child_num].args[0],cmd[child_num].args);
        perror(cmd[child_num].args[0]);
        _exit(1);
    }
    else
    {
        for (int i=0;i<n-1;i++)
        {
            close(pipes[i][0]);
            close(pipes[i][1]);
        }
        for (int k=0;k<n;k++)
        {
            if (cmd[k].background==1)
            {
                return 0;
            }
        }
        for (int l=0;l<n;l++)
        {
            foreground_pids[l] = pids[l];
        }
        fg_count = n;
        for (int j=0;j<n;j++)
        {
            waitpid(-1,&status,0);
        }
        fg_count = 0;
    }
    return 0;
} 


