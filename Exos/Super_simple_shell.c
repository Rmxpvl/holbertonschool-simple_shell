#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

#define BUFFER_SIZE 1024

/**
 * main - Super simple shell that runs commands with full path
 * Description: Reads user input (full path to command, no arguments),
 *              forks a child process, and executes the command.
 *              Loop until user exits.
 * Return: 0 on success
 */
int main(void)
{
	char command[BUFFER_SIZE];
	pid_t pid;
	
	while (1)
	{
		/* Display prompt */
		printf("$ ");
		fflush(stdout);
		
		/* Read command from user */
		if (fgets(command, BUFFER_SIZE, stdin) == NULL)
		{
			/* Handle EOF (Ctrl+D) */
			printf("\n");
			break;
		}
		
		/* Remove trailing newline */
		command[strcspn(command, "\n")] = '\0';
		
		/* Skip empty commands */
		if (command[0] == '\0')
			continue;
		
		/* Handle exit command */
		if (strcmp(command, "exit") == 0)
			break;
		
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
			char *env[] = {NULL};
			
			execve(command, argv, env);
			/* If execve returns, there was an error */
			perror("execve");
			exit(1);
		}
		else
		{
			/* Parent process: wait for child to finish */
			wait(NULL);
		}
	}
	
	return (0);
}
