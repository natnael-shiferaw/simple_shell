#include "shell.h"

/**
* buff_input - IS CHAINED COMMANDS OF BUFFERS
* @stu: STRUCT PARAMETER
* @buff: ADDRESS FOR BUFFER
* @len: LENGTH
*
* Return: RETURNS THE BYTES READ.
*/
ssize_t buff_input(info_t *stu, char **buff, size_t *len)
{
	ssize_t k = 0;
	size_t LEN = 0;

	if (!*len)
	{
		free(*buff);
		*buff = NULL;
		signal(SIGINT, sign_handler);
#if (0)
k = getline(buff, &LEN, stdin);
#else
k = _getline(stu, buff, &LEN);
#endif
if (k > 0)
{
	if ((*buff)[k - 1] == '\n')
	{
		(*buff)[k - 1] = '\0';
		k--;
	}
	stu->line_count_flag = 1;
	comments_removal(*buff);
	hist_list_build(stu, *buff, stu->hist_num_count++);

	{
		*len = k;
		stu->cmd_buffer = buff;
	}
}
}
return (k);
}

/**
* retrieve_input - It GETS INPUT
* @stu: STRUCT PARAMETER
*
* Return: IT RETURNS BYTES READ
*/

ssize_t retrieve_input(info_t *stu)
{
	ssize_t k = 0;
	static char *buff;
	char **BUFF = &(stu->arg), *P;
	static size_t x, y, len;

	_vputchar(-1);
	k = buff_input(stu, &buff, &len);
	if (k == -1)
		return (-1);
	if (len)
	{
		y = x; /* init new iterator to current buff position */
		P = buff + x; /* It gets a pointer for return */

		chain_check(stu, buff, &y, x, len);
		while (y < len)
		{
			if (isChain(stu, buff, &y))
				break;
			y++;
		}

		x = y + 1;
		if (x >= len)
		{
			x = len = 0;
			stu->cmd_buffer_type = 0;
		}

		*BUFF = P;
		return (_vstrlen(P));/* return LENGTH of current command */
	}

	*BUFF = buff;
	return (k); /* It returns LENGTH of buffer from _getline() */
}

/**
* read_buf - IT READS A BUFFER
* @stu: STRUCT PARAMETER
* @buff: REPRESENTS A BUFFER
* @x: SIZE
*
* Return: k
*/

ssize_t read_buf(info_t *stu, char *buff, size_t *x)
{
	ssize_t k = 0;

	if (*x)
		return (0);
	k = read(stu->read_nm, buff, 1024);
	if (k >= 0)
		*x = k;
	return (k);
}

/**
* _getline - GETS INPUT FROM STDIN.
* @stu: STRUCT PARAMETER
* @ptr: POINTER
* @LENGTH: SIZE OF POINTER
*
* Return: s
*/

int _getline(info_t *stu, char **ptr, size_t *LENGTH)
{
	size_t k;
	static char buff[1024];
	char *P = NULL, *Pnew = NULL, *c;
	static size_t x, len;
	ssize_t r = 0, s = 0;

	P = *ptr;
	if (P && LENGTH)
		s = *LENGTH;
	if (x == len)
		x = len = 0;

	r = read_buf(stu, buff, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _vstrchr(buff + x, '\n');
	k = c ? 1 + (unsigned int)(c - buff) : len;
	Pnew = _vrealloc(P, s, s ? s + k : k + 1);
	if (!Pnew)
		return (P ? free(P), -1 : -1);

	if (s)
		_vstrncat(Pnew, buff + x, k - x);
	else
		_vstrncpy(Pnew, buff + x, k - x + 1);

	s += k - x;
	x = k;
	P = Pnew;

	if (LENGTH)
		*LENGTH = s;
	*ptr = P;
	return (s);
}

/**
* sign_handler - a function that handles sign.
* @num_signal: NUMBER USED FOR SIGNAL
*
* Return: void
*/
void sign_handler(__attribute__((unused))int num_signal)
{
	_vputs("\n");
	_vputs("$ ");
	_vputchar(-1);
}
