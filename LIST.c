#include "shell.h"

/**
* node_add - NODE IS ADDED AT FIRST
* @HEAD: POINTER ADDRESS FOR HEAD NODE
* @str: STRING
* @NUM: INDEX OF THE NODE
*
* Return: LIST SIZE
*/

list_t *node_add(list_t **HEAD, const char *str, int NUM)
{
	list_t *HEADnew;

	if (!HEAD)
		return (NULL);
	HEADnew = malloc(sizeof(list_t));
	if (!HEADnew)
		return (NULL);
	_vmemset((void *)HEADnew, 0, sizeof(list_t));
	HEADnew->Number = NUM;
	if (str)
	{
		HEADnew->str = _vstrdup(str);
		if (!HEADnew->str)
		{
			free(HEADnew);
			return (NULL);
		}
	}
	HEADnew->next = *HEAD;
	*HEAD = HEADnew;
	return (HEADnew);
}

/**
* node_add_at_end - IT ADDS NODE AT THE END
* @HEAD: POINTER ADDRESS FOR HEAD NODE
* @str: STRING
* @NUM: NODE INDEX used by history
*
* Return: size of list
*/
list_t *node_add_at_end(list_t **HEAD, const char *str, int NUM)
{
	list_t *NODEnew, *NODE;

	if (!HEAD)
		return (NULL);

	NODE = *HEAD;
	NODEnew = malloc(sizeof(list_t));
	if (!NODEnew)
		return (NULL);
	_vmemset((void *)NODEnew, 0, sizeof(list_t));
	NODEnew->Number = NUM;
	if (str)
	{
		NODEnew->str = _vstrdup(str);
		if (!NODEnew->str)
		{
			free(NODEnew);
			return (NULL);
		}
	}
	if (NODE)
	{
		while (NODE->next)
			NODE = NODE->next;
		NODE->next = NODEnew;
	}
	else
		*HEAD = NODEnew;
	return (NODEnew);
}

/**
* Print_List_Str - IT PRINTS ONLY STRINGS
* @First: IS A POINTER FOR THE FIRST NODE
*
* Return: LIST SIZE
*/

size_t Print_List_Str(const list_t *First)
{
	size_t i = 0;

	while (First)
	{
		_vputs(First->str ? First->str : "(nil)");
		_vputs("\n");
		First = First->next;
		i++;
	}
	return (i);
}

/**
* remove_node_at_index - REMOVES NODE AT INDEX
* @HEAD: POINTER ADDRESS FOR FIST NODE
* @INDEX: INDEX TO BE DELETED
*
* Return: 1 on SUCCESSS, 0 on FAILURE
*/

int remove_node_at_index(list_t **HEAD, unsigned int INDEX)
{
	unsigned int i = 0;
	list_t *NODE, *LASTnode;

	if (!HEAD || !*HEAD)
		return (0);

	if (!INDEX)
	{
		NODE = *HEAD;
		*HEAD = (*HEAD)->next;
		free(NODE->str);
		free(NODE);
		return (1);
	}
	NODE = *HEAD;
	while (NODE)
	{
		if (i == INDEX)
		{
			LASTnode->next = NODE->next;
			free(NODE->str);
			free(NODE);
			return (1);
		}
		i++;
		LASTnode = NODE;
		NODE = NODE->next;
	}
	return (0);
}

/**
* list_free - NODES ARE FREED IN THE LIST.
* @HEADptr: POINTER ADDRESS TO THE HEAD NODE
*
* Return: NOTHING
*/

void list_free(list_t **HEADptr)
{
	list_t *NODE, *NEXTnode, *HEAD;

	if (!HEADptr || !*HEADptr)
		return;
	HEAD = *HEADptr;
	NODE = HEAD;
	while (NODE)
	{
		NEXTnode = NODE->next;
		free(NODE->str);
		free(NODE);
		NODE = NEXTnode;
	}
	*HEADptr = NULL;
}
