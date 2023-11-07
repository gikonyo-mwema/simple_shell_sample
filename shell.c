#include "shell.h"
/**
 * main - prompt the user to enter command, read command using getline
 * @ac: no of arguments
 * @argv: pointer to arguments
 *
 * Return: 0 success
 */
int main(int ac, char **argv __attribute__((unused)))
{
	char *prompt = "($) ";
	char *lineptr = NULL;
	const char *delim = " \n";
	char **user_argv = NULL;



	print_prompt(prompt);
	lineptr = read_command();
	user_argv = parse_command(lineptr, delim);




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
			free(lineptr);
			return (-1);
		}

		token_num = 0;
		/* split the string/user input into an array of words */
		token  = strtok(lineptr, delim);

		/* allocate memory to store the variable, determine no of token */
		while (token != NULL)
		{
			token_num++;
			token = strtok(NULL, delim);
		}
		
		/* allocate memory for the pointer to the argument variable */
		user_argv = (char **)malloc(sizeof(char *) * (token_num + 1));

		/* Re-tokenize the input and Store each token in user_argv*/
		token = strtok(lineptr, delim);

		for (i = 0; i <token_num; i++)
		{
			user_argv[i] = strdup(token);
			token = strtok(NULL, delim);
		}

		user_argv[i] = NULL;

		if (strcmp(user_argv[0], "exit") == 0)
		{
		free(lineptr);
		free(user_argv);
		printf("Exiting shell....\n");
		return (0);
		}
		else if (strcmp(user_argv[0], "env") == 0)
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
		if (execmd(user_argv) != 0)
		{
			fprintf(stderr, "Command execution failed");
		}










}

		/* Free allocated memory */
		free(lineptr);
		for (i = 0; i < token_num; i++)
{
free(user_argv[i]);
}
		free(user_argv);
	}
	return (0);
}
