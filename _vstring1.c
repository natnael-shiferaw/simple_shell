#include "shell.h"

/**
 * _vstrcpy - A FUNCTION THAT COPIES A STRING
 * @DEST: DESTINATION
 * @SRC: SOURCE
 *
 * Return: POINTER TO DESTINATION
 */
char *_vstrcpy(char *DEST, char *SRC)
{
	int j = 0;

	if (DEST == SRC || SRC == 0)
		return (DEST);
	while (SRC[j])
	{
		DEST[j] = SRC[j];
		j++;
	}
	DEST[j] = 0;
	return (DEST);
}

/**
 * _vstrdup - DUPLICATES STRING
 * @STR: THE STRING
 *
 * Return: POINTER TO DUPLICATED STRING
 */

char *_vstrdup(const char *STR)
{
	char *RETURN;
	int LEN = 0;

	if (STR == NULL)
		return (NULL);
	while (*STR++)
		LEN++;
	RETURN = malloc(sizeof(char) * (LEN + 1));
	if (!RETURN)
		return (NULL);
	for (LEN++; LEN--;)
		RETURN[LEN] = *--STR;
	return (RETURN);
}

/**
 * _vputs - PRINTS STRING
 * @STR: THE STRING
 *
 * Return: VOID
 */

void _vputs(char *STR)
{
	int j = 0;

	if (!STR)
		return;

	while (STR[j] != '\0')
	{
		_vputchar(STR[j]);
		j++;
	}
}

/**
 * _vputchar - PRINTS THE CHARACTER TO stdout
 * @C: THE CHARACTER
 *
 * Return: ON SUCCESS 1, -1 ON FAILURE
 */

int _vputchar(char C)
{
	static char buf[1024];
	static int j;

	if (C == -1 || j >= 1024)
	{
		write(1, buf, j);
		j = 0;
	}

	if (C != -1)
		buf[j++] = C;
	return (1);
}
