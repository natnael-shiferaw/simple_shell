#include "shell.h"

/**
* **vstrtow - USED TO SPLIT STRINGS TO WORDS
* @STR: STRING
* @DELIM: DELIMETER
* Return: POINTER TO ARRAY OF STRINGS, NULL OTHERWISE
*/

char **vstrtow(char *STR, char *DELIM)
{
	char **S;
	int i, j, X, Y, NUMwords = 0;

	if (NULL == STR || 0 == STR[0])
		return (NULL);

	if (!DELIM)
		DELIM = " ";
	for (i = 0; STR[i] != '\0'; i++)
		if (!isDelim(STR[i], DELIM) && (isDelim(STR[i + 1], DELIM) || !STR[i + 1]))
			NUMwords++;

	if (NUMwords == 0)
		return (NULL);
	S = malloc((1 + NUMwords) * sizeof(char *));
	if (!S)
		return (NULL);
	for (i = 0, j = 0; j < NUMwords; j++)
	{
		while (isDelim(STR[i], DELIM))
			i++;
		X = 0;
		while (!isDelim(STR[i + X], DELIM) && STR[i + X])
			X++;
		S[j] = malloc((X + 1) * sizeof(char));
		if (!S[j])
		{
			for (X = 0; X < j; X++)
				free(S[X]);
			free(S);
			return (NULL);
		}

		for (Y = 0; Y < X; Y++)
			S[j][Y] = STR[i++];
		S[j][Y] = 0;
	}
	S[j] = NULL;
	return (S);
}

/**
* **vstrtow1 - USED TO SPLIT INTO WORDS
* @STR: STRING
* @DELIM: DELIMETER
* Return: POINTER TO ARRAY OF STRINGS, NULL OTHERWISE
*/

char **vstrtow1(char *STR, char DELIM)
{
	char **S;
	int i, j, X, Y, NUMwords = 0;

	if (STR == NULL || STR[0] == 0)
		return (NULL);

	for (i = 0; STR[i] != '\0'; i++)
		if ((STR[i] != DELIM && STR[i + 1] == DELIM) ||
				    (STR[i] != DELIM && !STR[i + 1]) || STR[i + 1] == DELIM)
			NUMwords++;
	if (NUMwords == 0)
		return (NULL);
	S = malloc((1 + NUMwords) * sizeof(char *));
	if (!S)
		return (NULL);
	for (i = 0, j = 0; j < NUMwords; j++)
	{
		while (STR[i] == DELIM && STR[i] != DELIM)
			i++;
		X = 0;
		while (STR[i + X] != DELIM && STR[i + X] && STR[i + X] != DELIM)
			X++;
		S[j] = malloc((X + 1) * sizeof(char));
		if (!S[j])
		{
			for (X = 0; X < j; X++)
				free(S[X]);
			free(S);
			return (NULL);
		}

		for (Y = 0; Y < X; Y++)
			S[j][Y] = STR[i++];
		S[j][Y] = 0;
	}
	S[j] = NULL;
	return (S);
}
