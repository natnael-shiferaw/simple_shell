#include "shell.h"

/**
 * info_remove - CLEARS INFORMATION
 * @stu: ADDRESS STRUCT
 * RETURN: NOTHING
 */
void info_remove(info_t *stu)
{
	stu->arg = NULL;
	stu->argv = NULL;
	stu->path = NULL;
	stu->argc = 0;
}

/**
 * info_set - SETS INFORMATION
 * @stu: ADDRESS STRUCT
 * @av: REPRESENTS AN ARGUMENT VECTOR
 * RETURN: NOTHING
 */

void info_set(info_t *stu, char **av)
{
	int i = 0;

	stu->file_name = av[0];
	if (stu->arg)
	{
		stu->argv = vstrtow(stu->arg, " \t");
		if (!stu->argv)
		{

			stu->argv = malloc(sizeof(char *) * 2);
			if (stu->argv)
			{
				stu->argv[0] = _vstrdup(stu->arg);
				stu->argv[1] = NULL;
			}
		}
		for (i = 0; stu->argv && stu->argv[i]; i++)
			;
		stu->argc = i;

		alias_replace(stu);
		var_replace(stu);
	}
}

/**
 * info_free - IT FREES INFORMATION
 * @stu: ADDRESS OF STRUCT
 * @ALL: REPRESENTS ALL FIELDS
 */
void info_free(info_t *stu, int ALL)
{
	vfree(stu->argv);
	stu->argv = NULL;
	stu->path = NULL;
	if (ALL)
	{
		if (!stu->cmd_buffer)
			free(stu->arg);
		if (stu->env_local)
			list_free(&(stu->env_local));
		if (stu->hist)
			list_free(&(stu->hist));
		if (stu->alias)
			list_free(&(stu->alias));
		vfree(stu->environ);
		stu->environ = NULL;
		z_free((void **)stu->cmd_buffer);
		if (stu->read_nm > 2)
			close(stu->read_nm);
		_vputchar(-1);
	}
}
