#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

char *_getenv(const char *name);
char *find_in_path(char *cmd);
int fork_execute(char *path, char **args, char *prog_name, int line_num);
int execute(char **args, char *prog_name, int line_num);
int run_shell(char *prog_name);

#endif /* SHELL_H */
