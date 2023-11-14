#include "shell.h"

#define BUFFER_SIZE 1024

char **parse_command(char *lineptr, const char *delim)
{
	int token_num = 0, buf = BUFFER_SIZE;
	char **user_argv = malloc(sizeof(char *) * BUFFER_SIZE);
	char *token, **temp;
	int i;

	if (user_argv == NULL || lineptr == NULL)
	{
		return (NULL);
	}
	token = strtok(lineptr, delim);
	while (token != NULL)
	{
		if (token_num >= buf - 1)
		{
			temp = realloc(user_argv, sizeof(char *) * (buf * 2));
			if (temp == NULL)
			{
				for (i = 0; i < token_num; i++)
				{
					free(user_argv);
				}
				free(user_argv);
				return (NULL);
			}
		        user_argv = temp;
			buf *= 2;
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
