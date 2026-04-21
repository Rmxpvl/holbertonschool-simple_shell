#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

char	*find_in_path(char *cmd, char **envp);
char	*get_path(char *line, char **envp, int *sfree);
int	execute(char *line, char **argv, char **envp, int cmd_num);

#endif /* SHELL_H */
