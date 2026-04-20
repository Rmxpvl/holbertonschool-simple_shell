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
int main(void)
{
	char command[BUFFER_SIZE];
	pid_t pid;
	int status;
	int is_tty;

	/* Check if stdin is a terminal (for prompt display) */
	is_tty = isatty(STDIN_FILENO);

	while (1)
	{
		/* Display prompt only if stdin is a terminal */
		if (is_tty)
		{
			printf("#cisfun$ ");
			fflush(stdout);
		}

		/* Read command from user */
		if (fgets(command, BUFFER_SIZE, stdin) == NULL)
		{
			/* Handle EOF (Ctrl+D) */
			if (is_tty)
				printf("\n");
			break;
		}

		/* Remove trailing newline */
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
			char *argv[] = {command, NULL};

			execve(command, argv, environ);
			/* If execve returns, there was an error */
			fprintf(stderr, "./shell: %s: No such file or directory\n", command);
			exit(127);
		}
		else
		{
			/* Parent process: wait for child to finish */
			waitpid(pid, &status, 0);
		}
	}

	return (0);
}
