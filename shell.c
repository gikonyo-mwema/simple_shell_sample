#include "shell.h"

char* allocate_env_output(char **env_p, char *lineptr, char **user_argv)
{
	char *env = *env_p;
	char *env_output = NULL;
	size_t env_length;
	size_t total_length = 0;

	while (env != NULL)
	{	
	
		env_length = strlen(env);

		env_output = realloc(env_output, total_length + env_length + 2);

		if (env_output == NULL)
		{
			perror("Memory allocation error");
			exit(EXIT_FAILURE);
		}
		strcat(env_output, env);
		strcat(env_output, "\n");

		total_length += env_length + 1;
		env = *(++env_p);
	}
	free(lineptr);
	free(user_argv);
	return (env_output);
}

/**
 * main - prompt the user to enter command, read command using getline
 * @ac: no of arguments
 * @argv: pointer to arguments
 *
 * Return: 0 success
 */
int main(int ac, char **argv)
{
	char *prompt = "($) ";
	char *lineptr = NULL;
	const char *delim = " \n";
	char **user_argv = NULL;
	int token_num = 0;
	char *token = NULL;
	int i = 0;
	char **env_p = environ;
	char *env_output = NULL;
	int result;


	/* declaring void variables */
	(void)ac;
	(void)argv;

	/* Create  a loop for shell prompt */
	while (1)
	{
		/* Only print the prompt in interactive mode */
		if (isatty(STDIN_FILENO))
		{
			print_prompt(prompt);
		} 
		
		/* get user input */
		lineptr = get_command();
			
		/* allocate memory for the pointer to the argument variable */
	/*	user_argv = (char **)malloc(sizeof(char *) * (token_num + 1)); */

		/* split the string/user input into an array of words */
		user_argv = parse_command(lineptr, delim);

		/* Re-tokenize the input and Store each token in user_argv*/
		token = strtok(lineptr, delim);

		for (i = 0; i < token_num; i++)
		{
			if (token != NULL)
			{
				user_argv[i] = strdup(token);
			}
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
			/*	_print_shell("Exiting shell....\n");*/
				return (0);
			}

			else if (strcmp(user_argv[0], "env") == 0)
			{
				env_output = allocate_env_output(env_p, lineptr, user_argv);

				_print_shell(env_output);
			}
				/* execute the command with execve */
			/*	if (execmd(user_argv) != 0)*/
				result = process_command(user_argv, lineptr, NULL);
				if (result != 0)
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

	return (0);
}
