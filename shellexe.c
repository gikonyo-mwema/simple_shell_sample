#include "shell.h"

/**
 * execmd - 
 *
 * @argv:
 * Return: 
 */
void execmd(char **argv)
{
	char *command = NULL, *user_command = NULL;

	if (argv)
	{
		/* get the command */
		command = argv[0];

		/* generate the path to this command before passing it to execve */
		user_command = get_location(command);

		/* execute the command with execve */
		if (execve(user_command, argv, NULL) == -1)
		{
			perror("Error:");
		};
	}
}
