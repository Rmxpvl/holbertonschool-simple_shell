#ifndef SIMPLE_SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

int	run_command(char *line, char **argv, int cmd_num);

#endif /* SHELL_H */
