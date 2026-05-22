#ifndef READLINE_H
#define READLINE_H

#include <stdio.h>

int readline(char *buffer,size_t size);
void history_add(const char *line);
int history_size(void);
char *history_get(int index);

#endif
