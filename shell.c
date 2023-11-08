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
	int token_num = 0;
	char *token = NULL;
	int i = 0;
	char env_output[256];


	/* declaring void variables */
	(void)ac;

	/* Create  a loop for shell prompt */
	while (1)
	{
		print_prompt(prompt);
		
		/* get user input */
		lineptr = get_command();
			
		/* allocate memory for the pointer to the argument variable */
		user_argv = (char **)malloc(sizeof(char *) * (token_num + 1));

		/* split the string/user input into an array of words */
		user_argv = parse_command(lineptr, delim);

		/* Re-tokenize the input and Store each token in user_argv*/
		token = strtok(lineptr, delim);

		for (i = 0; i <token_num; i++)
		{
			user_argv[i] = strdup(token);
			token = strtok(NULL, delim);
		}

		if (i >= 0 && i < token_num)
		{
		user_argv[i] = NULL;
		}

		if (user_argv[0] != NULL)
		{
		if (strcmp(user_argv[0], "exit") == 0)
		{
		free(lineptr);
		free(user_argv);
		_print_shell("Exiting shell....\n");
		return (0);
		}
		else if (strcmp(user_argv[0], "env") == 0)
		{
		char *env = *environ;
		while (env)
		{
		strcpy(env_output, env);
		strcat(env_output,"\n");
		_print_shell(env_output);
		env = *(environ++);
		}
		
		}
		
		else
		{/* execute the command with execve */
		if (execmd(user_argv) != 0)
		{
			_print_shell("Command execution failed");
		}
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
