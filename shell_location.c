#include "shell.h"

/**
 * get_location - generate the path for each command
 * @command: A pointer to a string representing the command to be located.
 * Return: A dynamically allocated string containing the full path to the command if found,
 * or NULL if the command is not found.
 */
char *get_location(char *command)
{
	char *path, *path_new = NULL, *token_path, *file_path;
	int command_length, directory_length;
	struct stat buffer;

	if (command == NULL || *command == '\0')
	{
		return (NULL);
	}

	path = getenv("PATH");
	if (path_new == NULL)
	{
		return (NULL);
	}
	path_new = strdup(path);
	if (path_new == NULL)
	{
		return (NULL);
	}

	token_path = strtok(path_new, ":");
	while (token_path != NULL)
	{
		command_length = strlen(command);
		directory_length = strlen(token_path);

		file_path = malloc(command_length + directory_length + 2);
		if (file_path == NULL)
		{
			free(path_new);
			return (NULL);
		}
		strcpy(file_path, token_path);
		strcat(file_path, "/");
		strcat(file_path, command);
		
		if (stat(file_path, &buffer) == 0)
		{
			free(path_new);
			return (file_path);
		}
		else
		{
			free(file_path);
			return (NULL);
		}
		token_path = strtok(NULL, ":");
	}
	free(path_new);
	return (NULL);
}
