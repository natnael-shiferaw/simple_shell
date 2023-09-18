#include "shell.h"

/**
 * get_hist_file - gets the history file
 * @stu: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_hist_file(info_t *stu)
{
	char *buff, *DIR;

	DIR = _get_env(stu, "HOME=");
	if (!DIR)
		return (NULL);
	buff = malloc(sizeof(char) * (_vstrlen(DIR) +
_vstrlen(".simple_shell_history"
) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_vstrcpy(buff, DIR);
	_vstrcat(buff, "/");
	_vstrcat(buff, ".simple_shell_history"
);
	return (buff);
}

/**
 * hist_write - CREATES A FILE OR APPENDS ON IT
 * IF IT EXISTS
 * @stu: STRUCT PARAMETER
 *
 * Return: 1 on success, -1 ON FAILURE
 */

int hist_write(info_t *stu)
{
	ssize_t f;
	char *fname = get_hist_file(stu);
	list_t *NODE = NULL;

	if (!fname)
		return (-1);

	f = open(fname, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fname);
	if (f == -1)
		return (-1);
	for (NODE = stu->hist; NODE; NODE = NODE->next)
	{
		_putsnm(NODE->str, f);
		_putnm('\n', f);
	}
	_putnm(-1, f);
	close(f);
	return (1);
}

/**
 * hist_read - A FUNCTION THAT READS HISTORY
 * @stu: STRUCT PARAMETER
 *
 * Return: THE HISTORY COUNT, 0 otherwise
 */
int hist_read(info_t *stu)
{
	char *buff = NULL, *fname = get_hist_file(stu);
	struct stat ST;
	ssize_t f, _len, f_size = 0;
	int j, last = 0, Line_Count = 0;

	if (!fname)
		return (0);

	f = open(fname, O_RDONLY);
	free(fname);
	if (f == -1)
		return (0);
	if (!fstat(f, &ST))
		f_size = ST.st_size;
	if (f_size < 2)
		return (0);
	buff = malloc(sizeof(char) * (f_size + 1));
	if (!buff)
		return (0);
	_len = read(f, buff, f_size);
	buff[f_size] = 0;
	if (_len <= 0)
		return (free(buff), 0);
	close(f);
	for (j = 0; j < f_size; j++)
		if (buff[j] == '\n')
		{
			buff[j] = 0;
			hist_list_build(stu, buff + last, Line_Count++);
			last = j + 1;
		}
	if (last != j)
		hist_list_build(stu, buff + last, Line_Count++);
	free(buff);
	stu->hist_num_count = Line_Count;
	while (stu->hist_num_count-- >= 4096)
		remove_node_at_index(&(stu->hist), 0);
	hist_re_num(stu);
	return (stu->hist_num_count);
}

/**
 *  * hist_list_build - ADDS AN ENTRY TO HISTORY LINKED LIST
 *  @stu: STRUCT PARAMETER
 *  @buff: BUFFER
 *  @Line_Count: HISTORY LINE COUNT
 *
 * Return: Always 0
 */
int hist_list_build(info_t *stu, char *buff, int Line_Count)
{
	list_t *NODE = NULL;

	if (stu->hist)
		NODE = stu->hist;
	node_add_at_end(&NODE, buff, Line_Count);

	if (!stu->hist)
		stu->hist = NODE;
	return (0);
}

/**
 * hist_re_num - A FUNCTION THAT RENUMBERS A HISTORY LINKED LIST
 * @stu: STRUCT PARAMETER
 *
 * Return: THE NEW HISTORY COUNT
 */
int hist_re_num(info_t *stu)
{
	list_t *NODE = stu->hist;
	int j = 0;

	while (NODE)
	{
		NODE->Number = j++;
		NODE = NODE->next;
	}
	return (stu->hist_num_count = j);
}
