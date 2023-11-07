#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

void print_prompt(const char *prompt);
void _print_shell( const char *output);
char** parse_command(char *lineptr, const char *delim);
char * get_command();

int execmd(char **argv);
char *get_location(char *command);
int stat(const char *pathname, struct stat *statbuf);
extern char **environ;
#endif
