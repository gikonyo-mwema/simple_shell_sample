#include "shell.h"

char * get_command()
{
char *lineptr = NULL;
size_t n = 0;
if (getline(&lineptr, &n, stdin) == -1)
{
_print_shell("Exiting shell>>>>\n");
free(lineptr);
exit(-1);
}
return (lineptr);
}
