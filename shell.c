#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

#define BUFFER_SIZE 1024

extern char **environ;

/**
 * main - Simple UNIX command line interpreter
 * Description: A basic shell that executes commands with full paths.
 *              Reads from stdin, displays prompt, and executes commands.
 *              Handles EOF (Ctrl+D) gracefully.
 * Return: 0 on success
 */
int main(int ac, char *av[])
{
	char buffer[BUFFER_SIZE];
	char *command;
	pid_t pid;
	int is_interactive;

	(void)ac;

	is_interactive = isatty(STDIN_FILENO);

	while (1)
	{
		if (is_interactive)
		{
			printf("#cisfun$ ");
			fflush(stdout);
		}

		if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
		{
			break;
		}

		/* Remove trailing newline */
		command = buffer;
		command[strcspn(command, "\n")] = '\0';

		/* Skip empty commands */
		if (command[0] == '\0')
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
			/* Child process: execute the command */
			char *argv[2];

			argv[0] = command;
			argv[1] = NULL;
			execve(command, argv, environ);
			/* If execve returns, there was an error */
			fprintf(stderr, "%s: No such file or directory\n", av[0]);
			exit(127);
		}
		else
		{
			/* Parent process: wait for child to finish */
			wait(NULL);
		}
	}

	return (0);
}
