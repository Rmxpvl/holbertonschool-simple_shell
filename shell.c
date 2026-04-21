#include "shell.h"

/**
 * find_in_path - searches for a command in PATH directories
 * @cmd: the command name to search for
 * @envp: environment variables array
 *
 * Return: malloc'd full path if found, NULL otherwise
 */
char *find_in_path(char *cmd, char **envp)
{
	int i;
	char *path = NULL, *dup, *dir, *full;
	size_t len;

	for (i = 0; envp[i]; i++)
	{
		if (strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = envp[i] + 5;
			break;
		}
	}
	if (!path || path[0] == '\0')
		return (NULL);
	dup = strdup(path);
	if (!dup)
		return (NULL);
	dir = strtok(dup, ":");
	while (dir)
	{
		len = strlen(dir) + strlen(cmd) + 2;
		full = malloc(len);
		if (!full)
			break;
		sprintf(full, "%s/%s", dir, cmd);
		if (access(full, X_OK) == 0)
		{
			free(dup);
			return (full);
		}
		free(full);
		dir = strtok(NULL, ":");
	}
	free(dup);
	return (NULL);
}

/**
 * get_path - resolves full path for a command
 * @line: the command (absolute path or name)
 * @envp: environment variables
 * @sfree: set to 1 if returned path must be freed
 *
 * Return: full path or NULL if not found
 */
char *get_path(char *line, char **envp, int *sfree)
{
	*sfree = 0;
	if (strchr(line, '/'))
		return (line);
	*sfree = 1;
	return (find_in_path(line, envp));
}

/**
 * execute - forks and executes a command
 * @line: the command to run
 * @argv: shell argv for error messages
 * @envp: environment variables
 * @cmd_num: command number for error messages
 *
 * Return: exit status of the child process
 */
int execute(char *line, char **argv, char **envp, int cmd_num)
{
	char *path, *args[2];
	int sfree = 0, status = 0;
	pid_t pid;

	path = get_path(line, envp, &sfree);
	if (!path)
	{
		fprintf(stderr, "%s: %d: %s: not found\n", argv[0], cmd_num, line);
		return (127);
	}
	args[0] = path;
	args[1] = NULL;
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		if (sfree)
			free(path);
		return (1);
	}
	if (pid == 0)
	{
		execve(path, args, envp);
		fprintf(stderr, "%s: %d: %s: not found\n", argv[0], cmd_num, line);
		exit(127);
	}
	waitpid(pid, &status, 0);
	if (sfree)
		free(path);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

/**
 * main - entry point of the simple shell
 * @argc: argument count (unused)
 * @argv: argument vector
 * @envp: environment variables
 *
 * Return: last command exit status
 */
int main(int argc, char **argv, char **envp)
{
	char *line = NULL;
	char *newline;
	size_t len = 0;
	ssize_t nread;
	int cmd_num = 1, last_status = 0;

	(void)argc;
	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(1, "($) ", 4);
		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			if (isatty(STDIN_FILENO))
				write(1, "\n", 1);
			free(line);
			return (last_status);
		}
		newline = strchr(line, '\n');
		if (newline)
			*newline = '\0';
		if (line[0] == '\0')
			continue;
		if (strcmp(line, "exit") == 0)
		{
			free(line);
			return (last_status);
		}
		last_status = execute(line, argv, envp, cmd_num);
		cmd_num++;
	}
	free(line);
	return (last_status);
}
