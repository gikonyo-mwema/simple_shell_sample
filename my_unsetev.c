#include "shell.h"

int my_setenv(const char *name, const char *value, char *overwrite)
{
	char *env_var;

	if (name == NULL || strchr(name, '=') != NULL)
	{
		return (-1);
	}

	/*Check if the variable already exists*/
	env_var = getenv(name);

	/*Variable already exists, overwrite flag not set */
	if (env_var != NULL && !atoi(overwrite))
	{
		return (0);
	}

	/*Create or modify the environment variable*/
	if (setenv(name, value, atoi(overwrite)) != 0)
	{
		return (-1);
	}

	return (0);
}

int my_unsetenv(const char *name)
{
char *env_var;

 if (name == NULL || strchr(name, '=') != NULL)
 {
 return (-1);
 }

/*Check if the variable exists*/
env_var = getenv(name);

if (env_var == NULL)
{
	return (0);
}

/*Remove the environment variable*/
if (unsetenv(name) != 0)
{
	return (-1);
}

return (0);
}
