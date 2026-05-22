#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "readline.h"

int builtin(char *cmd_name,char **args)
{
    if (strcmp(cmd_name,"cd")==0)
    {
        args[1] ? chdir(args[1]) : chdir(getenv("HOME"));
        return 0;
    }
    else if (strcmp(cmd_name,"exit")==0) 
    {
        int code = args[1] ? atoi(args[1]) : 0;
        exit(code);
        return 0;
    }
    else if (strcmp(cmd_name,"pwd")==0)
    {
        char buf[4096];
        getcwd(buf,sizeof(buf));
        printf("%s\n",buf);
        return 0;
    }
    else if (strcmp(cmd_name,"export")==0)
    {
        char *eq    = {0};
        char *name  = {0};
        char *value = {0};
        for (int i=1;args[i] != NULL;i++)
        {
            eq = strchr(args[i],'=');
            if (eq == NULL) continue;
            *eq = '\0';
            name = args[i];
            value = eq+1; 
            
            setenv(name,value,1);
        }
        return 0;
    }
    else if (strcmp(cmd_name,"history")==0)
    {
        int n = history_size();
        if (args[1] != NULL)
        {n = atoi(args[1]);}
        int start = history_size() - n;
        if (start <0 )
        {start=0;}

        for (int i= start;i<history_size();i++)
        {
            printf("%d  %s\n",i+1,history_get(i));
        }
        return 0;
    }
    else 
    {
        return -1;
    }
}
