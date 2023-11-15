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
	char *pipe_sign, *command_1, *command_2,**argv_redir, **argv_1, **argv_2, *redir_sign, *command, *file;
	(void)ac;
	(void)argv;
	

	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			print_prompt(prompt);
		} 
		lineptr = get_command();
		if (lineptr == NULL)
		{
			break;
		}
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
			if (i < token_num)
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
			else if (strcmp(user_argv[0], "setenv") == 0)
                        {
                                if (user_argv[1] != NULL && user_argv[2] != NULL)
                                {
                                        my_setenv(user_argv[1], user_argv[2], "1");
                                }
                                else
                                {
                                        fprintf(stderr, "%s: setenv: Too few arguments. \n", argv[0]);
                                }
                        }

			else if (strcmp(user_argv[0], "unsetenv") == 0)
			{
				if (user_argv[1] != NULL)
				{
					my_unsetenv(user_argv[1]);
				}
				else
				{
					fprintf(stderr, "%s: unsetenv: Too few arguments.\n", argv[0]);
				}
			}
			else if (strchr(user_argv[0], '|') != NULL)
			{
				pipe_sign = strchr(user_argv[0], '|');
				*pipe_sign = '\0';
				command_1 = user_argv[0];
				command_2 = pipe_sign + 1;

				argv_1 = parse_command(command_1, " ");
				argv_2 = parse_command(command_2, " ");

				execute_pipe(argv_1, argv_2);
				free(argv_1);
				free(argv_2);
			}
			else if (strchr(user_argv[0], '>') != NULL)
			{
				redir_sign = strchr(user_argv[0], '>');
				*redir_sign = '\0';
				command = user_argv[0];
				file = redir_sign + 1;

				argv_redir= parse_command(command, " ");
				execute_redirection(argv, file, 1);
				free(argv_redir);
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
