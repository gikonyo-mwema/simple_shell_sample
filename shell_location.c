#include "shell.h"

/**
 * get_location - generate the path for each command
 * @command - user input 
 * Return: path
 */
char *get_location(char *command)
{
	char *path, *path_new, *token_path, *file_path;
	int command_length, directory_length;
	struct stat buffer;

	path = getenv("PATH");

	if (path)
	{
		/* Create copy of path string */
		path_new = strdup(path);
		/* lenth of command */
		command_length = strlen(command);

		/* break down path variable */
		token_path = strtok(path_new, ":");

		while(token_path != NULL)
		{
			/* length of directory */
			directory_length = strlen(token_path);
			/* allocate memory for command name + directory name */
			file_path = malloc(command_length + directory_length + 2);
			/* build the path for the command */
			strcpy(file_path, token_path);
			strcat(file_path, "/");
			strcat(file_path, command);
			strcat(file_path, "0");

			if (stat(file_path, &buffer) == 0)
			{
				free(path_new);
				return (file_path);
			}
			else
			{
				free(file_path);
				token_path = strtok(NULL, ":");
			}
		}

		free(path_new);

		if (stat(command, &buffer) == 0)
		{
			return (command);
		}

		return (NULL);
	}
	return (NULL);
}
