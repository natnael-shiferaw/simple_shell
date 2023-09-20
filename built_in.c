#include "shell.h"

/**
 * _vexit - A FUNCTION USED TO exit shell.
 * @stu: A Struct THAT CONTAINS potential arguments,
 * FOR  MAINTAING constant FUNCTION PROTOTYPE.
 * Return: EXITS with specific exit status
 * (0) if stu.argv[0] != "exit"
 */
int _vexit(info_t *stu)
{
	int check_exit;

	if (stu->argv[1])
	{
		check_exit = _err_vatoi(stu->argv[1]);
		if (check_exit == -1)
		{
			stu->stat = 2;
			error_display(stu, "Illegal number: ");
			_vputs(stu->argv[1]);
			_vputchar('\n');
			return (1);
		}
		stu->exit_err_num = _err_vatoi(stu->argv[1]);
		return (-2);
	}
	stu->exit_err_num = -1;
	return (-2);
}

/**
 * _cd - CHANGES CURRENT DIRECTORY.
 * @stu: A Struct THAT CONTAINS potential arguments,
 * FOR  MAINTAING constant FUNCTION PROTOTYPE.
 * Return: Always 0
 */
int _cd(info_t *stu)
{
	char *S, *Dir, buff[1024];
	int chdir_ret;

	S = getcwd(buff, 1024);
	if (!S)
		_vputs("TODO: >>getcwd failure emsg here<<\n");
	if (!stu->argv[1])
	{
		Dir = _get_env(stu, "HOME=");
		if (!Dir)
			chdir_ret = /* TODO: What Should this be? */
				chdir((Dir = _get_env(stu, "PWD=")) ? Dir : "/");
		else
			chdir_ret = chdir(Dir);
	}
	else if (_vstrcmp(stu->argv[1], "-") == 0)
	{
		if (!_get_env(stu, "OLDPWD="))
		{
			_vputs(S);
			_vputchar('\n');
			return (1);
		}
		_vputs(_get_env(stu, "OLDPWD=")), _vputchar('\n');
		chdir_ret = /* TODO: What Should this be? */
			chdir((Dir = _get_env(stu, "OLDPWD=")) ? Dir : "/");
	}
	else
		chdir_ret = chdir(stu->argv[1]);
	if (chdir_ret == -1)
	{
		error_display(stu, "can't cd to ");
		_vputs(stu->argv[1]), _vputchar('\n');
	}
	else
	{
		_setenv_(stu, "OLDPWD", _get_env(stu, "PWD="));
		_setenv_(stu, "PWD", getcwd(buff, 1024));
	}
	return (0);
}

/**
 * _help - PROVIDES HELP.
 * @stu: A Struct THAT CONTAINS potential arguments,
 * FOR  MAINTAING constant FUNCTION PROTOTYPE.
 * Return: Always 0
 */
int _help(info_t *stu)
{
	char **array_arg;

	array_arg = stu->argv;
	_vputs("help call works. Function not yet implemented \n");
	if (0)
		_vputs(*array_arg);
	return (0);
}
