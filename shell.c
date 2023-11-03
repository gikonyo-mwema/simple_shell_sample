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
	char *prompt = "(Sample-Shell) $ ";
	char *lineptr = NULL, *lineptr_new = NULL;
	size_t n = 0;
	ssize_t input;
	const char *delim = " \n";
	int token_num = 0;
	char *token;
	int i;

	/* declaring void variables */
	(void)ac;

	/* Create  a loop for shell prompt */
	while (1)
	{
		printf("%s", prompt);
		
		/* get user input */
		input = getline(&lineptr, &n, stdin);
		
		/* check if the getline function failed or reached EOF or user use CTRL + D */
		if (input == -1)
		{
			printf("Exiting shell....\n");
			return (-1);
		}

		/* allocate memory for a copy of user input */
		lineptr_new = malloc(sizeof(char) * input);

		if (lineptr_new == NULL)
		{
			perror("tsh: memory allocation error");
			return (-1);
		}
		/* make a compy of the command/user input */
		strcpy(lineptr_new, lineptr);

		/* split the string/user input into an array of words */
		token  = strtok(lineptr, delim);

		/* allocate memory to store the variable, determine no of token */
		while (token != NULL)
		{
			token_num++;
			token = strtok(NULL, delim);
		}
		token_num++;

		/* allocate memory for the pointer to the argument variable */
		argv = malloc(sizeof(char *) * token_num);

		/* Store each token in argv array */
		token = strtok(lineptr_new, delim);

		for (i = 0; token != NULL; i++)
		{
			argv[i] = malloc(sizeof(char) * strlen(token));
			strcpy(argv[i], token);

			token = strtok(NULL, delim);
		}
		argv[i] = NULL;

		/* execute the command with execve */
		execmd(argv);
	}
	free(lineptr);
	free(lineptr_new);

	return (0);
}
