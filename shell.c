#include "shell.h"

/**
 * handle_builtins - Checks and executes built-in commands
 * @args: Argument array
 * @line_num: Current line number
 * @line: Current input line (needed to free on exit)
 * @last_status: Status of the last executed command
 * @prog_name: Program name
 * Return: 1 if builtin was executed, 0 otherwise
 */
int handle_builtins(char **args, int *line_num, char *line, int last_status,
	char *prog_name)
{
int i;
(void)prog_name;

if (strcmp(args[0], "exit") == 0)
{
free(line);
exit(last_status);
}

if (strcmp(args[0], "env") == 0)
{
for (i = 0; environ[i]; i++)
printf("%s\n", environ[i]);
(*line_num)++;
return (1);
}
return (0);
}

/**
 * parse_line - Tokenizes the input line
 * @line: Input line
 * @args: Array to populate with tokens
 * Return: Number of arguments parsed
 */
int parse_line(char *line, char **args)
{
int argc = 0;
char *token;

token = strtok(line, " \t");
while (token && argc < 511)
{
args[argc++] = token;
token = strtok(NULL, " \t");
}
args[argc] = NULL;
return (argc);
}

/**
 * run_shell - main shell loop
 * @prog_name: program name for error messages
 * Return: the last exit status
 */
int run_shell(char *prog_name)
{
char *line = NULL, *args[512];
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
argc = parse_line(line, args);
if (argc == 0)
{
line_num++;
continue;
}
if (handle_builtins(args, &line_num, line, last_status, prog_name))
continue;
last_status = execute(args, prog_name, line_num);
line_num++;
}
free(line);
return (last_status);
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
return (run_shell(argv[0]));
}
