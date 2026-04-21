#include "shell.h"

extern char **environ;

/**
 * execute - forks and executes a command with its arguments
 * @args: NULL-terminated array of argument strings
 * @prog_name: shell program name for error messages
 * @line_num: current line number for error messages
 *
 * Return: exit status of the child process
 */
int execute(char **args, char *prog_name, int line_num)
{
	int status = 0;
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
	{
		execve(args[0], args, environ);
		fprintf(stderr, "%s: %d: %s: not found\n",
			prog_name, line_num, args[0]);
		exit(127);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

/**
 * run_shell - main shell loop
 * @prog_name: program name for error messages
 */
void run_shell(char *prog_name)
{
	char *line = NULL, *token, *args[512];
	size_t len = 0;
	ssize_t nread;
	int line_num = 1, argc, last_status = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "($) ", 4);

		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		line[strcspn(line, "\n")] = '\0';

		argc = 0;
		token = strtok(line, " \t");
		while (token && argc < 511)
		{
			args[argc++] = token;
			token = strtok(NULL, " \t");
		}
		args[argc] = NULL;

		if (argc == 0)
		{
			line_num++;
			continue;
		}

		if (strcmp(args[0], "exit") == 0)
		{
			free(line);
			exit(last_status);
		}

		if (strcmp(args[0], "env") == 0)
		{
			int i;

			for (i = 0; environ[i]; i++)
				printf("%s\n", environ[i]);
			line_num++;
			continue;
		}

		last_status = execute(args, prog_name, line_num);
		line_num++;
	}
	free(line);
}

/**
 * main - entry point
 * @argc: argument count (unused)
 * @argv: argument vector
 *
 * Return: 0
 */
int main(int argc, char **argv)
{
	(void)argc;
	run_shell(argv[0]);
	return (0);
}
