#include "shell.h"
/**
 * getenv -  retrieve the value of a specified environment variable
 * @info: struct
 * @name: name
 * Return: 0
 */
char *_getenv(info_t *info, const char *name)
{
	int i;
	char *env_var, *delimiter;

    if (info == NULL || info->env == NULL || name == NULL) {
        return (NULL);
    }

    for (i = 0; info->env[i] != NULL; i++) {
        env_var = info->env[i];

        delimiter = strchr(env_var, '=');

        if (delimiter != NULL) {
            *delimiter = '\0';

            if (strcmp(env_var, name) == 0) {
                *delimiter = '=';
                return (delimiter + 1);
            }

            *delimiter = '=';
        }
    }

    return (NULL);
}

int _erratoi(const char *str)
{
	char *endptr;
	long vali;

	if (str == NULL) 
		errno = EINVAL;
		return (0);
	errno = 0;
	val = strtol(str, &endptr, 10);
	if ((errno == ERANGE &&
	(val == LONG_MAX || val == LONG_MIN)) || (errno != 0 && val == 0))
        errno = ERANGE;
        return (0);

	if (endptr == str || *endptr != '\0')
	{
		errno = EINVAL;
		return (0);
	}
	return (val);
}
/**
 * _myexit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: exits with a given exit status
 * (0) if info->argv[0] != "exit"
 */
int _myexit(info_t *info)
{
	int exitcheck;

	if (info->argv[1]) /* If there is an exit argument */
	{
		exitcheck = _erratoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_error("Illegal number: ");
			_print_shell(argv[1]);
			_print_shell("\n");
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _mycd(info_t *info)
{
	char *cwd, *dir, buffer[1024];
	int chdir_ret;

	cwd= getcwd(buffer, sizeof(buffer));
	if (!cwd)
		_print_shell("TODO: >>getcwd failure emsg here<<\n");
		return (1);
	
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_ret = chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_print_shell(cwd);
			_print_shell("\n");
			return (1);
		}
		_print_shell(_getenv(info, "OLDPWD=")), _print_shell("\n");
		chdir_ret = chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		perror(info, "can't cd to ");
		_print_shell(info->argv[1]);
		_print_shell("\n");
	}
	else
	{
		my_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		my_setenv(info, "PWD", cwd);
	}
	return (0);
}

/**
 * _myhelp - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_print_shell("help call works. Function not yet implemented \n");
	if (0)
		_print_shell(*arg_array); /* temp att_unused workaround */
	return (0);
}

