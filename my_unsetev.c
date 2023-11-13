#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern char **environ;

/*Function to set environment variable*/
int my_setenv(const char *name, const char *value, int overwrite)
{
	if (name == NULL || strchr(name, '=') != NULL)
	{
		fprintf(stderr, "Invalid variable name\n");
		return (-1);
	}

	/*Check if the variable already exists*/
	char *env_var = getenv(name);

	if (env_var != NULL && !overwrite)
	{
		fprintf(stderr, "Variable already exists. Use setenv with overwrite flag to modify.\n");
		return (0);
	}

	/*Create or modify the environment variable*/
	if (setenv(name, value, 1) != 0)
	{
		perror("setenv");
		return (-1);
	}

	return (0);
}

 int my_unsetenv(const char *name)
 {
 if (name == NULL || strchr(name, '=') != NULL)
 {
 fprintf(stderr, "Invalid variable name\n");
 return (-1);
 }

/*Check if the variable exists*/
char *env_var = getenv(name);

if (env_var == NULL)
{
	fprintf(stderr, "Variable does not exist\n");
	return (0);
}

/*Remove the environment variable*/
if (unsetenv(name) != 0)
{
	perror("unsetenv");
	return (-1);
}

return (0);
}

 int main(void)
 {
/*Example usage of setenv and unsetenv*/
my_setenv("MY_VARIABLE", "my_value", 1);
my_setenv("ANOTHER_VARIABLE", "another_value", 1);

/*Print environment variables*/
char **env = environ;
while (*env != NULL)
{
	printf("%s\n", *env);
	env++;
}

/*nset an environment variable*/
my_unsetenv("MY_VARIABLE");

/*Print environment variables after unset*/
env = environ;
while (*env != NULL)
{
	printf("%s\n", *env);
	env++;
}

return (0);
}

