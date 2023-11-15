#include "shell.h"
/**
 * execute_pipe - works on pipe
 * @argv_1: first argument
 * @argv_2: second argument
 * Return: 0
 */
void execute_pipe(char **argv_1, char **argv_2)
{
	int pipefd[2];

	pid_t pid1, pid2;

	if (pipe(pipefd) < 0)
	{
		perror("pipe() failed");
		return;
	}
	pid1 = fork();
	if (pid1 < 0)
	{
		perror("fork() failed");
		return;
	}
	if (pid1 == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		if (execvp(argv_1[0], argv_1) < 0)
		{
			perror(argv_1[0]);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		pid2 = fork();
		if (pid2 < 0)
		{
			perror("fork() failed");
			return;
		}
		if (pid2 == 0)
		{
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
			if (execvp(argv_2[0], argv_2) < 0)
			{
				perror(argv_2[0]);
				exit(EXIT_FAILURE);
			}
		}
		else
		{	
			close(pipefd[0]);
			close(pipefd[1]);
			wait(NULL);
			wait(NULL);
		}
	}
}
/**
 * execute_redirection - redirections handling
 * @argv: user command
 * @file: file 
 * @direction: direction
 * Return: void
 */

void execute_redirection(char **argv, char *file, int direction)
{
	int fd;
	pid_t pid;

	pid = fork();

	if (pid == -1)
	{
		perror("fork() failed");
		return;
	}
	if (pid == 0)
	{
		if (direction == 0)
		{
			fd = open(file, O_RDONLY);
			if (fd < 0)
			{
				perror("Input redirection failed");
				exit(EXIT_FAILURE);
			}
			dup2(fd, STDIN_FILENO);
		}
		else
		{
			fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
			{
				perror("Output redirection failed");
				exit(EXIT_FAILURE);
			}
			dup2(fd, STDOUT_FILENO);
		}
		close(fd);
		if (execvp(argv[0], argv) < 0)
		{
			perror("execvp() failed");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(NULL);
	}
}
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
			if (strchr(argv[0], '/') != NULL)
			{
				command = argv[0];
			}
			else
			{
				command = get_location(argv[0]);
			}
			if (command)
			{
				if (access(command, X_OK) == 0)
				{
					if (execve(command, argv, NULL) == -1)
					{
						perror("execve() failed");
						free(command);
						exit(EXIT_FAILURE);
					}
				}
				else
				{
					_print_shell("Command not found or permission denied\n");
					free(command);
					exit(EXIT_FAILURE);
				}
			}
		}
		else
		{
			int status;

			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
			{
				return (WEXITSTATUS(status));
			}
		}
	}
	else
	{
		_print_shell("Invalid command or arguments\n");
		return (-1);
	}
	return (0);
}
