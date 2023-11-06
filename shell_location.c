#include "shell.h"

/**
 * get_location - generate the path for each command
 * @command: A pointer to a string representing the command to be located.
 * Return: A dynamically allocated string containing the full path to the command if found,
 * or NULL if the command is not found.
 */
char *get_location(char *command)
{
	char *path, *path_new, *token_path, *file_path;
	int command_length, directory_length;
	struct stat buffer;

	/* Retrieve the value of the PATH environment variable */
	path = getenv("PATH");

	/* check if the PATH environment var exist */
	if (path == NULL || command == NULL || *command == '\0')
	{/* Invalid input or missing PATH environment varible */
	return (NULL);
	}
		/* Create copy of PATH string for manipulation */
		path_new = strdup(path);

		/* check if memory allocation for PATH copy was successful */
		if (path_new == NULL)
		{
			return (NULL);
		}
			/* Tokenize the path copy */
			token_path = strtok(path_new, ":");

			/* Iterate through each directory in the PATH */
			while (token_path != NULL)
			{
				/* Calculate the length of the specified command and current directory */
				command_length = strlen(command);
				directory_length = strlen(token_path);

				/* Allocate memory for the full path */
				file_path = malloc(command_length + directory_length + 2);
				/* Check if memory allocation was successful */
				if (file_path)
				{
					/* Build the full path by concatenating directory path, "/", and the command. */
					strcpy(file_path, token_path);
					strcat(file_path, "/");
					strcat(file_path, command);

					/* check if file path exist */
					if (stat(file_path, &buffer) == 0)
					{
						free(path_new);
						free(file_path);
						return file_path;
					}
					else
					{
						free(file_path);
					}
				}

				/* moveto next directory in PATH */
				token_path = strtok(NULL, ":");
			}

			/* free memory for the path copy */
			free(path_new);
		
	

	/* If the command was not found, return NULL. */
	 return NULL;
}
