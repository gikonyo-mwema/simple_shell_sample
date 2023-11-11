#include "shell.h"

char** parse_command(char *lineptr, const char *delim)
{
	int token_num = 0;
	char **user_argv = malloc(sizeof(char *) * BUFFER_SIZE);
	char *token;
	char **temp;

	if (user_argv == NULL)
	{
		return (NULL);
	}

	if (lineptr == NULL)
	{
		/* Handle the error */
		free(user_argv);
		return (NULL);
	}

	token = strtok(lineptr, delim);
	while (token != NULL)
	{
		user_argv[token_num] = token;
		token_num++;
		if (token_num >= BUFFER_SIZE)
		{
			temp = realloc(user_argv, sizeof(char *) * (BUFFER_SIZE + token_num + 1));
			if (temp == NULL)
			{
				free(user_argv);
				return (NULL);
			}
		        user_argv = temp;
		}
        	token = strtok(NULL, delim);
	}
	user_argv[token_num] = NULL;

	return (user_argv);
}
