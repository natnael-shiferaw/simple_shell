#include "shell.h"

/**
 * get_env - COPY OF STRING ARRAY OF ENVIRONMENT
 * @stu: STRUCT PARAMETER.
 * Return: Always 0
 */
char **get_env(info_t *stu)
{
	if (!stu->environ || stu->env_updated)
	{
		stu->environ = List_to_Strings(stu->env_local);
		stu->env_updated = 0;
	}

	return (stu->environ);
}

/**
 * _unsetenv_ - UNSETS AN ENVIRONMENT VARIABLE
 * @stu: STRUCT PARAMETER
 * @var: ENVIRONMENT VARIABLE
 * Return: 1 on SUCCESS, 0 ON FAILURE.
 */

int _unsetenv_(info_t *stu, char *var)
{
	list_t *NODE = stu->env_local;
	char *P;
	size_t I = 0;

	if (!NODE || !var)
		return (0);

	while (NODE)
	{
		P = vstarts_with(NODE->str, var);
		if (P && *P == '=')
		{
			stu->env_updated = remove_node_at_index(&(stu->env_local), I);
			I = 0;
			NODE = stu->env_local;
			continue;
		}
		NODE = NODE->next;
		I++;
	}
	return (stu->env_updated);
}

/**
 * _setenv_ - SETS A NEW ENVIRONMENT VARIABLE
 * @stu: STRUCT PARAMETER
 * @var: STRING ENVIRONMENT VARIABLE
 * @val: VALUE OF THE ENVIRONMENT VAIRABLE
 * Return: 0
 */
int _setenv_(info_t *stu, char *var, char *val)
{
	char *buff = NULL;
	char *P;
	list_t *NODE;

	if (!var || !val)
		return (0);

	buff = malloc(_vstrlen(var) + _vstrlen(val) + 2);

	if (!buff)
		return (1);
	_vstrcpy(buff, var);
	_vstrcat(buff, "=");
	_vstrcat(buff, val);
	NODE = stu->env_local;
	while (NODE)
	{
		P = vstarts_with(NODE->str, var);
		if (P && *P == '=')
		{
			free(NODE->str);
			NODE->str = buff;
			stu->env_updated = 1;
			return (0);
		}
		NODE = NODE->next;
	}
	node_add_at_end(&(stu->env_local), buff, 0);
	free(buff);
	stu->env_updated = 1;
	return (0);
}
