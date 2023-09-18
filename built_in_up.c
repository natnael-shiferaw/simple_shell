#include "shell.h"

int alias_unset(info_t *stu, char *str);
int alias_set(info_t *stu, char *str);
int alias_print(list_t *nodeali);

/**
 * _hist - DISPLAY HISTORY LIST.
 * @stu: A STURCT THAT CONTAINS ARGUMENTS.
 *
 * Return: Always 0
 */
int _hist(info_t *stu)
{
	list_print(stu->hist);
	return (0);
}

/**
 * alias_unset - It UNSETS alias to string
 * @stu: STRUCT PARAMETER
 * @str: IS THE STRING ALIAS.
 *
 * Return: Always 0 on success, 1 on error
 */
int alias_unset(info_t *stu, char *str)
{
	char *P, C;
	int RETURN;

	P = _vstrchr(str, '=');
	if (!P)
		return (1);
	C = *P;
	*P = 0;
	RETURN = remove_node_at_index(&(stu->alias),
			retrieve_node_at_index(stu->alias, node_begins_with(stu->alias, str, -1)));
	*P = C;
	return (RETURN);
}

/**
 * alias_set - IT SETS alias to string.
 * @stu: IT'S A STRUCT PARAMETER
 * @str: IT'S A STRING ALIAS.
 *
 * Return: Always 0 on success, 1 on error
 */
int alias_set(info_t *stu, char *str)
{
	char *P;

	P = _vstrchr(str, '=');
	if (!P)
		return (1);
	if (!*++P)
		return (alias_unset(stu, str));

	alias_unset(stu, str);
	return (node_add_at_end(&(stu->alias), str, 0) == NULL);
}

/**
 * alias_print - PRINTS AN ALIAS STRING.
 * @nodeali: IT'S AN ALIAS NODE.
 *
 * Return: Always 0 on success, 1 on error
 */
int alias_print(list_t *nodeali)
{
	char *P = NULL, *b = NULL;

	if (nodeali)
	{
		P = _vstrchr(nodeali->str, '=');
		for (b = nodeali->str; b <= P; b++)
			_vputchar(*b);
		_vputchar('\'');
		_vputs(P + 1);
		_vputs("'\n");
		return (0);
	}
	return (1);
}

/**
 * _alias - OPERATES AS the alias built_in
 * @stu: STRUCT PARAMETER
 * Return: Always 0
 */
int _alias(info_t *stu)
{
	int index = 0;
	char *P = NULL;
	list_t *nodeali = NULL;

	if (stu->argc == 1)
	{
		nodeali = stu->alias;
		while (nodeali)
		{
			alias_print(nodeali);
			nodeali = nodeali->next;
		}
		return (0);
	}
	for (index = 1; stu->argv[index]; index++)
	{
		P = _vstrchr(stu->argv[index], '=');
		if (P)
			alias_set(stu, stu->argv[index]);
		else
			alias_print(node_begins_with(stu->alias, stu->argv[index], '='));
	}

	return (0);
}
