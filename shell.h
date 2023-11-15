#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define BUFFER_SIZE 1024

typedef struct
{
	char **argv;
	int status;
	int err_num;
} info_t;

int _erratoi(const char *str);
int _myexit(info_t *info);
int _mycd(info_t *info);
int _myhelp(info_t *info);

void print_prompt(const char *prompt);
void _print_shell( const char *output);
char** parse_command(char *lineptr, const char *delim);
char * get_command();

char* allocate_env_output(char **env_p, char *lineptr, char **user_argv);
int process_command(char **user_argv, char *lineptr, char **env_p);
void execute_redirection(char **argv, char *file, int direction);
void execute_pipe(char **argv_1, char **argv_2);

int execmd(char **argv);
char *get_location(char *command);
int stat(const char *pathname, struct stat *statbuf);
extern char **environ;

/*my_unsetev*/
int my_setenv(const char *name, const char *value, char *overwrite);
int my_unsetenv(const char *name);

#endif
