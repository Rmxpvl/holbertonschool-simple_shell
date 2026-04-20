#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

/**
 * main - Entry point of the simple shell
 *
 * Return: Always 0
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	pid_t pid;
	int status;
	char *newline;

	while (1)
	{
		/* Display prompt only if interactive (terminal) */
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);

		/* Read a line from stdin */
		nread = getline(&line, &len, stdin);

		/* Handle EOF (Ctrl+D) */
		if (nread == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			free(line);
			exit(0);
		}

		/* Remove trailing newline */
		newline = strchr(line, '\n');
		if (newline)
			*newline = '\0';

		/* Skip empty input */
		if (line[0] == '\0')
			continue;

		/* Fork a child process */
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			continue;
		}

		if (pid == 0)
		{
			/* Child process: build argv and execute */
			char *argv[2];

			argv[0] = line;
			argv[1] = NULL;

			if (execve(line, argv, environ) == -1)
			{
				/* execve failed: command not found or not executable */
				fprintf(stderr, "./simple_shell: 1: %s: not found\n", line);
				free(line);
				exit(127);
			}
		}
		else
		{
			/* Parent process: wait for child */
			waitpid(pid, &status, 0);
		}
	}

	free(line);
	return (0);
}
