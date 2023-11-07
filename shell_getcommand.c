#include "shell.h"

char * get_command()
{
char *lineptr = NULL;
size_t = 0;
getline(&lineptr, &n, stdin);
return (lineptr);
}
