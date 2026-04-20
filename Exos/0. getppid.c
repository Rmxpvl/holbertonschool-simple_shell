#include <stdio.h>
#include <unistd.h>

/**
 * main - Entry point
 *
 * Return: 0 on success
 */
int main(void)
{
	printf("%d\n", getppid());
	return (0);
}
