#include "shell.h"

/**
 * execute - forks and executes a command
 * @line: the command to run
 * @argv: shell argv for error messages
 * @cmd_num: command number for error messages
 *
 * Return: exit status of the child process
 */
int execute(char *line, char **argv, int cmd_num)
{
	pid_t pid;
	int status = 0;
	char *args[2];

	args[0] = line;
	args[1] = NULL;
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
	{
		if (execve(line, args, environ) == -1)
		{
			fprintf(stderr, "%s: %d: %s: not found\n",
				argv[0], cmd_num, line);
			exit(127);
		}
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

/**
 * main - entry point of the simple shell
 * @argc: argument count (unused)
 * @argv: argument vector
 *
 * Return: 0
 */
int main(int argc, char **argv)
{
	char *line = NULL;
	char *newline;
	size_t len = 0;
	ssize_t nread;
	int cmd_num = 1;
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
		last_status = execute(line, argv, cmd_num);
		cmd_num++;
	}
	free(line);
	return (last_status);
}
