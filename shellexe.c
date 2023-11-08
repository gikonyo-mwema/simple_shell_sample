#include "shell.h"

/**
 * execmd - execute child processes
 *
 * @argv: character array
 * Return: 0 (success) otherwise -1
 */
int execmd(char **argv)
{
	pid_t pid;
	char *command = NULL;
	/* *user_command = NULL;*/

	if (argv && argv[0])
	{
		pid = fork();

		if (pid == -1)
		{
			perror("fork");
			return (-1);
		}

		if (pid == 0)
		{
			/* child process */
			/* Check if the command includes a full path */
			if (strchr(argv[0], '/') != NULL)
			{
				command = argv[0];
			}
			else
			{
				/* Get command from the PATH */
				command = get_location(argv[0]);
			}

			if (command)
			{
				if (access(command, X_OK) == 0)
				{
					/* Execute the command with execve */
					if (execve(command, argv, NULL) == -1)
					{
						perror("execve");
						_print_shell("Failed to execute command: ");
						_print_shell(argv[0]);
						_print_shell("\n");
						free(command);
						exit(EXIT_FAILURE);
					}
				}
				else
				{
					_print_shell("Command not found: ");
					_print_shell(argv[0]);
					_print_shell("\n");
					free(command);
					exit(EXIT_FAILURE);
				}
			}
		}
		else
		{
			/* Parent process */
			int status;
			waitpid(pid, &status, 0);
		}
	}
	else
	{
		_print_shell("Invalid command or arguments\n");
		return (-1);
	}
	return (0);
}
