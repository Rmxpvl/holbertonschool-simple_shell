#include "shell.h"

extern char **environ;

/**
 * get_path - validates command path
 * @line: the command (must be an absolute path)
 * @sfree: set to 1 if returned path must be freed
 *
 * Return: path if it's absolute, NULL otherwise
 */
char *get_path(char *line, int *sfree)
{
	*sfree = 0;
	if (line[0] == '/' && access(line, F_OK) == 0)
		return (line);
	return (NULL);
}

/**
 * execute - forks and executes a command
 * @line: the command to run
 * @prog_name: shell program name for error messages
 * @line_num: line number for error messages
 *
 * Return: exit status of the child process
 */
int execute(char *line, char *prog_name, int line_num)
{
	char *path;
	char *args[2];
	int sfree = 0, status = 0;
	pid_t pid;

	path = get_path(line, &sfree);
	if (!path)
	{
		fprintf(stderr, "%s: %d: %s: not found\n", prog_name, line_num, line);
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
		execve(path, args, environ);
		fprintf(stderr, "%s: %d: %s: not found\n", prog_name, line_num, line);
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
 * run_shell - main shell loop
 * @prog_name: program name for error messages
 *
 * Return: void
 */
void run_shell(char *prog_name)
{
	char *line = NULL;
	char *newline;
	size_t len = 0;
	ssize_t nread;
	int line_num = 1;

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
			return;
		}
		newline = strchr(line, '\n');
		if (newline)
			*newline = '\0';
		if (line[0] == '\0')
		{
			line_num++;
			continue;
		}
		execute(line, prog_name, line_num);
		line_num++;
	}
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
