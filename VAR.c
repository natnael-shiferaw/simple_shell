#include "shell.h"

/**
* isChain - CHECKS FOR CHAIN DELIMETER
* @stu: STRUCT PARAMETER
* @BUFF: THTE CHAR BUFFER
* @poss: ADDRESS OF CURRENT POSITION
*
* Return: 1 ON SUCCESS, 0 OTHERWISE
*/

int isChain(info_t *stu, char *BUFF, size_t *poss)
{
	size_t j = *poss;

	if (BUFF[j] == '|' && BUFF[j + 1] == '|')
	{
		BUFF[j] = 0;
		j++;
		stu->cmd_buffer_type = 1;
	}
	else if (BUFF[j] == '&' && BUFF[j + 1] == '&')
	{
		BUFF[j] = 0;
		j++;
		stu->cmd_buffer_type = 2;
	}
	else if (BUFF[j] == ';')
	{
		BUFF[j] = 0;
		stu->cmd_buffer_type = 3;
	}
	else
		return (0);
	*poss = j;
	return (1);
}

/**
* chain_check - USED FOR CHECKING CHAIN
*@stu: STRUCT PARAMETER
* @BUFF: BUFFER CHAR
* @poss: ADDRESS OF CURRENT POSITION
* @i: INITIAL POSITION
* @LEN: LENGTH OF BUFF
*
* Return: NOTHING
*/

void chain_check(info_t *stu, char *BUFF, size_t *poss, size_t i, size_t LEN)
{
	size_t j = *poss;

	if (stu->cmd_buffer_type == 2)
	{
		if (stu->stat)
		{
			BUFF[i] = 0;
			j = LEN;
		}
	}
	if (stu->cmd_buffer_type == 1)
	{
		if (!stu->stat)
		{
			BUFF[i] = 0;
			j = LEN;
		}
	}

	*poss = j;
}

/**
* alias_replace - USED FOR ALIAS REPLACEMENT
* @stu: STRUCT PARAMETER
*
* Return: 1 ON SUCCESS, 0 OTHERWISE
*/

int alias_replace(info_t *stu)
{
	char *poss;
	list_t *NODE;
	int i;

	for (i = 0; i < 10; i++)
	{
		NODE = node_begins_with(stu->alias, stu->argv[0], '=');
		if (!NODE)
			return (0);
		free(stu->argv[0]);
		poss = _vstrchr(NODE->str, '=');
		if (!poss)
			return (0);
		poss = _vstrdup(poss + 1);
		if (!poss)
			return (0);
		stu->argv[0] = poss;
	}
	return (1);
}

/**
* var_replace - USED FOR VAR REPLACEMENT
* @stu: STRUCT PARAMETER
*
* Return: 1 ON SUCCESS, 0 ON FAILURE
*/

int var_replace(info_t *stu)
{
	list_t *NODE;
	int i = 0;

	for (i = 0; stu->argv[i]; i++)
	{
		if (stu->argv[i][0] != '$' || !stu->argv[i][1])
			continue;

		if (!_vstrcmp(stu->argv[i], "$?"))
		{
			string_replace(&(stu->argv[i]),
					_vstrdup(number_conversion(stu->stat, 10, 0)));
			continue;
		}

		if (!_vstrcmp(stu->argv[i], "$$"))
		{
			string_replace(&(stu->argv[i]),
					_vstrdup(number_conversion(getpid(), 10, 0)));
			continue;
		}
		NODE = node_begins_with(stu->env_local, &stu->argv[i][1], '=');
		if (NODE)
		{
			string_replace(&(stu->argv[i]),
					_vstrdup(_vstrchr(NODE->str, '=') + 1));
			continue;
		}
		string_replace(&stu->argv[i], _vstrdup(""));

	}
	return (0);
}

/**
* string_replace - USED FOR STRING REPLACEMENT
* @OLD: OLD STRING
* @NEW: NEW STRING
*
* Return: 1 ON SUCCESS, 0 ON FAILURE
*/

int string_replace(char **OLD, char *NEW)
{
	free(*OLD);
	*OLD = NEW;
	return (1);
}
