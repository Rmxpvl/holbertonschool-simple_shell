#include <stdio.h>
#include <string.h>

int main(void)
{
    char str[] = "ls -l /tmp";
    char *token = strtok(str, " ");

    while (token)
    {
        printf("%s\n", token);
        token = strtok(NULL, " ");
    }
}