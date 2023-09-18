#include "shell.h"

/**
* hsh - A FUCNTION THAT IS THE MAIN SHELL LOOP
* @stu: STRUCT PARAMETER
* @AV: ARGUMENT VECTOR
*
* Return: 0 on SUCCESS, 1 on ERROR
*/

int hsh(info_t *stu, char **AV)
{
	ssize_t v = 0;
	int br = 0;

	while (v != -1 && br != -2)
	{
		info_remove(stu);
		if (inter_active(stu))
			_vputs("$ ");
		_vputchar(-1);
		v = retrieve_input(stu);

		if (v != -1)
		{
			info_set(stu, AV);
			br = capture_builtin(stu);
			if (br == -1)
				capture_cmd(stu);
		}
		else if (inter_active(stu))
			_vputchar('\n');
		info_free(stu, 0);
	}
	hist_write(stu);
	info_free(stu, 1);
	if (!inter_active(stu) && stu->stat)
		exit(stu->stat);
	if (br == -2)
	{
		if (stu->exit_err_num == -1)
			exit(stu->stat);
		exit(stu->exit_err_num);
	}
	return (br);
}

/**
* capture_builtin - A FUCNTION THAT FINDS BUILTIN CMD
* @stu: STRUCT PARAMETER
*
* Return: RETUNRS -1 IF BUILTIN NOT FOUND,
*1 IF FOUND(BUT NOT SUCCESSFUL),
*-2 IF BUILTIN SIGNAL exit(),
*0 IF BUILTIN EXECUTED(SUCCESSFULY).
*/
int capture_builtin(info_t *stu)
{
	int j, bir = -1;
	builtin_t built_intb[] = {
		{"exit",_vexit},
		{"env", _env},
		{"help", _help},
		{"history", _hist},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		{"cd", _cd},
		{"alias", _alias},
		{NULL, NULL}
	};

	for (j = 0; built_intb[j].flag; j++)
		if (_vstrcmp(stu->argv[0], built_intb[j].flag) == 0)
		{
			stu->error_count++;
			bir = built_intb[j].function(stu);
			break;
		}
	return (bir);
}

/**
* capture_cmd - FINDS CMD IN PATH
* @stu: STRUCT PARAMETER
*
* Return: NOTHING
*/

void capture_cmd(info_t *stu)
{
	int j, h;
	char *PATH = NULL;

	stu->path = stu->argv[0];
	if (stu->line_count_flag == 1)
	{
		stu->error_count++;
		stu->line_count_flag = 0;
	}

	for (j = 0, h = 0; stu->arg[j]; j++)
		if (!isDelim(stu->arg[j], " \t\n"))
			h++;
	if (!h)
		return;

	PATH = path_find(stu, _get_env(stu, "PATH="), stu->argv[0]);

	if (PATH)
	{
		stu->path = PATH;
		cmd_fork(stu);
	}
	else
	{
		if ((inter_active(stu) || _get_env(stu, "PATH=")
					|| stu->argv[0][0] == '/') && isCmd(stu, stu->argv[0]))
			cmd_fork(stu);
		else if (*(stu->arg) != '\n')
		{
			stu->stat = 127;
			error_display(stu, "not found\n");
		}
	}
}

/**
* cmd_fork - USED TO FORK A CMD
* @stu: STRUCT PARAMETER
*
* Return: NOTHING
*/

void cmd_fork(info_t *stu)
{
	pid_t CHILD_PID;

	CHILD_PID = fork();
	if (CHILD_PID == -1)
	{
		perror("Error:");
		return;
	}

	if (CHILD_PID == 0)
	{
		if (execve(stu->path, stu->argv, get_env(stu)) == -1)
		{
			info_free(stu, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(stu->stat));
		if (WIFEXITED(stu->stat))
		{
			stu->stat = WEXITSTATUS(stu->stat);
			if (stu->stat == 126)
				error_display(stu, "Permission denied\n");
		}
	}
}
