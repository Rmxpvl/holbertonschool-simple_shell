#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

char	*get_path(char *line, char **envp, int *sfree);
int	execute(char *line, char **argv, char **envp);

#endif /* SHELL_H */
