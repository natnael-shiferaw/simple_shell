#include "shell.h"

/**
* list_length - USED TO FIND LENGTH OF THE LIST
* @First: POINTER TO THE FIRST NODE
*
* Return: LIST SIZE
*/

size_t list_length(const list_t *First)
{
	size_t i = 0;

	while (First)
	{
		First = First->next;
		i++;
	}
	return (i);
}

/**
* List_to_Strings - CHANGES THE LIST TO STRINGS
* @First: POINTER TO FIRST NODE
*
* Return: STRINGS WHICH TYPE IS ARRAY
*/

char **List_to_Strings(list_t *First)
{
	char *str;
	list_t *NODE = First;
	size_t i = list_length(First), j;
	char **STR;

	if (!First || !i)
		return (NULL);
	STR = malloc(sizeof(char *) * (i + 1));
	if (!STR)
		return (NULL);
	for (i = 0; NODE; NODE = NODE->next, i++)
	{
		str = malloc(_vstrlen(NODE->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(STR[j]);
			free(STR);
			return (NULL);
		}

		str = _vstrcpy(str, NODE->str);
		STR[i] = str;
	}
	STR[i] = NULL;
	return (STR);
}


/**
* list_print - A FUCNTION THAT PRINTS ELEMENTS OF LIST
* @First: IS A POINTER TO FIRST NODE
*
* Return: LIST SIZE
*/
size_t list_print(const list_t *First)
{
	size_t i = 0;

	while (First)
	{
		_vputs(number_conversion(First->Number, 10, 0));
		_vputchar(':');
		_vputchar(' ');
		_vputs(First->str ? First->str : "(nil)");
		_vputs("\n");
		First = First->next;
		i++;
	}
	return (i);
}

/**
* node_begins_with - USED TO RETURN STRING WHICH BEGIN WITH PREFIX
* @NODE: POINTER TO THE NODE LIST
* @PREFIX: THE STRING TO BE MATCHED
* @C: NEXT CHARACTER AFTER THE PREFIX
*
* Return: THE MATCHED NODE, null ON FAILURE
*/

list_t *node_begins_with(list_t *NODE, char *PREFIX, char C)
{
	char *Z = NULL;

	while (NODE)
	{
		Z = vstarts_with(NODE->str, PREFIX);
		if (Z && ((C == -1) || (*Z == C)))
			return (NODE);
		NODE = NODE->next;
	}
	return (NULL);
}

/**
* retrieve_node_at_index - RETRIEVE INDEX OF NODE
* @First: POINTER TO FIRST
* @NODE: NODE POINTER
*
* Return: INDEX of NODE, -1 ON FAILURE
*/

ssize_t retrieve_node_at_index(list_t *First, list_t *NODE)
{
	size_t i = 0;

	while (First)
	{
		if (First == NODE)
			return (i);
		First = First->next;
		i++;
	}
	return (-1);
}
