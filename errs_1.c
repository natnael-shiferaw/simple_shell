#include "shell.h"

/**
 * _err_vatoi - CHANGES STRING TO INTEGER
 * @S: THE STRING TO BE CONVERTED.
 * Return: THE CONVERTED INTEGER, 0 IF STRING DOESN'T
 * CONTAIN NUMBER AND -1 ON ERROR.
 */
int _err_vatoi(char *S)
{
	int INDEX = 0;
	unsigned long int RESULT = 0;

if (*S == '+')
S++;
	for (INDEX = 0;  S[INDEX] != '\0'; INDEX++)
	{
		if (S[INDEX] >= '0' && S[INDEX] <= '9')
		{
			RESULT *= 10;
			RESULT += (S[INDEX] - '0');
			if (RESULT > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (RESULT);
}

/**
 * error_display - ERROR MESSAGE IS PRINTED.
 * @stu: STRUCT PARAMETER.
 * @STR: A STRING WITH SPECIFIC TYPE OF ERROR.
 * Return: THE CONVERTED INTEGER, 0 IF STRING DOESN'T
 * CONTAIN NUMBER AND -1 ON ERROR.
 */
void error_display(info_t *stu, char *STR)
{
	_vputs(stu->file_name);
	_vputs(": ");
	d_print(stu->error_count, STDERR_FILENO);
	_vputs(": ");
	_vputs(stu->argv[0]);
	_vputs(": ");
	_vputs(STR);
}

/**
 * d_print - PRINT DECIMAL NUMBER.
 * @INPUT: IS THE INPUT.
 * @FD: THE FILE DISCRIPTOR.
 *
 * Return: NUMBER OF CHARACTERS THAT ARE PRINTED.
 */
int d_print(int INPUT, int FD)
{
	int (*__vputchar)(char) = _vputchar;
	int INDEX, COUNT = 0;
	unsigned int abs, CURRENT;

	if (FD == STDERR_FILENO)
		__vputchar = _vputchar;
	if (INPUT < 0)
	{
		abs = -INPUT;
		__vputchar('-');
		COUNT++;
	}
	else
		abs = INPUT;
	CURRENT = abs;
	for (INDEX = 1000000000; INDEX > 1; INDEX /= 10)
	{
		if (abs / INDEX)
		{
			__vputchar('0' + CURRENT / INDEX);
			COUNT++;
		}
		CURRENT %= INDEX;
	}
	__vputchar('0' + CURRENT);
	COUNT++;

	return (COUNT);
}

/**
 * number_conversion - performs NUMBER CONVERSION
 * @n: THE NUMBER
 * @b: THE BASE
 * @flag: FLAGS OF ARGUMENT
 *
 * Return: RETURNS THE STRING.
 */
char *number_conversion(long int n, int b, int flag)
{
	static char *arr;
	static char Buff[50];
	char SIGN = 0;
	char *ptr;

	if (!(flag & 2) && n < 0)
	{
		n = -n;
		SIGN = '-';

	}
	arr = flag & 1 ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &Buff[49];
	*ptr = '\0';

	do	{
		*--ptr = arr[n % b];
		n /= b;
	} while (n != 0);

	if (SIGN)
		*--ptr = SIGN;
	return (ptr);
}

/**
 * comments_removal - IT REPLACES '#' WITH '\0'
 * @buff: ADDRESS OF THE STRING TO BE MODIFIED.
 *
 * Return: 0;
 */
void comments_removal(char *buff)
{
	int INDEX;

	for (INDEX = 0; buff[INDEX] != '\0'; INDEX++)
		if (buff[INDEX] == '#' && (!INDEX || buff[INDEX - 1] == ' '))
		{
			buff[INDEX] = '\0';
			break;
		}
}
