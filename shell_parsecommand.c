#include "shell.h"

char** parse_command(char *lineptr, const char *delim)
{
int token_num = 0;
char **user_argv = NULL;
char *token;

token = strtok(lineptr, delim);
while (token != NULL)
{
user_argv = realloc(user_argv, sizeof(char *) * (token_num + 1));
        user_argv[token_num] = token;
        token_num++;
        token = strtok(NULL, delim);
    }
    user_argv = realloc(user_argv, sizeof(char *) * (token_num + 1));
    user_argv[token_num] = NULL;

    return (user_argv);
}
