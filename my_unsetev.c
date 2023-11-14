#include "shell.h"

int my_setenv(const char *name, const char *value, int overwrite)
{
	char *env_var;

	if (name == NULL || strchr(name, '=') != NULL)
	{
		_print_shell("Invalid variable name\n");
		return (-1);
	}

	/*Check if the variable already exists*/
	env_var = getenv(name);

	if (env_var != NULL && !overwrite)
	{
		_print_shell("Variable already exists. Use setenv with overwrite flag to modify.\n");
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
char *env_var;

 if (name == NULL || strchr(name, '=') != NULL)
 {
 _print_shell("Invalid variable name\n");
 return (-1);
 }

/*Check if the variable exists*/
env_var = getenv(name);

if (env_var == NULL)
{
	_print_shell("Variable does not exist\n");
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
