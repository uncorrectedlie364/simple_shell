#includei "shell.h"

/**
 * _myexit - Exits the shell or sets an exit status.
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 *
 * Return: Exits with a given exit status (0) if info->argv[0] != "exit".
 */

int _myexit(info_t *info)
{
	if (info->argv[1])
	{
		int exitcheck = _erratoi(info->argv[1]);

		if (exitcheck == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = exitcheck;
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - Changes the current directory of the process.
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 *
 * Return: Always 0.
 */

int _mycd(info_t *info)
{
	char buffer[1024], *dir, *s;

	s = getcwd(buffer, 1024);

	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			dir = _getenv(info, "PWD=");
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		dir = _getenv(info, "OLDPWD=");
		if (!dir)
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
	}
	else
	{
		dir = info->argv[1];
	}
	int chdir_ret = chdir(dir);

	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]);
		_eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - Provides help for the shell or a specific command.
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 *
 * Return: Always 0.
 */

int _myhelp(info_t *info)
{
	_puts("help call works. Function not yet implemented \n");
	return (0);
}
