#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include "readline.h"

#define HISTORY_MAX 128

static char *history[HISTORY_MAX];
static int history_count = 0;

int readline(char *buffer, size_t size)
{
    printf("mini-shell>");
    fflush(stdout);
    if (fgets(buffer, size, stdin) == NULL)
    {
        fprintf(stderr, "fgets failed\n");
        return -1;
    }
    size_t len = strlen(buffer);
    if (len>0 && buffer[len-1] == '\n')
    {
        buffer[len-1] = '\0';
    }
    history_add(buffer);
    return 0;
}

void history_add(const char *line)
{
    if (history_count < HISTORY_MAX)
    {
        history[history_count++]=strdup(line);
    }
}

int history_size(void)
{
    return history_count;
}

char *history_get(int index)
{
    if (index < 0 || index >= history_count)
    {return NULL;}
    return history[index];
}