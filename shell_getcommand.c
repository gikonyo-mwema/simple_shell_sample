#include "shell.h"
/**
 * get_command - get the user command
 * Return: pointer to string
 */
char *get_command(void)
{
	char *lineptr = NULL;
	size_t n = 0;
	int i;

	if (getline(&lineptr, &n, stdin) == -1)
	{
		/* _print_shell("Exiting shell>>>>\n"); */
		free(lineptr);
		exit(-1);
	}

	/* Check if the line is empty or contains only whitespace */
	for (i = 0; lineptr[i]; i++)
	{
		if (lineptr[i] != ' ' && lineptr[i] != '\t' && lineptr[i] != '\n' && lineptr[i] != '\r')
		{
			/* Line contains a not-whitespace character, so NOT empty */
			break;
		}
	}

	if (!lineptr[i])
	{
		/* The line is empty, free  the memory and return NULL */
		free(lineptr);
		return (NULL);
	}

	return (lineptr);
}
