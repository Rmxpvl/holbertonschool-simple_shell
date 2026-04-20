#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

/**
 * main - Entry point of the simple shell
 * @argc: argument count (unused)
 * @argv: argument vector, argv[0] is the program name
 *
 * Return: 0 on success
 */
int main(int argc, char **argv)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	pid_t pid;
	int status;
	char *newline;
	int cmd_num = 1;
	int last_exit = 0;

	(void)argc;

	while (1)
	{
		/* Display prompt only in interactive mode */
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);

		/* Read line */
		nread = getline(&line, &len, stdin);

		/* EOF */
		if (nread == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			free(line);
			exit(last_exit);
		}

		/* Strip newline */
		newline = strchr(line, '\n');
		if (newline)
			*newline = '\0';

		/* Skip empty lines */
		if (line[0] == '\0')
			continue;

		/* Fork */
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			continue;
		}

		if (pid == 0)
		{
			char *child_argv[2];

			child_argv[0] = line;
			child_argv[1] = NULL;

			if (execve(line, child_argv, environ) == -1)
			{
				fprintf(stderr, "%s: %d: %s: not found\n",
					argv[0], cmd_num, line);
				free(line);
				exit(127);
			}
		}
		else
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				last_exit = WEXITSTATUS(status);
		}
		cmd_num++;
	}

	free(line);
	return (last_exit);
}
