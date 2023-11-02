#include "shell.h"
/**
 * main - prompt the user to enter command, read command using getline
 * @ac: no of arguments
 * @argv: pointer to arguments
 *
 * Return: 0 success
 */
int main(int ac, char **argv)
{
	char *prompt = "(shell) $ ";
	char *lineptr = NULL, *lineptr_new = NULL;
	size_t n = 0;
	ssize_t input;
	const char *delim = " \n";
	int token_num = 0;
	char *token;
	int i;

	/* declaring void variables */
	(void)ac;

	/* create an infinite loop */
	while (1)
	{
		printf("%s", prompt);
		input = getline(&lineptr, &n, stdin);
		/* check if the getline function failed or reached EOF */
		if (input == -1)
		{
			printf("Exiting NOW \n");
			return (-1);
		}

		/* allocate memery for a copy of the lineprtr - lineptr_new */
		lineptr_new = malloc(sizeof(char) * input);
		if (lineptr_new == NULL)
		{
			perror("memory allocation error");
			return (-1);
		}

		/* copy lineptr to lineptr_new */
		strcpy(lineptr_new, lineptr);

		/* split the string (lineptr) intor an array of words */
		/* calculate the total number of tokens */
		token = strtok(lineptr, delim);

		while (token != NULL)
		{
			token_num++;
			token = strtok(NULL, delim);
		}
		token++;

		/* Allocate space to hold the array of strings */
		argv = malloc(sizeof(char *) * token_num);

		/* store each token in the argv array */
		token = strtok(lineptr_new, delim);

		for (i = 0; token != NULL; i++)
		{
			argv[i] = malloc(sizeof(char) * strlen(token));
			strcpy(argv[i], token);

			token = strtok(NULL, delim);
		}
		argv[i] = NULL;

		printf("%s\n", lineptr);

		/* free up allocated memory */
		free(lineptr);
	}
	return (0);
}
