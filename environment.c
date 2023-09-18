#include "shell.h"

/**
 * _env - PRINTS CURRENT ENVIRONMENT
 * @stu: STRUCT PARAMETER.
 * Return: Always 0
 */
int _env(info_t *stu)
{
	Print_List_Str(stu->env_local);
	return (0);
}

/**
 * _get_env - GETS VARIABLE ENVIRONMENT VALUE.
 * @stu: STRUCT PARAMETER
 * @name: IT'S THE NAME OF ENVIRONMENT VARIABLE.
 *
 * Return: the value
 */
char *_get_env(info_t *stu, const char *name)
{
	list_t *Node = stu->env_local;
	char *P;

	while (Node)
	{
		P = vstarts_with(Node->str, name);
		if (P && *P)
			return (P);
		Node = Node->next;
	}
	return (NULL);
}

/**
 * _setenv - SET NEW environment variable, MODIFY EXISTING ONE
 * @stu: STRUCT PARAMETER.
 * Return: Always 0
 */
int _setenv(info_t *stu)
{
	if (stu->argc != 3)
	{
		_vputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv_(stu, stu->argv[1], stu->argv[2]))
		return (0);
	return (1);
}

/**
 * _unsetenv - UNSETS ENVIRONMENT VARIABLE
 * @stu: STRUCT PARAMETER.
 * Return: Always 0
 */
int _unsetenv(info_t *stu)
{
	int y;

	if (stu->argc == 1)
	{
		_vputs("very few arguements.\n");
		return (1);
	}
	for (y = 1; y <= stu->argc; y++)
		_unsetenv_(stu, stu->argv[y]);

	return (0);
}

/**
 * env_population - USED FOR POPULATION OF LINKED LIST.
 * @stu: STRUCT PARAMETER.
 * Return: Always 0
 */
int env_population(info_t *stu)
{
	list_t *Node = NULL;
	size_t y;

	for (y = 0; environ[y]; y++)
		node_add_at_end(&Node, environ[y], 0);
	stu->env_local = Node;
	return (0);
}
