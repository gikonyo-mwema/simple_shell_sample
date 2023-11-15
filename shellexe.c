#include "shell.h"

void execute_pipe(char **argv_1, char **argv_2)
{
    int pipefd[2];
    pid_t pid1, pid2;

    if (pipe(pipefd) < 0) {
        perror("pipe() failed");
        return;
    }

    pid1 = fork();
    if (pid1 < 0) {
        perror("fork() failed");
        return;
    }

    if (pid1 == 0) {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);

        if (execvp(argv_1[0], argv_1) < 0) {
            perror(argv_1[0]);
            exit(1);
        }
    } else {
        pid2 = fork();

        if (pid2 < 0) {
            perror("fork() failed");
            return;
        }

        if (pid2 == 0) {
            close(pipefd[1]);
            dup2(pipefd[0], STDIN_FILENO);
            close(pipefd[0]);

            if (execvp(argv_2[0], argv_2) < 0) {
                perror(argv_2[0]);
                exit(1);
            }
        } else {
            close(pipefd[0]);
            close(pipefd[1]);
            wait(NULL);
            wait(NULL);
        }
    }
}


int process_command(char **user_argv, char *lineptr, char **env_p)
{
	char *pipe_sign, *command_1, *command_2, *redir_sign, *command, *file;
	char **argv_1, **argv_2, **argv;
	char *env_output;
	
	if (strcmp(user_argv[0], "exit") == 0)
	{
		free(lineptr);
		free(user_argv);
		exit(EXIT_SUCCESS);
	}
	else if (strcmp(user_argv[0], "env") == 0)
	{
		env_output = allocate_env_output(env_p, lineptr, user_argv);
		_print_shell(env_output);
	}
	else
	{
		pipe_sign = strchr(user_argv[0], '|');
		if (pipe_sign != NULL)
		{
			*pipe_sign = '\0';
			command_1 = user_argv[0];
			command_2 = pipe_sign + 1;

			argv_1 = parse_command(command_1, " ");
			argv_2 = parse_command(command_2, " ");

			execute_pipe(argv_1, argv_2);

			free(argv_1);
			free(argv_2);
		}
		else
        	{
			redir_sign = strchr(user_argv[0], '>');
			if (redir_sign != NULL)
			{
				*redir_sign = '\0';
				command = user_argv[0];
				file = redir_sign + 1;

				argv = parse_command(command, " ");
				execute_redirection(argv, file, 1);
				free(argv);
			}
			else
			{
				if (execmd(user_argv) != 0)
				{
					_print_shell("Command execution failed");
				}
			}
		}
	}
	return 0;
}

void execute_redirection(char **argv, char *file, int direction)
{
    int fd;
    pid_t pid;

    pid = fork();
    if (pid == -1) {
        perror("fork() failed");
        return;
    }

    if (pid == 0) {
        /* Input redirection */
	if (direction == 0)
	{
		fd = open(file, O_RDONLY);
            dup2(fd, STDIN_FILENO);
        /* Output redirection */
	} else {  
            fd = open(file, O_WRONLY | O_CREAT, 0644);
            dup2(fd, STDOUT_FILENO);
        }

        close(fd);

        if (execvp(argv[0], argv) < 0) {
            perror("execvp() failed");
            exit(EXIT_FAILURE);
        }
    } else {
        wait(NULL);
    }
}
/** execmd - execute child processes
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
			/* Parent process */
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
