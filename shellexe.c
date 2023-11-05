#include "shell.h"

/**
 * execmd - 
 *
 * @argv:
 * Return: 
 */
int execmd(char **argv)
{
	char *command = NULL, *user_command = NULL;

	if (argv && argv[0])
	{
		/* get the command */
		command = argv[0];

		/* generate the path to this command before passing it to execve */
		user_command = get_location(command);

		if (user_command)
		{
			/* Execute the command with execve */
			if (execve(user_command, argv, NULL) == -1)
{
perror("execve");
fprintf(stderr, "Failed to execute command: %s\n", command);
return (-1);
}
free(user_command);
		}
		else
		{
			fprintf(stderr, "Command not found: %s\n", command);
			return (-1);
		}
	}
	else
	{
		fprintf(stderr, "Invalid command or arguments\n");
		return (-1);
	}
return (0);
}
