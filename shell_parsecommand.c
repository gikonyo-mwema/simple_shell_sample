#include "shell.h"

char **parse_command(char *lineptr, const char *delim)
{
	int i,
	int token_num = 0;
	char **user_argv = malloc(sizeof(char *) * BUFFER_SIZE);
	char *token, **temp;

	if (user_argv == NULL)
	{
		return (NULL);
	}

	if (lineptr == NULL)
	{
		free(user_argv);
		return (NULL);
	}

	token = strtok(lineptr, delim);
	while (token != NULL)
	{
		if (token_num >= BUFFER_SIZE - 1)
		{
			temp = realloc(user_argv, sizeof(char *) * (BUFFER_SIZE * 2));
			if (temp == NULL)
			{
				free(user_argv);
				return (NULL);
			}
		        user_argv = temp;
			BUFFER_SIZE *= 2;
		}
        	user_argv[token_num] = strdup(token);
		if(user_argv[token_num] == NULL)
		{
			for (i = 0; i < token_num; i++)
			{
				free(user_argv[i]);
			}
			free(user_argv);
			return (NULL);
		}
		token_num++;
		token = strtok(NULL, delim);
	}
	user_argv[token_num] = NULL;

	return (user_argv);
}
