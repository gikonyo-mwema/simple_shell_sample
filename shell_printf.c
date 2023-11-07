#include "shell.h"
/**
 *_print_shell - custom printf function
 *@output: string to output
 * Return: void
*/
void _print_shell( const char *output)
{
	write(STDOUT_FILENO, output, strlen(output));
}
