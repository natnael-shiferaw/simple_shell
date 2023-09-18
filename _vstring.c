#include "shell.h"

/**
 * _vstrlen - DETERMINES THE LENGTH OF STRING
 * @S: THE STRING
 *
 * Return: LENGTH OF STRING
 */

int _vstrlen(char *S)
{
	int k = 0;

	if (!S)
		return (0);

	while (*S++)
		k++;
	return (k);
}

/**
 * _vstrcmp - COMPARES STRINGS
 * @S_1: FIRST STRING
 * @S_2: SECOND STRING
 *
 * Return: POSITIVE IF FIRST STRING IS GREATER, NEGATIVE
 * IF IT'S LESSTHAN, 0 IF THEY ARE EQUAL
 */

int _vstrcmp(char *S_1, char *S_2)
{
	while (*S_1 && *S_2)
	{
		if (*S_1 != *S_2)
			return (*S_1 - *S_2);
		S_1++;
		S_2++;
	}

	if (*S_1 == *S_2)
		return (0);
	else
		return (*S_1 < *S_2 ? -1 : 1);
}

/**
 * vstarts_with - checks if pin starts with PILE
 * @PILE: THE STRING
 * @pin: SUBSTRING TO FIND
 *
 * Return: ADDRESS OF NEXT CHAR IN PILE, OTHERWISE NULL
 */

char *vstarts_with(const char *PILE, const char *pin)
{
	while (*pin)
		if (*pin++ != *PILE++)
			return (NULL);
	return ((char *)PILE);
}

/**
 * _vstrcat - USED TO CONCATNATE STRINGS
 * @DEST: DESTINATION
 * @SRC: SOURCE
 *
 * Return: POINTER TO DESTINATION
 */

char *_vstrcat(char *DEST, char *SRC)
{
	char *RETURN = DEST;

	while (*DEST)
		DEST++;
	while (*SRC)
		*DEST++ = *SRC++;
	*DEST = *SRC;
	return (RETURN);
}
