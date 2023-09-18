#include "shell.h"

/**
**_vstrncpy - IT COPIES A STRING
*@first: DESTINATION
*@second: SOURCE
*@n: NUMBER OF CHARACTER TO BE COPIED
*Return: THE COPIED STRING.
*/

char *_vstrncpy(char *first, char *second, int n)
{
	int x, y;
	char *c = first;

	x = 0;
	while (second[x] != '\0' && x < n - 1)
	{
		first[x] = second[x];
		x++;
	}
	if (x < n)
	{
		y = x;
		while (y < n)
		{
			first[y] = '\0';
			y++;
		}
	}
	return (c);
}

/**
**_vstrncat - CONCATNATES STRINGS
*@first: FIRST STRING
*@second: SECOND STRING
*@n: NUMBER OF BYTES
*Return: STRING THAT IS CONCATNATED
*/

char *_vstrncat(char *first, char *second, int n)
{
	int x, y;
	char *c = first;

	x = 0;
	y = 0;
	while (first[x] != '\0')
		x++;
	while (second[y] != '\0' && y < n)
	{
		first[x] = second[y];
		x++;
		y++;
	}
	if (y < n)
		first[x] = '\0';
	return (c);
}

/**
**_vstrchr - FINDS A CHARACTER IN STRING
*@s: THE STRING
*@c: CHARACTER TO LOOK FOR
*Return: A POINTER
*/

char *_vstrchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
