#include "shell.h"

/**
 * get_path - validates command path
 * @line: the command (must be an absolute path)
 * @envp: environment variables (unused for task 0.1)
 * @sfree: set to 1 if returned path must be freed
 *
 * Return: path if it's absolute, NULL otherwise
 */
char *get_path(char *line, char **envp, int *sfree)
{
	(void)envp;
	*sfree = 0;
	if (line[0] == '/' && access(line, F_OK) == 0)
		return (line);
	return (NULL);
}

/**
 * execute - forks and executes a command
 * @line: the command to run
 * @argv: shell argv for error messages
 * @envp: environment variables
 *
 * Return: exit status of the child process
 */
int execute(char *line, char **argv, char **envp)
{
	char *path;
	char *args[2];
	int sfree = 0, status = 0;
	pid_t pid;

	path = get_path(line, envp, &sfree);
	if (!path)
	{
		fprintf(stderr, "%s: %s: No such file or directory\n", argv[0], line);
		return (127);
	}
	args[0] = line;
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
		fprintf(stderr, "%s: %s: No such file or directory\n", argv[0], line);
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
	int last_status = 0;

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
		last_status = execute(line, argv, envp);
	}
	free(line);
	return (last_status);
}
