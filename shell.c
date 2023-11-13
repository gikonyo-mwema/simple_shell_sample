#include "shell.h"

char *allocate_env_output(char **env_p, char *lineptr, char **user_argv)
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
	int result, token_num = 0, i = 0;
	char *token = NULL, **user_argv = NULL, **env_p = environ, *env_output = NULL;
	(void)ac;
	(void)argv;

	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			print_prompt(prompt);
		} 
		lineptr = get_command();
		user_argv = parse_command(lineptr, delim);
		token = strtok(lineptr, delim);
		while (token != NULL)
		{
			user_argv[i] = strdup(token);
			token = strtok(NULL, delim);
			i++;
		}
		user_argv[i] = NULL;
		if (user_argv[0] != NULL)
		{
			if (i >= 0 && i < token_num)
			{
				if (strcmp(user_argv[0], "exit") == 0)
				{
					/*free(lineptr);*/
					/*free(user_argv);*/
					return (0);
				}
			}
			else if (strcmp(user_argv[0], "env") == 0)
			{
				env_output = allocate_env_output(env_p, lineptr, user_argv);
				_print_shell(env_output);
				free(env_output);
			}
			else
			{
				result = process_command(user_argv, lineptr, NULL);
				if (result != 0)
				{
					_print_shell("Command execution failed");
				}
			}
		}
		free(lineptr);
		for (i = 0; user_argv[i] != NULL; i++)
		{
			free(user_argv[i]);
		}
		free(user_argv);
	}
	return (0);
}
