#include "shell.h"

/**
 * build_path - Creates a full path by joining directory and command.
 * @dir: Directory string.
 * @cmd: Command string.
 * Return: A newly allocated string containing dir/cmd, or NULL on failure.
 */
char *build_path(char *dir, char *cmd)
{
	size_t len;
	char *full;

	len = strlen(dir) + strlen(cmd) + 2;
	full = malloc(len);
	if (!full)
		return (NULL);

	sprintf(full, "%s/%s", dir, cmd);
	return (full);
}

/**
 * find_in_path - Searches for an executable command in PATH.
 * @cmd: The command to look for.
 * Return: The full path to the executable, or NULL if not found.
 */
char *find_in_path(char *cmd)
{
	char *path_env, *path_copy, *dir, *full;

	path_env = _getenv("PATH");
	if (!path_env || path_env[0] == '\0')
		return (NULL);

	path_copy = strdup(path_env);
	if (!path_copy)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir)
	{
		full = build_path(dir, cmd);
		if (!full)
		{
			free(path_copy);
			return (NULL);
		}

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
