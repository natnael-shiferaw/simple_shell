#include "shell.h"

/**
 * _putnm - WRITES c TO GIVEN nm
 * @c: THE CHARACTER TO BE PRINTED
 * @nm: FILE DISCRIPTOR TO WRITE TO.
 *
 * Return: On success 1. -1 ON FAILURE.
 */
int _putnm(char c, int nm)
{
	static int z;
	static char buf[1024];

	if (c == -1 || z >= 1024)
	{
		write(nm, buf, z);
		z = 0;
	}
	if (c != -1)
		buf[z++] = c;
	return (1);
}

/**
 * _putsnm - PRINTS INPUT STRING.
 * @str: THE STRING THAT MUST BE PRINTED.
 * @nm: IS THE FILE DISCRIPTOR
 *
 * Return: NUMBER OF chars put
 */
int _putsnm(char *str, int nm)
{
	int z = 0;

	if (!str)
		return (0);
	while (*str)
	{
		z += _putnm(*str++, nm);
	}
	return (z);
}
