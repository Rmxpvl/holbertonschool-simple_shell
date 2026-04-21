#include "shell.h"

/**
 * fork_execute - Forks and runs a process
 * @path: Execution path
 * @args: Command arguments
 * @prog_name: Shell program name
 * @line_num: Line number
 * Return: Exit status
 */
int fork_execute(char *path, char **args, char *prog_name, int line_num)
{
	pid_t pid;
	int status = 0;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
	{
		args[0] = path;
		execve(path, args, environ);
		fprintf(stderr, "%s: %d: %s: not found\n",
			prog_name, line_num, path);
		exit(127);
	}
	waitpid(pid, &status, 0);

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

/**
 * execute - resolves path and calls fork_execute.
 * @args: NULL-terminated array of argument strings
 * @prog_name: shell program name for error messages
 * @line_num: current line number for error messages
 * Return: exit status of the child process
 */
int execute(char **args, char *prog_name, int line_num)
{
	char *path;
	int need_free = 0, status;
	struct stat st;

	if (args[0][0] == '/' || args[0][0] == '.')
	{
		if (stat(args[0], &st) != 0 || access(args[0], X_OK) != 0)
		{
			fprintf(stderr, "%s: %d: %s: not found\n",
				prog_name, line_num, args[0]);
			return (127);
		}
		path = args[0];
	}
	else
	{
		path = find_in_path(args[0]);
		if (!path)
		{
			fprintf(stderr, "%s: %d: %s: not found\n",
				prog_name, line_num, args[0]);
			return (127);
		}
		need_free = 1;
	}

	status = fork_execute(path, args, prog_name, line_num);

	if (need_free)
		free(path);

	return (status);
}
