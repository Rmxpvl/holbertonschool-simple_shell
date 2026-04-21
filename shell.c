#include "shell.h"

extern char **environ;

/**
 * find_in_path - searches PATH directories for an executable
 * @cmd: command name (no slash)
 *
 * Return: allocated full path string, or NULL if not found
 */
char *find_in_path(char *cmd)
{
	char *path_env, *path_copy, *dir, *full;
	size_t len;

	path_env = _getenv("PATH");
	if (!path_env || path_env[0] == '\0')
		return (NULL);

	path_copy = strdup(path_env);
	if (!path_copy)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir)
	{
		len = strlen(dir) + strlen(cmd) + 2;
		full = malloc(len);
		if (!full)
		{
			free(path_copy);
			return (NULL);
		}
		sprintf(full, "%s/%s", dir, cmd);
		if (access(full, X_OK) == 0)
		{
			free(path_copy);
			return (full);
		}
		free(full);
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}

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
	char *path;
	int need_free = 0, status = 0;
	pid_t pid;

	if (args[0][0] == '/' || args[0][0] == '.')
	{
		if (access(args[0], F_OK) != 0)
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

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		if (need_free)
			free(path);
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
	if (need_free)
		free(path);
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
