#include "shell.h"

/**
 * _vputs - PRINTS THE STRING.
 * @str: IS THE STRING THAT MUST BE PRINTED
 *
 * Return: IT'S VOID
 */
void _vputs(char *str)
{
	int z = 0;

	if (!str)
		return;
	while (str[z] != '\0')
	{
		_vputchar(str[z]);
		z++;
	}
}

/**
 * _vputchar - IT WRITES c to stderr.
 * @c: THE CHARACTER TO BE PRINTED
 *
 * Return: On success 1.
 * On FAILURE, -1 is returned
 */
int _vputchar(char c)
{
	static int z;
	static char buf[1024];

	if (c == '-1' || z >= 1024)
	{
		write(2, buf, z);
		z = 0;
	}
	if (c != '-1')
		buf[z++] = c;
	return (1);
}

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

	if (c == '-1' || z >= 1024)
	{
		write(nm, buf, z);
		z = 0;
	}
	if (c != '-1')
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
