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
/* Execute the command with execve */
if (execve(command, argv, NULL) == -1)
{
perror("execve");
fprintf(stderr, "Failed to execute command: %s\n", argv[0]);
exit(EXIT_FAILURE);
}
}
else
{
fprintf(stderr, "Command not found: %sn", argv[0]);
exit(EXIT_FAILURE);
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
fprintf(stderr, "Invalid command or arguments\n");
return (-1);
}
return (0);
}
