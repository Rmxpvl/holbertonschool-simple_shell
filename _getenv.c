#include "shell.h"

/**
 * _getenv - gets the value of an environment variable
 * @name: name of the variable
 *
 * Return: string value or NULL
 */
char *_getenv(const char *name)
{
        int i, j;
        int len;

        if (!name || !environ)
                return (NULL);

        len = strlen(name);
        for (i = 0; environ[i] != NULL; i++)
        {
                for (j = 0; j < len; j++)
                {
                        if (environ[i][j] != name[j])
                                break;
                }
                if (j == len && environ[i][j] == '=')
                        return (environ[i] + j + 1);
        }
        return (NULL);
}
