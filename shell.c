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

		lineptr_new = strdup(lineptr);
		
		if (lineptr_new == NULL)
		{
			perror("tsh: memory allocation error");
			return (-1);
		}

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
			argv[i] = strdup(token);
			token = strtok(NULL, delim);
		}


		argv[i] = NULL;

if (strcmp(argv[0], "exit") == 0)
{
free(lineptr);
free(lineptr_new);
free(argv);
printf("Exiting shell....\n");
return (0);
}
else if 
(strcmp(argv[0], "env") == 0)
{
char *env = *environ;
while (env)
{
printf("%s\n", env);
env = *(environ++);
}
}
else
{/* execute the command with execve */
		if (execmd(argv) != 0)
		{
			fprintf(stderr, "Command execution failed");
		}
}

		free(lineptr);
		free(lineptr_new);
		free(argv);
	}
	return (0);
}
