#include "shell.h"

/**
 * inter_active - a FUNCTION FOR inter_active mode
 * @address: IS A STRUCT address
 *
 * Return: 1 if inter_active mode, 0 on failure.
 */
int inter_active(info_t *address)
{
	return (isatty(STDIN_FILENO) && address->read_nm <= 2);
}

/**
 * isDelim - A FUCNTION THAT checks if CHARACTER is a DELIMETER
 * @c: IS THE char TO BE CHECKED
 * @delim: IS THE delimeter STRING.
 * Return: 1 if true, 0 if false
 */
int isDelim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _visalpha - A FUNCTION used for CHECKING alphabetic character.
 * @a: The character to BE CHECKED.
 * Return: 1 on SUCCESS, 0 on FAILURE.
 */

int _visalpha(int a)
{
	if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _vatoi - A FUNCTION TO CONVERT string to integer.
 * @S: REPRESENTS THE string to be converted.
 * Return: converted number, 0 ON FAILURE.
 */

int _vatoi(char *S)
{
	int i, sign = 1, flag = 0, OUTPUT;
	unsigned int RESULT = 0;

for (i = 0;  S[i] != '\0' && flag != 2; i++)
{
if (S[i] == '-')
sign *= -1;

if (S[i] >= '0' && S[i] <= '9')
{
flag = 1;
RESULT *= 10;
RESULT += (S[i] - '0');
}
else if (flag == 1)
flag = 2;
}

if (sign == -1)
OUTPUT = -RESULT;
else
OUTPUT = RESULT;

return (OUTPUT);
}
